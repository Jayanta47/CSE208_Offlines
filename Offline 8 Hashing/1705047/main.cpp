#include<bits/stdc++.h>
using namespace std;
#include "HashTable_chaining.h"
#include "HashTable_Double_Hashing.h"
#include "HashTable_Custom_Probing.h"

set<string> WordGenerator(int wordsCount, int wordLength)
{
    set<string> ststr;
    while(ststr.size() != wordsCount)
    {
        string s = "";
        for(int j=0; j<wordLength; j++)
        {
            int letter = rand()%26;
            s += ('a' + letter);
        }
        ststr.insert(s);
    }
    return ststr;
}

vector<string> searchKeyGenerator(set<string> wordLib, int num)
{
    vector<int> indexSerial;
    for(int i=0; i<num; i++)
    {
        indexSerial.push_back(rand()%wordLib.size());
    }

    sort(indexSerial.begin(), indexSerial.end());

    vector<string> searchKeys;
    auto itr = wordLib.begin();
    int present = indexSerial[0];

    for(int i=0, j=0; i < wordLib.size(); i++, itr++)
    {
        if(i == present)
        {
            searchKeys.push_back(*itr);
            j++;
            present = indexSerial[j];
        }
    }
    return searchKeys;
}

void InsertionUtil(set<string> wordLib, int table_size=10000)
{
    cout<<"Hash Table Type: Chaining"<<endl;
    cout<<"......................................."<<endl;
    cout<<"Utilizing Hash Function 1"<<endl;
    cout<<"Starting Insertion..."<<endl;
    HashTableChaining *HC = new HashTableChaining(table_size);
    for (auto s: wordLib)
    {
        HC->Insert(s);
    }
    cout<<"Searching Keys..."<<endl<<endl;
    vector<string> searchKeys = searchKeyGenerator(wordLib, 100);

    for(auto s:searchKeys)
    {
        if(!HC->SearchIndex(s))
        {
            cout<<s<<" not found"<<endl;
        }
    }
    float avg_probe = (HC->probesCount()*1.0)/100.0;

    cout<<"Collision : "<<HC->collisionCount()<<" Unique Counts: "<<HC->uniqueCount()<<" Uniquely Generated Keys: "
        <<HC->generatedUKeys()<<" Avg Probes: "<<avg_probe<<"\nTotal Insertion: "<<HC->insertedElemsCount()<<endl<<endl;


    HC->resetAll();
    cout<<"Utilizing Hash Function 2"<<endl;
    cout<<"Starting Insertion..."<<endl;
    HC->activateHashFunc(2);

    for (auto s: wordLib)
    {
        HC->Insert(s);
    }
    cout<<"Searching Keys..."<<endl<<endl;
    for(auto s:searchKeys)
    {
        if(!HC->SearchIndex(s))
        {
            cout<<s<<" not found"<<endl;
        }
    }
    avg_probe = (HC->probesCount()*1.0)/100.0;
    cout<<"Collision : "<<HC->collisionCount()<<" Unique Counts: "<<HC->uniqueCount()<<" Uniquely Generated Keys: "
        <<HC->generatedUKeys()<<" Avg Probes: "<<avg_probe<<"\nTotal Insertion: "<<HC->insertedElemsCount()<<endl<<endl;

    cout<<"Hash Table Type: Double Hashing"<<endl;
    cout<<"......................................."<<endl;
    cout<<"Utilizing Hash Function 1"<<endl;
    cout<<"Starting Insertion..."<<endl;
    HashTableDoubleHashing *DH = new HashTableDoubleHashing(table_size);
    for (auto s: wordLib)
    {
        DH->Insert(s);
    }
    cout<<"Searching Keys..."<<endl<<endl;
    searchKeys = searchKeyGenerator(wordLib, 100);
    for(auto s:searchKeys)
    {
        if(DH->SearchIndex(s) == -1)
        {
            cout<<s<<" not found"<<endl;
        }
    }
    avg_probe = (DH->probesCount()*1.0)/100.0;

    cout<<"Collision: "<<DH->collisionCount()<<" Unique Counts: "<<DH->uniqueCount()<<" Uniquely Generated Keys: "
        <<DH->generatedUKeys()<<" Avg Probes: "<<avg_probe<<"\nTotal Insertion: "<<DH->insertedElemsCount()<<endl<<endl;
    DH->resetAll();
    cout<<"Utilizing Hash Function 2"<<endl;
    cout<<"Starting Insertion..."<<endl;
    DH->activateHashFunc(2);

    for (auto s: wordLib)
    {
        DH->Insert(s);
    }
    cout<<"Searching Keys..."<<endl<<endl;
    for(auto s:searchKeys)
    {
        if(DH->SearchIndex(s) == -1)
        {
            cout<<s<<" not found"<<endl;
        }
    }
    avg_probe = (DH->probesCount()*1.0)/100.0;
    cout<<"Collision: "<<DH->collisionCount()<<" Unique Counts: "<<DH->uniqueCount()<<" Uniquely Generated Keys: "
        <<DH->generatedUKeys()<<" Avg Probes: "<<avg_probe<<"\nTotal Insertion: "<<DH->insertedElemsCount()<<endl<<endl;


    cout<<"Hash Table Type: Custom Probing"<<endl;
    cout<<"......................................."<<endl;
    cout<<"Utilizing Hash Function 1"<<endl;
    cout<<"Starting Insertion..."<<endl;
    HashCustomProbing *CP = new HashCustomProbing(table_size);
    for (auto s: wordLib)
    {
        CP->Insert(s);
    }
    cout<<"Searching Keys..."<<endl<<endl;
    searchKeys = searchKeyGenerator(wordLib, 100);
    for(auto s:searchKeys)
    {
        if(CP->SearchIndex(s) == -1)
        {
            cout<<s<<" not found"<<endl;
        }
    }

    avg_probe = (CP->probesCount()*1.0)/100.0;
    cout<<"Collision: "<<CP->collisionCount()<<" Unique Counts: "<<CP->uniqueCount()<<" Uniquely Generated Keys: "
        <<CP->generatedUKeys()<<" Avg Probes: "<<avg_probe<<"\nTotal Insertion: "<<CP->insertedElemsCount()<<endl<<endl;

    CP->resetAll();
    cout<<"Utilizing Hash Function 2"<<endl;
    cout<<"Starting Insertion..."<<endl;
    CP->activateHashFunc(2);

    for (auto s: wordLib)
    {
        CP->Insert(s);
    }
    cout<<"Searching Keys..."<<endl<<endl;
    for(auto s:searchKeys)
    {
        if(CP->SearchIndex(s)==-1)
        {
            cout<<s<<" not found"<<endl;
        }
    }
    avg_probe = (CP->probesCount()*1.0)/100.0;
    cout<<"Collision: "<<CP->collisionCount()<<" Unique Counts: "<<CP->uniqueCount()<<" Uniquely Generated Keys: "
        <<CP->generatedUKeys()<<" Avg Probes: "<<avg_probe<<"\nTotal Insertion: "<<CP->insertedElemsCount()<<endl<<endl;

}

int main()
{
    srand(2);
    for(int i=0;i<1;i++)
    {
        set<string> wordLib = WordGenerator(10000, 7);
        cout<<"Iteration: "<<i+1<<endl;
        InsertionUtil(wordLib, 10007);
    }
}
