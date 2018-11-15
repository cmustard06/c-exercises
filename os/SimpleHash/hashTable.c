#include "hashTable.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define TABLE_SIZE (1024*1024)

//hash表中的链表
struct kv
{
	struct kv *next;
	char *key;
	void *value;
	void(*free_value)(void*);
};

//HashTable
struct HashTable{
	struct kv **table;
};

//结构体kv的构造函数
static void init_kv(struct kv *kv){
	kv->next = NULL;
	kv->key = NULL;
	kv->value = NULL;
	kv->free_value = NULL;
}

//结构体kv的析构函数
static void free_kv(struct kv *kv){
	if(kv){
		if(kv->free_value){
			kv->free_value(kv->value);
		}
		free(kv->key);
		kv->key = NULL;
		free(kv);
	}
}


/*使用经典的times33hash函数*/
static unsigned int hash_33(char *key){
	unsigned int hash = 0;
	while(*key){
		hash = (hash<<5)+hash+*key++;
	}
	return hash;
}

/*新建一个hash表*/
HashTable *hash_table_new(){
	HashTable* ht = malloc(sizeof(HashTable));
	if(ht==NULL){
		hash_table_delete(ht);
		return NULL;
	}

	memset(ht->table,0,sizeof(struct kv*)*TABLE_SIZE);
	return ht;
}

/*删除一个hash表*/
void hash_table_delete(HashTable *ht){
	if(ht){
		if(ht->table){
			int i=0;
			for(i=0;i<TABLE_SIZE;i++){
				struct kv *p = ht->table[i]; //(*table)[]
				struct kv *q = NULL;
				while(p){  //从第一个节点开始删除
					q = p->next;
					free_kv(p);
					p=q;
				}
			}
			free(ht->table);
			ht->table = NULL; //重新初始化
		}
		free(ht); //释放整个空间
	}
}

/*插入或更新由key索引的值*/
int hash_table_put2(HashTable* ht, char* key, void* value, void(*free_value)(void*)){
	int i = hash_33(key)%TABLE_SIZE;
	struct kv *p=ht->table[i];
	struct kv *prep = p;

	while(p){
		/*如果键值已经存在，就更新值*/
		if(strcmp(p->key,key)==0){
			if(p->free_value){ //判断该函数是否被声明
				p->free_value(p->value); 
			}
			p->value = value; //修改值
			p->free_value = free_value;
			break;
		}
		prep = p;
		p = p->next;
	}

	/*如果没有找到就增加*/
	if(p==NULL){
		char *kstr = malloc(strlen(key)+1);
		if(kstr==NULL){
			return -1;
		}
		struct kv *kv = malloc(sizeof(struct kv));
		if(kv==NULL){
			free(kstr);
			kstr = NULL;
			return -1;
		}

		init_kv(kv);
		kv->next = NULL;  //尾部增加
		strcpy(kstr,key);
		kv->key = kstr;
		kv->value = value;
		kv->free_value = free_value;

		if(prep==NULL){
			ht->table[i]=kv;
		}else{
			prep->next = kv;
		}
	}
	return 0;
}

/*获取值*/
void *hash_table_get(HashTable *ht,char *key){
	int i = hash_33(key)%TABLE_SIZE;
	struct kv *p = ht->table[i];
	while(p){
		if(strcmp(key,p->key)==0){
			return p->value;
		}
		p = p->next;
	}
	return NULL;
}

/*删除值*/
void hash_table_rm(HashTable *ht,char *key){
	int i = hash_33(key)%TABLE_SIZE;
	struct kv *p = ht->table[i];
	struct kv *prep = p;
	while(p){
		if(strcmp(key,p->key)==0){
			free_kv(p);
			if(p==prep){
				ht->table[i] = NULL;
			}else{
				prep->next = p->next;
			}
		}
		prep = p;
		p = p->next;
	}
}


