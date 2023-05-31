#pragma once
#include <sstream>
#include <regex>
#include <string>
#include <vector>
#include <stdexcept>
#include <locale.h>
#include "Windows.h"
using namespace std;

/*!
*\file
*\brief Файл содержит заголовки функций программы, а также структуру данных, используемую для записи выделенных заголовков и их уровней.
*/

/**
* @brief Структура, содердащая выделенные заголовки и их уровни.
*/
struct headers {
    /// <summary>Список с выделенным текстом заголовков.</summary>
    std::vector<std::string> header;
    /// <summary>Список с выделенными уровнями заголовков.</summary>
    std::vector<std::string> headerLevel;
};
/**
* @brief Считывает текст из входного файла, проверяет удовлетворяет ли количество строк в тексте допустимому диапазону, выводит ошибки, если есть.
* @param[in] - InputfileName - имя входного файла.
* @return InputHTML - строка, сожержащая все строки входного файла.
* <summary>Пример вызова функции:</summary>
  *\code
    std::string inputHTML = readHtmlFileToString(&inputFileName);
  *\endcode
*/
std::string readHtmlFileToString(const char** InputfileName);

/**
* @brief Считывает заголовки с индексами в структуру данных headers.
* @param[in] - InputHTML - строка, сожержащая все строки входного файла.
* @param[out] - headerList - структура, содержащая заголовки и их уровни.
* @return True/False - были ли выделены заголовки.
* <summary>Пример вызова функции:</summary>
  *\code
    bool headersFound = insertHeaderTagsInHeadersStructure(inputHTML, &headerList);
  *\endcode
*/
bool insertHeaderTagsInHeadersStructure(const std::string& inputHTML, headers* headerList);

/**
* @brief Добавляет в выходной вектор все выделенные заголовки и теги вложенности для них.
* @param[in] - headerList - структура, содержащая заголовки и их уровни.
* @param[out] - outputHeaders - текст выходного файла.
* <summary>Пример вызова функции:</summary>
  *\code
    insertNestsForHeadersInOutputVector(&headerList, outputHeaders);
  *\endcode
*/
void insertNestsForHeadersInOutputVector(headers* headerList, std::vector<std::string>& outputHeaders);

/**
* @brief Добавляет нужное количество открывающих/закрывающих тегов неупорядоченного списка в зависимости от индекса заголовка в выходной вектор, содержащий сформированный код HTML страницы.
* @param[in] - indexOfHeader - уровень текущего заголовка.
* @param[in] - isOpenNest - тип тега, который необходимо вставить.
* @param[in, out] - outputHeaders - список заголовков.
* <summary>Пример вызова функции:</summary>
  *\code
    insertULTagsInOutputVector(currentHeaderIndex - previousHeaderIndex, outputHeaders, true);
  *\endcode
*/
void insertULTagsInOutputVector(int levelOfHeader, std::vector<std::string>& outputHeaders, bool isOpenNest);

/**
* @brief Создаёт код HTML страницы и добавляет выделенные вложенные заголовки.
* @param[in, out] - outputHeaders - список, содержащий заголовки с учётом вложенности.
* <summary>Пример вызова функции:</summary>
  *\code
    formOutputHtmlCode(outputHeaders);
  *\endcode
*/
void formOutputHtmlCode(std::vector<std::string>& outputHeaders);

/**
* @brief Создаёт код HTML страницы и добавляет выделенные вложенные заголовки.
* @param[in] - outputFileName - имя выходного файла.
* @param[in] - outputHTML - текст выходного файла.
* <summary>Пример вызова функции:</summary>
  *\code
    printOutputHtmlCodeIntoOutputFile(&outputFileName, outputHeaders);
  *\endcode
*/
void printOutputHtmlCodeIntoOutputFile(const char** outputFileName, const std::vector<std::string>& outputHTML);