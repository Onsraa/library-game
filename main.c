#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"



int main(){

Library * library = initialisation();
Dictionary * dictionary = library->first_dictionary;

addWord(dictionary, "hello you haha wtf");
showDictionary(dictionary);


exit(EXIT_SUCCESS);
}
