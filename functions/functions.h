typedef struct Library Library;
typedef struct Book Book;
typedef struct Word Word;

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
void addWord(Book * book, char * word);
void addBook(Library * library);
void showBook(Book * book);
void showLibrary(Library * library);

void returnMenu(Library * library);

