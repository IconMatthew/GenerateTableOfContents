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
   ��������� ����� �� �������� �����, ��������� ������������� �� ���������� ����� � ������ ����������� ���������, 
   ������� ������, ���� ����.
   param[in] - InputfileName - ��� �������� �����.
   return - InputHTML - ������, ���������� ��� ������ �������� �����.
*/
std::string readHtmlFileToString(const char** InputfileName);


/*
   ��������� ��������� � ��������� � ��������� ������ headers.
   param[in] - InputHTML - ������, ���������� ��� ������ �������� �����.
   param[out] - headerList - ���������, ���������� ��������� � �� ������.
   return - ���� �� �������� ���������.
*/
bool insertHeaderTagsInHeadersStructure(const std::string& inputHTML, headers* headerList);

/*
   ��������� � �������� ������ ��� ���������� ��������� � ���� ����������� ��� ���.
   param[in] - headerList - ���������, ���������� ��������� � �� ������.
   param[out] - outputHeaders - ����� ��������� �����.
*/
void insertNestsForHeadersInOutputVector(headers* headerList, std::vector<std::string>& outputHeaders);

/*
   ��������� ������ ���������� �����������/����������� ����� ���������������� ������ 
   � ����������� �� ������� ��������� � �������� ������, 
   ���������� �������������� ��� HTML ��������.
   param[in] - indexOfHeader - ������� �������� ���������.
   param[in] - isOpenNest - ��� ����, ������� ���������� ��������.
   param[in/out] - outputHeaders - ������ ����������.
*/
void insertULTagsInOutputVector(int levelOfHeader, std::vector<std::string>& outputHeaders, bool isOpenNest);

/*
   ������ ��� HTML �������� � ��������� ���������� ��������� ���������.
   param[in/out] - outputHeaders - ������, ���������� ��������� � ������ �����������.
   param[in] - headerList - ���������, ���������� ��������� � �� ������.
*/
void formOutputHtmlCode(std::vector<std::string>& outputHeaders, headers* headerList);

/*
   ������ ��� HTML �������� � ��������� ���������� ��������� ���������.
   param[in] - outputFileName - ��� ��������� �����.
   param[in] - outputHTML - ����� ��������� �����.
*/
void printOutputHtmlCodeIntoOutputFile(const char** outputFileName, const std::vector<std::string>& outputHTML);