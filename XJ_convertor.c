#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include<math.h>
#include<time.h>
#include"cJSON.h"
#include"svg.h"

/**********************************************************************/
#define N 500
#define SVG_WIDTH 1024
#define SVG_HEIGHT 1024
#define WINDOW_WIDTH 180
#define WINDOW_HEIGHT 80
/***************************************************/

void treatChild(cJSON* element){ // pass the main child element (root of the new branch)
    int i;
    while(element!=NULL){
        printf("\n%s",(element->valuestring));
        printf("%s\n",(element->string));
        element=element->child;
    }
}

/***************************************************/

char* readfile(char* filepath){
    char* fileContent=(char*)malloc(N*sizeof(char));
    FILE *f;
    char c;
    int index=0;
    f = fopen(filepath, "r");
    if(f==NULL){
        printf("erreur: impossible d'ouvrir le fichier");
        exit(0);
    }else{
        while((c = fgetc(f)) != EOF){
            fileContent[index] = c;
            index++;
        }
        fileContent[index] = '\0';
    }

    fclose(f);
    return fileContent;
}


/***************************************************/


void treatJson(char* filepath, char* outputName){
    char* fileName=filepath;
    char* fileContent=readfile(fileName);
    cJSON* json=cJSON_Parse(fileContent);

//    printf("formatted: %s",cJSON_Print(json));
    int size=cJSON_GetArraySize(json);

//    printf("number of element:%d\n",size);

    if(size==0){
        printf("veuillez verifier la validite du fichier");
    }else{
        // file had been well read
        int i;
        printf("demarrage de l'extraction");
        for(i=0;i<3;i++){
           //sleep(1000);
            printf(".");
        }

        cJSON* myJson[size];

        for(i=0;i<size;i++){
            myJson[i]=cJSON_GetArrayItem(json,i);
        }

        for(i=0;i<size;i++){
            printf("\n%s:%s",myJson[i]->string,cJSON_GetStringValue(myJson[i]));
       
        }

        svg* mySvg;
        mySvg = svg_create(SVG_WIDTH, SVG_HEIGHT);

        if(mySvg == NULL){
            puts("mySvg is NULL");
        }else{

            int i,x=0,y=20;
            for(i=0;i<size;i++){
                x+=200;
                if(x>=800){
                    x=200;
                    y+=100;
                }
                svg_rectangle(mySvg, WINDOW_WIDTH, WINDOW_HEIGHT, x, y, "#00BFFF", "#000000", 4, 0, 0);
                svg_text(mySvg, x, y+20, "sans-serif", 16, "#000000", "#000000", myJson[i]->string);
                svg_line(mySvg, "#000000", 2, x,y+25, x+WINDOW_WIDTH, y+25);
                svg_text(mySvg, x, y+40, "sans-serif", 16, "#000000", "#000000", cJSON_GetStringValue(myJson[i]));
            }
            svg_finalize(mySvg);
            svg_save(mySvg, outputName);
            svg_free(mySvg);
            printf("\n fin du processus.\n Fichier %s genere avec succes\n",outputName);
            //Sleep(2000);
            system(outputName);
        }
    }
}



/*********************************************************************/
// declaration de la fonction parcourir qui permet de parcourir les noeuds et ensuite afficher leur valeur
void parcourir(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next)
    {
               char *retour;
                if(strcmp((const char *)cur_node->name,(const char *)"produit") == 0){
                 xmlChar *a = xmlNodeGetContent(cur_node);
                        printf("Produit-> %s\n", a);
			retour = a;
                        }
             else if(strcmp((const char *)cur_node->name,(const char *)"prix") == 0)  {
                    xmlChar *b = xmlNodeGetContent(cur_node);
                        printf("\tPrix->%s\n", b);
                        retour = b;
                        }
        parcourir(cur_node->children);
	
    }
}

void drawrectangles(char *nom)
{
    svg* psvg;
    psvg = svg_create(1024, 1024);

    if(psvg == NULL)
    {
        puts("Ereur de création du fichier svg");
    }
    else
    {
	svg_rectangle(psvg, 1024, 1024, 0, 0, "#00FF00", "#000000", 4, 0, 0);
        svg_rectangle(psvg, 100, 100, 24, 10, "#C0C0FF", "black", 1, 0, 0);
        svg_finalize(psvg);
        svg_save(psvg, nom);
	svg_print(psvg);
        svg_free(psvg);
    }
}

int main(int argc, char **argv)
{
    xmlDocPtr doc;
    xmlNode *racine = NULL;
/*
Le nombre d'arguments passés en paramètres ne doit se différencier de 8
nom du fichier
-i 
xml/json
-t
-f
nom de l'executable
-o 
nom du fichier svg

*/
    if (argc != 8)
    {
        printf("Nombre d'arguments invalides, veuillez bien spécifier les aruments\n");
        return(1);
    }
/*
dans cette partie on s'occupe du cas d'un fichier XML

*/
    if(strcmp(argv[2],"xml")==0){
        doc = xmlReadFile(argv[5], NULL, XML_PARSE_NOBLANKS | XML_PARSE_NOERROR | XML_PARSE_NOWARNING | XML_PARSE_NONET);
        if (doc == NULL)
        {
            fprintf(stderr, "Votre fichier n'est pas valide car il ne peut être parsé.\n");
            return 0;
        }

        racine = xmlDocGetRootElement(doc);
  
        if (racine == NULL)
     {
            fprintf(stderr, "Votre Document XML est vide\n");
            xmlFreeDoc(doc);
            return 0;
        }

        parcourir(racine);
        drawrectangles(argv[7]);

        xmlFreeDoc(doc);       
        xmlCleanupParser();   
    }else if (strcmp(argv[2],"json")==0){
        char* filepath=argv[5];
        char* output=argv[7];
        treatJson(filepath,output);
    }
	else printf("Veuillez choisir un fichier XML/JSON PLEASE!\n");


    return 0;
}
