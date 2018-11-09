#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "heap.h"
int main() {
	time_t tt;
	int x = 1024, flag, row, column, i;
	char ***matrix;
	void *ptr[7];
	int *p[10000];
	ptr[0] = (int *)smalloc(0);
	if(ptr[0] == NULL) {
		printf("Test for size 0 successful\n");
	}
	else {
		printf("Test for size 0 was unsuccessful\n");
	}
	 /* Test to check if various data types and their respective sizes can get allocated */
	ptr[0] = (short *)smalloc(sizeof(short));
	if(ptr[0] != NULL) {
		printf("Test for short* successful\n");
	}
	else {
		printf("Test for short* was unsuccessful\n");
	}
	ptr[1] = (int *)smalloc(sizeof(int));
	if(ptr[1] != NULL) {
		printf("Test for int* successful\n");
	}
	else {
		printf("Test for int* was unsuccessful\n");
	}
	ptr[2] = (long *)smalloc(sizeof(long));
	if(ptr[2] != NULL) {
		printf("Test for long* successful\n");
	}
	else {
		printf("Test for long* was unsuccessful\n");
	}
	ptr[3] = (float *)smalloc(sizeof(float));
	if(ptr[3] != NULL) {
		printf("Test for float* successful\n");
	}
	else {
		printf("Test for float* was unsuccessful\n");
	}
	ptr[4] = (double *)smalloc(sizeof(double));
	if(ptr[4] != NULL) {
		printf("Test for double* successful\n");
	}
	else {
		printf("Test for double* was unsuccessful\n");
	}
	ptr[5] = (long double *)smalloc(sizeof(long double));
	if(ptr[5] != NULL) {
		printf("Test for long double* successful\n");
	}
	else {
		printf("Test for long double* was unsuccessful\n");
	}
	ptr[6] = (char *)smalloc(sizeof(char));
	if(ptr[6] != NULL) {
		printf("Test for char* successful\n");
	}
	else {
		printf("Test for char* was unsuccessful\n");
	}
	i = 0;
	while(i < 7){
		sfree(ptr[i]);
		i++;
	}
	/*Test for checking whether arrays of various data types and their respective sizes get allocated*/
	ptr[0] = (short *)smalloc(4 * sizeof(short));
	if(ptr[0] != NULL) {
		printf("Test for array of short* successful\n");
	}
	else {
		printf("Test for array of short* was unsuccessful\n");
	}
	ptr[1] = (int *)smalloc(4 * sizeof(int));
	if(ptr[1] != NULL) {
		printf("test for array of int* successful\n");
	}
	else {
		printf("test for array of int* was unsuccessful\n");
	}
	ptr[2] = (long *)smalloc(4 * sizeof(long));
	if(ptr[2] != NULL) {
		printf("test for array of long* successful\n");
	}
	else {
		printf("test for array of long* was unsuccessful\n");
	}
	ptr[3] = (float *)smalloc(4 * sizeof(float));
	if(ptr[3] != NULL) {
		printf("test for array of float* successful\n");
	}
	else {
		printf("test for array of float* was unsuccessful\n");
	}
	ptr[4] = (double *)smalloc(8 * sizeof(double));
	if(ptr[4] != NULL) {
		printf("test for array of double* successful\n");
	}
	else {
		printf("test for array of double* was unsuccessful\n");
	}
	ptr[5] = (long double *)smalloc(16 * sizeof(long double));
	if(ptr[5] != NULL) {
		printf("test for array of long double* successful\n");
	}
	else {
		printf("test for array of long double* was unsuccessful\n");
	}
	ptr[6] = (char *)smalloc(10 * sizeof(char));
	if(ptr[6] != NULL) {
		printf("test for array of char* successful\n");
	}
	else {
		printf("test for array of char* was unsuccessful\n");
	}
	i = 0;
	while(i < 7){
		sfree(ptr[i]);
		i++;
	}
	/*Test for allocating matrix using a triple pointer */
	matrix = (char ***)smalloc(x * sizeof(char **));
	for(row = 0; row < x; row++) {
        	matrix[row] = (char **)smalloc(x * sizeof(char *));
        	if(matrix[row] != NULL) 
			flag = 1;
		else {
			flag = 0;
			break;
		}
		for (column = 0; column < x; column++) {
			matrix[row][column] = NULL ;
		}
	}
        if(flag) {
		printf("test for matrix row was successful\n");
		for (row = 0; row < x; row++) 
			sfree(matrix[row]);
	}
	else
		printf("test for matrix row was unsuccessful\n");
	sfree(matrix);
	srandom(time(&tt));
	while(i < 100) {
		x = random() % 100000;
		p[i++] = malloc(x);
	}
	while(i < 50) {
		x = random() % 50;
		free(p[x]);
		p[x] = NULL;
	}
	return 0;
}
