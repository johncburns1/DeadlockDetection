#define NLOCK 3	//maximum number of locks
#define NPROC 3	//maximum number of processes

//TODO - add an "extern" declaration for the RAG
//size is the max # of locks + max # of processes
extern int rag[NLOCK + NPROC][NLOCK + NPROC];

//TODO - add your deadlock function prototypes
void rag_request(int pid, int lockid);
void rag_alloc(int pid, int lockid);
void rag_print();
void deadlock_detect(void);
void initializeRAG();


//Define the structure of an input from file
typedef struct Entry 
{
	int pid;	//holds the pid of the process
	char req;	//request 	
	int lockid;	//ID of the lock
} Entry;
