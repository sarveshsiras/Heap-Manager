#define SIZE 100000
typedef struct node {
	int start, size, status;
	void *p;
}node;
typedef struct manager {
	node n[SIZE];	
	int currpos, available, i;
}manager;
int manageit(manager *m);
int insert(manager *m, int size, void *p);
int remove(manager *m, void *p);
int modify(manager *m, int size, void *p);	
