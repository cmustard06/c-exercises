#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
* 查找c语言程序中的基本语法错误，如圆括号，花括号，方括号不匹配的情况，
* 要正确处理引号，转义字符序列与注释(\**\)情况
*/
#define MAXWORD 100

int read_file(char *filepath, char *contents,long s_len);
long file_size(char *filepath);
struct sysntax_state check(char *s);

struct sysntax_state{
	int leftparens;
	int rightparnes;
	int leftbrace;
	int rightbrace;
	int leftsquare;
	int rightsquare;
	int pos;
};


int main(int argc, char const *argv[])
{
	/* code */
	char *content;
	long f_size;
	char *filepath="1.txt";
	struct sysntax_state state;

	f_size = file_size(filepath);
	if(f_size==-1){
		return 1;
	}
	content = (char *)malloc(f_size);
	if(content==NULL){
		printf("assign fail\n");
		return 1;
	}
	read_file(filepath,content,f_size);
	//printf("%s\n", content);

	/*
	逻辑处理code
	 */
	
	
	state = check(content);
	free(content);
	printf("\n(%d %d) {%d %d} [%d %d]\n", state.leftparens,state.rightparnes,state.leftbrace,state.rightbrace,state.leftsquare,state.rightsquare);
	return 0;
}

void sysntax_state_init(struct sysntax_state *state){
	memset(state,0,sizeof(struct sysntax_state));
}

struct sysntax_state check(char *s){
	struct sysntax_state state;
	sysntax_state_init(&state);
	int pos = state.pos;
	int quote = 0;
	int comment=0; //注释符号
	while(*(s+pos)!='\0'){
		//printf("%c:%d ",*(s+pos),pos);
		if(*(s+pos)=='"' && quote==0){
			quote=1;
			pos++;
			continue;
		}else if(*(s+pos)=='"' &&quote==1){
			//转移
			if(*(s+pos-1)=='\\'){
				pos++;
				continue;
			}
			quote = 0;
			pos++;
			continue;
		}else if(*(s+pos)=='/' && *(s+pos+1)=='*'&&comment==0){
			comment = 1;
			pos +=2;
			continue;
		}else if(*(s+pos)=='*' &&*(s+pos+1)=='/' && comment==1){
			comment = 0;
			pos +=2;
			continue;
		}else if(*(s+pos)=='('&& comment==0){
			state.leftparens++;
			pos++;
			continue;
		}else if(*(s+pos)==')' && comment==0){
			state.rightparnes++;
			pos++;
			continue;
		}else if(*(s+pos)=='{' && comment==0){
			state.leftbrace++;
			pos++;
			continue;
		}else if(*(s+pos)=='}' && comment==0){
			state.rightbrace++;
			pos++;
			continue;
		}else if(*(s+pos)=='[' && comment==0){
			state.leftsquare++;
			pos++;
			continue;
		}else if(*(s+pos)==']' && comment==0){
			state.rightsquare++;
			pos++;
			continue;
		}else{
			pos++;
		}
	}
	return state;

}

/*
 * 获取文件大小
 */
long file_size(char *filepath){
	long size;
	FILE *fp = fopen(filepath,"r");
	if(fp==NULL){
		printf("open file fail!!!\n");
		return -1;
	}
	fseek(fp,0,SEEK_END);  //将指针指向文件末尾
	size = ftell(fp);  //获取文件内容长度
	//printf("%ld\n",size);
	fclose(fp);
	return size;
}

/*
* 获取文件内容
*/
int read_file(char *filepath, char *contents,long s_len){
	char *str;

	FILE *fp = fopen(filepath,"r");
	if(!fp){
		printf("Not open file\n");
		return 0;
	}

	str = (char *)calloc(s_len,sizeof(char));
	fread(str,sizeof(char),s_len,fp);

	strncpy(contents,str,s_len);
	fclose(fp);
	return 1;
}