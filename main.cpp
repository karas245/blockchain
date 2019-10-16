#include "header.h"
#include "block.h"
int main()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << "  " << ltm->tm_hour << ":"
         << ltm->tm_min << ":" << ltm->tm_sec << endl;
    int t=now;
    cout << "hello " << now << endl;

    vector<block> Block1;
    string hash="054as6";
    int ver=1;
    string treeHash="2asg55";
    int non=1;
    double dificulty= 2.35;
    vector<Transaction> transac;
    Transaction TR;
    TR.amount=2;
    TR.from="JOHN";
    TR.to="MARK";
    transac.push_back(TR);

    //Block1(hash,ver,treeHash,non,dificulty,transac);
    cout << hash.c_str() << " --" << Block1[0].getVersion();






    return 0;
}