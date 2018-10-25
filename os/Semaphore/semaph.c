#include "semaph.h"

static int CommSemid(int nums,int flags){
	key_t _key = ftok(PATHNAME,PROJ_ID);
	if(_key>0){
		/*用来创建和访问一个信号量集
		1)第一个参数key是长整型（唯一非零），系统建立IPC通讯 （ 消息队列、 信号量和 共享内存） 时必须指定一个ID值。通常情况下，该id值通过ftok函数得到，由内核变成标识符，要想让两个进程看到同一个信号集，只需设置key值不变就可以。
		(2)第二个参数nsem指定信号量集中需要的信号量数目，它的值几乎总是1。=
		(3)第三个参数flag是一组标志，当想要当信号量不存在时创建一个新的信号量，可以将flag设置为IPC_CREAT与文件权限做按位或操作。 
		设置了IPC_CREAT标志后，即使给出的key是一个已有信号量的key，也不会产生错误。而IPC_CREAT | IPC_EXCL则可以创建一个新的，唯一的信号量，如果信号量已存在，返回一个错误。一般我们会还或上一个文件权限
		*/
		return semget(_key,nums,flags);
	}else{
		perror("CommSemid");
		return -1;
	}
}

int CreateSemid(int nums){
	return CommSemid(nums,IPC_CREAT|IPC_EXCL|0666);
}

int GetSemid(int nums){
	return CommSemid(nums,IPC_CREAT);
}

int Destory(int semid){
	/*
	 功能：用来控制信号量集。
	   函数原型：int semctl(int semid,int semnum,int cmd, ...);
            参数：
                    semid：由semget返回的信号集标识码；
                    semnum：信号集中信号量的序号；
            返回值：成功返回0；失败返回-1。
	*/
	if(semctl(semid,0,IPC_RMID)>0){
		return 0;
	}else{
		perror("Destory");
		return -1;
	}
}

int InitSem(int semid,int which,int _val){
	union semun _semun;
	_semun.val = _val;
	if(semctl(semid,which,SETVAL,_semun)<0){
		perror("InitSem");
		return -1;
	}
	return 0;
}

static int SemPV(int semid,int which,int _op){
	struct sembuf _sf;
	_sf.sem_num = which;
	_sf.sem_op = _op;
	_sf.sem_flg = 0;
	/**
	 *  功能：用来创建和访问一个信号量集。
            函数原型：int semop(int semid,struct sembuf *sops,unsigned nsops);
            参数：
                    semid：该信号量的标识码，即semget的返回值；
                    sops：指向一个结构数组的指针；
                    nsops：信号量的个数。
            返回值：成功返回0；失败返回-1

	 */
	return semop(semid,&_sf,1);
}

int P(int semid,int which,int _op){
	if(SemPV(semid,which,_op)<0){
		perror("P");
		return -1;
	}
	return 0;
}


int V(int semid,int which,int _op){
	if(SemPV(semid,which,_op)<0){
		perror("V");
		return -1;
	}
	return 0;
}