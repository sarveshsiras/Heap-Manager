#include "manager.h"
void manageit(manager *m, unsigned int mem) {
	int a, b;
	m->available[0] = mem;
	m->bi = 0;
	m->j = 0;
	m->blkfreed = 0;
	for(a = 0; a < BLOCK; a++) {
		m->currpos[a] = 0;
		m->i[a] = 0;
		for(b = 0; b < SIZE; b++) {
			m->u[a][b].p = m->u[a][b].ref = NULL;
			m->u[a][b].start = m->u[a][b].size = 0;
		}
	}
	for(b = 0; b < SIZE; b++) {
		m->f[b].p = m->f[b].ref = NULL;
		m->f[b].start = m->f[b].size = m->f[b].blkno = 0;
	}
}
int sizeofptr(manager *m, void *p) {
	int x, y;
	size_t size;
	find(m, p, &x, &y);
	if(x == -1 || y == -1) {
		return 0;
	}
	size = m->u[x][y].size;
	return size;
}
void insert(manager *m, unsigned int size, void *p, void *ref, int b) {
	m->u[b][m->i[b]].start = m->currpos[b];
	m->u[b][m->i[b]].size = size;
	m->u[b][m->i[b]].p = p;
	m->u[b][m->i[b]].ref = ref;
	m->available[b]= m->available[b] - size;
	m->currpos[b] = m->currpos[b] + size;
	m->i[b]++;
}
void find(manager *m, void *p, int *a, int *b) {
	int flag = 0, x, y;
	for(x = 0; x < m->bi; x++) {
		for(y = 0; m->u[x][y].p != NULL; y++) {
			if(p == m->u[x][y].p) {
				*a = x;
				*b = y;
				flag = 1;
				break;
			}
		}
	}
	if(flag == 0) {
		*a = -1;
		*b = -1;
		return;
	}
}
void remov(manager *m, void *p) {
	int x, y;
	find(m, p, &x, &y);
	if(x == -1 || y == -1) {
		printf("No record\n");
		return;
	}
	finsert(m, m->u[x][y], x);
	m->blkfreed = m->blkfreed + m->u[x][y].size;
	while(y < m->i[x] - 1) {
		m->u[x][y] = m->u[x][y + 1];
		y++;
	}
	m->i[x]--;
}
void finsert(manager *m, node u, int x) {
	int a, b, c;
	fnode tmp;
	m->f[m->j].start = u.start;
	m->f[m->j].size = u.size;
	m->f[m->j].p = u.p;
	m->f[m->j].ref = u.ref;
	m->f[m->j].blkno = x;
	if(m->j > 1) {
		c = m->j;
		for(a = 0; a < c - 1; a++)
			for(b = 0; b < c - 1 - a; b++)
				if(m->f[b].size > m->f[b + 1].size) {
					tmp = m->f[b];
					m->f[b] = m->f[b + 1];
					m->f[b + 1] = tmp;
				}
	}
}
void* fralloc(manager *m, unsigned int size, int a) {
	//int a, b = 0;
	void *ptr;
	if(!m->j)
	return NULL;
	/*a = 0;
	while(a < m->j) {
		if(size <= m->f[a].size) {
			ptr = m->f[a].p;
			b = 1;
			break;
		}
		a++;	
	}
	if(!b)
		return NULL;
	*/
	ptr = m->f[a].p;
	insert(m, size, ptr, m->f[a].ref, m->f[a].blkno);
	while(a < m->j -1) {
		m->f[a] = m->f[a + 1];
		a++;
	}
	m->j--;
	return ptr;
}
void newbuddy(manager *m, void *p, size_t size, size_t tsize) {
	if(size == 0) {
		m->u[0][0].ref = p;
		m->available[0] = tsize;
		m->bi++;		
	}
	else {
		m->u[m->bi][0].ref = m->u[m->bi][0].p = p;
		m->available[m->bi] = tsize - size;
		m->u[m->bi][0].start = 0;
		m->u[m->bi][0].size = size;
		m->currpos[m->bi] = size;
		m->i[m->bi]++;
		m->bi++;
	}
}
int buddyavail(manager *m, size_t size) {
	int a;
	if(m->j) {
		for(a = 0; a < m->j; a++)
			if(m->f[a].size >= size){
				m->blkfreed = m->blkfreed - m->f[a].size;			
				return -a;
			}
	}
	if(m->bi) {
		for(a = 0; a < m->bi; a++)
			if(m->available[a] >= size)
				return a;

	}
	return 0;
}
int currposition(manager *m, int blk) {
	return m->currpos[blk];
}
void* allocate(manager *m, int blk, size_t size) {
	void *ptr;
	if(blk < 0) {
		blk = -blk;
		ptr = fralloc(m, blk, size);
	}
	else {
		ptr = m->u[blk][m->i[blk]].ref;
	}
	return ptr;
}
