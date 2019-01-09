/*
	Projet SGBD-2019
	Création d'outil de conversion de fichier xml/json en fichier .svg avec tracé des entités,
	des relations et des attributs de entités.
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<libxml/tree.h>
#include<libxml/parser.h>

int verifParam1(char p1[]){
	if (strcmp(p1, "-i") == 0)
		return 1;
	else 
		return 0;
}

int verifParam2(char p2[]) 
{
	if (strcmp(p2, "xml") == 0)
		return 1;
	else return 0;
}

int verifParam3(char p3[]){
	if (strcmp(p3, "-t") == 0) 
		return 1;
	else return 0;
}

int verifParam4(char p4[]){
	if (strcmp(p4, "-f") == 0)
		return 1;
	else return 0;
}

xmlNodePtr creer_produit(const char *reference, const char *intitule, const char *prix) {
    xmlNodePtr noeud_produit;
    xmlNodePtr noeud_intitule;

    // Création du noeud "produit"
    if ((noeud_produit = xmlNewNode(NULL, BAD_CAST "produit")) == NULL) {
        return NULL;
    }
    // Ajout de son attribut "reference"
    if (xmlSetProp(noeud_produit, BAD_CAST "reference", BAD_CAST reference) == NULL) {
        xmlFreeNode(noeud_produit);
        return NULL;
    }
    // Création du noeud intitule
    if ((noeud_intitule = xmlNewNode(NULL, BAD_CAST "intitule")) == NULL) {
        xmlFreeNode(noeud_produit);
        return NULL;
    }
    xmlNodeSetContent(noeud_intitule, BAD_CAST intitule);
    // Ajout du noeud (intitule) à son père (produit)
    if (xmlAddChild(noeud_produit, noeud_intitule) == NULL) {
        xmlFreeNode(noeud_produit);
        xmlFreeNode(noeud_intitule);
        return NULL;
    }
    // Equivalent plus rapide par rapport au noeud intitule
    // Création du noeud "prix" et ajout à son père (produit)
    if (xmlNewTextChild(noeud_produit, NULL, BAD_CAST "prix", BAD_CAST prix) == NULL) {
        xmlFreeNode(noeud_produit);
        return NULL;
    }

    return noeud_produit;
}

/**
 * Retourne le premier produit du catalogue (sinon NULL)
 **/
xmlNodePtr obtenir_premier_produit(xmlDocPtr doc) {
	// pour l'implémentation voir les sources
}


int main(int argc, char *argv[])
{	
  /** ... **/
 	xmlDocPtr doc;
	xmlNodePtr racine, premier_prod, nouv_prod;

	/*
xmlParseFile permet de parser le fichier .xml et stocker le resultat sous forme d'arbre si le document est bien valide, sinon (le document xml est invalide) le résultat sera null
	*/
		
   if (verifParam1(argv[1]) && verifParam2(argv[2]) && verifParam3(argv[3]) && verifParam4(argv[4]))
   {
	doc = xmlParseFile(argv[5]);
	// Ouverture du fichier XML
    	xmlKeepBlanksDefault(0);
    	doc = xmlParseFile(argv[5]);
	    if (doc == NULL) {
		fprintf(stderr, "Document XML invalide\n");
		return EXIT_FAILURE;
	    }
	    // Récupération de la racine
	    racine = xmlDocGetRootElement(doc);
	    if (racine == NULL) {
		fprintf(stderr, "Document XML vierge\n");
		xmlFreeDoc(doc);
		return EXIT_FAILURE;
	    }
	    // Récupération du premier produit
	    premier_prod = obtenir_premier_produit(doc);
	    if (premier_prod == NULL) {
		fprintf(stderr, "Impossible de trouver le premier produit\n");
		xmlFreeDoc(doc);
		return EXIT_FAILURE;
	    }
	    // Ajout d'un nouveau produit avant le premier produit (en tête)
	    nouv_prod = creer_produit("CD0YAH", "Autocollant Developpez.com", "0.80");
	    if (nouv_prod) {
		xmlAddPrevSibling(premier_prod, nouv_prod);
	    }
	    // Ajout d'un nouveau produit après le premier produit
	    nouv_prod = creer_produit("U0TZ6K", "Lot de 10 autocollants Developpez.com", "5.00");
	    if (nouv_prod) {
		xmlAddPrevSibling(premier_prod, nouv_prod);
	    }
	    // Ajout d'un nouveau produit en fin/queue
	    nouv_prod = creer_produit("ZQEYAN", "Mug Developpez.com", "4.00");
	    if (nouv_prod) {
		xmlAddSibling(premier_prod, nouv_prod);
	    }
	    // Affichage de l'arbre DOM tel qu'il est en mémoire
	    xmlDocFormatDump(stdout, doc, 1);
	    // Libération de la mémoire
	    xmlFreeDoc(doc);

    return EXIT_SUCCESS;
	/*}
	else {
		printf("Erreur de parsing : Fichier XML non valide!\n");
		exit(EXIT_FAILURE);
	}
	*/
   }
	else
	{
	printf("Erreur de paramétrage! Paramètres manquants ou non pris en compte!\n"); 
      	exit(EXIT_FAILURE);
	}
 
  /** ... **/
 
  return 0;
}
