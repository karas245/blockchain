//#include "header.h"
//#include "picosha2.h"
#include "Blockchain.h"

string stolenHash(string text)
{
    return picosha2::hash256_hex_string(text);
}
void generateUser( vector<Userdata> &user)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> ran(4,11);
    std::uniform_int_distribution<std::mt19937::result_type> rand(0,52);
    std::uniform_real_distribution<double> randA(100,1000000);
    string ABC="AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
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
}
void generateTransactions(vector<Transaction> &transac, vector<Userdata> &user)
{
    Transaction tempor;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randU(0,1000);
    std::uniform_real_distribution<double> randAmount(1,10000);

    for(int i=0;i<10000;i++)
    {

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

    }
}
void fillBlocks(vector<block> &Blockchain, vector<Transaction> &transac, vector<Userdata> &user)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    int count=0;
    vector<Transaction> tra;
    vector<Transaction> tra1;
    vector<Transaction> tra2;
    vector<Transaction> tra3;
    vector<Transaction> tra4;
    vector<Transaction> tra5;
    int index=0;
    string text="0000000000000000000000000000000000000000000000000000000000000000";
    std::uniform_int_distribution<std::mt19937::result_type> randT(0,10000);
    for(int i=0;i<10000;i++)
    {

        tra1.push_back(transac[randT(rng)]);
        tra2.push_back(transac[randT(rng)]);
        tra3.push_back(transac[randT(rng)]);
        tra4.push_back(transac[randT(rng)]);
        tra5.push_back(transac[randT(rng)]);

        //cout << transac[i].from << " " << transac[i].to << " " << transac[i].amount << endl;
        if(i%100==99 && i!=0)
        {

            Blockchain.push_back(block());
            if(count==0)
            {
                Blockchain[0].createGenesis();
            }
            unsigned long req=1000000;

            //cout << Blockchain[count].getVersion() << endl;
            for(int j=0;j<5;j++)
            {
                if(j==0)
                {
                    tra=tra1;
                }
                else if(j==2)
                {
                    tra=tra2;
                }
                else if(j==3)
                {
                    tra=tra3;
                }
                else if(j==4)
                {
                    tra=tra4;
                }
                else if(j==5)
                {
                    tra=tra5;
                }

                Blockchain[count].Ttesting(tra, user);
                Blockchain[count].setTransactions(tra,user);
                Blockchain[count].proofOfWork();

                if(Blockchain[count].getNonce() < req)
                {
                    Blockchain[count].setVersion(count);
                    Blockchain[count].setPrevHash(text);
                    Blockchain[count].setBlockHash();
                    text=Blockchain[count].getBlockHash();

                    tra1.clear();
                    tra2.clear();
                    tra3.clear();
                    tra4.clear();
                    tra5.clear();


                    count++;



                    tra.clear();
                    break;
                }
                if(i==4)
                {
                    req=req+1000000;
                    i=0;
                }
                if(req > 4294967294)
                {
                    Blockchain.pop_back();

                    break;
                }

            }

        }

    }

    for(auto &blo:Blockchain)
    {
        blo.setMerkelTreeHash();
    }
}
void StartBlockchain()
{
    vector<Userdata> user;
    generateUser(user);

    vector<Transaction> transac;
    generateTransactions(transac,user);

    vector<block> Blockchain;
    fillBlocks(Blockchain,transac,user);


   cout << "Number of existing blocks in blockchain: " << Blockchain[Blockchain.size()-1].getVersion()+1 << endl;
   cout << "Which block information you want to see?" << endl;
   int a;
   std::cin>>a;
   if(a<0 || a>Blockchain.size()-1)
       cout << "You chose a block that doesnt exist";
   else
   {
       cout << std::left << std::setw(20)<< "Block hash " << Blockchain[a].getBlockHash() << endl;
       cout << std::left << std::setw(20)<< "Prev hash " << Blockchain[a].getPrevHash() << endl;
       cout << std::left << std::setw(20)<< "Timestamp "; Blockchain[a].getTimestamp() ;
       cout << std::left << std::setw(20)<< "Version  " << Blockchain[a].getVersion() << endl;
       cout << std::left << std::setw(20)<< "Merkel Root " << Blockchain[a].getMerkelTreeHash() << endl;
       cout << std::left << std::setw(20)<< "Nonce " << Blockchain[a].getNonce() << endl;
       cout << std::left << std::setw(20)<< "Dificulty target " << Blockchain[a].getDificultyTarget() << endl;
       Blockchain[a].getTransactions();

   }

}
