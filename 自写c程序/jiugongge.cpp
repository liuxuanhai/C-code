//二十五宫格代码
#include <stdio.h>
int i,j,k,x,y,x1,y1,a[6][6];
int main(){
    x=2;
	y=0;
    a[x][y]=1;
    for(i=2;i<26;i++){
		x1=x-1;
		y1=y-1;
		if(x1<0){
			x1=4;
		}
		if(y1<0){
			y1=4;
		}
		if(a[x1][y1]!=0){
			x1=x;
			y1=y+1;
		}
		a[x1][y1]=i;
		x=x1;
		y=y1;
	}
	for(j=0;j<5;j++){
		for(k=0;k<5;k++)
			if(k==4){
			printf("%d\n",a[j][k]);
		}else if(a[j][k]<10){
			printf("%d    ",a[j][k]);
		}else
			printf("%d   ",a[j][k]);
	}
	return 0;
}