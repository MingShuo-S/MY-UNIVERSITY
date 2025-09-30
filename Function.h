#include<string>

/*提取文件WORD.txt中的单词，并将其排序扔进AFTER.txt文件中*/
int SortintoAFTER();

/*从文件AFTER.txt中查找所输入单词，若有则返回单词和中文释义，输入0结束*/
std::string SearchInAfter(std::string& word1);

/*从文件WITH_SENTENCE.txt中查找所输入单词，若有则返回单词、中文释义、词性与例句，输入0结束*/
int SearchInWithSentence(std::string& word1);

/*n次换行*/
void ENTERN(int n);

/*添加新单词及释义进WORDS.txt*/
int AddWordInWORDS();

/*在WORDS.txt中查看第n天记录的单词*/
int LookUpDay(int n);

/*返回最新一天是第几天*/
int GetLatestDay();

/*安全地输入一个数字*/
int GetNum_s();

/*模糊查找单词/词根/词缀/中文释义*/
int FuzzySearch();

/*深度积累，在积累单词的时候可以输入对应的词性、词组、例句，输入至DEEP_ACCUMULATION.txt，并将单词与释义同步到WORD.txt*/
int DeepAccumulation();

/*提取文件DEEP_ACCUMULATION.txt中的单词，并将其排序扔进AFTER_DEEP_ACCUMULATION.txt文件中*/
int DASortIntoAfter();



//内部函数：
void AutoAppEnter(std::fstream& p); //可以自动检查是否需要在输入开头换行，避免直接跟到同一行末尾
