#include<string>
#include<vector>
#include<iostream>

class Word
{
public:
    std::string word;
    std::string meaning;

public:
    Word() :word("0"), meaning("1") {};
    Word(std::string& inword, std::string& inmeaning) :word(inword), meaning(inmeaning) {};
    Word(const Word& other) : word(other.word), meaning(other.meaning) {}
    void reset();
    
    bool operator>(const Word& word1);
    bool operator<(const Word& word1);
    friend std::ostream& operator<<(std::ostream& os,const Word& word);
    Word& operator=(const Word& word1);
};

class WordPlus :public Word
{
public:
    std::vector<std::string> Sentences;
    std::string WordClass;
    std::vector<std::string> Phrases;
    std::vector<std::string> PhrasesMeaning;

public:
    WordPlus():Word(),Sentences(0),WordClass("0"),Phrases(0),PhrasesMeaning(0){};
    WordPlus(std::string& inword, std::string& inmeaning,std::string& insentence, std::string& inclass){};
    WordPlus(const WordPlus& other)
    {
    word=other.word;
    meaning=other.meaning;
    Sentences=other.Sentences;
    WordClass=other.WordClass;
    Phrases=other.Phrases;
    PhrasesMeaning=other.PhrasesMeaning;
    };
    void reset();
    friend std::ostream& operator<<(std::ostream& os,const WordPlus& wordplus);
    friend void GetWordPlus(WordPlus& wordplus);
    friend WordPlus BeWordPlus(std::string const& inword,std::string const& inmeaning);
};

void GetWordPlus(WordPlus& wordplus);
WordPlus BeWordPlus(std::string const& inword,std::string const& inmeaning);