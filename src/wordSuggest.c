#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "wordCreation.h"


wordSuggest* createWordSuggest()
{
	wordSuggest *suggestions = (wordSuggest*)malloc(sizeof(wordSuggest));
	int i=0;
	for(i=0; i<noOfRanks; i++)
	{
		suggestions->wordList[i].head=suggestions->wordList[i].tail=NULL;
	}
	return suggestions;
}

wordNode* makeWordNode(char *word)
{
	wordNode *temp = (wordNode*)malloc(sizeof(wordNode));
	strcpy(temp->word, word);
	temp->next = NULL;
	return temp;
}

int wordInList(rankWord *list, char *word)
{
	wordNode *temp = list->head;
	while(temp!=NULL)
	{
		if(!strcmp(temp->word, word))
			return 1;
		temp = temp->next;
	}
	return 0;
}

void addWordToList(rankWord *list, char *word)
{
	if(wordInList(list, word))
		return;
	
	if(list->head==NULL)
	{
		list->head = (wordNode*)makeWordNode(word);
		list->tail = list->head;
		return;
	}
	list->tail->next = makeWordNode(word);
	list->tail = list->tail->next;
}

int addSuggest(wordSuggest *suggestion, char *word, int freq)
{
	if(freq<=0 || freq>(noOfRanks))
		return 0;
	rankWord *temp = &suggestion->wordList[freq-1];
	addWordToList(temp, word);
	
	return 1;
}

void printSuggest(wordSuggest *suggestions, char *prefix)
{
	int i=noOfRanks-1;
	printf("\n");
	for(; i>=0; i--)
	{
		wordNode *temp = suggestions->wordList[i].head;
		if(temp==NULL)
			continue;
		printf("%d\n", i);
		while(temp!=NULL)
		{
			printf("%s%s ", prefix, temp->word);
			temp = temp->next;
		}
		printf("\n");
	}
}

void printHalfSuggest(wordSuggest *suggestions, char *prefix)
{
	int i=noOfRanks-1;
	int k = 0;
	for(; i>=0; i--)
	{
		wordNode *temp = suggestions->wordList[i].head;
		if(temp==NULL)
			continue;
		while(temp!=NULL)
		{
			if(strlen(temp->word)==0)
			{
				temp = temp->next;
				continue;
			}
			printf("%s", temp->word);
			printf(" ");
			k++;
			temp = temp->next;
			if(k==4)
				return;
		}
	}	
}

void clearList(rankWord *rank)
{
	wordNode *temp = rank->head, *p = rank->head;
	while(temp!=NULL)
	{
		temp = temp->next;
		free(p);
		p = temp;
	}
	rank->head = rank->tail = NULL;
	return;
}

void clearSuggest(wordSuggest *suggestion)
{
	int i=0;
	for(i=0; i<noOfRanks; i++)
		clearList(&suggestion->wordList[i]);
}
