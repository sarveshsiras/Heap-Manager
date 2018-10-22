#define SIZE 100000
typedef struct node {
	int start, size, status;
	void *p;
}node;
typedef struct manager {
	node u[SIZE], f[SIZE];	
	int currpos, available, i;
}manager;
void manageit(manager *m, int mem);
int insert(manager *m, int size, void *p);
int remove(manager *m, void *p);
int modify(manager *m, int size, void *p);	
