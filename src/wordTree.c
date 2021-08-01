#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "wordCreation.h"

int numberOfNodes = 0;

node* makeNode(char letter)
{
	node *newNode = (node*)malloc(sizeof(node));
	newNode->letter = letter;
	int i=0;
	for(i=0; i<Alphabets; i++)
		newNode->nextLetter[i] = NULL;
	newNode->isWord = 0;
	numberOfNodes++;
	
	return newNode;
}

int cleanWord(char *word)
{
	int i = 0;
	while(word[i]!='\0' && word[i]!='\n')
	{
		char ch = word[i];
		if(!((ch>='A' && ch<='Z')||(ch>='a' && ch<='z')))
			return 0;
		if(ch>='A' && ch<='Z')
			word[i]+=32;
		i++;
	}
	return 1;
}

int addWord(tree *wordTree, char *word)
{
	int i=0;
	node *temp = wordTree->root;
	while(word[i]!='\0' && word[i]!='\n')
	{
		int letterValue = (int)word[i]-97;
		if(temp->nextLetter[letterValue]==NULL)
			temp->nextLetter[letterValue] = makeNode(word[i]);
		temp = temp->nextLetter[letterValue];
		i++;
	}
	temp->isWord = 1;
}

int isAWord(tree *wordTree, char *word)
{
	int i=0;
	node *temp = wordTree->root;
	while(temp!=NULL && word[i]!='\0' && word[i]!='\n')
	{
		int letterValue = (int)word[i]-97;
		temp = temp->nextLetter[letterValue];
		i++;
	}
	
	if(temp!=NULL && temp->isWord!=0)
		return temp->isWord;
		
	return 0;
}

tree* createTree()
{
	tree *wordTree = (tree*)malloc(sizeof(tree));
	wordTree->root = makeNode(' ');
	return wordTree;
}

void treePrioritise(tree* wordTree)
{
	FILE *readFile = fopen(fileFreq, "r");
	char word[40];
	while(fgets(word, 40, readFile))
	{
		int i=0;
		node *temp = wordTree->root;
		while(temp!=NULL && word[i]!=' ')
		{
			int letterValue = (int)word[i]-97;
			temp = temp->nextLetter[letterValue];
			i++;
		}
		if(temp!=NULL && temp->isWord==1)
			temp->isWord = (int)(word[i+1]-48);
	}
}

void readTree(tree *wordTree)
{
	FILE *readFile = fopen(fileName, "r");
	char word[30];
	while(fgets(word, 30, readFile))
	{
		addWord(wordTree, word);
	}
	fclose(readFile);
	treePrioritise(wordTree);
}

void searchWords(wordSuggest *suggestion, node *temp, char *word)
{
	int i=0;
	if(temp->isWord!=0)
		addSuggest(suggestion, word, temp->isWord);
	for(i=0; i<Alphabets; i++)
	{
		if(temp->nextLetter[i]==NULL)
			continue;
		char extra[2], newWord[30];
		extra[0] = (char)(i+97);
		extra[1] = '\0';
		strcpy(newWord, word);
		strcat(newWord, extra);
		searchWords(suggestion, temp->nextLetter[i], newWord);
	}
	return;
}

int findSuggestions(tree *wordTree, char *prefix, wordSuggest *suggestion)
{
	int i = 0;
	node *temp = wordTree->root;
	if(!cleanWord(prefix))
		return 0;
	while(prefix[i]!='\n' && prefix[i]!='\0')
	{
		if(prefix[i]>='A' && prefix[i]<='Z')
			prefix[i]+=32;
		temp = temp->nextLetter[(int)(prefix[i]-97)];
		if(temp==NULL)
			return 0;
		i++;
	}
	clearSuggest(suggestion);
	searchWords(suggestion, temp, "");
	printHalfSuggest(suggestion, prefix);
	return 1;
}

void checkFlipped(tree *wordTree, char *word, wordSuggest *suggestion)
{
	if(strlen(word)<=1)
		return;
	int i = 1;
	char ch;
	while(word[i]!='\n' && word[i]!='\0')
	{
		ch = word[i];
		word[i] = word[i-1];
		word[i-1] = ch;
		addSuggest(suggestion, word, isAWord(wordTree, word));
		ch = word[i];
		word[i] = word[i-1];
		word[i-1] = ch;
		i++;
	}
}

void checkExcess(tree *wordTree, char *word, wordSuggest *suggestion)
{
	if(strlen(word)<=1)
		return;
	int i = 1;
	char removed[30];
	while(word[i]!='\n' && word[i]!='\0')
	{
		strcpy(removed, "");
		strncpy(removed, word, i-1);
		removed[i-1] = '\0';
		strncat(removed, &word[i], strlen(word)-i);
		addSuggest(suggestion, removed, isAWord(wordTree, removed));
		i++;
	}
}

void checkMissing(tree *wordTree, char *word, wordSuggest *suggestion)
{
	
}

int findAlternates(tree *wordTree, char *word, wordSuggest *suggestion)
{
	if(isAWord(wordTree, word) || !cleanWord(word))
		return 0;
		
	clearSuggest(suggestion);
	
	//flipped letters
	checkFlipped(wordTree, word, suggestion);
	
	//excess letter
	checkExcess(wordTree, word, suggestion);
	
	//missing letters
	
	//adjacent letters
	
	printSuggest(suggestion, "");
	return 1;
}

/*int main()
{
	tree *wordTree = createTree();
	readTree(wordTree);
	wordSuggest *suggestions = createWordSuggest();
	char word[30];
	int ch;
	printf("Success %d\n", numberOfNodes);
	printf("Completion Suggestions: ");
	scanf("%d", &ch);
	while(ch!=0)
	{
		scanf("%s", word);
		if(!findSuggestions(wordTree, word, suggestions))
			printf("No Suggestions Found\n");
		ch--;
	}
	printf("Correction Suggestions: ");
	scanf("%d", &ch);
	while(ch!=0)
	{
		scanf("%s", word);
		if(!findAlternates(wordTree, word, suggestions))
			printf("Given Word Exists.\n");
		ch--;
	}
}*/
