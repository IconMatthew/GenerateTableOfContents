#pragma once
#include <sstream>
#include <regex>
#include <string>
#include <vector>
#include <stdexcept>
#include <locale.h>
#include "Windows.h"
using namespace std;

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
*/
std::string readHtmlFileToString(const char** InputfileName);

/**
* @brief ��������� ��������� � ��������� � ��������� ������ headers.
* @param[in] - InputHTML - ������, ���������� ��� ������ �������� �����.
* @param[out] - headerList - ���������, ���������� ��������� � �� ������.
* @return ���� �� �������� ���������.
*/
bool insertHeaderTagsInHeadersStructure(const std::string& inputHTML, headers* headerList);

/**
* @brief ��������� � �������� ������ ��� ���������� ��������� � ���� ����������� ��� ���.
* @param[in] - headerList - ���������, ���������� ��������� � �� ������.
* @param[out] - outputHeaders - ����� ��������� �����.
*/
void insertNestsForHeadersInOutputVector(headers* headerList, std::vector<std::string>& outputHeaders);

/**
* @brief ��������� ������ ���������� �����������/����������� ����� ���������������� ������ � ����������� �� ������� ��������� � �������� ������, ���������� �������������� ��� HTML ��������.
* @param[in] - indexOfHeader - ������� �������� ���������.
* @param[in] - isOpenNest - ��� ����, ������� ���������� ��������.
* @param[in, out] - outputHeaders - ������ ����������.
*/
void insertULTagsInOutputVector(int levelOfHeader, std::vector<std::string>& outputHeaders, bool isOpenNest);

/**
* @brief ������ ��� HTML �������� � ��������� ���������� ��������� ���������.
* @param[in, out] - outputHeaders - ������, ���������� ��������� � ������ �����������.
*/
void formOutputHtmlCode(std::vector<std::string>& outputHeaders);

/**
* @brief ������ ��� HTML �������� � ��������� ���������� ��������� ���������.
* @param[in] - outputFileName - ��� ��������� �����.
* @param[in] - outputHTML - ����� ��������� �����.
*/
void printOutputHtmlCodeIntoOutputFile(const char** outputFileName, const std::vector<std::string>& outputHTML);