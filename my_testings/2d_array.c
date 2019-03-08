#include <stdio.h>

int main(void){

//	int a[2][3] = {1,2,3,4,5};
	int a[2][3] = {{1,2},{4,5}};
	int i = 0, j = 0;
	for (i = 0; i < 2; i++){
		for(j = 0; j < 3; j++){
			printf("%d\n", a[i][j]);
		}
	}
}
