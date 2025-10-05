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
#define BOOK_FILE_PATH "C:\\Users\\29548\\Desktop\\Sunshine\\Words\\BOOK.txt"

struct FileConfig
{

};

class Singles
{
    std::ifstream InFile;
    std::ifstream PlusInFile;
    std::ofstream OutFile;

};