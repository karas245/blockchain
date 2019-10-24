//
// Created by volun on 2019-10-12.
//

#ifndef BLOCKCHAIN_HEADER_H
#define BLOCKCHAIN_HEADER_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <random>
#include <sstream>
#include <iomanip>
//#include "block.h"




using std::cout;
using std::endl;
using std::string;
using std::vector;

struct Userdata
{
    string name;
    string hash;
    double balance;
};
struct Transaction
{
    string from;
    string to;
    double amount;
    string Thash;
};
string stolenHash(string text);
void StartBlockchain();
void generateUser( vector<Userdata> &user);
void generateTransactions(vector<Transaction> &transac, vector<Userdata> &user);



#endif //BLOCKCHAIN_HEADER_H
