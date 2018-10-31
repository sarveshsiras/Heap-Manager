#define SIZE 100000
typedef struct node {
	int start, size;
	void *p;
}node;
typedef struct manager {
	node u[SIZE], f[SIZE];	
	int currpos, available, i, j;
}manager;
void manageit(manager *m, unsigned int mem);
int currposition(manager *m);
int sizeofptr(manager *m, void *p); 
int insert(manager *m, unsigned int size, void *p);
int find(manager *m, void *p); 
int remov(manager *m, void *p);
int modify(manager *m, unsigned int size);
int mfull(manager *m, unsigned int size);
void finsert(manager *m, node u);
void* fralloc(manager *m, unsigned int size);
