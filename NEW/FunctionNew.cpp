#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <thread>   // 包含线程库
#include <chrono>   // 包含时间库
#include <filesystem>

#include "Words.h"
#include "FunctionNew.h"
#include "HEAP_SORT.h"

namespace fs=std::filesystem;

//========================================================================================//
/*--------全局变量--------*/
std::map <std::string,std::string> 
menu={
    {"0","退出"},
    {"1","添加新单词"},
    {"?","查看功能菜单"}
} ;
std::map <std::string,std::string> 
fuc={
    {"exit","返回主菜单"},
    {"add","添加新单词"},
    {"help","查看功能菜单"}
} ;


//========================================================================================//
/*--------辅助功能--------*/
/*---判断---*/
bool IsFileWritePosAtEnd(std::fstream& f)
{
    if(!f)
    {
        std::cerr<<"Error:文件打开失败"<<std::endl;
        return false;
    }
    std::streampos current=f.tellp(),end;
    f.seekp(0,std::ios::end);
    end=f.tellp();
    f.seekp(current);
    return current==end;
}


/*--------基础功能--------*/
/*---显示---*/
//打一定量空格
void Space(int n)
{
    for(int i=0;i<n;i++)
        std::cout<<' ';
}

//标题格式输出
void Title(std::string a)
{
    int total=30;
    if(a.length()>total)
        total=a.length();

    for(int i=0;i<total;i++)
        std::cout<<'=';
    std::cout<<std::endl;

    Space((total-a.length())>>1);
    std::cout<<a<<std::endl;

     for(int i=0;i<total;i++)
        std::cout<<'=';
    std::cout<<std::endl;
}

void BigTitle(std::string a)
{
    int total=45;
    if(a.length()>total)
        total=a.length();

    for(int i=0;i<total;i++)
        std::cout<<'=';
    std::cout<<std::endl<<std::endl;

    Space((total-a.length())>>1);
    std::cout<<a<<std::endl<<std::endl;
    
     for(int i=0;i<total;i++)
        std::cout<<'=';
    std::cout<<std::endl;
}

//Tips格式输出
void Tips(std::string tip)
{
    std::cout<<"*Tips:"<<tip<<std::endl;
}

//Notation格式输出
void Notation(std::string note)
{
    std::cout<<"\n*"<<note<<'\n'<<std::endl;
}

//一次性输出WORD数组
template <class A>
int PrintVector(const std::vector<A>& a )
{
    int n=a.size();

    if(n==0)
        return 1;

    for(int i=0;i<n;i++)
    {
        std::cout<<a[i]<<std::endl;
    }
    std::cout<<"输出完毕，共输出"<<n<<"个单位\n"<<std::endl;
    return 0;
}

//慢慢地输出WORD数组
template <class A>
int PrintVectorSlowly(const std::vector<A>& a ,int total=10000)
{
    int n=a.size();

    if(n==0)
        return 1;

    for(int i=0;i<n;i++)
    {
        std::cout<<a[i]<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(total/n));
    }
    std::cout<<"输出完毕，共输出"<<n<<"个单位,耗时"<<total/1000.0<<"秒\n"<<std::endl;
    return 0;
}

//换下一页


//返回上一页


/*---输入---*/
//输入换行保证
void AutoAppEnter(std::fstream& p)
{
    if(p.tellp()==0) return;
    p.clear();
    p.seekp(-1,std::ios::end);
    char c=p.get();
    p.seekp(0,std::ios::end);
    if(c!='\n') p<<'\n';
}

//输入一个word
Word Pack(std::fstream& File)
{
    Word word;
    std::string line;
    getline(File,word.word);

    word.meaning.clear();
    while(getline(File,line))
    {
        if(line.empty())
            break;
        else
            word.meaning+=line+'\n';
    }
    
    return word;
}

//将文件内容打包为vector<Word>,进而方便排序
std::vector<Word> PackAll(fs::path filepath)
{
    std::ifstream InFile(filepath);

    std::string line;
    Word w;
    std::vector<Word> words;

    if(!InFile.is_open())
    {
        std::cerr<<filepath.string()<<"打开失败"<<std::endl;
        return words;
    }

    while(getline(InFile,line))
    {
        w.meaning.clear();
        if(line.empty())
            continue;
        else if(line[0]=='D'&&line[1]=='a'&&line[2]=='y')
            continue;
        else
            w.word=line; 
        
        while(getline(InFile,line))
        {
            if(line.empty())
                break;
            else
                w.meaning+=line+'\n';
        }
        w.meaning.pop_back();

        words.emplace_back(w);
    }

    InFile.close();
    return words;
}

//将文件指定内容打包为vector<Word>,进而方便排序
std::vector<Word> PackPortion(fs::path filepath,int start=0,int end=99999)
{
    std::ifstream InFile(filepath);
    std::string line;
    Word w;
    std::vector<Word> words;

    if(!InFile.is_open())
    {
        std::cerr<<filepath.string()<<"打开失败"<<std::endl;
        return words;
    }

    InFile.seekg(start);

    while(getline(InFile,line)&&InFile.tellg()<end)
    {
        w.meaning.clear();
        if(line.empty())
            continue;
        else if(line[0]=='D'&&line[1]=='a'&&line[2]=='y')
            continue;
        else
            w.word=line; 
        
        while(getline(InFile,line))
        {
            if(line.empty())
                break;
            else
                w.meaning+=line+'\n';
        }
        w.meaning.pop_back();

        words.emplace_back(w);
    }

    InFile.close();
    return words;
}

/*---输入---*/
//交互式普通输入文件，一次一个词（检测到在单词侧首位输入'='时或只输入'0'退出） 
//// -'='表示进入指令  -'0'该程序默认退出符
std::string AddWord(std::fstream& f)
{
    std::string flag;
    std::string word,meaning;
    //加到大功能上：std::cout<<"\nPS:如需退出,请任意一项输入0;如需使用功能请参照“功能指南”\n"<<std::endl;
    
    while(word!="0"&&meaning!="0")
    {
        std::cout<<"请添加单词和中文释义（中间用空格隔开）："<<std::endl;
        std::cin>>word;
        if(word=="0")
            goto s_exit;
        else if(word[0]=='=')
        {
            goto s_function;
        }

        std::cin>>meaning;
        if(meaning=="0")
            goto s_exit;

        std::cout<<"\n您输入的是："<<word<<" "<<meaning<<std::endl;
        std::cout<<"请确认是否有误，确认无误请输入1";
        std::cin>>flag;
        if(flag=="1")
            std::cout<<"\n正在录入文件……"<<std::endl<<std::endl;
        else
        {
            std::cout<<"一猜就是不小心，请重新输入————"<<std::endl;
            continue;
        }
        
        f<<word<<'\n'<<meaning<<std::endl<<std::endl;
        std::cout<<"录入成功！"<<std::endl<<std::endl;
        break;
    }

    return "0";
    s_exit:
    return "1";
    s_function:
    word.erase(0,1);
    return word;     //这里是指令，第一个词为指令名称，后面的词充当参数（在同一行）
}

//===不想做直接的深度积累功能了===
//交互式确认是否要进入新的一天
void IsNewDay(std::fstream& AppFile)
{
    std::string flag,byte;
    if(!IsFileWritePosAtEnd(AppFile))
    {
        std::cerr<<"非文件末尾，无法添加新的一天"<<std::endl;
        return;
    }

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
            AppFile.clear();
            AppFile.seekp(0,std::ios::end);
            break;
        }
        else
            std::cout<<"\n您输入有误，请重新输入！"<<std::endl<<std::endl;
    }
}

/*---切换---*/
//普通输入后进入深度积累（单次进入） BeWordPlus();<Words.h>


/*---检索---*/
//返回最新天数
int GetLatestDay(fs::path path)
{
    std::ifstream InFile(path);
    std::string byte;
    int i=0;
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

//返回指定天数所在位置（的该行首位）
std::streampos GetDayNPos(fs::path path,int n)
{
    std::string word,N=std::to_string(n),a;
    std::streampos pos;
    std::ifstream InFile(path);
    while(InFile>>word)
    {
        if(word=="Day")
        {
            pos=InFile.tellg();
            pos-=4;
            InFile>>a;
            if(a==N)
            {
                InFile.close();
                return pos;
            }
        }
    }
    //std::cerr<<"该天不在文件中"<<std::endl;
    InFile.close();
    return 0;
}

//返回指定单词位置（在单词行首位）
std::vector<std::streampos> GetWordPoses(fs::path path,std::string target)
{
    std::string word;
    std::streampos pos;
    std::vector<std::streampos> poses;
    std::ifstream InFile(path);
    int length=target.length();

    while(getline(InFile,word))
    {
        pos=InFile.tellg();
        if(word==target)
        {
            poses.emplace_back(pos);
        }
    }
    InFile.close();
    //std::cerr<<"该单词不在文件中"<<std::endl;
    return poses;
}

/*---搜索---*/ /*2*/
//文件内单次模糊搜索，存入数组
std::vector<Word> FuzzySearch(fs::path path,std::string target)
{
    std::fstream InFile(path,std::ios::in);
    if(!InFile)
    {
        std::cerr<<"文件打开失败\n"<<std::endl;
        return {};
    }

    std::vector<Word> words;
    Word word;
    std::string line;
    std::streampos pos;

    while(getline(InFile,line))
    {
        pos=InFile.tellg();
        if(line.find(target)!=std::string::npos)
        {
            InFile.seekg(pos);
            word=Pack(InFile);
            words.emplace_back(word);
        }
    }

    if(words.size()==0)
    {
        std::cerr<<"未在"<<path.string()<<"中找到含"<<target<<"的词\n"<<std::endl;
    }

    InFile.close();
    return words;
} 

//文件内单次精确搜索，存入数组
std::vector<Word> Search(fs::path path,std::string target)
{
    std::vector<std::streampos> poses=GetWordPoses(path,target);

    std::fstream InFile(path,std::ios::in);
    if(!InFile)
    {
        std::cerr<<"文件打开失败\n"<<std::endl;
        return {};
    }

    std::vector<Word> words;
    Word word;
    int n=poses.size(),i;
    if(n==0)
    {
        std::cout<<target<<"不存在于"<<path.string()<<'\n'<<std::endl;
    }
    else
    {
        for(i=0;i<n;i++)
        {
            InFile.seekg(poses[i]);
            word=Pack(InFile);
            words.emplace_back(word);
        }
    }

    InFile.close();
    return words;
} 

//查找形近词，存入数组


//根据词根词缀查找相关单词，存入数组


/*---修改---*/
//指定已在文件中的单词进行深度积累，并覆盖原有单词记录（只是在原有单词处写一个删除标记再重新计入）


//指定修改文件中的单词内容，并覆盖原有单词记录（只是在原有单词处写一个删除标记再重新计入）


//删除某日标记(不小心按错时候用)


/*---标记---*/
//指定已在文件中的单词进行标记，进入UPPER_WORDS


//将标记词打入冷宫（背得很熟悉）


//标记熟词生义


/*---复习---*/
//根据指定单词进行单次复习（确认已存在，先确认“是否认识”，后逐步展现中文释义


//根据指定单词进行单次深度复习（确认已存在于深度复习，先确认“是否认识”，后逐步展现词组、例句


//单次考查（显示中文写英文，或根据英文写中文，不要直接比对，让用户输入是否回答正确/有偏差/完全错误）




//========================================================================================//
/*--------菜单--------*/
//功能菜单（主页）
void Menu()
{
    Title("主菜单");
    int n=menu.size();
    for(auto it=++menu.begin();it!=menu.end();it++)
    {
        std::cout<<it->first<<"--"<<it->second<<std::endl;
    }
    std::cout<<"0--"<<menu["0"]<<'\n'<<std::endl;
}

//功能菜单（转换）
void Menu2()
{
    Title("功能菜单");
    for(const auto& pair : fuc)
    {
        std::cout<<pair.first<<"--"<<pair.second<<std::endl;
    }
    std::cout<<std::endl;
}


//========================================================================================//
/*--------应用功能--------*/
//进行单次排序，包括输入与输出（堆排序在头文件中已经有了），会使用到打包


//将单词输入文件（核心交互模式）


//在某个文件内进行模糊查找（需要用到打包，以更好呈现内容）


//大复习


//已有单词修改or增加深度积累