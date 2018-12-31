/*
Author : Jean Philippe FALL
compiler avec gcc validatio.c -o validation -lxml2 -lm
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<libxml/tree.h>
#include<libxml/parser.h>
int verifieExtension(char s[]) // fonction de verification de l'extension .xml
{
	int j;
	j=strlen(s)-1;
	if ((s[j-3] == '.') && (s[j-2] == 'x') && (s[j-1] == 'm') && (s[j] == 'l')){
	 
		return 1; //retourner si l'extension est juste ie .xml
	}
	else return 0;
}

int main(int argc, char *argv[])
{	
  /** ... **/
 	xmlDocPtr doc;
	/*
xmlParseFile permet de parser le fichier .xml et stocker le resultat sous forme d'arbre si le document est bien valide, sinon le résultat sera null
	*/
	doc = xmlParseFile(argv[1]);	
   // Si fichier donne en argument au format .xml
   if (verifieExtension(argv[1]) && !(doc == NULL))
   {
	printf("Fichier parsé: donc valide \n");
	exit(EXIT_SUCCESS);
   }
	else
	{
	printf("fichier non valide\n");
 	printf("format de fichier non correct: .xml accepte seulement\n");
      	exit(EXIT_FAILURE);
	}
 
  /** ... **/
 
  return 0;
}
