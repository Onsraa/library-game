#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "../scenarios/scenarios.h"
#define MAX 40 //Nombre max de caractères par saisie.

//Fonction pour initialiser le dictionnaire.
Library * initialisation(){
	
	Library * library = malloc(sizeof(Library));
	
	if(library == NULL){
		exit(EXIT_FAILURE);
	}
	
	library->first_book = NULL;
	library->nb_book = 0;
	
	return library;
}

//Fonction d'ajout de mot au dictionnaire.
void addWord(Book * book, char * word){
	
	if(word[0] != '\0' && book != NULL){
		int start_position = 0;
		int end_position = 0;
		
		while(word[end_position] != '\0'){
			end_position++;

			if(word[end_position] == 32){
				Word * myWord = malloc(sizeof(Word));
				myWord->value = malloc(sizeof(char) * (end_position - start_position));

				if(myWord == NULL || myWord->value == NULL){
					exit(EXIT_FAILURE);
				}

				int scale = 0;
				for(int i = start_position ; i < end_position ; i++){
					myWord->value[scale] = word[i];
					scale++;
				}

				if(book->first_word == NULL){
					book->first_word = myWord;
				}else{
					myWord->next_word = book->first_word;
					book->first_word = myWord;
				}
				book->nb_word += 1;
				start_position = end_position + 1;
			}
		}
		Word * myWord = malloc(sizeof(Word));
		myWord->value = malloc(sizeof(char) * (end_position - start_position));

		if(myWord == NULL || myWord->value == NULL){
			exit(EXIT_FAILURE);
		}

		int scale = 0;
		for(int i = start_position ; i < end_position ; i++){
			myWord->value[scale] = word[i];
			scale++;
		}

		if(book->first_word == NULL){
			book->first_word = myWord;
		}else{
			myWord->next_word = book->first_word;
			book->first_word = myWord;
		}
		book->nb_word += 1;		
	}
}

void addBook(Library * library){

	//Création d'un tout premier livre.
	Book * newBook = malloc(sizeof(Book));
	newBook->first_word = NULL;

	if(newBook == NULL){
		printf("Le livre n'a pas pu être crée.");
		exit(EXIT_FAILURE);
	}

	if(library == NULL){
		library = initialisation();
		library->first_book = newBook;
	}else{
		newBook->next_book = library->first_book;
		library->first_book = newBook;
	}
	
	library->nb_book += 1;

	system("clear");
	printf("Vous venez de créer un livre !");
	puts("\n");
	printf("Entrez-y un petit mot pour commencer : ");
		
	char newWord[MAX];
	fgets(newWord, sizeof(newWord), stdin);
	fgets(newWord, sizeof(newWord), stdin);

	int count = 0;
	
	while(newWord[count] != '\0'){
		if(newWord[count] == '\n'){
			newWord[count] = '\0';
		}
		count++;
	}

	int old_nb_word = newBook->nb_word;
	
	addWord(newBook, newWord);
	
	if(newBook->first_word == NULL){
		printf("Le mot n'a pas pu être ajouté au livre.");
		exit(EXIT_FAILURE);
	}

	system("clear");
	if(newBook->nb_word - old_nb_word > 1){
		printf("Les mots ont été ajoutés au livre !");
	}else{
		printf("Le mot a été ajouté au livre !");
	}
	returnMenu(library);
}

//Fonction qui montre le contenu d'un livre.
void showBook(Book * book){
	
	if(book == NULL){
		printf("Le livre n'existe pas.");
		exit(EXIT_FAILURE);
	}
	printf("[");
	Word * actual = book->first_word;
	if(actual == NULL){
		printf("~empty~");
	}else{
		int counter = book->nb_word;
		while(actual != NULL){
			printf("%s", actual->value);
			actual = actual->next_word;
			if(counter != 1){
				printf(", ");
			}
			counter--;
		}
	}
	printf("]");
	puts("\n");
}

//Fonction qui montre le contenu de la livrairie.
void showLibrary(Library * library){

	if(library == NULL){
		exit(EXIT_FAILURE);
	}

	Library * temp = malloc(sizeof(Library));
	memcpy(temp, library, sizeof(Library));
	
	for(int i = 0 ; i < temp->nb_book ; i++){
		printf("Livre n°%d : ", i);
		showBook(temp->first_book);
		temp->first_book = temp->first_book->next_book;
	}
	free(temp);
	returnMenu(library);
}

void returnMenu(Library * library){
	puts("\n");
	printf("0 - Retourner au menu");
	puts("\n");
	int option;
	do{
		if(scanf("%d", &option) != 1){
			while(fgetc(stdin) != '\n');
		};
	}while(option != 0);

	switch (option){
		case 0:
			menu(library);
			break;
		default:
			break;
	}
}