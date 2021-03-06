#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>

#define BUFF_SIZE 3
#define PRODUCE_THREAD_SIZE 5
int g_buff[BUFF_SIZE];
int g_write_index = 0;
int g_read_index = 0;

sem_t lock;
sem_t consume_sem,produce_sem;
/*
P操作表示申请一个资源，P操作的定义：S=S-1，
若S>=0，则执行P操作的线程继续执行；若S<0，
则置该线程为阻塞状态，并将其插入阻塞队列。

V操作表示释放一个资源，V操作定义：S=S+1，
若S>0则执行V操作的线程继续执行；
若S<0，则从阻塞状态唤醒一个线程，并将其插入就绪队列
 */
void *produce(void *ptr){
	int idx = *(int*)ptr;
	
	//使用hasnsen模式 while 形式
	while(1){
		sem_wait(&produce_sem);//限制了生产者的并发数目,p操作
		sem_wait(&lock); //对临界区的访问要加锁
		sleep(2);
		printf("in produce idx=%d g_write_index=%d g_read_index=%d\n", idx,g_write_index,g_read_index);
		g_buff[g_write_index] = idx;
		g_write_index = (g_write_index+1)%BUFF_SIZE;
		sem_post(&lock); //V操作
		sem_post(&consume_sem);
	}
	return NULL;
}

void * consume(void *ptr){
	while(1){
		sem_wait(&consume_sem);
		sem_wait(&lock);
		int data = g_buff[g_read_index];
		sleep(1);
		g_read_index = (g_read_index+1)%BUFF_SIZE;
		printf("consume data=%d g_read_index=%d g_write_index=%d\n",data,g_read_index,g_write_index );
		sem_post(&lock);
		sem_post(&produce_sem);
	}
	return NULL;
}

int main(int argc, char *argv[]){
	pthread_t con;
	pthread_t pros[PRODUCE_THREAD_SIZE];
	/*int sem_init (sem_t *sem, int pshared, unsigned int value);
       这个函数的作用是对由sem指定的信号量进行初始化，设置好它的共享选项，并
       指定一个整数类型的初始值。pshared参数控制着信号量的类型。如果 pshared的值是０，
       就表示它是当前进程的局部信号量；否则，其它进程就能够共享这个信号量。我们现在只对不让进程共享的信号量感兴趣。　
       （这个参数 受版本影响）,pshared传递一个非零将会使函数调用失败。
       value给出了信号量的初始值。
    */
	sem_init(&lock,0,1);
	sem_init(&consume_sem,0,0);
	sem_init(&produce_sem,0,BUFF_SIZE);

	pthread_create(&con,NULL,consume,NULL);
	int thread_args[PRODUCE_THREAD_SIZE];
	for(int i=0;i<PRODUCE_THREAD_SIZE;i++){
		thread_args[i]=i+1;
		pthread_create(&pros[i],NULL,produce,(thread_args+1));
	}
	pthread_join(con,0);
	for(int i=0;i<PRODUCE_THREAD_SIZE;i++){
		pthread_join(pros[i],0);
	}
	sem_destroy(&lock);
	sem_destroy(&consume_sem);
	sem_destroy(&produce_sem);
	return 0;
}
