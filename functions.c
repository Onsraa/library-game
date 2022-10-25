#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

//Fonction pour initialiser le dictionnaire.
Library * initialisation(){
	
	Library * library = malloc(sizeof(Library));
	Dictionary * dictionary = malloc(sizeof(Dictionary));
	
	if(library == NULL && dictionary == NULL){
		exit(EXIT_FAILURE);
	}
	
	library->first_dictionary = dictionary;
	library->nb_dictionary = 1;

	dictionary->first_word = NULL;
	dictionary->nb_word = 0;
	dictionary->next_dictionary = NULL;
	
	return library;
}

//Ajout de mot au dictionnaire.
void addWord(Dictionary * dictionary, char * word){
	
	if(word[0] != '\0' && dictionary != NULL){
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

				myWord->next_word = dictionary->first_word;
				dictionary->first_word = myWord;
				dictionary->nb_word += 1;

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

		myWord->next_word = dictionary->first_word;
		dictionary->first_word = myWord;
		dictionary->nb_word += 1;		
	}
}

//Fonction qui montre le contenu du dictionnaire.
void showDictionary(Dictionary * dictionary){
	
	if(dictionary == NULL){
		exit(EXIT_FAILURE);
	}
	printf("The dictionary : [");
	Word * actual = dictionary->first_word;
	if(actual == NULL){
		printf("no word is censored");
	}else{
		int counter = dictionary->nb_word;
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
}


//

void compteur(char * phrase){

	int i = 0;
	int espace = 0;
	while(*(phrase+i) != '\0'){
		if(*(phrase+i) == 32){
		espace =1;
		}
		i++;
	}
	
	printf("%s", espace ? "Il y a un espace." : "Il n\'y a pas d\'espace.");

}
