#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/wait.h>
#include<error.h>
#define PATHNAME "."
#define PROJ_ID 0

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *arry;
	struct seminfo *__buf;
};

//信号量的创建还是获取在于semget函数参数flag的设置
static int CommSemid(int nums,int flag);

//创建信号量
int CreateSemid(int nums);

//获取已经创建的信号量
int GetSemid(int nums);

//初始化信号量
int InitSemid(int semid,int which,int _val);

//PV操作在于它的_op的值
static int SemPV(int semid,int which,int _op);

//P操作，wait操作
int P(int semid,int which,int _op);

//V操作
int V(int semid,int which,int _op);

//销毁信号量
int Destory(int semid);
