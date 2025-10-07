#include "INIT.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

//是否首次运行检查
bool IsFirstRun()
{
    fs::path flagFile=configDir/".first_run_flag";
    if(!fs::exists(flagFile))
    {
        std::ofstream(flagFile).close();
        return true;
    }
    else
        return false;
}



//类方法实现
void AppConfig::initialize(const fs::path& AppFile)
{
    if(!initialized_)
    {
        try{
            ConfigFile=AppFile/"Config";
            fs::create_directory(ConfigFile);

            WORDS_=ConfigFile/"WORDS.txt";
            AFTER_WORDS_=ConfigFile/"AFTER_WORDS.txt";
            PLUSWORDS_=ConfigFile/"PLUSWORDS.txt";
            PLUSAFTER_WORDS_=ConfigFile/"PLUSAFTER_WORDS.txt";
            BOOK_=ConfigFile/"BOOK.txt";
            UPPER_WORDS_=ConfigFile/"UPPER_WORDS.txt";

            CreatFileIfNotExists(WORDS_);
            CreatFileIfNotExists(AFTER_WORDS_);
            CreatFileIfNotExists(PLUSWORDS_);
            CreatFileIfNotExists(PLUSAFTER_WORDS_);
            CreatFileIfNotExists(BOOK_);
            CreatFileIfNotExists(UPPER_WORDS_);

            initialized_=true;

        }catch(const fs::filesystem_error& e){
            throw std::runtime_error("Filesystem error: " + std::string(e.what()));
        }
    }
}

void AppConfig::CreatFileIfNotExists(const fs::path& filePath)
{
    if(!fs::exists(filePath))
        std::ofstream(filePath).close();
}


//正式初始化
int AppConfigInitialize()
{
    if(IsFirstRun())
    {
        std::cout<<"检测到此为第一次运行……正在进行初始化，请耐心等待……\n"<<std::endl;
        extern AppConfig CFile;
        CFile.instance();
        CFile.initialize(configDir);
        std::cout<<"初始化已完成，祝您在本应用体验愉快\n"<<std::endl;
        return 0;
    }
    else
        return 1;
}