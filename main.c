#include <stdlib.h>
#include <stdio.h>
#include "deadlock.h"

//define rag
int rag[NLOCK + NPROC][NLOCK + NPROC];

int main(int argc, char *argv[])
{
	FILE *fp;			//file pointer
	char *line = NULL;		//Line pointer
	size_t length = 0;		//length
	ssize_t read;			//hold read data
	int i,j = 0;

	Entry **entries = malloc(8 * sizeof(Entry *));
	for(i = 0; i < 8; i++)
	{
		entries[i] = malloc(sizeof(Entry *));
	}	

	//open file reader
	fp = fopen(argv[1], "r");	//read the input file
	
	//check for errors
	if(fp == NULL)
	{
		printf("\nError, file cannot be read\n");
		exit(1);
	}

	//while there is still stuff to read
	while((read = getline(&line, &length, fp)) != -1)
	{
		entries[j]->pid = atoi(&line[0]);
		entries[j]->req = line[2];
		entries[j]->lockid = atoi(&line[4]);		
		j++;
	}	

	//close fp
	fclose(fp);
	if(line)
	{
		//free the pointer
		free(line);
	}

	initializeRAG();
	rag_print();

	return 0;	
}
