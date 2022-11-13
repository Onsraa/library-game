#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../functions/functions.h"
#include "scenarios.h"

// Lancer le jeu
void startGame(Library *library)
{

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

	printf(COLOR_GREEN "1 " COLOR_RESET "- Lancer la partie\n");
	printf(COLOR_GREEN "2 " COLOR_RESET "- Quitter");
	puts("\n");

	int option;
	do
	{
		if (scanf("%d", &option) != 1)
		{
			while (fgetc(stdin) != '\n')
				;
		};
	} while (option != 1 && option != 2);

	switch (option)
	{
	case 1:
		menu(library);
		break;
	case 2:
		system("clear");
		puts("\n");
		printf("Oh...aurevoir.");
		puts("\n");
		exit(EXIT_SUCCESS);
	default:
		break;
	}
}

void menu(Library *library)
{

	system("clear");
	puts("\n");
	printf(COLOR_GREEN "1 " COLOR_RESET "- Rentrer dans la librairie\n\n"); // Montre tous les livres et les autres options.
	printf(COLOR_GREEN "2 " COLOR_RESET "- Retourner au démarrage");
	puts("\n");

	int option;
	do
	{
		if (scanf("%d", &option) != 1)
		{
			while (fgetc(stdin) != '\n')
				;
		};
	} while (option < 1 || option > 6);

	switch (option)
	{
	case 1:
		enterLibrary(library);
		break;
	case 2:
		startGame(library);
		break;
	default:
		break;
	}
}

void enterLibrary(Library *library)
{
	system("clear");
	puts("\n");
	if (library == NULL || library->nb_book == 0)
	{
		printf("Il n\'y a pas de livre dans la librairie..");
		puts("\n");
	}
	else
	{
		showLibrary(library, 0);
	}
	puts(" ");
	printf(COLOR_GREEN "1" COLOR_RESET " - Ajouter un livre\n\n");	// Initialisation d'un livre.
	printf(COLOR_GREEN "2" COLOR_RESET " - Examiner un livre\n\n"); // De nouvelles options s'ouvriront après ce choix : ajouter un mot / le supprimer.
	printf(COLOR_GREEN "3" COLOR_RESET " - Parler à un livre\n\n"); // Lance une session qui censure tous les mots que l'on dit qui sont présents dans le livre.
	printf(COLOR_GREEN "0" COLOR_RESET " - Retourner au menu");
	puts("\n");

	int option;

	do
	{
		if (scanf("%d", &option) != 1)
		{
			while (fgetc(stdin) != '\n')
				;
		};
	} while (option < 0 && option > 3);
	switch (option)
	{
	case 1:
		addBookMenu(library);
		break;
	case 2:
		checkBook(library);
		break;
	case 3:
		talkBook(library);
		break;
	case 0:
		menu(library);
		break;
	default:
		break;
	}
}

void addBookMenu(Library *library)
{

	system("clear");
	puts("\n");
	puts("Veux-tu rajouter un livre à la librairie ?");
	puts(" ");
	printf("(" COLOR_GREEN "o" COLOR_RESET ")ui - (" COLOR_GREEN "n" COLOR_RESET ")on");
	puts("\n");

	char option;
	do
	{
		if (scanf("%c", &option) != 1)
		{
			while (fgetc(stdin) != '\n')
				;
		};
	} while (option != 'o' && option != 'n');

	switch (option)
	{
	case 'o':
		addBook(library);
		break;
	case 'n':
		enterLibrary(library);
		break;
	default:
		break;
	}
};

void checkBook(Library *library)
{ // Examiner un livre

	system("clear");
	puts("\n");
	if (library == NULL || library->nb_book == 0)
	{
		printf("Il n\'y a pas de livre dans la librairie..");
		puts("\n");
		returnLibrary(library);
	}
	else
	{

		showLibrary(library, 0);

		int option;

		printf("Choisissez un livre : ");
		do
		{
			if (scanf("%d", &option) != 1)
			{
				while (fgetc(stdin) != '\n')
					;
			};
		} while (option < 0 || option > library->nb_book - 1);

		int bookNumber = option;

		Book *temp = library->first_book;

		while (option != 0)
		{
			temp = temp->next_book;
			option--;
		}

		system("clear");
		puts("\n");
		showBook(temp, 1);
		puts("\n");

		printf(COLOR_GREEN "0" COLOR_RESET " - Ajouter un ou plusieurs mots\n\n");
		printf(COLOR_GREEN "1" COLOR_RESET " - Supprimer un ou plusieurs mots\n\n");
		printf(COLOR_GREEN "2" COLOR_RESET " - Supprimer le livre\n\n");
		printf(COLOR_GREEN "3" COLOR_RESET " - Revenir dans la librairie");
		puts("\n");

		option = -1;

		do
		{
			if (scanf("%d", &option) != 1)
			{
				while (fgetc(stdin) != '\n')
					;
			};
		} while (option < 0 || option > 3);

		switch (option)
		{
		case 0:
			system("clear");
			puts("\n");
			showBook(temp, 0);
			modifyBook(temp, library);
			break;
		case 1:
			system("clear");
			puts("\n");
			if (temp->nb_word == 0)
			{
				printf("Le livre ne contient pas de mot.");
				puts("\n");
			}
			else
			{
				deleteWordMenu(temp, library);
			}
			break;
		case 2:
			deleteBookMenu(bookNumber, temp, library);
			break;
		case 3:
			enterLibrary(library);
			break;
		default:
			break;
		}

		returnLibrary(library);
	}
};

void talkBook(Library *library)
{

	system("clear");
	puts("\n");
	if (library == NULL || library->nb_book == 0)
	{
		printf("Il n\'y a pas de livre dans la librairie..");
		puts("\n");
		returnLibrary(library);
	}
	else
	{
		showLibrary(library, 0);
		printf("Avec quel livre souhaitez-vous échanger ?");
		puts("\n");

		int option;

		do
		{
			if (scanf("%d", &option) != 1)
			{
				while (fgetc(stdin) != '\n')
					;
			};
		} while (option < 0 || option > library->nb_book - 1);

		Book *temp = library->first_book;

		while (option != 0)
		{
			temp = temp->next_book;
			option--;
		}

		system("clear");
		if (temp->first_word == NULL)
		{
			puts("\n");
			printf("Le livre est vide.");
			puts("\n");
			returnLibrary(library);
		}
		printf("Vous discutez avec ce livre : ");
		showBook(temp, 1);
		puts(COLOR_RED "Dites Salomon pour quitter la discussion.");
		puts(COLOR_RESET " ");
		puts("**************************************************");
		puts(" ");
		int stay = 1;
		char sentence[MAX_SENTENCE];
		fgets(sentence, 2, stdin);
		while (stay)
		{
			printf("Vous  : ");
			stay = repeatSentence(temp, fgets(sentence, MAX_SENTENCE, stdin));
		}
		menu(library);
	}
}

int repeatSentence(Book *book, char *sentence)
{

	if (book == NULL)
	{
		exit(EXIT_FAILURE);
	}

	int count = 0;
	while (sentence[count] != '\n')
	{
		count++;
	}
	sentence[count] = '\0';

	if (!strcmp(sentence, "Salomon"))
	{
		return 0;
	}
	else
	{

		int start_position = 0;
		int end_position = 0;

		printf(COLOR_GREEN "Livre" COLOR_RESET ": ");
		while (sentence[end_position] != '\0')
		{
			end_position++;
			if (sentence[end_position] == 32)
			{
				printWord(book, sentence, start_position, end_position);
				start_position = end_position + 1;
			}
		}
		printWord(book, sentence, start_position, end_position);
		puts("\n");
		return 1;
	}
}

void printWord(Book *book, char *sentence, int start_position, int end_position)
{

	char *mySentence = malloc(sizeof(char) * (end_position - start_position + 1));
	int scale = 0;

	for (int i = start_position; i < end_position; i++)
	{
		mySentence[scale] = sentence[i];
		scale++;
	}

	int isPresent = 0;

	Word *temp = book->first_word;

	if (book->nb_word > 1)
	{
		for (int i = 0; i < book->nb_word; i++)
		{
			if (!strcmp(mySentence, temp->value))
			{
				isPresent = 1;
			}
			temp = temp->next_word;
		}
	}
	else
	{
		if (!strcmp(mySentence, temp->value))
		{
			isPresent = 1;
		}
	}

	if (isPresent)
	{
		for (int nb_letters = 0; nb_letters < strlen(mySentence); nb_letters++)
		{
			printf(COLOR_RED "*");
		}
		printf(COLOR_RESET);
	}
	else
	{
		printf("%s", mySentence);
	}
	printf(" ");

	free(mySentence);
}

void deleteBookMenu(int bookNumber, Book *book, Library *library)
{
	system("clear");
	puts("\n");
	printf("Êtes-vous sûr de vouloir supprimer le livre ?");
	puts("\n");
	printf("(" COLOR_GREEN "o" COLOR_RESET ")ui - (" COLOR_GREEN "n" COLOR_RESET ")on");
	puts("\n");

	char option;
	do
	{
		if (scanf("%c", &option) != 1)
		{
			while (fgetc(stdin) != '\n')
				;
		};
	} while (option != 'o' && option != 'n');

	switch (option)
	{
	case 'o':
		deleteBook(bookNumber, library);
		system("clear");
		puts("\n");
		printf("Le livre a bien été supprimé.");
		puts("\n");
		break;
	case 'n':
		enterLibrary(library);
		break;
	default:
		break;
	}
}

void deleteWordMenu(Book *book, Library *library)
{
	showBook(book, 1);
	puts("\n");
	printf("Quel(s) mot(s) voulez-vous effacer du livre ?");
	puts("\n");

	char newWord[MAX];
	fgets(newWord, sizeof(newWord), stdin);
	fgets(newWord, sizeof(newWord), stdin);

	int count = 0;

	while (newWord[count] != '\n')
	{
		count++;
	}
	newWord[count] = '\0';

	int old_nb_word = book->nb_word;

	deleteString(book, newWord);

	system("clear");
	puts("\n");
	if (old_nb_word - book->nb_word > 1)
	{
		printf("Les mots ont été effacés du livre !");
	}
	else
	{
		printf("Le mot a été effacé du livre !");
	}
	puts("\n");
	returnLibrary(library);
}