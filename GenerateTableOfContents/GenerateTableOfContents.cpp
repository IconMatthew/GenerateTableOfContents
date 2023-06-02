#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include <vector>
#include <stdexcept>
#include <locale.h>
#include "Windows.h"
#include "../GenerateTableOfContents/GenerateTableOfContents.h"

using namespace std;

/*!
*\file
*\brief Файл содержит вызываемые функции программы, а также управляющую функцию.
*\mainpage Документация для программы "GenerateTableOfContents"
Программа должна определять оглавление HTML-страницы на основании заголовков «H», а также визуально отображать заголовки и их вложенность при помощи отступов.

Для функционирования программы необходима операционная система Windows 10 или выше.
Программа будет разработана на языке С++ с применением библиотек <iostream>, <fstream>, <sstream>, <string>, <regex>, <vector>, <locale.h>, "Windows.h". Дополнительного программного обеспечения не требуется.
Входные файлы могут быть подготовлены в редакторе Блокнот. Необходимо заменить расширения входных файлов на ".html". Выходные файлы могут быть прочитаны с его помощью.

Стандарт языка ISO C++17 (/std:c++17). Исходный код программы является кроссплатформенным.
Программа должна получать два параметра командной строки: имя входного файла с исходным кодом HTML-страницы и имя файла для записи оглавления страницы.

Пример команды запуска программы:
*\code
GenerateTableOfContents.exe C:\\Documents\input.html C:\\Documents\output.html
*\endcode
*\author Жадаев Матвей Юрьевич
*\date Май 2023 года
*\version 1.0
*/

/* Функция считывает текст из входного файла, проверяет удовлетворяет ли количество строк в тексте допустимому диапазону,
выводит ошибки, если есть.*/
std::string readHtmlFileToString(const char** InputfileName) {

    // Открыть входной файл.
    std::ifstream inputFile(*InputfileName);
    
    // Если не удалось открыть файл - выбросить исключение об ошибке.
    if (!inputFile.is_open()) {
        throw std::runtime_error("Не удалось открыть входной файл. Проверьте введённые параметры.");
    }

    std::string fileContent;
    std::string line;
    int lineCount = 0;
    const int maxLines = 5000;

    // Пока не достигнут конец файла:
    while (std::getline(inputFile, line)) {

        // Увеличить счётчик обнаруженных строк.
        lineCount++;

        // Если счётчик обнаруженных строк превышает максимально-допустимое число строк – выбросить исключение об ошибке.
        if (lineCount > maxLines) {
            throw std::runtime_error("Программа принимает на вход файлы, содержащие не более 5000 строк. Убедитесь, что в исходном файле не более 5000 строк.");
        }

        // Записать текущую строку файла в конец строки, содержащей все строки входного файла.
        fileContent += line + " ";
    }

    inputFile.close();

    // Если счётчик обнаруженных строк меньше 1 – выбросить исключение об ошибке.
    if (lineCount < 1) {
        throw std::runtime_error("Программа принимает на вход файлы, содержащие не менее 1 строки. Убедитесь, что в исходном файле не менее 1 строки.");
    }

    // Вернуть строку, включающую все строки входного файла.
    return fileContent;
}

// Функция выделяет заголовки с их уровнями в структуру данных headers.
bool insertHeaderTagsInHeadersStructure(std::string& inputHTML, headers* headerList) {

    // Создать шаблон (регулярное выражение), по которому будут искаться заголовки в HTML коде.
    std::regex headerRegex("<h[1-6](.*?)>(.*?)<\\/h[1-6]>");
    std::smatch match;

    // Создать шаблон, по которому будет проверяться закомментированность заголовка.
    std::regex commentRegex("<!--.*?-->|<script(.*?)>.*?<\/script>");

    const std::string format("");

    // Удалить все многострочные комментарии и теги script в строке с кодом входного файла вместе с их содержимым.
    const std::string remadeHTML = std::regex_replace(inputHTML, commentRegex, format);

    bool headersFound = false;
    int headerIndex = 0;

    std::string::const_iterator searchStart = remadeHTML.begin();

    // Для каждого совпадения строки, включающей все строки входного файла:
    while (std::regex_search(searchStart, remadeHTML.end(), match, headerRegex)) {
        headersFound = true;

        std::string::const_iterator headerStart = match[0].first;
        std::string::const_iterator headerEnd = match[0].second;

        // Извлечь текст заголовка.
        std::string headerText = match.str(2);

        // Получить заголовок целиком (с тегами H).
        std::string heading = match.str(0);

        std::regex innerHeaderRegex("<h[1-6]");

        // Если внутри выделенного заголовка есть другие h-теги - выбросить исключение об ошибке.
        if (std::regex_search(headerText, innerHeaderRegex)) {
            headersFound = false;
            throw std::runtime_error("Невозможно составить оглавление страницы – во входном файле присутствует заголовок, включающий в себя другой заголовок.");
        }

        // Выделить уровень заголовка.
        headerIndex = heading[2] - '0';

        // Записать заголовок в структуру.
        headerList->header.push_back(headerText);

        // Записать уровень заголовка в структуру.
        headerList->headerLevel.push_back(std::to_string(headerIndex));

        searchStart = match.suffix().first;
        ++headerIndex;
    }

    return headersFound;
}


/* Добавляет нужное количество открывающих/закрывающих тегов неупорядоченного списка
в зависимости от индекса заголовка в вектор заголовков, содержащий сформированный
код HTML страницы.*/
void insertULTagsInOutputVector(int levelOfHeader, std::vector<std::string>& outputHeaders, bool isOpenNest) {
    std::string ulTag;

    // Если необходимо добавить открывающие теги:
    if (isOpenNest) {

        // Сформировать строку с открывающим тегом неупорядоченного списка.
        ulTag = "<ul>";
    }

    // Иначе сформировать строку с закрывающим тегом неупорядоченного списка.
    else {
        ulTag = "</ul>";
    }

    // Записать в выходной вектор нужное количество тегов указанного типа (открывающие/закрывающие).
    for (int i = 0; i < levelOfHeader; ++i) {
        outputHeaders.push_back(ulTag);
    }
}

// Функция добавляет в выходной вектор все выделенные заголовки и теги вложенности для них.
void insertNestsForHeadersInOutputVector(headers* headerList, std::vector<std::string>& outputHeaders) {
    int previousHeaderIndex = 0;

    // Пока в структуре есть заголовки:
    for (int i = 0; i < headerList->header.size(); ++i) {

        int currentHeaderIndex = std::stoi(headerList->headerLevel[i]);
        if (currentHeaderIndex > previousHeaderIndex) {

            // В зависимости от уровня заголовка добавить нужное количество открывающих тегов неупорядоченного списка в вектор.
            insertULTagsInOutputVector(currentHeaderIndex - previousHeaderIndex, outputHeaders, true);
        }
        else if (currentHeaderIndex < previousHeaderIndex) {

            // В зависимости от уровня заголовка добавить нужное количество закрывающих тегов неупорядоченного списка в вектор.
            insertULTagsInOutputVector(previousHeaderIndex - currentHeaderIndex, outputHeaders, false);
        }

        // Добавить текст заголовка, окружённый тегами элемента списка <li> в вектор заголовков.
        outputHeaders.push_back("<li><a href=\"#\">" + headerList->header[i] + "</a></li>");

        previousHeaderIndex = currentHeaderIndex;
    }

    // В зависимости от уровня заголовка добавить нужное количество закрывающих/открывающих тегов неупорядоченного списка в вектор заголовков.
    insertULTagsInOutputVector(previousHeaderIndex, outputHeaders, false);
}

// Создаёт код HTML страницы и добавляет выделенные вложенные заголовки.
void formOutputHtmlCode(std::vector<std::string>& outputHeaders) {

    // Создать вектор, содержащий каркас HTML кода страницы.
    std::vector<std::string> htmlCode = {
        "<!DOCTYPE html>",
        "<html lang=\"en\">",
        "<head>",
        "<meta charset=\"UTF-8\">",
        "<title>Table of contents</title>",
        "<link rel=\"preconnect\" href=\"https://fonts.googleapis.com\">",
        "<link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin>",
        "<link href=\"https://fonts.googleapis.com/css2?family=Open+Sans:wght@300&display=swap\" rel=\"stylesheet\">",
        "</head>",
        "<style>li{list-style-type: none;}\n a{text-decoration: none; color: whitesmoke;}</style>",
        "<body style=\"background: black; color: whitesmoke; font-size: 26px; font-family: 'Open Sans', sans-serif;\">",
        "<h1 style=\"text-align: center; margin: 100px 0 30px 0; font-size: 40px\">Table of contents:</h1>",
        "<ul>"  //Добавить открывающий тег неупорядоченного списка для формирования первого уровня вложенности.
    };

    // Добавить в вектор с каркасом HTML кода выделенные заголовки, обрамлённые тегами элемента списка, с учётом их вложенности.
    for (const std::string& header : outputHeaders) {
        htmlCode.push_back(header);
    }

    // Добавить закрывающий тег неупорядоченного списка для формирования первого уровня вложенности.
    htmlCode.push_back("</ul>");

    // Добавить закрывающие теги каркаса HTML кода.
    htmlCode.push_back("</body>");
    htmlCode.push_back("</html>");

    // Записать выходной список строк сформированной HTML - страницы.
    outputHeaders = std::move(htmlCode);
}

// Создаёт код HTML страницы и добавляет выделенные вложенные заголовки.
void printOutputHtmlCodeIntoOutputFile(const char** outputFileName, const std::vector<std::string>& outputHTML) {

    // Открыть выходной файл.
    std::ofstream outputFile(*outputFileName, std::ios::out | std::ios::binary);

    // Если не удалось создать файл - выбросить исключение об ошибке.
    if (!outputFile.is_open()) {
        throw std::runtime_error("Неверно указан файл для выходных данных. Возможно указанного расположения не существует или нет прав на запись.");
    }
    else {
        // Установить кодек для выходного файла
        outputFile << u8"\uFEFF";

        // Для каждой строки вектора со сформированным кодом HTML:
        for (const std::string& line : outputHTML) {

            // Записать текущую строку выходного вектора в выходной файл.
            outputFile << line << '\n';
        }

    }

    // Закрыть выходной файл
    outputFile.close();
}

/**
* @brief Обеспечивает проверку корректности входного файла, вывод в консоль ошибок, если они есть, вызов функций, решающих задачу.
*/
int main(int argc, char* argv[]) {

    setlocale(LC_ALL, "ru");

    try {

        /*
            Проверить наличие входного и выходного файла в аргументах командной строки.
            Если его нет – выбросить исключение об ошибке.
        */
        if (argc < 3) {
            throw std::runtime_error("Неверные входные параметры. Возможно, файлы не существуют или доступ к ним осуществляется по другому пути.");
        }
        
        const char* inputFileName = argv[1];
        const char* outputFileName = argv[2];        
        
        // Вызвать функцию, считывающую текст из входного файла в строку, содержащую все строки входного файла.
        std::string inputHTML = readHtmlFileToString(&inputFileName);

        // Создать структуру данных, содержащую текст заголовков и их уровени.
        headers headerList;

        // Вызвать функцию, записывающую заголовки и их уровни в структуру заголовков.
        bool headersFound = insertHeaderTagsInHeadersStructure(inputHTML, &headerList);

        // Создать выходной список строк, которые будут записаны в выходной файл.
        vector<string> outputHeaders;

        // Если не был выделен хотя бы один заголовок - выбросить исключение об ошибке.
        if (!headersFound) {
            throw std::runtime_error("Невозможно составить оглавление страницы - во входном файле отсутствуют заголовки.");
        }

        // Иначе
        else {

            // Добавить в выходной вектор все выделенные заголовки и теги вложенности для них.
            insertNestsForHeadersInOutputVector(&headerList, outputHeaders);

            // Вызвать функцию, формирующую список строк выходного кода HTML – страницы.
            formOutputHtmlCode(outputHeaders);

            // Вызвать функцию, записывающую выходной код страницы в выходной файл.
            printOutputHtmlCodeIntoOutputFile(&outputFileName, outputHeaders);
        }

    }

    // Если где-то были выброшены исключения об ошибке: вывести сообщение ошибки в консоль.
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
