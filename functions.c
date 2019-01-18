#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<windows.h>
#include"cJSON.h"
#include"svg.h"

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
           sleep(1000);
            printf(".");
        }

        cJSON* myJson[size];

        for(i=0;i<size;i++){
            myJson[i]=cJSON_GetArrayItem(json,i);
        }

        for(i=0;i<size;i++){
            printf("\n%s:%s",myJson[i]->string,cJSON_GetStringValue(myJson[i]));
            Sleep(1000);
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
            Sleep(2000);
            system(outputName);
        }
    }
}
