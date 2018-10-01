#include<stdio.h>

/*
打印输入中单词长度的直方图(垂直方向的)
1.确定一个单词
2.单词的长度
3.直方图
 */

#define MAXHIST 15 //直方图的最大长度
#define MAXWORD  11 //单词的最大长度
#define IN 1  //表示在单词内部
#define OUT 0 //表示在一个单词外部

int main(int argc, char const *argv[])
{
	int c,i,j,nc,state;
	int maxvalue; //存放w1[]中的最大值
	int overflow; //溢出字数

	int w1[MAXWORD];
	state = OUT;
	nc = 0; //单词中的字符数量
	overflow = 0;

	for(i=0;i<MAXWORD;i++){
		w1[i] = 0;
	}
	while((c=getchar())!=EOF){
		if(c==' ' ||c=='\t' ||c=='\n'){  //在单词外部
			state = OUT;
			if(nc>0){
				if(nc<MAXWORD){
					++w1[nc];  //
				}else{
					++overflow;
				}
			}
			nc = 0;
		}else if(state == OUT){
			state = IN;
			nc = 1;  //一个新单词的开始
		}else{
			++nc;  //正在单词的内部
		}
	}

	maxvalue = 0;
	for(i=1;i<MAXWORD;++i){
		if(w1[i]>maxvalue){
			printf("%d\n",w1[i]);
			maxvalue=w1[i];
		}
	}

	for(i=MAXHIST;i>0;--i){
		for(j=1;j<MAXWORD;++j){
			if(w1[j]*MAXHIST/maxvalue>=i){
				printf(" * ");
			}else{
				printf(" ");
			}
			putchar('\n');
		}
	}
	for(i=1;i<MAXWORD;++i){
		printf("%4d ",i);
	}
	putchar('\n');
	for(i=i;i<MAXWORD;++i){
		printf("%4d ",w1[i]);
	}
	putchar('\n');
	if(overflow>0){
		printf("There are %d words >=%d\n",overflow,MAXWORD);
	}
	return 0;
}


