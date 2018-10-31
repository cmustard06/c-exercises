#include<stdio.h>
#include<string.h>

typedef int bool;
#define false 0
#define true !false

//系统中所有进程数量
#define PROCESSES_NUMBER 5
//现有资源
typedef struct {
	int A;
	int B;
	int C;
	int D;
}RESOURCE;

//最大需求矩阵 Max
RESOURCE Max[PROCESSES_NUMBER]={
	{4,1,1,1},
	{0,2,1,2},
	{4,2,1,0},
	{1,1,1,1},
	{2,1,1,0}
};

//已经分配的资源数量 Allocation
RESOURCE Allocation[PROCESSES_NUMBER]={
	{3,0,1,1},
    {0,1,0,0},
    {1,1,1,0},
    {1,1,0,1},
    {0,0,0,0}
};

//还需要的资源矩阵
RESOURCE Need[PROCESSES_NUMBER]={
	{1,1,0,0},
	{0,1,1,2},
	{3,1,0,0},
	{0,0,1,0},
	{2,1,1,0}
};

//可用资源向量
RESOURCE Available = {1,0,2,0};
//安全序列
int safe[PROCESSES_NUMBER];


//试探分配
void ProbAlloc(int process,RESOURCE *res){

	//可用的资源减去需要的资源
	Available.A -= res->A;
	Available.B -= res->B;
	Available.C -= res->C;
	Available.D -= res->D;

	//将从上面获取的资源进行分配
	Allocation[process].A += res->A;
	Allocation[process].B += res->B;
	Allocation[process].C += res->C;
	Allocation[process].D += res->D;

	//分配完成后，进程需要的资源就会减少
	Need[process].A -= res->A;
	Need[process].B -= res->B;
	Need[process].C -= res->C;
	Need[process].D -= res->D;
}

//检查安全性
bool SafeCheck(){
	//可用于工作的资源
	RESOURCE Work = Available;
	//初始化那些进程能获取到资源
	bool Finish[PROCESSES_NUMBER] = {false,false,false,false,false};
	int i;
	int j=0;
	for(i=0;i<PROCESSES_NUMBER;++i){
		//对进程是否已经检测过
		if(Finish[i]==false){
			//是否还有足够的资源分配给该进程
			if(Need[i].A<=Work.A && Need[i].B<=Work.B && Need[i].C<=Work.C&&Need[i].D<=Work.D){
				//如果有足够的资源，就让其执行完成，并将已分配的资源回收
				Work.A += Allocation[i].A;
				Work.B += Allocation[i].B;
				Work.C += Allocation[i].C;
				Work.D += Allocation[i].D;
				Finish[i] = true;
				safe[j++]=i;
				i=-1; //重新遍历
			}
		}
	}
	//如果所有的进程的FInish向量都是true则处于安全状态，否则为不安全状态
	for(i=0;i<PROCESSES_NUMBER;i++){
		if(Finish[i]==false){
			return false;
		}
	}
	return true;
}

//若试探分配之后进入不安全状态，将会把已经分配的资源进行回滚
void RollBack(int process,RESOURCE *res){
	Available.A += res->A;
	Available.B += res->B;
	Available.C += res->C;
	Available.D += res->D;

	Allocation[process].A -= res->A;
	Allocation[process].B -= res->B;
	Allocation[process].C -= res->C;
	Allocation[process].D -= res->D;

	Need[process].A += res->A;
	Need[process].B += res->B;
	Need[process].C += res->C;
	Need[process].D += res->D;

}

//资源分配请求
bool request(int process,RESOURCE *res){
	//request向量需要小于Need矩阵中对应的向量
	if(res->A<=Need[process].A && res->B <= Need[process].B && res->C <= Need[process].C&& res->D <= Need[process].D){
		//request向量需要小于Available
		if(res->A<=Available.A&&res->B<=Available.B&&res->C<=Available.C&&res->D<=Available.D){
			//试探分配
			ProbAlloc(process,res);
			//如果安全检查成立，则请求成功，否则将分配回滚并返回失败
			if(SafeCheck()){
				return true;
			}else{
				printf("安全性检查失败，原因：系统将进入不安全状态，有可能引起死锁\n");
				printf("正在回滚...\n");
				RollBack(process,res);
			}
		}else{
			printf("安全性检查失败，原因：请求向量大于可利用资源向量\n");
		}
	}else{
		printf("安全检查失败，原因：请求向量大于需求向量\n");
	}
	return false;
}

void PrintTable(){
	printf("\t\t\t*********资源分配表*********\n");
    printf("Process       Max          Allocation          Need          Available\n");
    printf("          A    B    C    D     A    B    C    D      A    B    C    D     A    B    C   D\n");
    printf("  P0      %d    %d    %d    %d     %d    %d    %d    %d      %d    %d    %d    %d     %d    %d    %d   %d\n",Max[0].A,Max[0].B,Max[0].C,Max[0].D,Allocation[0].A,Allocation[0].B,Allocation[0].C,Allocation[0].D,Need[0].A,Need[0].B,Need[0].C,Need[0].D,Available.A,Available.B,Available.C,Available.D);
    printf("  P1      %d    %d    %d    %d     %d    %d    %d    %d      %d    %d    %d    %d\n",Max[1].A,Max[1].B,Max[1].C,Max[1].D,Allocation[1].A,Allocation[1].B,Allocation[1].C,Allocation[1].D,Need[1].A,Need[1].B,Need[1].C,Need[1].D);
    printf("  P2      %d    %d    %d    %d     %d    %d    %d    %d      %d    %d    %d    %d\n",Max[2].A,Max[2].B,Max[2].C,Max[2].D,Allocation[2].A,Allocation[2].B,Allocation[2].C,Allocation[2].D,Need[2].A,Need[2].B,Need[2].C,Need[2].D);
    printf("  P3      %d    %d    %d    %d     %d    %d    %d    %d      %d    %d    %d    %d\n",Max[3].A,Max[3].B,Max[3].C,Max[3].D,Allocation[3].A,Allocation[3].B,Allocation[3].C,Allocation[3].D,Need[3].A,Need[3].B,Need[3].C,Need[3].D);
    printf("  P4      %d    %d    %d    %d     %d    %d    %d    %d      %d    %d    %d    %d\n",Max[4].A,Max[4].B,Max[4].C,Max[4].D,Allocation[4].A,Allocation[4].B,Allocation[4].C,Allocation[4].D,Need[4].A,Need[4].B,Need[4].C,Need[4].D);
    printf("\n");
}

int main(){
	int ch;
	printf("先检查初始状态是否安全\n");

	if(SafeCheck()){
		printf("系统处于安全状态\n");
		printf("安全序列时{P%d,P%d,P%d,P%d,P%d}\n",safe[0],safe[1],safe[2],safe[3],safe[4]);
	}else{
		printf("系统处于不安全状态。程序将推出...\n");
		goto over;
	}

	do{
		int process;
		RESOURCE res;
		PrintTable();
		printf("请依次输入请求分配的进程和对四类资源的请求数量:\n");
		scanf("%d%d%d%d%d",&process,&res.A,&res.B,&res.C,&res.D);
		if(request(process,&res)){
			printf("分配成功\n");
			printf("安全序列时{P%d,P%d,P%d,P%d,P%d}\n",safe[0],safe[1],safe[2],safe[3],safe[4]);
		}else{
			printf("分配失败\n");
		}
		printf("是否继续分配(Y/N):");
		ch = getchar();
		ch = getchar();
	}while(ch=='Y'||ch =='y');
over:
	printf("执行完毕\n");
	return 0;
}