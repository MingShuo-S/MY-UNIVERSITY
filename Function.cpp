#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include "Words.h"
#include "HEAP_SORT.h"
#include "Function.h"

#define INPUT_FILE_PATH "C:\\Users\\29548\\Desktop\\Sunshine\\Words\\WORDS.txt"
#define OUTPUT_FILE_PATH "C:\\Users\\29548\\Desktop\\Sunshine\\Words\\AFTER.txt"
#define PLUS_INPUT_FILE_PATH "C:\\Users\\29548\\Desktop\\Sunshine\\Words\\DEEP_ACCUMULATION.txt"
#define PLUS_OUTPUT_FILE_PATH "C:\\Users\\29548\\Desktop\\Sunshine\\Words\\AFTER_DEEP_ACCUMULATION.txt"

//#define INPUT_FILE_PATH "C:\\Users\\29548\\Desktop\\Sunshine\\Course_study\\INCLASS.txt"
//#define OUTPUT_FILE_PATH "C:\\Users\\29548\\Desktop\\Sunshine\\Course_study\\AFTERSORT.txt"

void ENTERN(int n)
{
    for(int i=0;i<n;i++)
        std::cout<<std::endl;
}

int SortintoAFTER()
{
    int n = 0;
    std::ifstream inFile(INPUT_FILE_PATH);
    std::ofstream outFile(OUTPUT_FILE_PATH);

    if (!inFile.is_open()) {
        std::cerr << "Failed to open file for reading!" << std::endl;
        return 1;
    }

    std::vector<Word> words(5000);
    std::string word, meaning;
    Word p;

    for (int i = 0; inFile >> word; i++)
    {
        if(word == "Day") 
        {
            inFile>>word;
            i--;
            continue;
        }
        inFile >> meaning;
        words[i].word = word;
        words[i].meaning = meaning;
        n++;
    }

    heapsort<Word>(words, n);

    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing!" << std::endl;
        return 1;
    }

    for (int i = 0;i<n ; i++)
    {
        outFile << words[i];
        if(i+1<n)
            if(words[i+1].word[0]!=words[i].word[0])
                outFile<<'\n';
    }

    inFile.close();
    outFile.close();
    return 0;
}

std::string SearchInAfter(std::string& word1)
{
    if(word1=="0") return word1;
    std::ifstream inFile(OUTPUT_FILE_PATH);
    std::string word0;
    inFile>>word0;
    while(word1!=word0)
    {
        if(inFile>>word0);
        else
        {
            std::cout<<word1<<" is not in the list"<<std::endl;
            std::cout<<std::endl;
            return word1;
        }
    }
    inFile>>word0;
    std::cout<<std::endl;
    std::cout<<word1<<std::endl;
    std::cout<<word0<<std::endl;
    std::cout<<std::endl;
    inFile.close();
    return word0;
}

int SearchInWithSentence(std::string& word1)
{
    if(word1=="0") return 1;
    std::ifstream inFile("C:\\Users\\29548\\Desktop\\Sunshine\\Words\\WITH_SENTENCE.txt");
    std::string word0;
    inFile>>word0;
    while(word1!=word0)
    {
        if(inFile>>word0);
        else
        {
            std::cout<<word1<<" is not in the list"<<std::endl;
            std::cout<<std::endl;
            return 1;
        }
    }
    inFile>>word0;
    std::cout<<std::endl;
    std::cout<<word1<<" "<<word0<<std::endl;
    inFile>>word0;
    std::cout<<word0<<std::endl;
    char ch;
    inFile.get(ch);
    while(inFile.get(ch))
    {
        if(ch=='\n') break;
        else std::cout<<ch;
    }
    std::cout<<std::endl;
    inFile.close();
    return 0;
}

int AddWordInWORDS()
{    
    std::fstream AppFile(INPUT_FILE_PATH,std::ios::in|std::ios::out);
    AutoAppEnter(AppFile);

    std::string flag,byte;
    int n=0;
    std::cout<<"Create a NEW Day?(Y or N)"<<std::endl;
    while(std::cin>>flag)
    {
        if(flag=="Y")
        {
            while(AppFile>>byte)
            {
                if(byte=="Day")
                    AppFile>>n;
            }
            n++;
            AppFile.clear();
            AppFile.seekp(0,std::ios::end);
            AppFile<<std::endl<<"Day "<<n<<std::endl;
            break;
        }
        else if(flag=="N")
        {
            break;
        }
        else
            std::cout<<"\n您输入有误，请重新输入！"<<std::endl<<std::endl;
    }

    std::string word,meaning;
    std::cout<<"\nPS：如需退出，请输入0\n"<<std::endl;
    while(word!="0"&&meaning!="0")
    {
        std::cout<<"请添加单词和中文释义（中间用空格隔开）："<<std::endl;
        std::cin>>word>>meaning;

        if(word=="0"||meaning=="0")
            goto s_end;

        std::cout<<"\n您输入的是："<<word<<" "<<meaning<<std::endl;
        std::cout<<"请确认是否有误，确认无误请输入1:";
        std::cin>>flag;
        if(flag=="1")
            std::cout<<"\n正在录入文件……"<<std::endl<<std::endl;
        else
        {
            std::cout<<"收到，请重新输入————"<<std::endl;
            continue;
        }
        
        AppFile<<word<<" "<<meaning<<std::endl;
        std::cout<<"录入成功！"<<std::endl<<std::endl;
    }

    s_end:
    AppFile.close();
    return 0;
}

int LookUpDay(int n)
{
    std::ifstream InFile(INPUT_FILE_PATH);
    std::string byte,line;
    int i;
    while(InFile>>byte)
    {
        if(byte=="Day")
        {
            InFile>>i;
            if(i==n)
                goto PutOut;
        }
    }
    std::cout<<"第"<<n<<"天并没有被记录，无法输出\n"<<std::endl;
    InFile.close();
    return 1;

    PutOut: 
    std::cout<<"Day "<<n<<std::endl;
    while(std::getline(InFile,line))
    {
        if(line[0]=='D'&&line[1]=='a'&&line[2]=='y')
            break;
        else if(line[0]=='*')
            continue;
        std::cout<<line<<std::endl;
    }
    std::cout<<"\n";
    InFile.close();
    return 0;
}

int GetLatestDay()
{
    std::ifstream InFile(INPUT_FILE_PATH);
    std::string byte;
    int i;
    while(InFile>>byte)
    {
        if(byte=="Day")
        {
            InFile>>i;
        }
    }
    InFile.close();
    return i;
}

int GetNum_s()
{
    int i;
    while(1)
    {
        std::cin>>i;
        if(std::cin.fail())
        {
            std::cout<<"输入并非数字，请重新输入"<<std::endl;
            std::cin.clear();
            while(getchar()!='\n');
        }
        else
            break;
    }
    return i;
}
    
int FuzzySearch()
{
    int flag;
    std::string inword,line;
    std::ifstream InFile(OUTPUT_FILE_PATH);
    while(1)
    {
        flag=0;
        std::cout<<"请输入你想要查找的单词/词根词缀(输入0退出)：";
        std::cin>>inword;
        std::cout<<"\n";
        if(inword=="0") break;
        InFile.clear();
        InFile.seekg(0,std::ios::beg);
        while(getline(InFile,line))
        {
            if(line.find(inword)!=std::string::npos)
            {
                std::cout<<line<<std::endl;
                flag++;
            }
        }
        if(flag==0)
            std::cout<<"\n并未查找到对应单词或中文\n"<<std::endl;
        else
            std::cout<<"\n查找结束，共"<<flag<<"个输出\n"<<std::endl;
    }
    InFile.close();
    return 0;
}

int DeepAccumulation()
{
    std::fstream OutFile(INPUT_FILE_PATH,std::ios::app|std::ios::in);
    std::fstream PlusOutFile(PLUS_INPUT_FILE_PATH,std::ios::app|std::ios::in);

    AutoAppEnter(OutFile);
    AutoAppEnter(PlusOutFile);

    WordPlus p;
    std::string flag;

    std::string lflag,byte;
    int n=0;
    std::cout<<"是否在WORDS.txt中添加新的一天?(Y or N)"<<std::endl;
    while(std::cin>>lflag)
    {
        if(lflag=="Y")
        {
            while(OutFile>>byte)
            {
                if(byte=="Day")
                    OutFile>>n;
            }
            n++;
            OutFile.clear();
            OutFile.seekp(0,std::ios::end);
            OutFile<<std::endl<<"Day "<<n<<std::endl;
            break;
        }
        else if(lflag=="N")
        {
            break;
        }
        else
            std::cout<<"\n您输入有误，请重新输入！"<<std::endl<<std::endl;
    }

    while(1)
    {
        flag="0";
        p.reset();
        GetWordPlus(p);
        if(p.word=="0") break;

        std::cout<<"您的总输入是："<<std::endl;
        std::cout<<p<<std::endl;
        std::cout<<"确认无误请输入1：";
        std::cin>>flag;
        if(flag!="1") continue;

        PlusOutFile<<p<<std::endl;
        std::cout<<"\n已成功输入至DEEP_ACCUMULATION.txt！"<<std::endl;

        OutFile<<p.word<<' '<<p.meaning<<std::endl;
        std::cout<<"已同步到WORDS.txt！"<<std::endl;

        flag="0";
        std::cout<<"\n是否继续输入？继续输入请输入1：";
        std::cin>>flag;
        if(flag!="1") break;
    }
    PlusOutFile.close();
    return 0;
}

int DASortIntoAfter()
{
     int n = 0;
    std::ifstream inFile(PLUS_INPUT_FILE_PATH);
    std::ofstream outFile(PLUS_OUTPUT_FILE_PATH);

    if (!inFile.is_open()) {
        std::cerr << "Failed to open file for reading!" << std::endl;
        return 1;
    }

    std::vector<Word> words(500);
    std::string word, meaning,line;
    Word p;

    for (int i = 0; getline(inFile,line); i++)
    {
        if(line.empty()) continue;
        else word=line;
        meaning="";
        line="0";
        while(!line.empty())
        {
            getline(inFile,line);
            meaning+=line+'\n';
        }
        words[i].word = word;
        words[i].meaning = meaning;
        n++;
    }

    heapsort<Word>(words, n);

    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing!" << std::endl;
        return 1;
    }

    for (int i = 0;i<n ; i++)
    {
        outFile << words[i].word<<'\n'<<words[i].meaning;
        if(i+1<n)
            if(words[i+1].word[0]!=words[i].word[0])
                outFile<<"----\n";
    }

    inFile.close();
    outFile.close();
    return 0;
}











//内部函数
void AutoAppEnter(std::fstream& p)
{
    if(p.tellp()==0) return;
    p.clear();
    p.seekp(-1,std::ios::end);
    char c=p.get();
    p.seekp(0,std::ios::end);
    if(c!='\n') p<<'\n';
}