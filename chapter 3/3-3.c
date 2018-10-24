#include<stdio.h>
#include<string.h>

/*
编写函数expand(s1,s2)，将字符串s1中类似于a-z这一类的速记符号在
字符串s2中扩展为等价的完整列表abc
 */

void expand(char s1[],char s2[]){
	int index=0;
	int s_index = 0;
	while(s1[index]!='\0'){
		if(s1[index]=='-'&&s1[index-1]<=s1[index+1]){
			for(int i=s1[index-1]+1;i<=s1[index+1];++i){
				printf("%c,", i);
				s2[s_index++] = i;
			}
			index +=2;
		}
		else{
			s2[s_index++]=s1[index];
			index++;
		}
	}
	s2[s_index]='\0';
	printf("\n%s\n",s2);
}

int main(int argc, char const *argv[])
{
	char *s1="asdb-a0-91111";
	char s2[100];
	expand(s1,s2);
	return 0;
}