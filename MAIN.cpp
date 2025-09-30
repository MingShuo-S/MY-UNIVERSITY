#include "Function.h"

#include <string>
#include <iostream>
#include <windows.h>

using namespace std;

/*
int main()
{
    SortintoAFTER();
    return 0;
}
    */
/*
int main()
{
    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出编码为UTF-8
    SetConsoleCP(CP_UTF8);       // 设置控制台输入编码为UTF-8
    std::string word1;
    while(word1!="0")
    {
    std::cout<< "输入0时退出"<<std::endl;
    std::cin >> word1;
    SearchInAfter(word1);
    }
    return 0;
}
    */

int main()
{
    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出编码为UTF-8
    SetConsoleCP(CP_UTF8);       // 设置控制台输入编码为UTF-8
    cout<<"欢迎进入自主单词管理系统"<<endl;

    int flag=-1,err,i;
    string word1,word2;
    s0:
    word1=word2="1";
    while(1)
    {

        cout<<"--------选择功能--------"<<endl;
        cout<<"1-整理单词至AFTER.txt\n2-在AFTER.txt中查找单词\n3-在WITH_SENTENCE中查找并记忆单词\n4-向WORDS.txt中添加新单词\n5-回顾最近一天的单词\n6-回顾指定天单词\n7-回顾所有单词\n8-模糊搜索\n9-深度积累\n10-深度积累的排序整理\n0-直接退出"<<endl;
        cout<<endl<<"请输入数字：";

        while(cin>>flag)
        {
            switch(flag)
            {
                case 0:
                    goto s_end;
                case 1:
                    goto s1;
                case 2:
                    goto s2;
                case 3:
                    goto s3;
                case 4:
                    goto s4;
                case 5:
                    goto s5;
                case 6:
                    goto s6;
                case 7:
                    goto s7;
                case 8:
                    goto s8;
                case 9:
                    goto s9;
                case 10:
                    goto s10;
                default:
                    cout<<"接受不了，请重新输入"<<endl<<endl;
            }
        }
         if(cin.fail())
        {
            while(getchar()!='\n');
            std::cin.clear();
            cout<<endl<<"您输入有误，错误已处理，系统重启中……"<<endl<<endl;
            ENTERN(2);
        }
    }
    

    /*按下1*/
    s1:
    cout<<"------------------------"<<endl<<endl;
    err=SortintoAFTER();
    if(err==0)
        cout<<"已完成排序"<<endl<<endl;
    else
        cout<<"出现错误，排序失败"<<endl<<endl;
    goto s0;
    /*按下2*/
    s2:
    cout<<"------------------------"<<endl;
    while(word1!="0")
    {
    std::cout<< "输入0时退出"<<std::endl;
    std::cout<<std::endl;
    std::cin >> word1;
    SearchInAfter(word1);
    std::cout<<std::endl;
    }
    goto s0;
    /*按下3*/
    s3:
    cout<<"------------------------"<<endl;
    while(word2!="0")
    {
    std::cout<< "输入0时退出"<<std::endl;
    std::cout<<std::endl;
    std::cin >> word2;
    SearchInWithSentence(word2);
    std::cout<<std::endl;
    }
    goto s0;
    /*按下4*/
    s4:
    cout<<"------------------------"<<endl;
    err=AddWordInWORDS();
    if(err==0)
        std::cout<<"已全部输入成功\n"<<std::endl;
    else
        std::cout<<"过程出现问题\n"<<std::endl;
    goto s0;
    /*按下5*/
    s5:
    cout<<"------------------------"<<endl;
    LookUpDay(GetLatestDay());
    goto s0;
    /*按下6*/
    s6:
    cout<<"------------------------"<<endl;
    cout<<"请输入检索天数：";
    i=GetNum_s();
    cout<<endl;
    LookUpDay(i);
    goto s0;
    /*按下7*/
    s7:    
    cout<<"------------------------"<<endl;
    for(i=1;i<GetLatestDay();i++)
        LookUpDay(i);
    goto s0;
    /*按下8*/
    s8:    
    cout<<"------------------------"<<endl;
    FuzzySearch();
    /*按下9*/
    s9:
    cout<<"------------------------"<<endl;
    DeepAccumulation();
    goto s0;
    /*按下10*/
    s10:
    cout<<"------------------------"<<endl;
    err=DASortIntoAfter();
    if(err==0)
        cout<<"已完成排序"<<endl<<endl;
    else
        cout<<"出现错误，排序失败"<<endl<<endl;
    goto s0;
    /*按下0*/
    s_end:
    return 0;
}