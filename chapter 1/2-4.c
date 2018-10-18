#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#if 0
#define FOLD_DEBUG printf("%d \t *s=%c flag=%d\n", __LINE__, *s1,flag);
#else
#define FOLD_DEBUG
#endif
/*
* 实现字符串s1中的字符如果在字符串s2中出现，就在s1中删除该字符
 */
void squeeze(char *s1,char *s2,char *retVal,long s1_len);

int main(int argc, char const *argv[])
{
	/* code */
	char *s1="abcdefg";
	char *s2 = "eijfll";
	char *swap;
	long s1_len;
	s1_len = strlen(s1);
	if((swap=(char *)calloc(s1_len+1,sizeof(char)))==NULL){
		printf("memery assign fail!!!\n");
		return -1;
	}
	printf("字符串s1中的字符如果在字符串s2中出现，就在s1中删除该字符......\n");
	squeeze(s1,s2,swap,s1_len);
	printf("s1=%s\ts2=%s\n",s1,s2);
	printf("result:%s\n",swap);
	free(swap);
	return 0;
}

void squeeze(char *s1,char *s2,char *retVal,long s1_len){
	// printf("%c\n",*(s1++));
	int index=0,flag=0,pos=0;  //pos返回结果下标

	while(*s1!='\0'){
		index = 0; //s2 下标 
		while(*(s2+index)!='\0'){
			if(*s1==*(s2+index)){
				flag=1;
				break;
			}
			index++;
		}
		if(flag==0){
			*(retVal+pos)=*s1;
			pos++;
		}else{
			flag=0;
		}
		s1++;
	}

	*(retVal+pos) = '\0';	
}