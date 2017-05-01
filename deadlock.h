#define NLOCK 4			//maximum number of locks
#define NPROC 4			//maximum number of processes
#define SIZE 16			//size for num entries

//TODO - add an "extern" declaration for the RAG
extern int rag[NLOCK + NPROC][NLOCK + NPROC];

//Define the structure of an input from file
typedef struct Entry 
{
	int pid;	//holds the pid of the process
	char req;	//request 	
	int lockid;	//ID of the lock
} Entry;

//TODO - add your deadlock function prototypes
void rag_request(int pid, int lockid);
void rag_alloc(int pid, int lockid);
void rag_dealloc(int pid, int lockid);
void rag_print();
void deadlock_detect(void);
void initializeRAG(Entry **entries);
int isCycle(int index, int *visited, int *stack);

