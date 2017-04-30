//#include <xinu.h>
#include <stdlib.h>
#include <stdio.h>
#include "deadlock.h"

//TODO - add in your functions
//implement the graph as a matrix
void initializeRAG()
{
	int i,j;

	for(i = 0; i < NLOCK + NPROC; i++)
	{
		for(j = 0; j < NLOCK + NPROC; j++)
		{
			rag[i][j] = 0;
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
	rag[pid][lockid] = 1;
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
	rag[lockid][pid] = 1;
	
	//remove edge from pid->lockid
	rag[pid][lockid] = 0;
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
	rag[lockid][pid] = 0;
}

/**
 * Prints the adjacency matrix or list representing the current RAG
 *
 */
void rag_print() 
{
	int i,j;
	for(i = 0; i < NLOCK + NPROC; i++)
	{
		if(i < NLOCK)
		{
			printf("L%d\t", i+1);
		}
		
		else
		{
			printf("p%d\t", i+1);		
		}

		for(j = 0; j < NLOCK + NPROC; j++)
		{
			printf("%d\t", rag[i][j]);
		}
		
		printf("\n");
	}
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

}
