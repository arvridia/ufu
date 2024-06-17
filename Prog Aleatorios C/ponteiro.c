#include <stdio.h>
#include <stdlib.h>
	
int main(){
	double *p, *q, *r, A[5];
	p = A; 
	q = p+1;
	r = q+2;
	printf("&A[0] = %lu; *r = %lf;\n", &A[0], *r);
	printf("p = %lu; *A+1) = %lf;\n", p, *(A+1));
	r = p+4;
	p = q;
	printf("p+1 = %lu; *(r-2) = %lf; \n", &p+1, *(r-2));
	printf("&A[4] = %lu; *r = %lf;\n", &A, *r);
	return 0;
}