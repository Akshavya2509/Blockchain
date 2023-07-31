#include<ctime>
#include<vector>
#include<iostream>
using namespace std;

// Transaction Data
struct TransactionData
{
    double amount;
    string senderkey;
    string recieverkey;
    time_t timestamp;
};

// Block class
class Block
{
    private:
    int index;
    size_t blockhash;
    size_t previoushash;
    size_t generatehash();

    public:

    Block(int idx, TransactionData d, size_t prevhash);

    size_t gethash();

    size_t getprevioushash();

    TransactionData data;

    bool ishashvalid();
};

// Constructor

Block::Block(int idx, TransactionData d, size_t prevhash)
{
    index=idx;
    data=d;
    previoushash=prevhash;
    blockhash=generatehash();
}

size_t Block::generatehash()
{
    hash<string> hash1;
    hash<size_t> hash2;
    hash<size_t> finalhash;

    string tohash = to_string(data.amount) +data.recieverkey+data.senderkey+to_string(data.timestamp);

    return finalhash(hash1(tohash)+hash2(previoushash));
};

size_t Block::gethash()
{
    return blockhash;
}

size_t Block::getprevioushash()
{
    return previoushash;
}

bool Block::ishashvalid()
{
    return generatehash()==blockhash;
}

//Blockchain

class Blockchain
{
    private:
    Block creategenesisblock();

    public:

    vector<Block> chain;

    Blockchain();

    void addblock(TransactionData data);

    bool ischainvalid();

    Block *getlatestblock();
};

Blockchain::Blockchain()
{
    Block genesis = creategenesisblock();
    chain.push_back(genesis);
}

Block Blockchain::creategenesisblock()
{
    time_t current;
    TransactionData d;
    d.amount=0;
    d.recieverkey="None";
    d.senderkey="None";
    d.timestamp=time(&current);

    hash<int> hash1;
    Block genesis(0,d,hash1(0));
    return genesis;
}

Block *Blockchain::getlatestblock()
{
    return &chain.back();
}

void Blockchain::addblock(TransactionData d)
{
    int index = (int)chain.size()-1;
    Block newBlock(index, d, getlatestblock()->gethash());
}

bool Blockchain::ischainvalid()
{
    vector<Block>::iterator it;
    int chainlen=(int)chain.size();

    for(it=chain.begin(); it != chain.end(); it++)
    {
        Block currentblock=*it;
        if(!currentblock.ishashvalid())
        {
            return false;
        }

        if(chainlen>1)
        {
            Block previousBlock =*(it-1);
            if(currentblock.getprevioushash()!=previousBlock.gethash())
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    Blockchain TWSCCoin;

    TransactionData data1;

    time_t datatime;

    data1.amount=1.5;
    data1.recieverkey="Utkarsh Tripathi";
    data1.senderkey="Akshat Mehra";
    data1.timestamp=time(&datatime);

    TWSCCoin.addblock(data1);

    cout << "Is chain Valid?" << endl
    << TWSCCoin.ischainvalid() <<endl;

    TransactionData data2;

    time_t data2time;

    data2.amount=1.5;
    data2.recieverkey="Akshat Jaimini";
    data2.senderkey="Amit Goyal";
    data2.timestamp=time(&data2time);

    TWSCCoin.addblock(data2);

    cout << "Now is the chain valid?" << endl
    <<TWSCCoin.ischainvalid() << endl;
    
    Block *hackBlock = TWSCCoin.getlatestblock();
    hackBlock->data.amount=10000;
    hackBlock->data.recieverkey="Akshavya - From Crypto Enthusiasts";

    cout << "Now is the chain still valid ????" << endl;

    cout << TWSCCoin.ischainvalid() << endl;
}
