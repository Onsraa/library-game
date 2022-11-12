#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "../scenarios/scenarios.h"

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
void addString(Book * book, char * string){
	
	if(string[0] != '\0' && string[0] != 32 && book != NULL){
		int start_position = 0;
		int end_position = 0;
		
		while(string[end_position] != '\0'){
			end_position++;

			if(string[end_position] == 32){
				addWord(book, string, start_position, end_position);
				start_position = end_position + 1;
			}
		}
		addWord(book, string, start_position, end_position);
	}
}

void addWord(Book * book, char * string, int start_position, int end_position){

	Word * myWord = malloc(sizeof(Word));
	myWord->value = malloc(sizeof(char) * (end_position - start_position + 1));
	myWord->next_word = NULL;

	if(myWord == NULL || myWord->value == NULL){
		exit(EXIT_FAILURE);
	}

	int scale = 0;

	for(int i = start_position ; i < end_position ; i++){
		myWord->value[scale] = string[i];
		scale++;
	}

	myWord->value[scale] = '\0';
	
	int isPresent = 0; //Booléen qui vérifie si le mot est déjà présent.
	
	if(book->nb_word == 0){
		book->first_word = myWord;
	}else{
		Word * temp = book->first_word;

		for(int i = 0 ; i < book->nb_word; i++){
			if(!strcmp(myWord->value, temp->value)){
				isPresent = 1;
			}
			if(i < book->nb_word - 1){
				temp = temp->next_word;
			}
		}
		if(!isPresent){
			temp->next_word = myWord;
		}
	}
	if(!isPresent){
		book->nb_word += 1;
	}
}

void modifyBook(Book * book, Library * library){ 

	puts("\n");
	printf("Entrez-y un ou plusieurs mots pour commencer : ");
		
	char newWord[MAX];
	fgets(newWord, sizeof(newWord), stdin);
	fgets(newWord, sizeof(newWord), stdin);

	int count = 0;
	
	while(newWord[count] != '\n'){
		count++;
	}			
	newWord[count] = '\0';

	int old_nb_word = book->nb_word;
	
	addString(book, newWord);

	system("clear");
	puts("\n");
	if(book->nb_word == old_nb_word){
		printf("Le livre a été ajouté !");
	}
	else if(book->nb_word - old_nb_word > 1){
		printf("Les mots ont été ajoutés au livre !");
	}else if(book->nb_word - old_nb_word == 1){
		printf("Le mot a été ajouté au livre !");
	}
	puts("\n");
	returnLibrary(library);
}

void addBook(Library * library){

	//Création d'un tout premier livre.
	Book * newBook = malloc(sizeof(Book));
	newBook->first_word = NULL;

	if(newBook == NULL){
		printf("Le livre n'a pas pu être crée.");
		exit(EXIT_FAILURE);
	}

	if(library == NULL || library->first_book == NULL){
		library = initialisation();
		library->first_book = newBook;
	}else{
		Book * temp = library->first_book;
		while(temp->next_book != NULL){
			temp = temp->next_book;
		}
		temp->next_book = newBook;
	}
	
	library->nb_book += 1;

	system("clear");
	puts("\n");
	printf("Vous venez de créer un livre !");
	modifyBook(newBook, library);
}

//Fonction qui montre le contenu d'un livre.
void showBook(Book * book, int detail){
	
	if(book == NULL){
		printf("Le livre n'existe pas.");
		exit(EXIT_FAILURE);
	}

	printf("[");
	Word * actual = book->first_word;
	if(actual == NULL){
		printf("~empty~");
	}else{
		int i = 0;
		while(actual != NULL){
			if(detail){
				printf(COLOR_GREEN "%d" COLOR_RESET " : ", i);
				i++;
			}
			printf("%s", actual->value);
			if(actual->next_word != NULL){
				printf(", ");
			}
			actual = actual->next_word;
		}
	}
	printf("]");
	puts("\n");
}

//Fonction qui montre le contenu de la livrairie.
void showLibrary(Library * library, int detail){

	if(library == NULL){
		exit(EXIT_FAILURE);
	}

	Book * temp = library->first_book;
	
	for(int i = 0 ; i < library->nb_book ; i++){
		printf("Livre n°" COLOR_GREEN "%d" COLOR_RESET " : ", i);
		showBook(temp, detail);
		temp = temp->next_book;
	}
}

void returnLibrary(Library * library){

	puts("0 - Retourner dans la librairie");
	puts(" ");
	int option;
	do{
		if(scanf("%d", &option) != 1){
			while(fgetc(stdin) != '\n');
		};
	}while(option != 0);

	switch (option){
		case 0:
			enterLibrary(library);
			break;
		default:
			break;
	}
}

void deleteBook(int bookNumber, Library * library){

	Book * actual = library->first_book;

	while(bookNumber > 1){
		actual = actual->next_book;
		bookNumber--;
	}

	Book * deleteBook = malloc(sizeof(Book));

	if(bookNumber == 0){
		deleteBook = actual; 
	}else{
		deleteBook = actual->next_book;
	}

	clearBook(deleteBook);

	if(bookNumber == 0){
		free(deleteBook);
		library->first_book = library->first_book->next_book;
	}else{
		actual->next_book = deleteBook->next_book;
		free(deleteBook);
	}
	library->nb_book -= 1;
}

void clearBook(Book * book){//Libère tous les mots d'un livre

	if(book == NULL){
		exit(EXIT_FAILURE);
	}

	if(book->first_word != NULL && book->nb_word > 0){
		Word * temp = book->first_word;
		while(temp != NULL){
			book->first_word = book->first_word->next_word;
			free(temp);
			temp = book->first_word;
		}
	}
}

void deleteString(Book * book, char * string){
	if(string[0] != '\0' && string[0] != 32 && book != NULL){
		int start_position = 0;
		int end_position = 0;
		
		while(string[end_position] != '\0'){
			end_position++;

			if(string[end_position] == 32){
				deleteWord(book, string, start_position, end_position);
				start_position = end_position + 1;
			}
		}
		deleteWord(book, string, start_position, end_position);
	}
}

void deleteWord(Book * book, char * string, int start_position, int end_position){
	
	Word * myWord = malloc(sizeof(Word));
	myWord->value = malloc(sizeof(char) * (end_position - start_position + 1));
	myWord->next_word = NULL;

	if(myWord == NULL || myWord->value == NULL){
		exit(EXIT_FAILURE);
	}

	int scale = 0;

	for(int i = start_position ; i < end_position ; i++){
		myWord->value[scale] = string[i];
		scale++;
	}

	myWord->value[scale] = '\0';
	
	int isPresent = 0; //Booléen qui vérifie si le mot est présent.
	
	Word * actual = book->first_word;
	Word * deleteWord  = malloc(sizeof(Word));

	if(!strcmp(myWord->value, actual->value)){
		book->first_word = book->first_word->next_word;
		free(actual);
		book->nb_word -= 1;
	}else{
		while(actual != NULL){
			if(!strcmp(myWord->value, actual->next_word->value)){
				deleteWord = actual->next_word;
				actual->next_word = actual->next_word->next_word;
				free(deleteWord);
				book->nb_word -= 1;
			}
			actual = actual->next_word;
		}
	}
}
