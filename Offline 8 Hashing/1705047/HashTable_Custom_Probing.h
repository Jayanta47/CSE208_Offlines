#ifndef HashTable_Custom_Probing

class HashCustomProbing
{
    vector<pair<string, int>> *hashTable;
    set<int> unique_keys;
    int collision_count;
    int probes_count;
    int unique_count;
    int Count;

    int table_size;
    bool activeKey1;
    int hashIndex, hashIndexAux;

    int C1, C2;
    int Hash1(string key);
    int Hash2(string key);
    int auxHash(string key);

public:
    void setHashIndices(string key);
    int customProbeIndex(int iter);
    HashCustomProbing(int table_size = 10000, int C1 = 13, int C2 = 19);
    bool Insert(string key);
    int SearchIndex(string searchKey);
    void Delete(string deleteKey);
    void activateHashFunc(int option);
    void resetAll();
    int collisionCount() {return this->collision_count;}
    int uniqueCount() {return this->unique_count;}
    int insertedElemsCount() {return this->Count;}
    int probesCount(){return this->probes_count;}
    int generatedUKeys() {return this->unique_keys.size();}
};

int HashCustomProbing::Hash1(string key) // polynomial rolling hash function
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
    return (int)hash_index;
}



int HashCustomProbing::Hash2(string key) //sdbm
{
    long long int hash_index = 0;
    long long int m = 10007;
    for( char ch:key )
    {
        hash_index = (ch-'a') + (hash_index << 6) + ((hash_index << 16) - hash_index)%m;
        hash_index = hash_index%m;
    }
    return (int)(hash_index);
}

int HashCustomProbing::auxHash(string key) //djb2
{
    long long int hash_index = 13;
    int m = 10007;
    for(auto c:key)
    {
        hash_index = ((hash_index << 5) + hash_index) + (c-'a');
        hash_index = hash_index%m;
    }

    return (int)(hash_index);
}

HashCustomProbing::HashCustomProbing(int table_size, int C1, int C2)
{
    this->table_size = table_size;
    hashTable = new vector<pair<string, int>>(this->table_size, make_pair("", -1));
    this->activeKey1 = true;
    this->Count = 0;
    this->collision_count = 0;
    this->probes_count = 0;
    this->hashIndex = 0;
    this->hashIndexAux = 0;
    this->unique_count = 0;
    this->C1 = C1;
    this->C2 = C2;
}

void HashCustomProbing::activateHashFunc(int option)
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

void HashCustomProbing::setHashIndices(string key)
{
    if (activeKey1)
    {
        this->hashIndex = Hash1(key);
    }
    else
    {
        this->hashIndex = Hash2(key);
    }

    this->hashIndexAux = auxHash(key);
}

int HashCustomProbing::customProbeIndex(int iter)
{
    return (int)((this->hashIndex + (iter * this->hashIndexAux * 1ll * this->C1)%table_size + iter*iter*this->C2)%table_size);
}


int HashCustomProbing::SearchIndex(string searchKey)
{
    int iter = 0;
    this->setHashIndices(searchKey);
    int hashIndex = customProbeIndex(iter);

    while (hashTable->at(hashIndex).first != searchKey)
    {
        if (hashTable->at(hashIndex).second == -1) return -1;
        iter++;
        hashIndex = customProbeIndex(iter);
    }
    this->probes_count += (iter+1);
    return hashIndex;

}


bool HashCustomProbing::Insert(string key)
{
    if (this->Count == this->table_size)
    {
        return false;
    }

    int iter=0, index;

    this->setHashIndices(key);

    this->unique_keys.insert(this->customProbeIndex(0)); // To know the number of unique keys hash function is generating

    while(true)
    {
        index = this->customProbeIndex(iter);

        if (hashTable->at(index).first == key) return false;

        if (hashTable->at(index).second == -1)
        {
            this->Count++;
            hashTable->at(index) = make_pair(key, this->Count);
            this->collision_count += iter;
            if(iter==0) this->unique_count++;

            return true;
        }

        iter ++;

        if(iter >= this->table_size) return false;
    }
}


void HashCustomProbing::Delete(string deleteKey)
{
    int index = this->SearchIndex(deleteKey);
    if (index == -1)
    {
        cout<<"String Key '"<<deleteKey<<"' not found"<<endl;
        return;
    }
    hashTable->at(index) = make_pair("", -1);
}

void HashCustomProbing::resetAll()
{
    delete hashTable;
    hashTable = new vector<pair<string, int>>(this->table_size, make_pair("", -1));
    this->activeKey1 = true;
    this->Count = 0;
    this->collision_count = 0;
    this->probes_count = 0;
    this->hashIndex = 0;
    this->hashIndexAux = 0;
    this->unique_count = 0;
    this->unique_keys.clear();
}
#endif // HashTable_Custom_Probing
