#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "wordCreation.h"

int main(int argc, char *argv[])
{
	if(argc<=1)
		return;
	if(strlen(argv[1])<=1)
		return;
	tree *wordTree = createTree();
	readTree(wordTree);
	wordSuggest *suggestions = createWordSuggest();
	findSuggestions(wordTree, argv[1], suggestions);
}
