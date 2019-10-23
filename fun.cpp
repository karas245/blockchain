//#include "header.h"
//#include "picosha2.h"
#include "Blockchain.h"

string stolenHash(string text)
{
    return picosha2::hash256_hex_string(text);
}
void generate(vector<Userdata> &user)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> ran(4,11);
    string ABC="AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
    std::uniform_int_distribution<std::mt19937::result_type> rand(0,52);
    std::uniform_real_distribution<double> randA(100,1000000);

    for(int j=0;j<1000;j++)
    {
        Userdata temp;
        string nick="";
        for(int i=0;i<ran(rng);i++)
        {
            nick+=ABC[rand(rng)];

        }
        nick+="_";
        for(int i=0;i<ran(rng);i++)
        {
            nick+=ABC[rand(rng)];
        }
        temp.name=nick;
        temp.hash=stolenHash(nick);
        temp.balance=randA(rng);
        user.push_back(temp);
    }
    //cout << user[3].name << " " << user[3].hash << " " << user[3].balance << endl;
    vector<Transaction> transac;
    Transaction tempor;
    std::uniform_int_distribution<std::mt19937::result_type> randU(0,1000);
    std::uniform_real_distribution<double> randAmount(1,10000);

    for(int i=0;i<10000;i++)
    {
        //transac.push_back(Transaction);
        tempor.from=user[randU(rng)].name;
        tempor.to=user[randU(rng)].name;
        if(tempor.to == tempor.from)
        {
            tempor.from=user[randU(rng)].name;
        }
        if(tempor.to == tempor.from)
        {
            tempor.from=user[randU(rng)].name;
        }
        tempor.amount=randAmount(rng);
        transac.push_back(tempor);
        //cout << transac[i].from << " " << transac[i].to << " = " << transac[i].amount << endl;
    }

    vector<block> Blockchain;//Blockchain.push_back(block());
    //Blockchain[0].createGenesis();
    //Blockchain blockchain;
    int count=0;
    vector<Transaction> tra;
    int index=0;
    string text="0000000000000000000000000000000000000000000000000000000000000000";
    for(int i=0;i<10000;i++)
    {

        //cout << "working" << endl;
        tra.push_back(transac[i]);
        //cout << transac[i].from << " " << transac[i].to << " = " << transac[i].amount << endl;

        if(i%100==99 && i!=0)
        {   //cout << i << " " << transac[i].amount << endl;
            //blockchain.blocks.push_back(block());
            //blockchain.blocks[count].setTransactions(tra);

            //if(i!=100)

            Blockchain.push_back(block());
            if(count==0)
            {
                Blockchain[0].createGenesis();
            }
            Blockchain[count].setTransactions(tra);
            Blockchain[count].proofOfWork();
            Blockchain[count].setVersion(count);
            Blockchain[count].setPrevHash(text);
            Blockchain[count].setBlockHash();
            text=Blockchain[count].getBlockHash();

            count++;
            //Blockchain.push_back(block());
            //tra.erase(tra.begin(), tra.end());
            tra.clear();
            //cout << "----" << tra.size() << endl;
            //tra.resize(0);
        }
    }


    for(int i=0;i<Blockchain.size();i++)
    {
        Blockchain[i].setMerkelTreeHash();
        //cout << Blockchain[i].getMerkelTreeHash() << " -*-*-" << i << endl;
        //cout << Blockchain[i].getTransactions() << endl;
    }
    //cout << Blockchain[99].getTransactions() << endl;

   /* for(int i=0;i<Blockchain.size();i++)
    {
        Blockchain[i].proofOfWork();
    }*/

    //cout << " *****************************" << endl;
    //Blockchain[0].proofOfWork();




}
