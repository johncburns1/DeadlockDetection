//#include <xinu.h>
#include <stdlib.h>
#include <stdio.h>
#include "deadlock.h"

/**
 * Initializes the graph as an adjacency matrix
 * Fills the matrix with all zeros 
 * Handles each request line and alters the matrix accordingly
 *
 * @param Entry**	entries
 */
void initializeRAG(Entry **entries)
{
	int i,j;

	for(i = 0; i < NLOCK + NPROC; i++)
	{
		for(j = 0; j < NLOCK + NPROC; j++)
		{
			rag[i][j] = 0;
		}
	}

	//add the connection to the RAG
	for(i = 0; i < SIZE; i++) 
	{
		if(entries[i]->req == 'A')
		{
			rag_alloc(entries[i]->pid, entries[i]->lockid);
		}

		else if(entries[i]->req == 'R')
		{
			rag_request(entries[i]->pid, entries[i]->lockid);
		}

		else if(entries[i]->req == 'D')
		{
			rag_dealloc(entries[i]->pid, entries[i]->lockid);
		}
	}
}

/**
 * Adds a request edge to the RAG from pid to lockid
 *
 * @param int	pid
 * @param int 	lockid
 */
void rag_request(int pid, int lockid)
{
	//from pid to lockid
	rag[NLOCK + pid][lockid] = 1;
}

/**
 * Adds an allocation edge to the RAG from lockid to pid.
 * Removes request edge from pid to lockid
 * 
 * @param int	pid
 * @param int	lockid
 */
void rag_alloc(int pid, int lockid) 
{
	//adds edge from lockid->pid
	rag[lockid][NLOCK + pid] = 1;
	
	//remove edge from pid->lockid
	rag[NLOCK + pid][lockid] = 0;
}

/**
 * Removes the request or allocation edge from lockid to pid
 *
 * @param int	pid
 * @param int	lockid
 */
void rag_dealloc(int pid, int lockid)
{
	//remove request edge from lockid -> pid
	rag[lockid][NLOCK + pid] = 0;
}

/**
 * Prints the adjacency matrix or list representing the current RAG
 *
 */
void rag_print() 
{
	int i,j;
	int proc_index = 0;

	printf("\n");

	for(i = 0; i < NLOCK + NPROC; i++)
	{
		if(i < NLOCK)
		{
			printf("\nL%d\t", i);
		}
		
		else
		{
			printf("\np%d\t", proc_index++);		
		}

		for(j = 0; j < NLOCK + NPROC; j++)
		{
			printf("%d\t", rag[i][j]);
		}
		
		printf("\n\n");
	}

	proc_index = 0;

	//print the key at bottom
	for(i = 0; i < NLOCK + NPROC; i++)
	{
		if(i < NLOCK)
		{
			printf("\tL%d", i);
		}
		
		else
		{
			printf("\tp%d", proc_index++);		
		}
	}

	printf("\n\n");
}

/**
 * Checks the RAG for cycle(s).  
 * For each cycle found, print out DEADLOCK followed by the nodes
 * involved in the cycle.
 * If no cycles are found, then the system is deadlock-free.
 * You should produce no output in this case. 
 * Application of DFS
 *
 * @param void
 */
void deadlock_detect(void)
{
	int n = NPROC + NLOCK;		//holds number of vertices
	int stack[n];			//vertices currently on stack
	int visited[n];			//visited vertices
	int i, j = 0;

	//set int arrays
	for(i = 0; i < n; i++)
	{
		stack[i] = 0;
		visited[i] = 0;
	}

	//call the helper
	for(i = 0; i < n; i++)
	{
		if(isCycle(i, visited, stack) == 1)
		{
			printf("\n***CYCLE***\n");
		}
	}				
}

/**
 * A helper method to recursively check for cycles in a graph
 *
 * @param int	index
 * @param int*	visited
 * @param int*	stack
 */
int isCycle(int vertex_index, int *visited, int *stack)
{
	int i;
	int n = NPROC + NLOCK;
	int adjacent[n];
	int adjacent_size = 0;

	//fill adjacent with all adjacent nodes for a given vertex 
	for(i = 0; i < n; i++)
	{
		//if there is an edge
		if(rag[vertex_index][i] == 1)
		{
			adjacent[adjacent_size] = i;
			adjacent_size++;
		}
	}

	printf("\n");

	if(visited[vertex_index] == 0)
	{
		//mark the current vertex as visited and add it to stack
		visited[vertex_index] = 1;
		stack[vertex_index] = 1;

		//recurse over all connected vertices
		for(i = 0; i < adjacent_size; i++)
		{
			if(visited[adjacent[i]] == 0 && isCycle(adjacent[i], visited, stack) == 1)
			{
				//printf("%d ", vertex_index);
				if
				printf("Vertex: %d\n", vertex_index);
				return 1;
			}

			else if(stack[adjacent[i]] == 1)
			{
				printf("%d ", vertex_index);
				return 1;
			}
		}
	}

	//remove vertex @ index from stack
	stack[vertex_index] = 0;
	return 0;
}
