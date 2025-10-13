#include<iostream>
#include<string>
#include<vector>

#include<fstream>

using namespace std;

bool IsSimilarWord(std::string target,std::string ano,int baseline=3)
{
    int differ=0;
    int size1=target.size(),size2=ano.size();
    int upper=size1,lower=size1+size2;
    
    if(upper<size2)
        upper=size2;
    lower-=upper;

    if(upper-lower>baseline)
        return false;

    std::vector<int> s(lower,0);

    for(int i=1;i<lower+2;i++)
    {
        if(target[i]==ano[i+differ])
            s[i+1]=s[i];
        else if(target[i]==ano[i+1+differ])
        {
            differ++;
            s[i+1]=s[i]+1;
        }
        else if(target[i]==ano[i-1+differ])
        {
            differ--;
            s[i+1]=s[i]+1;
        }
        else
            s[i+1]=s[i]+1;
    }
    
    return s[lower+1]<=baseline;
}