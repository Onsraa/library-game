// Scenario
void startGame(Library *library);
void menu(Library *library);

// Menu
//*1
void enterLibrary(Library *library);
//*2
void addBookMenu(Library *library);
//*3
void checkBook(Library *library);
void deleteWordMenu(Book *book, Library *library);
void deleteBookMenu(int bookNumber, Book *book, Library *Library);

//*4
void talkBook(Library *Library);
int repeatSentence(Book *book, char *sentence);
void printWord(Book *book, char *sentence, int start_position, int end_position);
