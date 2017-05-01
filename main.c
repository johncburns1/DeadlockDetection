#include <stdlib.h>
#include <stdio.h>
#include "deadlock.h"

//define rag as num processes + num locks
int rag[NLOCK + NPROC][NLOCK + NPROC];

int main(int argc, char *argv[])
{
	FILE *fp;			//file pointer
	char *line = NULL;		//Line pointer
	size_t length = 0;		//length
	ssize_t read;			//hold read data
	int i,j = 0;

	//array of Entry pointers
	Entry **entries = malloc(SIZE * sizeof(Entry *));
	
	for(i = 0; i < SIZE; i++)
	{
		entries[i] = malloc(sizeof(Entry *));
	}	

	//open file reader and read the given file
	fp = fopen(argv[1], "r");
	
	//check for errors
	if(fp == NULL)
	{
		printf("\nError, file cannot be read\n");
		exit(1);
	}

	//while there is still stuff to read
	while((read = getline(&line, &length, fp)) != -1)
	{
		//set the entires for each request line
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

	//initialize the matrix to all zeros
	initializeRAG(entries);

	//print the matrix
	rag_print();

	//check for cycles
	deadlock_detect();
	
	//free up each memory entry
	for(i = 0; i < SIZE; i++)
	{
		free(entries[i]);
	}

	//free up the entire array
	free(entries);
	return 0;	
}
