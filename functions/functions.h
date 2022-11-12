typedef struct Library Library;
typedef struct Book Book;
typedef struct Word Word;

#define MAX 200 //Nombre max de caractères par saisie.
#define MAX_SENTENCE 1000 //Nombre max de caractères par phrase lors d'une discussion.

#define COLOR_RESET  "\x1b[0m"
#define COLOR_RED    "\x1b[31m"
#define COLOR_GREEN  "\x1b[32m"

struct Library{
	Book * first_book;
	int nb_book;
};

struct Book{
	Word * first_word;
	int nb_word;
	Book * next_book;
};

struct Word{
	char * value;
	Word * next_word;
};

Library * initialisation();


//Actions functions
void addString(Book * book, char * string);
void addWord(Book * book, char * word, int start_position, int end_position);
void deleteBook(int bookNumber, Library * library);
void clearBook(Book * book);

void addBook(Library * library);
void modifyBook(Book * book, Library * library);
void showBook(Book * book, int detail);
void showLibrary(Library * library, int detail);

void returnLibrary(Library * library);

void deleteString(Book * book, char * string);
void deleteWord(Book * book, char * string, int start_postition, int end_position);
