//
// Created by volun on 2019-10-12.
//

#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H

#include "header.h"
#include "picosha2.h"
//#include "fun.cpp"


class block {
private:
    string blockHash;

    string prevHash;
    time_t timestamp;
    unsigned int version;
    string merkelTreeHash;
    unsigned long nonce;
    int dificultyTarget;


    vector<Transaction> transactions;



public:

    block(){
        /*this -> blockHash='0';
        this -> prevHash='0';
        this -> timestamp= time(0);
        this -> version='0';
        this -> merkelTreeHash='0';
        this -> nonce=0;
        this -> dificultyTarget='0';
        vector<Transaction> transac;
        Transaction TR;
        TR.amount=2;
        TR.from="JOHN";
        TR.to="MARK";
        transac.push_back(TR);
        this -> transactions.push_back(TR);*/
        //cout << "constructor" << endl;
        /*cout << blockHash << " " << prevHash << " " << timestamp << " " << version << " " << merkelTreeHash << " "
             << nonce << " " << dificultyTarget << " " << transactions[0].from  << " " << transactions[0].to << " "
             << transactions[0].amount  << endl;*/
        //printf("\nInitializing Block: %d ---- Hash: %s \n", version,blockHash.c_str());
    }
    block(const block &B2)
    {
        blockHash=B2.blockHash;
        prevHash=B2.prevHash;
        timestamp=B2.timestamp;
        version=B2.version;
        merkelTreeHash=B2.merkelTreeHash;
        nonce=B2.nonce;
        dificultyTarget=B2.dificultyTarget;
        transactions=B2.transactions;
    }
    ~block() { /*cout << "destructor" << endl;*/};

    string getBlockHash(){
        return blockHash;
    }
    string getPrevHash(){
        return prevHash;
    }
    time_t getTimestamp(){
        tm *ltm = localtime(&timestamp);
        cout << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << "  " << ltm->tm_hour << ":"
             << ltm->tm_min << ":" << ltm->tm_sec << endl;

        return true;
    }
    unsigned int getVersion(){
        return version;
    }
    string getMerkelTreeHash(){
        return merkelTreeHash;
    }

    unsigned long getNonce() {
        return nonce;
    }
    double getDificultyTarget(){
        return dificultyTarget;
    }
    void getTransactions() {
        cout << "There are : " << transactions.size()  << " transactions in this block" << endl;

        for(auto &vec:transactions)
        {
            cout << vec.Thash << endl;
        }

    }

    void setPrevHash(string text){
        prevHash=text;
    }
    void setVersion(int v)
    {
        this -> version= v;
    }
    void setBlockHash()
    {
        string prehash;
        int t=timestamp;
        prehash= prevHash + merkelTreeHash + std::to_string(version) + std::to_string(t) + std::to_string(nonce)
                + std::to_string(dificultyTarget);
        blockHash=stolenHash(prehash);
        blockHash=stolenHash(blockHash);
    }
    void setTimestamp()
    {
        timestamp=time(0);
    }
    void setMerkelTreeHash()
    {
        vector<string> hashes;
        string h;

        for(int i=0;i<transactions.size();i++)
        {

            hashes.push_back(transactions[i].Thash);
        }


        while(hashes.size() !=1)
        {
            if(hashes.size()%2 != 0)
            {
                h=hashes.back();

                hashes.push_back(h);
            }
            int j=0;
            for(int i=0;i<hashes.size();i=i+2)
            {
                hashes[j]= hashes[i] + hashes[i+1];
                hashes[j]=stolenHash(hashes[j]);
                j++;
            }
            if(hashes.size()!=1)
            {
                hashes.resize(hashes.size()/2);
            }

        }
        merkelTreeHash=hashes[0];
        setTimestamp();

    }
    void Ttesting(vector<Transaction> &tra, vector<Userdata> user)
    {
        for(int i=0;i<tra.size();i++)
        {

            for(int j=0;j<user.size();j++)
            {
                if(tra[i].from == user[j].name)
                {
                    if(tra[i].amount >= user[j].balance)
                    {
                        tra.erase(tra.begin()+i+1);
                        tra.resize(tra.size()-1);
                        i--;
                        break;
                    }
                }
            }
        }
    }
    void setTransactions(vector<Transaction> tra, vector<Userdata> user)
    {
        transactions=tra;
        for(int i=0;i<transactions.size();i++)
        {
            transactions[i].Thash=transactions[i].from + std::to_string(transactions[i].amount) + transactions[i].to;
            transactions[i].Thash=stolenHash(transactions[i].Thash);
            transactions[i].Thash=stolenHash(transactions[i].Thash);
            tra[i].Thash=tra[i].from + std::to_string(tra[i].amount) + tra[i].to;
            tra[i].Thash=stolenHash(tra[i].Thash);
            tra[i].Thash=stolenHash(tra[i].Thash);
            if(tra[i].Thash != transactions[i].Thash)
            {
                transactions.erase(transactions.begin()+i+1);
            }
        }
        if(transactions.size()==0)
        {
            Transaction tr;
            tr.from=user[1].name;
            tr.to=user[2].name;
            tr.amount=1;
            transactions.push_back(tr);
            tr.from=user[3].name;
            tr.to=user[4].name;
            tr.amount=3;
            transactions.push_back(tr);
        }

        setTimestamp();

    }

    void createGenesis()
    {
        prevHash="0000000000000000000000000000000000000000000000000000000000000000";
        timestamp=time(0);
        version=0;
        dificultyTarget=0;
    }
    void proofOfWork()
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> ran(1,10);
        dificultyTarget=rand() % 10 + 1;

        string hashednonce;
        //dificultyTarget=3;

        for(unsigned long i=0;i<4294967294;i++)
        {
            int imp=0;

            hashednonce=picosha2::hash256_hex_string(std::to_string(i));
            hashednonce=picosha2::hash256_hex_string(hashednonce);
            for(int j=0;j<dificultyTarget;j++)
            {

                string t=hashednonce;
                t=t[j];
                if(t.find_first_not_of( "0123456789" ) == std::string::npos)
                {

                    int temp = std::stoi(t);

                    if(temp==0)
                    {
                        imp++;
                    }
                }

            }

            if(imp==dificultyTarget)
            {
                nonce=i;
                break;
            }
            if(i==4294967290)
            {
                i=0;
                dificultyTarget=ran(rng);


            }
        }
        setTimestamp();
    }


};

void fillBlocks(vector<block> &Blockchain, vector<Transaction> &transac, vector<Userdata> &user);

#endif //BLOCKCHAIN_BLOCK_H
