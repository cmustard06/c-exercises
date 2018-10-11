#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*
 * 编写函数reverse(s)将字符串中的字符顺序颠倒过来
 */


#define MAXWORDLEN 30
int reverse(char s[]);

int main(int argc, char const *argv[])
{
	/* code */
	char s[] = "abcdefsd";
	if(reverse(s)){
		printf("%s\n",s);
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
		printf("Long length,Terminate operation!!\n");
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

/*
 * 将字符串的顺序进行颠倒
 * eg: abcdef --> fedcba
 * 无法释放内存空间
 */
// char* reverse(char *s){
// 	int index=0;
// 	char *new;
// 	int start,end;

// 	while(*(s+index)!='\0'){
// 		index++;
// 	}
// 	//开辟一个新的内存块用于存储新的数据
// 	// printf("%d\n",index);
// 	new = (char *)malloc(sizeof(char)*(index+1));
// 	if(new==NULL){
// 		return '\0';
// 	}
// 	if((index+2)>MAXWORDLEN){
// 		printf("Long length,Terminate operation!!\n");
// 		return '\0';
// 	}
// 	//end=index-1; //忽略'\0'
// 	for(start=0,end=index-1;start<index;start++,end--){
// 		*(new+start) = *(s+end);
// 	}

// 	//一定要在最后加上\0
// 	*(new+index) = '\0';
// 	return new;
// }