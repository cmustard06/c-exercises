#include<stdio.h>
#include<string.h>
/*
 * 编写函数reverse(s)将字符串中的字符顺序颠倒过来
 */


#define MAXWORDLEN 100
int reverse(char old[]);

int main(int argc, char const *argv[])
{
	/* code */
	char s[] = "abcdef";

	if(reverse(s)){
		printf("%s\n",s);
	}else{
		printf("fail!\n");
	}

	return 0;
}


/*
 * 将字符串的顺序进行颠倒
 * eg: abcdef --> fedcba
 */
int reverse(char old[]){
	int start,end,index;
	char temp;
	//cacl length
	index = 0;
	while(old[index]!='\0'){
		index++;
	}

	if(index+1>MAXWORDLEN){
		printf("fail\n");
		return 0;
	}
	//除去'\0'
	index--;

	//前后对称交换
	start = 0;
	end = index; 
	while(start<end){
		temp = old[start];
		old[start] = old[end];
		old[end] = temp;
		start++;
		end--;
	}
	return 1;
}