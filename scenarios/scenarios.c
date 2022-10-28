#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../functions/functions.h"
#include "scenarios.h"

//Lancer le jeu
void startGame(Library * library){
	
	system("clear");
	puts("\n");
	printf("***************************\n");
	printf("* ~~~ ~~    ~~~   ~~ ~~~  *\n");
	printf("*~~   ~ ~Bienvenue~  ~~  ~*\n");
	printf("* ~~~    ~dans la~    ~~  *\n");
	printf("* ~  ~~ ~librairie~~   ~ ~*\n");
	printf("*~~~~   ~~ ~~~   ~~~~    ~*\n");
	printf("***************************\n");
	puts("\n");

	printf("1 - Lancer la partie\n");
	printf("2 - Quitter");
	puts("\n");
	
	int option;
	do{
		if(scanf("%d", &option) != 1){
			while(fgetc(stdin) != '\n');
		};
	}while(option != 1 && option != 2);

	switch (option)
	{
	case 1:
		menu(library);
		break;
	case 2:
		system("clear");
		puts("\n");
		printf("Oh...bye.");
		puts("\n");
		exit(EXIT_SUCCESS);
	default:
		break;
	}
}

void menu(Library * library){

	system("clear");
	puts("\n");
	printf("1 - Rentrer dans la librairie\n\n"); //Montre tous les dictionnaires et les autres options : fusionner les livres entre-eux / les faire combattre
	printf("2 - Ajouter un livre\n\n"); //Initialisation d'un livre
	printf("3 - Examiner un livre\n\n"); //De nouvelles options s'ouvriront après ce choix : ajouter un mot / le supprimer
	printf("4 - Parler à un livre\n\n"); //Lance une session qui censure tous les mots que l'on dit qui sont présents dans le livre.
	printf("5 - Ouvrir un livre interdit\n\n\n"); //A réfléchir pour plus tard.
	printf("6 - Retourner au démarrage");
	puts("\n");	

	int option;
	do{
		if(scanf("%d", &option) != 1){
			while(fgetc(stdin) != '\n');
		};
	}while(option < 1 || option > 6);

	switch (option)
	{
	case 1:
		enterLibrary(library);
		break;
	case 2:
		addBookMenu(library);
		break;
	case 6:
		startGame(library);
		break;
	default:
		break;
	}
}

void enterLibrary(Library * library){
	system("clear");
	puts("\n");
	if(library == NULL || library->nb_book == 0){
		printf("Il n\'y a pas de livre dans la librairie..");
		puts("\n");
		printf("0 - Retourner au menu");
		puts("\n");

		int option;

		do{
			if(scanf("%d", &option) != 1){
				while(fgetc(stdin) != '\n');
			};
		}while(option != 0);

		menu(library);
	}else{
		showLibrary(library);
	}
}

void addBookMenu(Library * library){

	system("clear");
	puts("\n");
	printf("Veux-tu rajouter un livre à la librairie ?");
	puts("\n");
	printf("(o)ui - (n)on");
	puts("\n");

	char option;
	do{
		if(scanf("%c", &option) != 1){
			while(fgetc(stdin) != '\n');
		};
	}while(option != 'o' && option != 'n');

	switch (option)
	{
	case 'o':
		puts("\n");
		addBook(library);
		break;
	case 'n':
		menu(library);
		break;
	default:
		break;
	}
};