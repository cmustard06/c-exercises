#include<stdio.h>
#include<string.h>
/*
函数strriindex(s,t)
返回字符串t在s中最右边出现的位置，如果s中不包含t，返回-1
 */

int strrindex(char s[], char t[]){
	int i,j,k,pos;
	pos = -1;

	for(i=0;s[i]!='\0';i++){
		for(j=i,k=0;t[k]!='\0'&&s[j]==t[k];j++,k++);
		if(k>0&&t[k]=='\0'){
			pos=i;
		}
	}
	return pos;
}
int main(int argc, char const *argv[])
{
	
	char *s = "hello world";
	char *t = "llo";
	int pos;
	pos = strrindex(s,t);
	printf("%d\n",pos);
	return 0;
}