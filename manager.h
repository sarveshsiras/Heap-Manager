#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000
#define BLOCK 10000
typedef struct node {
	int start, size;
	void *p, *ref;
}node;
typedef struct fnode {
	int start, size, blkno;
	void *p, *ref;
}fnode;
typedef struct manager {
	node u[BLOCK][SIZE];
	fnode f[SIZE];//u means under use and f means once freed and again used	
	int currpos[BLOCK], blkfreed, available[BLOCK], i[BLOCK], j, bi;
}manager;
void manageit(manager *m, unsigned int mem);
int currposition(manager *m, int blk);
int sizeofptr(manager *m, void *p); 
void insert(manager *m, unsigned int size, void *tmp, void *p, int num);
void find(manager *m, void *p, int *a, int *b); 
void remov(manager *m, void *p);
void finsert(manager *m, node u, int blk);
void* fralloc(manager *m, unsigned int size, int a);
void* allocate(manager *m, int blk, size_t size);
int buddyavail(manager *m, size_t size);
void newbuddy(manager *m, void *p, size_t size, size_t tsize);
