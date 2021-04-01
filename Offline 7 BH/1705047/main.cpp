# include<bits/stdc++.h>
# include "BinomialHeap.h"
using namespace std;


void split(const string& str, vector<string>& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         std::back_inserter(cont));
}


int stringToIntConverter(string s)
{
    stringstream stoiC(s);
    int retValue;
    stoiC>>retValue;
    return retValue;
}


void IOparser(BinomialHeap *H, string inputFileName, string outputFileName="output.txt")
{
    bool writeToFile = false;
    cout<<"Specify Output methods:"<<endl;
    cout<<"1. File"<<endl;
    cout<<"2. Console"<<endl;
    int ch;
    cin>>ch;
    if (ch == 1)
    {
        writeToFile = true;
    }
    else if (ch > 2 || ch < 1)
    {
        cout<<"Invalid Choice of Output Method\nReturning To main..."<<endl;
    }

    cout<<"Reading From File : '"<<inputFileName<<"'"<<endl;
    cout<<"Parsing Commands ... "<<endl;

    if (writeToFile)
    {
        cout<<"Writing outputs into File - Filename : '"<<outputFileName<<"'"<<endl;
    }
    else
    {
        cout<<"\n-------------------------------------------------------------"<<endl;
        cout<<"Output Log:"<<endl;
        cout<<"-------------------------------------------------------------"<<endl<<endl;
    }

    clock_t now;

    ifstream infile(inputFileName);
    ofstream outfile(outputFileName);
    string Command; int value; string line;

    now = clock();
    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            vector<string> split_v;
            split(line, split_v);
            Command = split_v[0];
            if (Command == "I")
            {
                value = stringToIntConverter(split_v[1]);
                H->Insert(value);
            }
            else if (Command == "P")
            {
                if (writeToFile)
                {
                    outfile<<"Printing Binomial Heap...\n";
                    ofstream *fileptr = &outfile;
                    H->print(fileptr);
                }
                else
                {
                    cout<<"Printing Binomial Heap..."<<endl;
                    H->print();
                }
            }
            else if (Command == "U")
            {
                vector<int> keyList;
                for(int i=1; i < split_v.size(); i++)
                {
                    keyList.push_back(stringToIntConverter(split_v[i]));
                }
                H->Union(keyList);
            }
            else if (Command == "E")
            {
                BinomialNode *minNode = H->ExtractMin();
                string minKey;
                if (minNode == nullptr)
                {
                    minKey = "Null Pointer";
                }
                else
                {
                    minKey = to_string(minNode->Key());
                }

                if (writeToFile)
                {
                    outfile<<"Extract-Min returned "<<minKey<<"\n";
                }
                else
                {
                    cout<<"Extract-Min returned "<<minKey<<endl;
                }
            }
            else if (Command == "F")
            {
                BinomialNode *minNode = H->FindMin();
                string minKey;

                if (minNode == nullptr)
                {
                    minKey = "Null Pointer";
                }
                else
                {
                    minKey = to_string(minNode->Key());
                }

                if (writeToFile)
                {
                    outfile<<"Find-Min returned "<<minKey<<"\n";
                }
                else
                {
                    cout<<"Find-Min returned "<<minKey<<endl;
                }
            }
            else
            {
                cout<<"Invalid Argument Read From File.\nReturning..."<<endl;
                return;
            }
        }

    }
    infile.close();
    if (writeToFile)
    {
        cout<<"Output written to File Successfully."<<endl;
    }
    cout<<"\n-------------------------------------------------------------"<<endl;
    cout<<"Total Time for Parsing and Generating Output : "
        <<1000.0*(clock() - now)/double(CLOCKS_PER_SEC)<<" millisecond(s)"<<endl;
    cout<<"-------------------------------------------------------------"<<endl;
    outfile.close();
}

int main()
{
    BinomialHeap *H = new BinomialHeap();

    IOparser(H, "input_5.txt", "output_5.txt");

///    To Generate Multiple output files...
//    for(int i=0; i < 11; i++)
//    {
//        BinomialHeap *H = new BinomialHeap();
//        string infile = "in" + to_string(i) + ".txt";
//        string outfile = "out"+to_string(i) + ".txt";
//        IOparser(H, infile, outfile);
//    }
}


