#include<stdio.h>
#include<string.h>

/*
编写一个函数escape(s,t)，将字符串t复制到字符串s中，并在复制过程中
将换行符，制表符等不可显示的字符分别转换为\n,\t等可显示的字符，使用switch
语句
 */


void escape(char s[],char t[]){
	int index=0;
	while(*(t++)!='\0'){
		switch(*t){
			case '\n':
				*(s+index)='\\';
				index++;
				*(s+index)='n';
				index++;
				break;
			case '\t':
				*(s+index) = '\\';
				index++;
				*(s+index)='t';
				index++;
				break;
			default:
				*(s+index)=*t;
				index++;
				break;
		}
	}
	*(s+index)='\0';
	printf("ret: %s\n",s);
}

int main(int argc, char const *argv[])
{
	char s[100];
	memset(s,0,100);
	char *t="acvv	kksad\nasdasd";
	escape(s,t);
	return 0;
}