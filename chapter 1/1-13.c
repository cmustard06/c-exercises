#include<stdio.h>
#include<string.h>
#define MAXWORDS 200

/*
打印输入中单词长度的直方图(水平方向的)
1.确定一个单词
2.单词的长度
3.直方图
 */

void printHistogram(char *word,int length){
	int init = 0;
	if(length==0){
		return;
	}
	printf("%-15s: ",word);
	for(init=0;init<length;init++){
		printf(">");
	}
	printf("\n");
}


int main(int argc, char const *argv[])
{
	/* code */
	char c;
	char word[MAXWORDS];
	int al_num=0,word_internal = 0,index=0;


	while((c=getchar())!=EOF){
		if((c<='Z'&&c>='A')||(c<='z'&&c>='a')){
			if(word_internal==0){ //下一个单词
				printHistogram(word,al_num);
				al_num = 0;
				index = 0;
				//清空数组
				memset(word, 0, MAXWORDS);
			}
			word_internal = 1;
			al_num++;
			word[index] = c;
			index++;
			
		}else if(c==' '||c=='\t'){
			if(word_internal==1){
				word_internal = 0;
			}
			continue;
		}else if(c=='\n'){
			printHistogram(word,al_num);
		}
	}


	return 0;
}