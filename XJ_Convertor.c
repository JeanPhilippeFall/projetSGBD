#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include<math.h>
#include<time.h>
//#include"svg.h"
//#include"functions.h"
#include"cJSON.h"
#include"svg2.h"

#define N 500
#define SVG_WIDTH 1024
#define SVG_HEIGHT 1024
#define WINDOW_WIDTH 180
#define WINDOW_HEIGHT 80

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
            //Sleep(1000);
        //    printf("has child: %d",cJSON_IsString(myJson[i]->child));
   /*         if(cJSON_IsString(myJson[i]->child)==1){
                treatChild(myJson[i]->child);
            }
      */  }

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
//declaration de la strcuture node et ses varables
struct node {
        char *nomEntite;
        char *id;
        char *nom;
        char *prenom;
        char *association;
       char  *date;

        struct node *next;
            };
        struct node *head = NULL;
//declaration de la fonction insert et Initialisation des variables a,b,c,d et e
void insert(char *a, char *b, char *c, char *d, char *e, char *f){
        struct node *temp;
        temp = (struct node*)malloc(sizeof(struct node));
        temp->nomEntite = a;
        temp->id = b;
        temp->next = head;
        head= temp;


}
// declaration de la fonction traverse_dom_trees qui permet de parcourir les noeuds et ensuite afficher leur valeur
void traverse_dom_trees(xmlNode * a_node)
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
        traverse_dom_trees(cur_node->children);

    }
}
/*void drawrectangles(char *nom)
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


        //svg_rectangle(psvg, 320, 320, 96, 96, "#FFFF00", "#000000", 2, 8, 8);
        //svg_rectangle(psvg, 256, 256, 128, 128, "#00FFFF", "#000000", 2, 8, 8);
        //svg_rectangle(psvg, 192, 192, 160, 160, "#FF80FF", "#000000", 2, 8, 8);
	//svg_text(psvg, 32, 32, "sans-serif", 16, "#000000", "#000000", entite);
	//vg_text(psvg, 32, 32, "sans-serif", 16, "#000000", "#000000", attribut);
        svg_finalize(psvg);
        svg_save(psvg, nom);
        svg_free(psvg);
    }
}*/

int main(int argc, char **argv)
{
    xmlDocPtr doc;
    xmlNode *roo_element = NULL;
//VERIFICATION DU NOMBRE D'ARGUMENT
    if (argc != 7)
    {
        printf("Nombre d'arguments invalides, veuillez bien spécifier les aruments\n");
        return(1);
    }
	if (strcmp(argv[2], "xml")==0){
//VERIFICATION DE LA VALIDITE DU DOCUMENT CONTENANT LE CODE XML PASSE EN PARAMETRE
    doc = xmlReadFile(argv[5], NULL, XML_PARSE_NOBLANKS | XML_PARSE_NOERROR | XML_PARSE_NOWARNING | XML_PARSE_NONET);
    if (doc == NULL)
    {
        fprintf(stderr, "Votre fichier n'est pas valide car il ne peut être parsé.\n");
        return 0;
    }

    roo_element = xmlDocGetRootElement(doc);
//ON VERIFIE SI LE DOCUMENT CONTENANT LE CODE XML PASSE EN PARAMETRE EST VIDE
    if (roo_element == NULL)
 {
        fprintf(stderr, "Votre Document XML est vide\n");
        xmlFreeDoc(doc);
        return 0;
    }

    //printf("La Racine est %s\n", roo_element->name);
    traverse_dom_trees(roo_element);
	//drawrectangles(argv[6]);

    xmlFreeDoc(doc);       // free document
    xmlCleanupParser();    // Free globals
	}else{
        if(strcmp(argv[2], "json")){
            char* filepath=argv[5];
            treatJson(filepath,"new.svg");
        }
    }
    return 0;
}
