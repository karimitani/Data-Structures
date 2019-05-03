typedef struct HashTableE {
	const char *key;
	void *data;
} HashTableE;

class HashTable {
	HashTableE **buckets;
	int size;
	int currSize;
	int hash(const char *key);	
	void rehash();
	
	public:
		HashTable();
		~HashTable();
		bool insert(const char *key, void *data);
		bool remove(const char *key);
};
