#include<stdio.h>
/*
以每行一个单词的形式打印其输入
 */


int main(int argc, char const *argv[])
{
	/* code */
	
	char c;
	int idle = 0; //不在单词的范围内

	while((c=getchar())!=EOF){
		if(c>='a'&&c<='z'||c>='A'&&c<='Z'){
			if(idle==0){
				printf("%c",c);
			}
			else if(idle==1){  //从非单词区域进入下一个单词的第一个字母  
				printf("\n%c",c); //先换行以与上一个单词分开
				idle=0;
			}
		}else if(c==' '||c=='\t'){
			idle = 1; //进入非单词区域
			continue;
		}else if(c=='\n'){ //结束
			return 0;
		}
	}

	return 0;
}