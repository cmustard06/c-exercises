#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
�ѽϳ��ĵ��������۳ɶ�һЩ�����кͶ��У����е�λ���������е�
��n��֮ǰ�����һ���ǿո��֮��Ҫ��֤�����ܹ����ܵش��������кܳ��Լ���ָ��
����ǰû�пո�����Ʊ�������
*/

#define MAXROWS 10
#define MAXWORD 100

void find_blank(char *s,int blankloc[],int s_len);
int split(char *s, int start, int end, char *retval);
int entabs(char *s, int blankloc[], char *retval[],int find);

int main(int args, char *argv[]) {
	//int pos = 0,front=-1;
	char *retval[MAXROWS];
	char *s = "aaa a	aa  a"; //3  5 8
	// char *s = "abcdefg";
	int temp[10];
	// temp = (char *)calloc(strlen(s),sizeof(char));
	find_blank(s,temp,10);
	for(int i=0;i<10;i++){
		printf("%d ", temp[i]);
	}
	entabs(s,temp,retval,3);

	//�ͷſռ�
	return 0;
}
/*
* �ҵ��ַ����пո��λ�ã���Ҫ�ֶ��ͷſռ�
*/
void find_blank(char *s,int blankloc[],int s_len) {
	//�ڶ������ٿռ�������(������ջ���������,���ź�������,������ָ��ĵ�ַ��ŵ�����Ҳ�ᱻϵͳ�ͷ�,�����ϵĿռ����ɳ���Ա�Զ����������ͷŵ�)
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
	for (pos = 0; pos < MAXROWS; pos++) {
		printf("%d ",blankloc[pos]);
	}
	printf("\n");
}

/*
* 
*/
int entabs(char *s, int blankloc[], char *retval[],int find) {
	int pos=0,index=0,r_index=0;

	while(blankloc[index]!=-1){
		if(find<blankloc[index]){
			split(s,pos,blankloc[index],retval[r_index]);
			printf("%s\n",retval[r_index]);
			pos = blankloc[index];
			//find = pos+blankloc[index];
		}
		index++;
		r_index++;
	}
	return 1;
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