#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <thread>   // 包含线程库
#include <chrono>   // 包含时间库
#include <filesystem>
#include <algorithm>

#include "FunctionNew.h"
namespace fs=std::filesystem;
AppConfig& config1=AppConfig::instance();

//========================================================================================//
//排序改为在main函数内交互完之后自动排序;查找模留在核心交互里面
/*--------全局变量--------*/

const std::map <std::string,std::string> 
menu={
    {"0","退出"},
    {"1","进入核心交互"},        //核心交互模式
    {"2","开始复习单词"},          //复习模式
    {"3","回顾积累单词"},            //回顾模式
    {"4","进入标签管理"},              //标签管理
    {"#","查看使用建议"},                //捏嘿
    {"?","查看指令菜单"}                   //打印指令菜单
} ;
const std::vector<std::pair<std::string,std::string>> 
func={
    {"exit","返回主菜单"},
    {"search","在目前所在文档中查找该词，该行第二个词为被查词"},
    {"search_similar","查找该单词的所有形近词，该行第二个词为被查词"},
    {"fuzzy_search","在目前所在文件中模糊查找该词，该行第二个词为被查词"},
    {"delete","删除某个词，进入该功能后需要确认具体删除哪个"},
    {"modify","修改某个词的释义，该行第二个词为被修改的词，进入该功能后需要确认具体修改哪个"},
    {"promote","给某个词添加深度积累，该行第二个词为被修改的词，进入该功能后需要确认提升哪个"},
    {"mark","给单词标记一个tag，方便后续查找，格式为：=mark word tag"},
    {"bible","查看使用建议，能帮你更好积累单词"},
    {"help","查看指令菜单"}
} ;

std::map<std::string,std::string>
funct={
    {"exit","返回主菜单"},
    {"search","在目前所在文档中查找该词，该行第二个词为被查词"},
    {"search_similar","查找该单词的所有形近词，该行第二个词为被查词"},
    {"fuzzy_search","在目前所在文件中模糊查找该词，该行第二个词为被查词"},
    {"delete","删除某个词，进入该功能后需要确认具体删除哪个"},
    {"modify","修改某个词的释义，该行第二个词为被修改的词，进入该功能后需要确认具体修改哪个"},
    {"promote","给某个词添加深度积累，该行第二个词为被修改的词，进入该功能后需要确认提升哪个"},
    {"mark","给单词标记一个tag，方便后续查找，格式为：=mark word tag"},
    {"bible","查看使用建议，能帮你更好积累单词"},
    {"help","查看指令菜单"}
};


const std::vector<std::string> 
//如果这些字符在行首，那么输出的时候就忽略这一行（输入的写了太多了不想改了（死））
ignore={
    "*",
    "~"
},
//如果这个字符在行首，那么说明这一行隶属于上面的单词（写入的时候删掉这个字符）
affiliate={
    "-"
},
//用于保存预设的提示句
tips={
    "输入任意指令请以“=”开头，如果想查看看指令菜单请输入“=help”~"
}
;


//========================================================================================//
/*--------辅助功能--------*/
/*---中转---*/
int Functions(fs::path p,std::string order,fs::path plus)
{
    std::string target;
    std::vector<Word> words;

    if(!funct.count(order))
    {
        std::cerr<<"指令未收录，无法运行"<<std::endl;
        return 1;
    }

    if(order=="exit"){
        return 2;
    }else if(order=="help"){
        Menu2();
    }else if(order=="search"){
        if(getline(std::cin,target))
        {
            words=Search(p,target);
            PrintVector<Word> (words);
        }
        else{
            std::cerr<<"未输入要查找的单词，无法执行"<<std::endl;
            return 1;
        }
    }else if(order=="search_similar"){
        if(getline(std::cin,target))
        {
            words=SearchSimilarWords(p,target);
            PrintVector<Word> (words);
        }
        else{
            std::cerr<<"未输入要查找的单词，无法执行"<<std::endl;
            return 1;
        }
    }else if(order=="fuzzy_search"){
        if(getline(std::cin,target))
        {
            words=FuzzySearch(p,target);
            PrintVector<Word> (words);
        }
        else{
            std::cerr<<"未输入要查找的单词，无法执行"<<std::endl;
            return 1;
        }
    }else if(order=="delete"){
        if(getline(std::cin,target))
        {
            InteractiveDelete(p,target);
        }
        else{
            std::cerr<<"未输入要查找的单词，无法执行"<<std::endl;
            return 1;
        }
    }else if(order=="modify"){
        if(getline(std::cin,target))
        {
            InteractiveModify(p,target);
        }
        else{
            std::cerr<<"未输入要查找的单词，无法执行"<<std::endl;
            return 1;
        }
    }else if(order=="promote"){
        if(getline(std::cin,target))
        {
            PromoteToB(p,plus,target);
        }
        else{
            std::cerr<<"未输入要添加深度积累的单词，无法执行"<<std::endl;
            return 1;
        }
    }else if(order=="mark"){

    }else if(order=="bible"){
        Bible();
    }

    return 0;
}

int Functions(fs::path p,std::string order,std::string target,fs::path plus)
{
    std::vector<Word> words;

    if(!funct.count(order))
    {
        std::cerr<<"指令未收录，无法运行"<<std::endl;
        return 1;
    }

    if(order=="exit"){
        return 2;
    }else if(order=="help"){
        Menu2();
    }else if(order=="search"){
        words=Search(p,target);
        PrintVector<Word> (words);
    
    }else if(order=="search_similar"){
        words=SearchSimilarWords(p,target);
        PrintVector<Word> (words);
    }else if(order=="fuzzy_search"){
        words=FuzzySearch(p,target);
        PrintVector<Word> (words);
    }else if(order=="delete"){
            InteractiveDelete(p,target);
    }else if(order=="modify"){
            InteractiveModify(p,target);
    }else if(order=="promote"){
            PromoteToB(p,plus,target);
    }else if(order=="mark"){

    }else if(order=="bible"){
        Bible();
    }

    return 0;
}
/*---良输入---*/
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

bool IsSimilarWord(std::string target,std::string ano,double accuracy)
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

bool IsAtHeadoftheLine(std::fstream& p)
{
    std::streampos pos=p.tellp();
    if(p.tellp()==0) return true;
    if(!p)  
    {
        std::cerr<<"文件打开失败，无法判断指针位置"<<std::endl;
        return false;
    }
    p.seekp(-1,std::ios::cur);
    char c=p.get();
    p.seekp(pos);

    if(c=='\n')
        return true;
    else 
        return false;
}

//========================================================================================//
/*--------基础功能--------*/
/*---显示---*/
//打一定量空格
void Space(int n)
{
    for(int i=0;i<n;i++)
        std::cout<<' ';
}

//标题格式输出
void Title(const std::string& a)
{
    int total=30;
    if(a.length()>total)
        total=a.length();

    for(int i=0;i<total;i++)
        std::cout<<'=';
    std::cout<<std::endl;

    Space((int)(total-0.6*a.length())>>1);
    std::cout<<a<<std::endl;

     for(int i=0;i<total;i++)
        std::cout<<'=';
    std::cout<<std::endl<<std::endl;
}

void BigTitle(const std::string& a)
{
    int total=45;
    if(a.length()>total)
        total=a.length();

    for(int i=0;i<total;i++)
        std::cout<<'=';
    std::cout<<std::endl<<std::endl;

    Space((int)(total-0.8*a.length())>>1);
    std::cout<<a<<std::endl<<std::endl;
    
     for(int i=0;i<total;i++)
        std::cout<<'=';
    std::cout<<std::endl<<std::endl;
}

//Tips格式输出
void Tips(const std::string& tip)
{
    std::cout<<"*Tips:"<<tip<<std::endl;
}

//Notation格式输出
void Notation(const std::string& note)
{
    std::cout<<"\n*"<<note<<'\n'<<std::endl;
}

/*
//一次性输出WORD数组
template <class A>
int PrintVector(const std::vector<A>& a)
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

// 输出数组至文件（覆盖原内容）
template <class A>
int PutOutVectorTo(const std::vector<A>& a,fs::path p)
{
    std::ofstream OutFile(p);
    int n=a.size();

    if(!OutFile.is_open())
    {
        std::cerr<<"文件打开失败"<<std::endl;
        return 1;
    }

    if(n==0)
        return 1;

    for(int i=0;i<n;i++)
    {
        OutFile<<a[i]<<std::endl;
    }
    std::cout<<"输出完毕，共输出"<<n<<"个单位\n"<<std::endl;
    return 0;
}

// 输出数组至文件（文件末尾添加）
template <class A>
int AppVectorTo(const std::vector<A>& a,fs::path p)
{
    std::fstream AppFile(p,std::ios::app);
    int n=a.size();

    if(!AppFile.is_open())
    {
        std::cerr<<"文件打开失败"<<std::endl;
        return 1;
    }

    if(n==0)
        return 1;

    for(int i=0;i<n;i++)
    {
        AppFile<<a[i]<<std::endl;
    }
    std::cout<<"输出完毕，共输出"<<n<<"个单位\n"<<std::endl;
    return 0;
}
*/

//累了，单独重载了
int PrintVectorSlowly(const std::vector<Word>& a,int total)
{
    int n=a.size();

    if(n==0)
        return 1;

    for(int i=0;i<n;i++)
    {
        for(std::string no : ignore )
        {
            if(a[i].word.find_first_of(no)==0)
                continue;
        }
        std::cout<<a[i]<<std::endl;
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

//打包一个word
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
std::vector<Word> PackPortion(fs::path filepath,int start,int end)
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

//将位置数组代表的单词全都打包至数组当中 /2
std::vector<Word> PackPortion(fs::path filepath,std::vector<std::streampos> poses)
{
    std::fstream File(filepath,std::ios::in|std::ios::out);
    std::string line;
    Word w;
    std::vector<Word> words;
    int n=poses.size();

    if(!File.is_open())
    {
        std::cerr<<filepath.string()<<"打开失败"<<std::endl;
        return words;
    }

    for(int i=0;i<n;i++)
    {
        File.seekp(poses[i]);
        words.emplace_back(Pack(File));
    }
    
    File.close();
    return words;
}

/*---输出---*/
//交互式普通输出至文件，一次一个词（检测到在单词侧首位输入'='时或只输入'0'退出） 
//// -'='表示进入指令  -'0'该程序默认退出符
std::string AddWord(std::fstream& f,std::fstream& plus)
{
    std::string flag;
    std::string word,meaning;
    //加到大功能上：std::cout<<"\nPS:如需退出,请任意一项输入0;如需使用功能请参照“功能指南”\n"<<std::endl;
    
    while(word!="0"&&meaning!="0")
    {
        std::cout<<"请添加单词和中文释义（中间用空格隔开）："<<std::endl;
        
        a:
        std::cin>>word;
        if(word=="0")
            goto s_exit;
        else if(word[0]=='=')
        {
            goto s_function;
        }

        std::cin>>meaning;
        if(meaning=="0"){
            std::cout<<"请重新输入单词: ";
            goto a;
        }

        std::cout<<"\n您输入的是:"<<word<<" "<<meaning<<std::endl;
        std::cout<<"请确认是否有误,确认无误请输入1,进入深度积累请输入2:";
        std::cin>>flag;
        if(flag=="1")
            std::cout<<"\n正在录入文件……"<<std::endl<<std::endl;
        else if(flag=="2"){
            Notation("正在进行深度积累……");
            WordPlus wp=BeWordPlus(word,meaning);
            plus<<wp;
            Notation("深度积累完成");
        }
        else
        {
            std::cout<<"\n请重新输入\n"<<std::endl;
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
std::vector<Word> SearchSimilarWords(fs::path p,std::string target,int baseline)
{
    std::fstream f(p,std::ios::in);
    std::vector<Word> w=PackAll(p),similars;

    int n=w.size(),num=0;

    for(int i=0;i<n;i++)
    {
        if(IsSimilarWord(target,w[i].word))
        {
            similars.emplace_back(w[i]);
        }
    }

    return similars;
}

//根据词根词缀查找相关单词，存入数组
std::vector<Word> SearchWithRootorAffixe(fs::path p,std::string target)
{
    //看什么看，以后再写
    return std::vector<Word>{};
}

/*---修改---*/
//指定已在文件中的单词进行深度积累，并覆盖原有单词记录（只是在原有单词处写一个删除标记再重新计入）
int PromoteToB(fs::path p,fs::path B,std::string target)
{
    std::vector<Word> ws;
    std::vector<std::streampos> poses;
    std::fstream File(p,std::ios::out|std::ios::in);
    std::fstream BFile(B,std::ios::app);
    int num;
    std::string meaning,flag="0";
    Word word;
    WordPlus wp;

    Notation("您已进入单词深度积累功能……");
    
    //获取单词位置，并将单词存入数组
    poses=GetWordPoses(p,target);
    ws=PackPortion(p,poses);

    int n=ws.size();
    //确认是否删的是这个单词
    std::cout<<"请确认你要深度积累的单词序号（请谨慎选择）："<<std::endl;
    for(int i;i<n;i++)
        std::cout<<i<<"-"<<ws[i].word<<"   "<<ws[i].meaning<<std::endl;
    
    while(flag!="1")
    {
        std::cout<<"请输入序号：";
        num=GetNum_s();
        if(num>=n||num<0)
        {
            std::cout<<"输入有误，请重新输入\n"<<std::endl;
            continue;
        }
        else
        {
            std::cout<<"您刚刚输入的是"<<num<<"\n输入正确请输入1：";
            std::cin>>flag;
        }
    }

    word=Pop(p,poses[num]);
    flag="1";

    std::cout<<"您正在修改的单词是："<<ws[n].word<<std::endl;

    wp=BeWordPlus(word.word,word.meaning);


    File.seekg(std::ios::end);
    AutoAppEnter(File);
    AutoAppEnter(BFile);
    File<<word;
    BFile<<wp;

    BFile.close();
    File.close();
    Notation("修改完成");
    return 0;
}

//删掉这个单词（单一功能，给单词和注释在的这几行前面都加上~）
int Delete(fs::path p,std::streampos pos)
{
    std::fstream f(p,std::ios::in|std::ios::out);
    f.seekg(pos);

    std::string after{},line;

    if(IsAtHeadoftheLine(f))
    {
        while(std::getline(f,line))
            after+=line+'\n';

        f.clear();
        f.seekg(pos);
        f<<"~"<<after;
        f.close();
        return 0;
    }
    else{
        std::cerr<<"单词删除失败"<<std::endl;
        f.close();
        return 1;
    }
}

//大量删除的时候使用，免得一直开关文件把文件炸了
int Delete(fs::path p,std::vector<std::streampos> poses)
{
    std::fstream f(p,std::ios::in|std::ios::out);
    std::string after{},line;

    int n=poses.size();

    if(n==0)
        return 0;

    for(int i=0;i<n;i++)
    {
        f.seekg(poses[i]);

        after.clear();
        line.clear();

        if(IsAtHeadoftheLine(f))
        {
            while(std::getline(f,line))
                after+=line+'\n';

            f.clear();
            f.seekg(poses[i]);
            f<<"~"<<after;
        }
        else{
            std::cerr<<"第"<<i<<"个单词删除失败"<<std::endl;
            return 1;
        }

    }
    f.close();
    return 0;
}

//删除的时候返回单词内容
Word Pop(fs::path p,std::streampos pos)
{
    std::fstream f(p,std::ios::in|std::ios::out);
    f.seekg(pos);
    
    Word w;
    std::string after{},line;

    if(IsAtHeadoftheLine(f))
    {
        while(std::getline(f,line))
            after+=line+'\n';

        f.clear();
        f.seekg(pos);
        f<<"~"<<after;
        w=Pack(f);
        f.close();
        return w;
    }
    else{
        std::cerr<<"单词删除失败"<<std::endl;
        f.close();
        return Word{};
    }
}

//指定修改文件中的单词内容（交互式,以免改错）  //2
void InteractiveModify(fs::path p,std::string target)
{
    std::vector<Word> ws;
    std::vector<std::streampos> poses;
    std::fstream File(p,std::ios::out|std::ios::in);
    int num;
    std::string meaning,flag="0";

    Notation("您已进入单词修改功能……");
    
    //获取单词位置，并将单词存入数组
    poses=GetWordPoses(p,target);
    ws=PackPortion(p,poses);

    int n=ws.size();
    //确认是否删的是这个单词
    std::cout<<"请确认你要修改的单词序号（请谨慎选择）："<<std::endl;
    for(int i;i<n;i++)
        std::cout<<i<<"-"<<ws[i].word<<"   "<<ws[i].meaning<<std::endl;
    
    while(flag!="1")
    {
        std::cout<<"请输入序号：";
        num=GetNum_s();
        if(num>n||num<0)
        {
            std::cout<<"输入有误，请重新输入\n"<<std::endl;
            continue;
        }
        else
        {
            std::cout<<"您刚刚输入的是"<<num<<"\n输入正确请输入1：";
            std::cin>>flag;
        }
    }

    Delete(p,poses[num]);
    flag="1";

    std::cout<<"您正在修改的单词是："<<ws[n].word<<std::endl;

    while(flag!="1")
    {
        std::cout<<"请输入修改后的释义：";
        std::cin>>meaning;
        std::cout<<"\n您刚刚输入的是："<<meaning<<"\n确认请输入1:";
        std::cin>>flag;
    }

    File.close();
    Notation("修改结束");
}

//交互式删除某个单词或某日标记
void InteractiveDelete(fs::path p,std::string target)
{
    std::vector<Word> ws;
    std::vector<std::streampos> poses;
    std::fstream File(p,std::ios::out|std::ios::in);
    int num;
    std::string meaning,flag="0";

    Notation("您已进入单词修改功能……");
    
    //获取单词位置，并将单词存入数组
    poses=GetWordPoses(p,target);
    ws=PackPortion(p,poses);

    int n=ws.size();
    //确认是否删的是这个单词
    std::cout<<"请确认你要删除的单词序号（请谨慎选择）："<<std::endl;
    for(int i;i<n;i++)
        std::cout<<i<<"-"<<ws[i].word<<"   "<<ws[i].meaning<<std::endl;
    
    flag="0";

    while(flag!="1")
    {
        std::cout<<"请输入序号：";
        num=GetNum_s();
        if(num>n||num<0)
        {
            std::cout<<"输入有误，请重新输入\n"<<std::endl;
            continue;
        }
        else
        {
            std::cout<<"您刚刚输入的是"<<num<<"\n输入正确请输入1：";
            std::cin>>flag;
        }
    }
    Delete(p,poses[num]);

    File.close();
    Notation("已成功删除");
}


/*---标记---*/
//对单词进行某种标记


//将标记统计并放入一个文档(在main内应该放到book.txt)中，以供参考


//打印目前的所有标记


//查找含有标记的单词，存入Word数组


//





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
    for(auto it=menu.begin();it!=menu.end();it++)
    {
        if(it->first=="0")
            continue;
        std::cout<<it->first<<"--"<<it->second<<std::endl;
    }
    std::cout<<"0--"<<menu.at("0")<<'\n'<<std::endl;
}

//指令菜单（转换）
void Menu2()
{
    Title("功能菜单");
    for(const auto& pair : func)
    {
        printf("%-20s--%s\n",pair.first.c_str(),pair.second.c_str());
    }
    std::cout<<std::endl;
}

//使用建议~
void Bible()
{
    Title("使用指南");
    Tips("   平日普通积累足,");
    Tips("   释义多加解释好。");
    Tips("   解释就用括号围,");
    Tips("   不扰意义方便找。");
    Tips("   同义词写出(=ai),");
    Tips("   多加解释用(:ao)。");
    Tips("   对比记忆写(<~>),");
    Tips("   如要追溯画(<-raw)。");
    Tips("其他相关的,比如:\n高级替换(>low),派生结构(->good),打上标记(#mark),好好想,好好用uwu");
    std::cout<<std::endl;
}

//========================================================================================//
/*--------应用功能--------*/
//进行单次排序，包括输入与输出（堆排序在头文件中已经有了），会使用到打包
int SortAintoB(fs::path A,fs::path B)
{
    std::vector<Word> WS=PackAll(A);
    int n=WS.size();

    if(n==0)
    {
        std::cerr<<"文件为空"<<std::endl;
        return 1;
    }

    heapsort<Word> (WS,n);

    PutOutVectorTo<Word> (WS,B);

    std::cout<<"排序完成\n"<<std::endl;
    return 0;
}

//将单词输入文件（核心交互模式）
int CoreAddWords(fs::path p,fs::path plus)
{
    std::string flag="0";
    std::fstream File(p,std::ios::in|std::ios::out);
    std::fstream Plus(p,std::ios::app);

    if(!File.is_open())
    {
        std::cerr<<"文件打开失败，启动失败"<<std::endl;
        return 1;
    }

    File.seekp(0,std::ios::end);
    
    AutoAppEnter(File);
    AutoAppEnter(Plus);

    Title("欢迎来到核心积累模式");
    Tips("输入 =help 以获取功能菜单");

    IsNewDay(File);

    while(flag!="1")
    {
        flag=AddWord(File,Plus);
        if(flag!="0"&&flag!="1")
        {
            Functions(p,flag);
        }
    }
    File.close();

    Notation("退出成功");

    return 0;
}

//在某个文件内进行查找（需要用到打包，以更好呈现内容）


//大复习