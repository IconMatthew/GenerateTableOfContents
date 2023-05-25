#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

struct headers
{
    string header;
    string headerLevel;
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
void insertNestsForHeadersInOutputVector(headers * headerList, vector <string> outputHeaders);

/*
   ��������� ������ ���������� �����������/����������� ����� ���������������� ������ 
   � ����������� �� ������� ��������� � �������� ������, 
   ���������� �������������� ��� HTML ��������.
   param[in] - indexOfHeader - ������� �������� ���������.
   param[in] - isOpenNest - ��� ����, ������� ���������� ��������.
   param[in/out] - outputHeaders - ������ ����������.
*/
void insertULTagsInOutputVector(int levelOfHeader, vector <string> outputHeaders, bool isOpenNest);

/*
   ������ ��� HTML �������� � ��������� ���������� ��������� ���������.
   param[in/out] - outputHeaders - ������, ���������� ��������� � ������ �����������.
   param[in] - headerList - ���������, ���������� ��������� � �� ������.
*/
void formOutputHtmlCode(vector <string> outputHeaders, headers* headerList);

/*
   ������ ��� HTML �������� � ��������� ���������� ��������� ���������.
   param[in] - outputFileName - ��� ��������� �����.
   param[in] - outputHTML - ����� ��������� �����.
*/
void printOutputHtmlCodeIntoOutputFile(char** outputFileName, vector <string> outputHTML);