#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
把较长的的输入行折成短一些的两行和多行，折行的位置在输入行的
第n列之前的最后一个非空格符之后，要保证程序能够智能地处理输入行很长以及在指定
的列前没有空格或者制表符的情况
*/

#define MAXROWS 10
#define MAXWORD 100

void find_blank(char *s,int blankloc[],int s_len);
int split(char *s, int start, int end, char *retval);
int entabs(char *s, int* blankloc, int find);
int main(int args, char *argv[]) {
	//int pos = 0,front=-1;
	char *s = "abcd   jej kk"; //3  5 8
	// char *s = "abcdefg";
	int temp[10];
	// temp = (char *)calloc(strlen(s),sizeof(char));
	find_blank(s,temp,10);
	entabs(s,temp,5);

	//释放空间
	return 0;
}
/*
* 找到字符串中空格的位置，需要手动释放空间
*/
void find_blank(char *s,int blankloc[],int s_len) {
	//在堆区开辟空间存放数组(若是在栈区存放数组,随着函数结束,数组名指向的地址存放的内容也会被系统释放,而堆上的空间是由程序员自动给予分配和释放的)
	int pos,isblank,index;
	pos = 0, isblank = 0,index=0;
	memset(blankloc, -1, sizeof(int)*s_len);
	while (*(s+pos) != '\0') {
		if (*(s+pos) == ' '||*(s+pos)=='\t') {
			if (isblank == 0) {
				isblank = 1;
			}
			else {
				pos++;
				continue;
			}
			blankloc[index++] = pos;
		}
		else {
			isblank = 0;
		}
		pos++;
	}
	/*for (pos = 0; pos < MAXROWS; pos++) {
		printf("%d ",blankloc[pos]);
	}*/
	
}

/*
* 
*/
int entabs(char *s, int* blankloc, int find) {
	int pos=0,index=0,r_index=0;
	char *temp;
	int s_len = strlen(s);
	find = find - 1;
	while (blankloc[index] != -1) {
		if (find <= blankloc[index]) { //4
			temp = (char *)calloc(blankloc[index] - pos+2, sizeof(char));
			split(s, pos, blankloc[index], temp);
			printf("%s\n",temp);
			free(temp);
			pos = pos + blankloc[index];//4
		}
		index++;
		if (pos > find) {
			temp = (char *)calloc(s_len - pos + 2, sizeof(char)); //下标+1为长度，再加1为\0
			split(s, pos, s_len, temp);
			printf("%s\n",temp);
			free(temp);
			break;
		}
	}
	return 1;
}
/*
* 切片，完成返回1，失败返回0,retval为输出结果
*/
int split(char *s, int start, int end,char *retval) {
	int s_len,r=0;
	s_len = strlen(s);
	char temp[MAXWORD];

	if (end > s_len || start < 0) {
		return 0;
	}
	for (int i = start; i <=end; i++) {
		//printf("%c ", s[i]);
		temp[r++] = s[i];
	}
	temp[r] = '\0';
	strcpy(retval,temp);

	return 1;
}

/*
*输出结果
*/
void print_ret(char *retval){

}