#include<stdio.h>
#include<stdlib.h>

#define noOfRanks 9
#define Alphabets 26
#define fileName "words.txt"
#define fileFreq "wordFreq.txt"

typedef struct NODE
{
	char letter;
	struct NODE* nextLetter[Alphabets];
	int isWord;
}node;

typedef struct TREE
{
	struct NODE* root;
}tree;

typedef struct wordNode
{
	char word[20];
	struct wordNode *next;
}wordNode;

typedef struct rankWord
{
	struct wordNode *head, *tail;
}rankWord;

typedef struct wordSuggest
{
	rankWord wordList[noOfRanks];
}wordSuggest;

node* makeNode(char letter);
int cleanWord(char *word);
int addWord(tree *wordTree, char *word);
int isAWord(tree *wordTree, char *word);
tree* createTree();
void treePrioritise(tree* wordTree);
void readTree(tree *wordTree);
void searchWords(wordSuggest *suggestion, node *temp, char *word);
int findSuggestions(tree *Wordtree, char *prefix, wordSuggest *suggestion);
void checkFlipped(tree *wordTree, char *word, wordSuggest *suggestion);
void checkExcess(tree *wordTree, char *word, wordSuggest *suggestion);
void checkMissing(tree *wordTree, char *word, wordSuggest *suggestion);
int findAlternates(tree *wordTree, char *word, wordSuggest *suggestion);

wordSuggest* createWordSuggest();
int wordInList(rankWord *list, char *word);
void addWordToList(rankWord *list, char* word);
wordNode* makeWordNode(char *word);
int addSuggest(wordSuggest *suggestion, char *word, int freq);
void printSuggest(wordSuggest *suggestions, char *prefix);
void printHalfSuggest(wordSuggest *suggestions, char *prefix);
void clearList(rankWord *rank);
void clearSuggest(wordSuggest *suggestion);
