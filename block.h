//
// Created by volun on 2019-10-12.
//

#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H

#include "header.h"

struct Transaction
{
    string from;
    string to;
    double amount;
};
class block {
private:
    string blockHash;

    string prevHash;
    time_t timestamp;
    unsigned int version;
    string merkelTreeHash;
    unsigned int nonce;
    double dificultyTarget;


    vector<Transaction> transactions;



public:
    block(){
        this -> blockHash='0';
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
        this -> transactions.push_back(TR);
        printf("\nInitializing Block: %d ---- Hash: %s \n", version,blockHash.c_str());
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

    unsigned getNonce() {
        return nonce;
    }
    double getDificultyTarget(){
        return dificultyTarget;
    }
    vector<Transaction> getTransactions() {
        return transactions;
    }

    void setVersion(int v)
    {
        this -> version= v+1;
    }
    void setBlockHash()
    {
        string prehash;
        int t=timestamp;
        prehash= prevHash + merkelTreeHash + std::to_string(version) + std::to_string(t) + std::to_string(nonce)
                + std::to_string(dificultyTarget);
        //blockHash=homemadeHash(prehash);
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
            h=transactions[i].from + std::to_string(transactions[i].amount) + transactions[i].to;
            //h=homeMadeHash(h);
            hashes.push_back(h);
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
                //hashes[j]=homeMadeHash(hashes[j]);
                j++;
            }
            if(hashes.size()!=1)
            hashes.resize(j+1);

        }
        merkelTreeHash=hashes[0];

    }












};


#endif //BLOCKCHAIN_BLOCK_H
