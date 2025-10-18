#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <windows.h>

#include "FunctionNew.h"

using namespace std;

AppConfig& config0=AppConfig::instance();


int main()
{
    SetConsoleOutputCP(CP_UTF8); // 设置控制台输出编码为UTF-8
    SetConsoleCP(CP_UTF8);       // 设置控制台输入编码为UTF-8

    if(IsFirstRun()){
        AppConfigInitialize();      //进行应用初始化
    }
    
    BigTitle("欢迎来到WordTina!你的贴心单词积累系统");
    string flag;

    while(1){
        Menu();
        Tips("建议先看一下使用指南");
        
        cout<<"请输入你要使用的功能代号:";
        cin>>flag;

        if(flag=="0"){
            Notation("欢迎你的下次使用,祝你天天开心");
            return 0;
        }else if(flag=="1"){
            Notation("您已进入核心交互模式");
            CoreAddWords(config0.WORDS());
        }else if(flag=="2"){
            Notation("别催了别催了在做了在做了呜呜呜呜呜呜");
        }else if(flag=="3"){
            Notation("别催了别催了在做了在做了呜呜呜呜呜呜");
        }else if(flag=="4"){
            Notation("别催了别催了在做了在做了呜呜呜呜呜呜");
        }else if(flag=="#"){
            Bible();
        }else if(flag=="？"||flag=="?"){
            Menu2();
        }else{
            Notation("无法识别，请重新输入");
        }
    }

    return 0;
}