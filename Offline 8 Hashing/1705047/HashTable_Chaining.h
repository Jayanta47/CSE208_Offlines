#ifndef Hash_Table_Chaining

class HashTableChaining
{
    vector<pair<string, int>> *hashTable;
    set<int> unique_keys;
    int collision_count;
    int probes_count;
    int unique_count;
    int Count;

    int table_size;
    bool activeKey1;

    int Hash1(string key);
    int Hash2(string key);

public:
    void setHashIndices(string key);
    HashTableChaining(int table_size = 10000);
    void Insert(string key);
    bool SearchIndex(string searchKey);
    void Delete(string deleteKey);
    void activateHashFunc(int option);
    int collisionCount() {return this->collision_count;}
    int uniqueCount() {return this->unique_count;}
    int insertedElemsCount() {return this->Count;}
    int probesCount(){return this->probes_count;}
    void resetAll();
    int generatedUKeys() {return this->unique_keys.size();}
};

int HashTableChaining::Hash1(string key) // polynomial rolling hash function
{
    int p = 31;
    int m = 10007;
    long long power = 1;
    long long hash_index = 0;

    for (int i = 0; i < key.length(); i++)
    {
        hash_index = (hash_index + (key[i] - 'a' + 1) * power) % m;
        power = (power * p) % m;
    }
    return (int)(hash_index%this->table_size);
}


int HashTableChaining::Hash2(string key) //sdbm
{
    long long int hash_index = 0;
    long long int m = 10007; // why prime?
    for( char ch:key )
    {
        hash_index = (ch-'a') + (hash_index << 6) + ((hash_index << 16) - hash_index)%m;;
        hash_index = hash_index%m;
    }
    return (int)(hash_index%this->table_size);
}


HashTableChaining::HashTableChaining(int table_size)
{
    this->table_size = table_size;
    hashTable = new vector<pair<string, int>>[this->table_size];
    this->activeKey1 = true;
    this->Count = 0;
    this->collision_count = 0;
    this->probes_count = 0;
    this->unique_count = 0;
}

void HashTableChaining::activateHashFunc(int option)
{
    if (option == 1)
    {
        activeKey1 = true;
    }
    else if (option == 2)
    {
        activeKey1 = false;
    }
}


bool HashTableChaining::SearchIndex(string searchKey)
{
    int iter = 0;
    int hashIndex;

    if (activeKey1)
    {
        hashIndex = Hash1(searchKey);
    }
    else
    {
        hashIndex = Hash2(searchKey);
    }

    for(int i=0; i<hashTable[hashIndex].size(); i++)
    {
        if (hashTable[hashIndex][i].first == searchKey)
        {
            this->probes_count+=(i+1);
            return true;
        }
    }

    return false;
}


void HashTableChaining::Insert(string key)
{
    int iter=0, index;
    if (activeKey1)
    {
        index = this->Hash1(key);
    }
    else
    {
        index = this->Hash2(key);
    }

    this->unique_keys.insert(index); // To know the number of unique keys hash function is generating

    if (hashTable[index].size() == 0)
    {
        this->unique_count++;
    }
    else
    {
        this->collision_count++;
    }

    hashTable[index].push_back(make_pair(key, this->Count));
    this->Count++;
}


void HashTableChaining::Delete(string deleteKey)
{
    int hash_index;
    if (activeKey1)
    {
        hash_index = this->Hash1(deleteKey);
    }
    else
    {
        hash_index = this->Hash2(deleteKey);
    }
    vector<pair<string, int>>:: iterator i;
    for(i = hashTable[hash_index].begin(); i!= hashTable[hash_index].end(); i++)
    {
        pair<string, int> p = *i;
        if (p.first == deleteKey) break;
    }
    if (i != hashTable[hash_index].end())
    {
        hashTable[hash_index].erase(i);
    }
}

void HashTableChaining::resetAll()
{
    delete hashTable;
    hashTable = new vector<pair<string, int>>[this->table_size];
    this->activeKey1 = true;
    this->Count = 0;
    this->collision_count = 0;
    this->probes_count = 0;
    this->unique_count = 0;
    this->unique_keys.clear();
}

#endif // Hash_Table_Chaining
