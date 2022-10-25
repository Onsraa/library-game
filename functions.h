typedef struct Library Library;
typedef struct Dictionary Dictionary;
typedef struct Word Word;

struct Library{
	Dictionary * first_dictionary;
	int nb_dictionary;
};

struct Dictionary{
	Word * first_word;
	int nb_word;
	Dictionary * next_dictionary;
};

struct Word{
	char * value;
	Word * next_word;
};

Library * initialisation();
void addWord(Dictionary * dictionary, char * word);
void showDictionary(Dictionary * dictionary);

void compteur(char * phrase);
