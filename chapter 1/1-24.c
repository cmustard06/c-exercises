#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
* 查找c语言程序中的基本语法错误，如圆括号，花括号，方括号不匹配的情况，
* 要正确处理引号，转义字符序列与注释情况
*/
#define MAXWORD 100

int read_file(char *filepath, char *contents,long s_len);
int main(int argc, char const *argv[])
{
	/* code */
	char *content;
	content = (char *)malloc(5000*sizeof(char));
	if(content==NULL){
		printf("assign fail\n");
		return 1;
	}
	read_file("1-22.c",content,5000);
	printf("%s\n", content);
	free(content);
	return 0;
}

/*
* 获取文件内容
*/
int read_file(char *filepath, char *contents,long s_len){
	char *str;
	long size;

	FILE *fp = fopen(filepath,"r");
	if(!fp){
		printf("Not open file\n");
		return 0;
	}
	fseek(fp,0,SEEK_END);  //将指针指向文件末尾
	size = ftell(fp);  //获取文件内容长度
	str = (char *)calloc(size+1,sizeof(char));
	rewind(fp);  //将指针指向文件开头
	printf("%ld\n",size);
	fread(str,sizeof(char),size,fp);
	str[size] = '\0';
	strncpy(contents,str,s_len);
	fclose(fp);
	return 1;
}