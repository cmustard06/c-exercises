#include<stdio.h>

/*
�ѽϳ��ĵ��������۳ɶ�һЩ�����кͶ��У����е�λ���������е�
��n��֮ǰ�����һ���ǿո��֮��Ҫ��֤�����ܹ����ܵش��������кܳ��Լ���ָ��
����ǰû�пո�����Ʊ�������
*/

#define MAXROWS 10
#define MAXWORD 100
int* find_blank(char *s);
int split(char *s, int start, int end, char *retval);

int main(int args, char *argv[]) {
	int pos = 0,front=-1;
	char *retval[MAXROWS];
	//char *s = "aaa a	aa  a"; //3  5 8
	char *s = "abcdefg";
	char *temp;
	temp = (char *)calloc(strlen(s) * sizeof(char));
	if (split(s, 2, 6, temp)!=0) {
		printf("%s",temp);
	}
	//�ͷſռ�
	return 0;
}
/*
* �ҵ��ַ����пո��λ�ã���Ҫ�ֶ��ͷſռ�
*/
int* find_blank(char *s) {
	//�ڶ������ٿռ�������(������ջ���������,���ź�������,������ָ��ĵ�ַ��ŵ�����Ҳ�ᱻϵͳ�ͷ�,�����ϵĿռ����ɳ���Ա�Զ����������ͷŵ�)
	int *blankloc=(int *)calloc(MAXROWS * sizeof(int));  
	int pos,isblank,index;
	pos = 0, isblank = 0,index=0;
	memset(blankloc, 0, sizeof(int)*MAXROWS);
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
	for (pos = 0; pos < MAXROWS; pos++) {
		printf("%d ",blankloc[pos]);
	}
	printf("\n");
	return blankloc;
}

/*
* 
*/
int entabs(char *s, int blanloc[], char *retval[],int find) {
	int pos=0,index=0;
	char temp[MAXWORD];

}
/*
* ��Ƭ����ɷ���1��ʧ�ܷ���0,retvalΪ������
*/
int split(char *s, int start, int end,char *retval) {
	int s_len,r=0;
	s_len = strlen(s);
	char temp[MAXWORD];

	if (end >= s_len || start < 0) {
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
*������
*/
void print_ret(char *retval){

}