//
// Created by volun on 2019-10-12.
//

#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H

#include "header.h"
#include "picosha2.h"
//#include "fun.cpp"

struct Transaction
{
    string from;
    string to;
    double amount;
    string Thash;
};
class block {
private:
    string blockHash;

    string prevHash;
    time_t timestamp;
    unsigned int version;
    string merkelTreeHash;
    unsigned int nonce;
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

    unsigned getNonce() {
        return nonce;
    }
    double getDificultyTarget(){
        return dificultyTarget;
    }
    void getTransactions() {
        //cout << "/-**-*-*-*-*-*-*-" << transactions.size() << endl;
        for(int index=0;index<transactions.size();index++)
        {
            cout << transactions[index].Thash << endl;
            //cout << transactions[index].from << " " << transactions[index].to << " " << transactions[index].amount << endl;
        }

        //return transactions;
    }
    void setPrevHash(string text){
        prevHash=text;
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
            //transactions[i].Thash=transactions[i].from + std::to_string(transactions[i].amount) + transactions[i].to;
            //transactions[i].Thash=stolenHash(transactions[i].Thash);
            //transactions[i].Thash=stolenHash(transactions[i].Thash);
            //cout << transactions[i].Thash << endl;
            //h=transactions[i].Thash;

            hashes.push_back(transactions[i].Thash);
        }


        while(hashes.size() !=1)
        {
            //cout << hashes.size() << endl;
            if(hashes.size()%2 != 0)
            {
                h=hashes.back();

                hashes.push_back(h);
            }
            //cout << hashes.size() << endl;
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
    void setTransactions(vector<Transaction> tra)
    {
        transactions=tra;
        for(int i=0;i<transactions.size();i++)
        {
            transactions[i].Thash=transactions[i].from + std::to_string(transactions[i].amount) + transactions[i].to;
            transactions[i].Thash=stolenHash(transactions[i].Thash);
            transactions[i].Thash=stolenHash(transactions[i].Thash);
        }
        setTimestamp();
        /*for(int i=0;i<transactions.size();i++)
        {
            cout << transactions[i].from << " " << transactions[i].to << " = " << transactions[i].amount << endl;
        }*/
        //cout << transactions.size() << endl;
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
        std::uniform_int_distribution<std::mt19937::result_type> ran(1,3);
        dificultyTarget=ran(rng);
        string hashednonce;
        //dificultyTarget=3;
        //cout << dificultyTarget << " ------" << endl;
        for(unsigned long i=0;i<4294967294;i++)
        {
            int imp=0;
            //cout << "**" << i << endl;
            hashednonce=picosha2::hash256_hex_string(std::to_string(i));
            //hashednonce=picosha2::hash256_hex_string(hashednonce);
            for(int j=0;j<dificultyTarget;j++)
            {
                //cout << hashednonce[j] ;
                string t=hashednonce;
                t=t[j];
                if(t.find_first_not_of( "0123456789" ) == std::string::npos)
                {

                    int temp = std::stoi(t);
                    //cout << temp << "=" << hashednonce[j] << endl;
                    if(temp==0)
                    {
                        imp++;
                    }
                }



            }
            //cout << endl;
            //cout << "---" << imp << endl;
            if(imp==dificultyTarget)
            {
                nonce=i;
                //cout << " FOUND IT ***********************************" << endl;
                break;
            }
            if(i==4294967290)
            {
                i=0;
                dificultyTarget=ran(rng);
                //cout << " END " << endl;

            }
        }
        //cout << nonce << " ******************* " << endl;
        setTimestamp();
    }













};


#endif //BLOCKCHAIN_BLOCK_H
