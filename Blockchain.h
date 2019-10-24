//
// Created by volun on 2019-10-21.
//

#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H

#include "block.h"

class Blockchain {
public:
    vector<block> blocks;
    Blockchain() { blocks.push_back(block());};
    ~Blockchain() {};

};


#endif //BLOCKCHAIN_BLOCKCHAIN_H
