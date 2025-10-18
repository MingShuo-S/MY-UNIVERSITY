#include<iostream>
#include<string>
#include<vector>

#include<fstream>

using namespace std;

bool IsSimilarWord(std::string target,std::string ano,double accuracy=0.7)
{
    int differ=0;
    int size1=target.size(),size2=ano.size();
    int upper=size1,lower=size1+size2;
    
    if(upper<size2)
        upper=size2;
    lower-=upper;

    if(upper-lower>upper*5*(1-accuracy))
        return false;

    std::vector<int> s(lower+3,0);

    for(int i=0;i<lower;i++)
    {
        if(i+differ<=lower&&target[i]==ano[i+differ])
            s[i+1]=s[i];
        else if(i+1+differ<=lower&&target[i]==ano[i+1+differ])
        {
            differ++;
            s[i+1]=s[i]+1;
        }
        else if(i-1+differ>=0&&target[i]==ano[i-1+differ])
        {
            differ--;
            s[i+1]=s[i]+1;
        }
        else
            s[i+1]=s[i]+1;
    }
    
    return s[lower]<=lower*2*(1-accuracy);
}

int main()
{
    std::string a,b;
    while(a!="0")
    {
        std::cin>>a>>b;
        bool m=IsSimilarWord(a,b);
        std::cout<<m<<std::endl;
    }
    return 0;
}