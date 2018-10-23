#include "manager.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define USED 1
#define UNUSD 0
void manageit(manager *m, int mem) {
	int j;
	m->currpos = 0;
	m->available = mem;
	m->i = 0;
	for(j = 0; j < SIZE; j++) {
		m->u[j].p = NULL;
		m->u[j].start = m->u[j].size = 0;
		 m->u[j].status = UNUSD;
	}
}
int currposition(manager *m) {
	return m->currpos;
}
int insert(manager *m, int size, void *p) {
	m->u[m->i].start = m->currpos;
	m->u[m->i].size = size;
	m->u[m->i].status = USED;
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
	m->available = m->available + m->u[num].size;
	while(m->u[num + 1].p != NULL) {
		m->u[num] = m->u[num + 1];
		num++;
	}
	m->i--;
	return m->available;
}
int modify(manager *m, int size, void *p, void *ptr) {
	int num;
	num = find(m, ptr);
	if(num == INT_MIN)
		return m->available;
	m->available = m->available + m->u[num].size - size;
	m->u[num].size = size;
	m->u[num].start = m->currpos;
	m->u[num].size = size;       
        m->u[num].p = p;
        m->currpos = m->currpos + size;
	return m->available;
}
