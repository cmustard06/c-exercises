typedef struct HashTable HashTable;


#ifdef __cplusplus
extern "C"{
#endif
	//新建一个hash表实例
	HashTable* hash_table_new();

	//删除一个hash表实例,所有值都是自动删除的。
	void hash_table_delete(HashTable *ht);

	//向hash表中增加或者更新一个值,当这个值被删除时，free_value()函数将会自动被回调
	#define hash_table_put(ht,key,value) hash_table_put2(ht,key,value,NULL)
	int hash_table_put2(HashTable *ht, char *key,void *value,void(*free_vlaue)(void *));

	//通过键得到一个值，如果没有找到就返回NULL
	void *hash_table_get(HashTable *ht,char *key);

	//通过键删除一个值
	void hash_table_rm(HashTable *ht,char *key);
	


#ifdef __cplusplus
}
#endif