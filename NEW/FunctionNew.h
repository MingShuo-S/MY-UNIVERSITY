#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <filesystem>

namespace fs=std::filesystem;

//========================================================================================//
/*--------全局变量--------*/
const std::map <std::string,std::string> menu;
const std::map <std::string,std::string> func;


const std::vector<std::string> 
//如果这些字符在行首，那么输出的时候就忽略这一行（输入的写了太多了不想改了（死））
ignore,
//如果这个字符在行首，那么说明这一行隶属于上面的单词（写入的时候删掉这个字符）
affiliate,
//用于保存预设的提示句
tips;


//========================================================================================//
/*--------辅助功能--------*/
/*---中转---*/
int Functions(fs::path p,std::string order);


/*---良输入---*/
int GetNum_s();

/*---判断---*/
bool IsFileWritePosAtEnd(std::fstream& f);
bool IsSimilarWord(std::string target,std::string ano,double accuracy=0.7);

bool IsAtHeadoftheLine(std::fstream& p);

//========================================================================================//
/*--------基础功能--------*/
/*---显示---*/
//打一定量空格
void Space(int n);

//标题格式输出
void Title(const std::string& a);

void BigTitle(const std::string& a);
//Tips格式输出
void Tips(const std::string& tip);

//Notation格式输出
void Notation(const std::string& note);

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
void AutoAppEnter(std::fstream& p);

//打包一个word
Word Pack(std::fstream& File);

//将文件内容打包为vector<Word>,进而方便排序
std::vector<Word> PackAll(fs::path filepath);

//将文件指定内容打包为vector<Word>,进而方便排序
std::vector<Word> PackPortion(fs::path filepath,int start=0,int end=99999);

//将位置数组代表的单词全都打包至数组当中 /2
std::vector<Word> PackPortion(fs::path filepath,std::vector<std::streampos> poses);

/*---输入---*/
//交互式普通输入文件，一次一个词（检测到在单词侧首位输入'='时或只输入'0'退出） 
//// -'='表示进入指令  -'0'该程序默认退出符
std::string AddWord(std::fstream& f);

//===不想做直接的深度积累功能了===
//交互式确认是否要进入新的一天
void IsNewDay(std::fstream& AppFile);
/*---切换---*/
//普通输入后进入深度积累（单次进入） BeWordPlus();<Words.h>


/*---检索---*/
//返回最新天数
int GetLatestDay(fs::path path);

//返回指定天数所在位置（的该行首位）
std::streampos GetDayNPos(fs::path path,int n);

//返回指定单词位置（在单词行首位）
std::vector<std::streampos> GetWordPoses(fs::path path,std::string target);

/*---搜索---*/ /*2*/
//文件内单次模糊搜索，存入数组
std::vector<Word> FuzzySearch(fs::path path,std::string target);

//文件内单次精确搜索，存入数组
std::vector<Word> Search(fs::path path,std::string target);

//查找形近词，存入数组
std::vector<Word> SearchSimilarWords(fs::path p,std::string target,int baseline=5);

//根据词根词缀查找相关单词，存入数组
std::vector<Word> SearchWithRootorAffixe(fs::path p,std::string target);

/*---修改---*/
//指定已在文件中的单词进行深度积累，并覆盖原有单词记录（只是在原有单词处写一个删除标记再重新计入）


//删掉这个单词（单一功能，给单词和注释在的这几行前面都加上~）
int Delete(fs::path p,std::streampos pos);

//大量删除的时候使用，免得一直开关文件把文件炸了
int Delete(fs::path p,std::vector<std::streampos> poses);
//指定修改文件中的单词内容（交互式,以免改错）  //2
void InteractiveModify(fs::path p,std::string target);

//交互式删除某个单词或某日标记
void InteractiveDelete(fs::path p,std::string target);

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
void Menu();
//指令菜单（转换）
void Menu2();


//========================================================================================//
/*--------应用功能--------*/
//进行单次排序，包括输入与输出（堆排序在头文件中已经有了），会使用到打包


//将单词输入文件（核心交互模式）


//在某个文件内进行模糊查找（需要用到打包，以更好呈现内容）


//大复习


//已有单词修改or增加深度积累