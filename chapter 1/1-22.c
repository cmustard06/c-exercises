#include<stdio.h>

/*
�ѽϳ��ĵ��������۳ɶ�һЩ�����кͶ��У����е�λ���������е�
��n��֮ǰ�����һ���ǿո��֮��Ҫ��֤�����ܹ����ܵش��������кܳ��Լ���ָ��
����ǰû�пո�����Ʊ�������
*/

#define MAXROWS 10
int* find_blank(char *s);

int main(int args, char *argv[]) {
	int pos = 0,front=-1;
	char *retval[MAXROWS];
	char *s = "aaa a	aa  a"; //3  5
	int *temp;
	temp = find_blank(s);
	for (pos=0; pos < 10; pos++)
	{
		printf("%d\t",temp[pos]);
	}
	//�ͷſռ�
	free(temp);
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
* �п�
*/
void split(char *s, int blanloc[], char *retval) {

}

/*
*������
*/
void print_ret(char *retval){

}