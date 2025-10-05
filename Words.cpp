#include "Words.h"

/*----------Word成员函数实现------------*/
bool Word::operator>(const Word& word1)
{
    return word>word1.word;
}

bool Word::operator<(const Word& word1)
{
    return word < word1.word;
}

Word& Word::operator=(const Word& word1)
{
    if(this!= &word1)
    {
        word = word1.word;
        meaning = word1.meaning;
    }
    return *this;
}

/*-----------Word输出实现------------*/
std::ostream& operator<<(std::ostream& os,const Word& word)
{
    os << word.word <<"   "<< word.meaning << std::endl;
    return os;
}

/*--------WordPlus成员函数实现--------*/
void WordPlus::reset()
{
    word='0';
    meaning='0';
    Sentences=std::vector<std::string> (0);
    WordClass="0";
    Phrases=std::vector<std::string> (0);
    PhrasesMeaning=std::vector<std::string> (0);
}

/*--------WordPlus输出与输入实现--------*/
std::ostream& operator<<(std::ostream& os,const WordPlus& p)
{
    int n1=p.Phrases.size(),n2=p.Sentences.size(),i;
    os<<p.word<<'\n'<<p.WordClass<<' '<<p.meaning<<std::endl;
    for(i=0;i<n1;i++)
    {
        os<<'-'<<p.Phrases[i]<<"  "<<p.PhrasesMeaning[i]<<std::endl;
    }
    for(i=0;i<n2;i++)
    {
        os<<'-'<<p.Sentences[i]<<std::endl;
    }
    return os;
}


void GetWordPlus(WordPlus& wordplus)
{
    std::string flag="-1",phrase,pmeaning,sentence;
    while(flag!="1")
    {
        std::cout<<"请输入单词、词性与中文释义（均用空格隔开）:"<<std::endl;
        std::cin>>wordplus.word;
        if(wordplus.word=="0") goto end;
        std::cin>>wordplus.WordClass>>wordplus.meaning;
        std::cout<<"\n您刚刚输入的是：\n"<<wordplus.word<<'\n'<<wordplus.WordClass<<' '<<wordplus.meaning<<"\n确认无误请输入1:";
        std::cin>>flag;
    }
    flag="-1";

    while(phrase!="0"&&pmeaning!="0")
    {
        std::cout<<"正在添加词组……\n若不添加请任意一项输入0\n"<<std::endl;
        while(flag!="1")
        {
            std::cout<<"请输入词组与中文释义（换行隔开）："<<std::endl;
            while(getchar()!='\n');
            getline(std::cin,phrase);
            if(phrase=="0")
                break;
            getline(std::cin,pmeaning);
            if(pmeaning=="0")
                break;
            std::cout<<"\n您刚刚输入的是："<<phrase<<' '<<pmeaning<<"\n确认无误请输入1:";
            std::cin>>flag;
            while(getchar()!='\n');
        }
        if(phrase=="0"||pmeaning=="0")
            break;
        wordplus.Phrases.emplace_back(phrase);
        wordplus.PhrasesMeaning.emplace_back(pmeaning);
        std::cout<<"已插入数组\n"<<std::endl;
        flag="-1";
    }
    std::cout<<"一共输入了"<<wordplus.Phrases.size()<<"个词组及释义\n"<<std::endl;

    while(sentence!="0")
    {
        std::cout<<"正在进行相关例句(停止添加请输入0)："<<std::endl;
        while(flag!="1")
        {
            std::cout<<"请输入相关例句（回车结束）："<<std::endl;

            getline(std::cin,sentence);
            if(sentence=="0")
                break;
            std::cout<<"\n您刚刚输入的是："<< sentence <<"\n确认无误请输入1:";
            std::cin>>flag;
            while(getchar()!='\n');
        }
        if(sentence=="0")
            break;
        wordplus.Sentences.emplace_back(sentence);
        std::cout<<"已插入数组\n"<<std::endl;
        flag="-1";
    }
    std::cout<<"一共输入了"<<wordplus.Sentences.size()<<"个例句\n"<<std::endl;
    end:
    return;
}

WordPlus BeWordPlus(std::string const& inword,std::string const& inmeaning)
{
    WordPlus wordplus;
    wordplus.word=inword;
    wordplus.meaning=inmeaning;

    std::string flag="-1",phrase,pmeaning,sentence;
    while(flag!="1")
    {
        std::cout<<"请补充词性:"<<std::endl;
        std::cin>>wordplus.WordClass;
        if(wordplus.word=="0"||wordplus.WordClass=="0") goto end;
        std::cout<<"\n此输入是：\n"<<wordplus.word<<'\n'<<wordplus.WordClass<<' '<<wordplus.meaning<<"\n确认无误请输入1:";
        std::cin>>flag;
    }
    flag="-1";

    while(phrase!="0"&&pmeaning!="0")
    {
        std::cout<<"正在添加词组……\n若不添加请任意一项输入0\n"<<std::endl;
        while(flag!="1")
        {
            std::cout<<"请输入词组与中文释义（换行隔开）："<<std::endl;
            getline(std::cin,phrase);
            if(phrase=="0")
                break;
            getline(std::cin,pmeaning);
            if(pmeaning=="0")
                break;
            std::cout<<"\n您刚刚输入的是："<<phrase<<' '<<pmeaning<<"\n确认无误请输入1:";
            std::cin>>flag;
            while(getchar()!='\n');
        }
        if(phrase=="0"||pmeaning=="0")
            break;
        wordplus.Phrases.emplace_back(phrase);
        wordplus.PhrasesMeaning.emplace_back(pmeaning);
        std::cout<<"已插入数组\n"<<std::endl;
        flag="-1";
    }
    std::cout<<"一共输入了"<<wordplus.Phrases.size()<<"个词组及释义\n"<<std::endl;

    while(sentence!="0")
    {
        std::cout<<"正在进行相关例句(停止添加请输入0)："<<std::endl;
        while(flag!="1")
        {
            std::cout<<"请输入相关例句（回车结束）："<<std::endl;
            getline(std::cin,sentence);
            if(sentence=="0")
                break;
            std::cout<<"\n您刚刚输入的是："<< sentence <<"\n确认无误请输入1:";
            std::cin>>flag;
            while(getchar()!='\n');
        }
        if(sentence=="0")
            break;
        wordplus.Sentences.emplace_back(sentence);
        std::cout<<"已插入数组\n"<<std::endl;
        flag="-1";
    }
    std::cout<<"一共输入了"<<wordplus.Sentences.size()<<"个例句\n"<<std::endl;
    
    std::cout<<"已完成本次深度积累\n"<<std::endl;

    end:
    return wordplus;
}