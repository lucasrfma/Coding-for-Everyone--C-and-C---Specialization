#define NDEBUG

#include <stdio.h>
#include <ctype.h>
#include <assert.h>

int main(){

	double x,y;

	while(1){
		printf("\n\nRead in 2 floats:\n");
		scanf("%lf %lf",&x,&y);

		assert(y!=0);
		printf("when devided x/y = %lf\n",x/y);
	}

	return 0;
}