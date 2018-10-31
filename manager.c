#include "manager.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
void manageit(manager *m, unsigned int mem) {
	int j;
	m->currpos = 0;
	m->available = mem;
	m->i = 0;
	m->j = 0;
	for(j = 0; j < SIZE; j++) {
		m->u[j].p = NULL;
		m->u[j].start = m->u[j].size = 0;
		m->f[j].p = NULL;
		m->f[j].start = m->u[j].size = 0;
	}
}
int currposition(manager *m) {
	return m->currpos;
}
int sizeofptr(manager *m, void *p) {
	int count;
	size_t size;
	count = find(m, p);
	if(count == INT_MIN)
		return m->available;
	size = m->u[count].size;
	return size;
}
int insert(manager *m, unsigned int size, void *p) {
	m->u[m->i].start = m->currpos;
	m->u[m->i].size = size;
	m->u[m->i++].p = p;
	m->available = m->available - size;
	m->currpos = m->currpos + size;
	return m->available;
}
int find(manager *m, void *p) {
	int count = 0, flag = 0;
	while(m->u[count].p != NULL) {
		if(p == m->u[count].p) {
			flag = 1;
			break;
		}
		count++;
	}
	if(flag == 0)
		return INT_MIN;
	return count;
}
int remov(manager *m, void *p) {
	int num;
	num = find(m, p);
	if(num == INT_MIN)
		return m->available;
	finsert(m, m->u[num]);
	m->available = m->available + m->u[num].size;
	while(num < m->i - 1) {
		m->u[num] = m->u[num + 1];
		num++;
	}
	m->i--;
	return m->available;
}
int modify(manager *m, unsigned int size) {
	m->available = m->available + size;
	return m->available;
}
int mfull(manager *m, unsigned int size) {
	return size >= m->available;
}
void finsert(manager *m, node u) {
	int a, b, c;
	node tmp;
	m->f[m->j++] = u;
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
void* fralloc(manager *m, unsigned int size) {
	int a, b = 0;
	void *ptr;
	if(!m->j)
	return NULL;
	a = 0;
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
	insert(m, size, ptr);
	while(a < m->j -1) {
		m->f[a] = m->f[a + 1];
		a++;
	}
	m->j--;
	return ptr;
}
