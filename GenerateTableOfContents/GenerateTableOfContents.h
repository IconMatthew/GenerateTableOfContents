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
*\brief ���� �������� ��������� ������� ���������, � ����� ��������� ������, ������������ ��� ������ ���������� ���������� � �� �������.
*/

/**
* @brief ���������, ���������� ���������� ��������� � �� ������.
*/
struct headers {
    /// <summary>������ � ���������� ������� ����������.</summary>
    std::vector<std::string> header;
    /// <summary>������ � ����������� �������� ����������.</summary>
    std::vector<std::string> headerLevel;
};
/**
* @brief ��������� ����� �� �������� �����, ��������� ������������� �� ���������� ����� � ������ ����������� ���������, ������� ������, ���� ����.
* @param[in] - InputfileName - ��� �������� �����.
* @return InputHTML - ������, ���������� ��� ������ �������� �����.
* <summary>������ ������ �������:</summary>
  *\code
    std::string inputHTML = readHtmlFileToString(&inputFileName);
  *\endcode
*/
std::string readHtmlFileToString(const char** InputfileName);

/**
* @brief ��������� ��������� � ��������� � ��������� ������ headers.
* @param[in] - InputHTML - ������, ���������� ��� ������ �������� �����.
* @param[out] - headerList - ���������, ���������� ��������� � �� ������.
* @return True/False - ���� �� �������� ���������.
* <summary>������ ������ �������:</summary>
  *\code
    bool headersFound = insertHeaderTagsInHeadersStructure(inputHTML, &headerList);
  *\endcode
*/
bool insertHeaderTagsInHeadersStructure(const std::string& inputHTML, headers* headerList);

/**
* @brief ��������� � �������� ������ ��� ���������� ��������� � ���� ����������� ��� ���.
* @param[in] - headerList - ���������, ���������� ��������� � �� ������.
* @param[out] - outputHeaders - ����� ��������� �����.
* <summary>������ ������ �������:</summary>
  *\code
    insertNestsForHeadersInOutputVector(&headerList, outputHeaders);
  *\endcode
*/
void insertNestsForHeadersInOutputVector(headers* headerList, std::vector<std::string>& outputHeaders);

/**
* @brief ��������� ������ ���������� �����������/����������� ����� ���������������� ������ � ����������� �� ������� ��������� � �������� ������, ���������� �������������� ��� HTML ��������.
* @param[in] - indexOfHeader - ������� �������� ���������.
* @param[in] - isOpenNest - ��� ����, ������� ���������� ��������.
* @param[in, out] - outputHeaders - ������ ����������.
* <summary>������ ������ �������:</summary>
  *\code
    insertULTagsInOutputVector(currentHeaderIndex - previousHeaderIndex, outputHeaders, true);
  *\endcode
*/
void insertULTagsInOutputVector(int levelOfHeader, std::vector<std::string>& outputHeaders, bool isOpenNest);

/**
* @brief ������ ��� HTML �������� � ��������� ���������� ��������� ���������.
* @param[in, out] - outputHeaders - ������, ���������� ��������� � ������ �����������.
* <summary>������ ������ �������:</summary>
  *\code
    formOutputHtmlCode(outputHeaders);
  *\endcode
*/
void formOutputHtmlCode(std::vector<std::string>& outputHeaders);

/**
* @brief ������ ��� HTML �������� � ��������� ���������� ��������� ���������.
* @param[in] - outputFileName - ��� ��������� �����.
* @param[in] - outputHTML - ����� ��������� �����.
* <summary>������ ������ �������:</summary>
  *\code
    printOutputHtmlCodeIntoOutputFile(&outputFileName, outputHeaders);
  *\endcode
*/
void printOutputHtmlCodeIntoOutputFile(const char** outputFileName, const std::vector<std::string>& outputHTML);