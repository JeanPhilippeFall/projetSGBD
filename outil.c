#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include<math.h>
#include<time.h>
#include"svg.h"

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
                char *pol, *dev, *stat, *srcz, *dstz;
                if(strcmp((const char *)cur_node->name,(const char *)"produit") == 0){
                 xmlChar *a = xmlNodeGetContent(cur_node);
                        printf("Nom entite: %s\n", a);
                        }
             else if(strcmp((const char *)cur_node->name,(const char *)"prix") == 0)  {
                    xmlChar *b = xmlNodeGetContent(cur_node);
                        printf("\tPrix : %s\n", b);
                        //dev = strdup(b);
                        }  
        traverse_dom_trees(cur_node->children);
    }
}
void drawrectangles(char *nom)
{
    svg* psvg;
    psvg = svg_create(1024, 1024);

    if(psvg == NULL)
    {
        puts("psvg is NULL");
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
}

int main(int argc, char **argv)
{
    xmlDocPtr doc;
    xmlNode *roo_element = NULL;
//VERIFICATION DU NOMBRE D'ARGUMENT
    if (argc != 7)
    {
        printf("\nInvalid argument\n");
        return(1);
    }

//VERIFICATION DE LA VALIDITE DU DOCUMENT CONTENANT LE CODE XML PASSE EN PARAMETRE
    doc = xmlReadFile(argv[5], NULL, XML_PARSE_NOBLANKS | XML_PARSE_NOERROR | XML_PARSE_NOWARNING | XML_PARSE_NONET);
    if (doc == NULL)
    {
        fprintf(stderr, "Document not parsed successfully.\n");
        return 0;
    }

    roo_element = xmlDocGetRootElement(doc);
//ON VERIFIE SI LE DOCUMENT CONTENANT LE CODE XML PASSE EN PARAMETRE EST VIDE
    if (roo_element == NULL)
 {
        fprintf(stderr, "empty document\n");
        xmlFreeDoc(doc);
        return 0;
    }

    printf("La Racine est %s\n", roo_element->name);
    traverse_dom_trees(roo_element);
	drawrectangles(argv[6]);

    xmlFreeDoc(doc);       // free document
    xmlCleanupParser();    // Free globals
    return 0;
}
