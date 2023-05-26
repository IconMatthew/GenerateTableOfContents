#pragma once
#include <sstream>
#include <regex>
#include <string>
#include <vector>
#include <stdexcept>
#include <locale.h>
#include "Windows.h"
using namespace std;

struct headers {
    std::vector<std::string> header;
    std::vector<std::string> headerLevel;
};

/*
   Считывает текст из входного файла, проверяет удовлетворяет ли количество строк в тексте допустимому диапазону, 
   выводит ошибки, если есть.
   param[in] - InputfileName - имя входного файла.
   return - InputHTML - строка, сожержащая все строки входного файла.
*/
std::string readHtmlFileToString(const char** InputfileName);


/*
   Считывает заголовки с индексами в структуру данных headers.
   param[in] - InputHTML - строка, сожержащая все строки входного файла.
   param[out] - headerList - структура, содержащая заголовки и их уровни.
   return - были ли выделены заголовки.
*/
bool insertHeaderTagsInHeadersStructure(const std::string& inputHTML, headers* headerList);

/*
   Добавляет в выходной вектор все выделенные заголовки и теги вложенности для них.
   param[in] - headerList - структура, содержащая заголовки и их уровни.
   param[out] - outputHeaders - текст выходного файла.
*/
void insertNestsForHeadersInOutputVector(headers* headerList, std::vector<std::string>& outputHeaders);

/*
   Добавляет нужное количество открывающих/закрывающих тегов неупорядоченного списка 
   в зависимости от индекса заголовка в выходной вектор, 
   содержащий сформированный код HTML страницы.
   param[in] - indexOfHeader - уровень текущего заголовка.
   param[in] - isOpenNest - тип тега, который необходимо вставить.
   param[in/out] - outputHeaders - список заголовков.
*/
void insertULTagsInOutputVector(int levelOfHeader, std::vector<std::string>& outputHeaders, bool isOpenNest);

/*
   Создаёт код HTML страницы и добавляет выделенные вложенные заголовки.
   param[in/out] - outputHeaders - список, содержащий заголовки с учётом вложенности.
   param[in] - headerList - структура, содержащая заголовки и их уровни.
*/
void formOutputHtmlCode(std::vector<std::string>& outputHeaders, headers* headerList);

/*
   Создаёт код HTML страницы и добавляет выделенные вложенные заголовки.
   param[in] - outputFileName - имя выходного файла.
   param[in] - outputHTML - текст выходного файла.
*/
void printOutputHtmlCodeIntoOutputFile(const char** outputFileName, const std::vector<std::string>& outputHTML);