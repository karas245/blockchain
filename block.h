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
    string prevHash;
    double timestamp;
    int version;
    string merkelTreeHash;
    int nonce;
    int dificultyTarget;

    vector<Transaction> transactions;



public:
    block(int prevHash, double timestamp,string version, string merkelTreeHash,int nonce,int dificultyTarget, string from,
            string to, double amount, vector<Transaction> transactions);

    string getPrevHash(){
        return prevHash;
    }
    double getTimestamo(){
        return timestamp;
    }
    int getVersion(){
        return version;
    }
    string getMerkelTreeHash(){
        return merkelTreeHash;
    }
    int getNonce() {
        return nonce;
    }
    int getDificultyTarget(){
        return dificultyTarget;
    }
    vector<Transaction> getTransactions() {
        return transactions;
    }










};


#endif //BLOCKCHAIN_BLOCK_H
