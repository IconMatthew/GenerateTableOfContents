#include "pch.h"
#include "CppUnitTest.h"
#include "../GenerateTableOfContents/GenerateTableOfContents.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestingGenerateTableOfContents
{
	TEST_CLASS(TestingGenerateTableOfContents)
	{
	public:

		// Тесты для insertHeaderTagsInHeadersStructure
		TEST_METHOD(inputTextHasNoHeaders)
		{
			std::string inputHTML = "<!DOCTYPE html> <html lang = \"en\"> <head> <meta charset = \"UTF-8\"> <title>Example< / title> < / head> <body> <div class = \"headers\"> < / div> < / body> < / html>";
			bool headersFound;
			bool error = false;
			bool sampleError = false;
			headers headerList1;

			try {
				headersFound = insertHeaderTagsInHeadersStructure(inputHTML, &headerList1);
			}
			catch (const std::exception& e) {
				error = &e;
			}

			vector<string> sampleHeaders = { "" };
			vector<string> sampleHeaderLevels = { "" };
			Assert::AreEqual(headersFound, false);

			for (int i = 0; i < headerList1.header.size(); ++i) {
				Assert::AreEqual(headerList1.header[i], sampleHeaders[i]);
				Assert::AreEqual(headerList1.headerLevel[i], sampleHeaderLevels[i]);
			}
			Assert::AreEqual(error, sampleError);
		}

		TEST_METHOD(inputTextHasOneHeader)
		{
			std::string inputHTML = "<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF - 8\"> <title>Example</title> </head> <body> <div class=\"headers\"> <h1>Заголовок 1</h1> </div> </body> </html>";
			bool headersFound;
			bool error = false;
			bool sampleError = false;
			headers headerList2;

			try {
				headersFound = insertHeaderTagsInHeadersStructure(inputHTML, &headerList2);
			}
			catch (const std::exception& e) {
				error = &e;
			}

			vector<string> sampleHeaders = { "Заголовок 1" };
			vector<string> sampleHeaderLevels = { "1" };
			Assert::AreEqual(headersFound, true);

			for (int i = 0; i < headerList2.header.size(); ++i) {
				Assert::AreEqual(headerList2.header[i], sampleHeaders[i]);
				Assert::AreEqual(headerList2.headerLevel[i], sampleHeaderLevels[i]);
			}
			Assert::AreEqual(error, sampleError);
		}

		TEST_METHOD(inputTextHasTwoHeader)
		{
			std::string inputHTML = "<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF - 8\"> <title>Example</title> </head> <body> <div class=\"headers\"> <h1>Заголовок 1</h1> <h2>Заголовок 2</h2> </div> </body> </html>";
			bool error = false;
			bool headersFound;
			bool sampleError = false;
			headers headerList3;

			try {
				headersFound = insertHeaderTagsInHeadersStructure(inputHTML, &headerList3);
			}
			catch (const std::exception& e) {
				error = &e;
			}

			vector<string> sampleHeaders = { "Заголовок 1", "Заголовок 2" };
			vector<string> sampleHeaderLevels = { "1", "2" };
			Assert::AreEqual(headersFound, true);

			for (int i = 0; i < headerList3.header.size(); ++i) {
				Assert::AreEqual(headerList3.header[i], sampleHeaders[i]);
				Assert::AreEqual(headerList3.headerLevel[i], sampleHeaderLevels[i]);
			}
			Assert::AreEqual(error, sampleError);
		}

		TEST_METHOD(inputTextHasSeveralHeaders)
		{
			std::string inputHTML = "<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF - 8\"> <title>Example</title> </head> <body> <div class=\"headers\"> <h1>Заголовок 1</h1> <h2>Заголовок 2</h2> <h3>Заголовок 3</h3> <h4>Заголовок 4</h4> </div> </body> </html>";
			bool error = false;
			bool sampleError = false;
			bool headersFound;
			headers headerList4;

			try {
				headersFound = insertHeaderTagsInHeadersStructure(inputHTML, &headerList4);
			}
			catch (const std::exception& e) {
				error = &e;
			}

			vector<string> sampleHeaders = { "Заголовок 1", "Заголовок 2", "Заголовок 3",  "Заголовок 4" };
			vector<string> sampleHeaderLevels = { "1", "2", "3", "4" };
			Assert::AreEqual(headersFound, true);

			for (int i = 0; i < headerList4.header.size(); ++i) {
				Assert::AreEqual(headerList4.header[i], sampleHeaders[i]);
				Assert::AreEqual(headerList4.headerLevel[i], sampleHeaderLevels[i]);
			}
			Assert::AreEqual(error, sampleError);
		}

		TEST_METHOD(inputTextHasHeaderInsideAnotherHeadersText)
		{
			std::string inputHTML = "<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF - 8\"> <title>Example</title> </head> <body> <div class=\"headers\"> <h1>Заголовок: <h2>Заголовок 2</h2> </h1> </div> </body> </html>";
			bool headersFound = false;
			bool error = false;
			bool sampleError = true;

			headers headerList5;
			try {
				headersFound = insertHeaderTagsInHeadersStructure(inputHTML, &headerList5);
			}
			catch (const std::exception& e) {
				error = &e;
			}

			vector<string> sampleHeaders = { "" };
			vector<string> sampleHeaderLevels = { "" };

			Assert::AreEqual(headersFound, false);
			Assert::AreEqual(error, sampleError);
		}

		TEST_METHOD(inputTextHasSeveralHeadersWithSameLevel)
		{
			std::string inputHTML = "<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF - 8\"> <title>Example</title> </head> <body> <div class=\"headers\"> <h1>Заголовок 1</h2> <h2>Заголовок 2</h2> <h2>Заголовок 3</h2> </div> </body> </html>";
			bool error = false;
			bool sampleError = false;
			bool headersFound;
			headers headerList6;

			try {
				headersFound = insertHeaderTagsInHeadersStructure(inputHTML, &headerList6);
			}
			catch (const std::exception& e) {
				error = &e;
			}

			vector<string> sampleHeaders = { "Заголовок 1", "Заголовок 2", "Заголовок 3" };
			vector<string> sampleHeaderLevels = { "1", "2", "2" };

			Assert::AreEqual(headersFound, true);

			for (int i = 0; i < headerList6.header.size(); ++i) {
				Assert::AreEqual(headerList6.header[i], sampleHeaders[i]);
				Assert::AreEqual(headerList6.headerLevel[i], sampleHeaderLevels[i]);
			}
			Assert::AreEqual(error, sampleError);
		}

		TEST_METHOD(allHeadersInTextAreTheSameLevel)
		{
			bool error = false;
			std::string inputHTML = "<!DOCTYPE html> <html lang = \"en\"> <head> <meta charset = \"UTF - 8\"> <title>Example< / title> < / head> <body> <div class = \"headers\"> <h6>Заголовок 1</h6> <h6>Заголовок 2</h6> <h6>Заголовок 3</h6> < / div> < / body> < / html>";
			bool sampleError = false;
			bool headersFound = false;
			headers headerList7;

			try {
				headersFound = insertHeaderTagsInHeadersStructure(inputHTML, &headerList7);
			}
			catch (const std::exception& e) {
				error = &e;
			}

			vector<string> sampleHeaders = { "Заголовок 1", "Заголовок 2", "Заголовок 3" };
			vector<string> sampleHeaderLevels = { "6", "6", "6" };

			Assert::AreEqual(headersFound, true);

			for (int i = 0; i < headerList7.header.size(); ++i) {
				Assert::AreEqual(headerList7.header[i], sampleHeaders[i]);
				Assert::AreEqual(headerList7.headerLevel[i], sampleHeaderLevels[i]);
			}
			Assert::AreEqual(error, sampleError);
		}

		TEST_METHOD(inputTextHasOnlyOneCommentedHeader)
		{
			bool error = false;
			std::string inputHTML = "<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF - 8\"> <title>Example</title> </head> <body> <div class=\"headers\"> <!-- <h1>Заголовок 1</h1> --> </div> </body> </html>";
			bool sampleError = false;
			bool headersFound = false;
			headers headerList8;

			try {
				headersFound = insertHeaderTagsInHeadersStructure(inputHTML, &headerList8);
			}
			catch (const std::exception& e) {
				error = &e;
			}

			vector<string> sampleHeaders = { "" };
			vector<string> sampleHeaderLevels = { "" };

			Assert::AreEqual(headersFound, true);

			for (int i = 0; i < headerList8.header.size(); ++i) {
				Assert::AreEqual(headerList8.header[i], sampleHeaders[i]);
				Assert::AreEqual(headerList8.headerLevel[i], sampleHeaderLevels[i]);
			}
			Assert::AreEqual(error, sampleError);
		}

		TEST_METHOD(inputTextHasSeveralCommentedHeaders)
		{
			bool error = false;
			std::string inputHTML = "<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF - 8\"> <title>Example</title> </head> <body> <div class=\"headers\"> <!-- <h1>Заголовок 1</h1> <h1>Заголовок 1</h1> --> </div> </body> </html>";
			bool sampleError = false;
			bool headersFound = false;
			headers headerList9;

			try {
				headersFound = insertHeaderTagsInHeadersStructure(inputHTML, &headerList9);
			}
			catch (const std::exception& e) {
				error = &e;
			}

			vector<string> sampleHeaders = { "" };
			vector<string> sampleHeaderLevels = { "" };

			Assert::AreEqual(headersFound, true);

			for (int i = 0; i < headerList9.header.size(); ++i) {
				Assert::AreEqual(headerList9.header[i], sampleHeaders[i]);
				Assert::AreEqual(headerList9.headerLevel[i], sampleHeaderLevels[i]);
			}
			Assert::AreEqual(error, sampleError);
		}

		TEST_METHOD(inputTextHasSeveralCommentedAndUncommentedHeaders)
		{
			bool error = false;
			std::string inputHTML = "<!DOCTYPE html> <html lang=\"en\"> <head> <meta charset=\"UTF - 8\"> <title>Example</title> </head> <body> <div class=\"headers\"> <!--<h6>Заголовок 1</h6> <h6>Заголовок 2</h6> --> <h6>Заголовок 3</h6> <h2>Заголовок 4</h2> </div> </body> </html>";
			bool sampleError = false;
			bool headersFound = false;
			headers headerList10;

			try {
				headersFound = insertHeaderTagsInHeadersStructure(inputHTML, &headerList10);
			}
			catch (const std::exception& e) {
				error = &e;
			}

			vector<string> sampleHeaders = { "Заголовок 3", "Заголовок 4" };
			vector<string> sampleHeaderLevels = { "6", "2" };

			Assert::AreEqual(headersFound, true);

			for (int i = 0; i < headerList10.header.size(); ++i) {
				Assert::AreEqual(headerList10.header[i], sampleHeaders[i]);
				Assert::AreEqual(headerList10.headerLevel[i], sampleHeaderLevels[i]);
			}
			Assert::AreEqual(error, sampleError);
		}

		// Тесты для insertNestsForHeadersInOutputVector

		TEST_METHOD(noHeadersAreHighlighted)
		{
			headers headerList11 = {};
			vector<string> outputHeaders = {};
			insertNestsForHeadersInOutputVector(&headerList11, outputHeaders);

			vector<string> sampleOutputHeaders = {};

			for (int i = outputHeaders.size() - 1; i > 0; i--)
				Assert::AreEqual(outputHeaders[i], sampleOutputHeaders[i]);
		}

		TEST_METHOD(oneHeaderOf1StLevelIsHighlighted)
		{
			headers headerList11 = { {"Заголовок 1"}, {"1"} };
			vector<string> outputHeaders = {};
			insertNestsForHeadersInOutputVector(&headerList11, outputHeaders);

			vector<string> sampleOutputHeaders = { "<ul>", "<li><a href=\"#\">Заголовок 1</a></li>", "</ul>" };

			for (int i = outputHeaders.size() - 1; i > 0; i--)
				Assert::AreEqual(outputHeaders[i], sampleOutputHeaders[i]);
		}

		TEST_METHOD(twoHeadersAreHighlighted1StAnd2dLevel)
		{
			headers headerList11 = { { "Заголовок 1", "Заголовок 2" }, {"1", "2"} };
			vector<string> outputHeaders = {};
			insertNestsForHeadersInOutputVector(&headerList11, outputHeaders);

			vector<string> sampleOutputHeaders = { "<ul>", "<li><a href=\"#\">Заголовок 1</a></li>", "<ul>", "<li><a href=\"#\">Заголовок 2</a></li>", "</ul>", "</ul>"};

			for (int i = outputHeaders.size() - 1; i > 0; i--)
				Assert::AreEqual(outputHeaders[i], sampleOutputHeaders[i]);
		}

		TEST_METHOD(severalHeadersOfDifferentLevelsAreHighlighted)
		{
			headers headerList11 = { { "Заголовок 1", "Заголовок 2", "Заголовок 3" }, {"1", "2", "4"}};
			vector<string> outputHeaders = {};
			insertNestsForHeadersInOutputVector(&headerList11, outputHeaders);

			vector<string> sampleOutputHeaders = { "<ul>", "<li><a href=\"#\">Заголовок 1</a></li>", "<ul>", "<li><a href=\"#\">Заголовок 2</a></li>", "<ul>", "<ul>", "<li><a href=\"#\">Заголовок 3</a></li>", "</ul>", "</ul>", "</ul>", "</ul>" };

			for (int i = outputHeaders.size() - 1; i > 0; i--)
				Assert::AreEqual(outputHeaders[i], sampleOutputHeaders[i]);
		}

		TEST_METHOD(headersOfMaxAndMinLevelsAreHighlighted)
		{
			headers headerList11 = { { "Заголовок 1", "Заголовок 2" }, {"1", "6"} };
			vector<string> outputHeaders = {};
			insertNestsForHeadersInOutputVector(&headerList11, outputHeaders);

			vector<string> sampleOutputHeaders = { "<ul>", "<li><a href=\"#\">Заголовок 1</a></li>", "<ul>", "<ul>", "<ul>", "<ul>", "<ul>", "<li><a href=\"#\">Заголовок 2</a></li>", "</ul>", "</ul>", "</ul>", "</ul>", "</ul>", "</ul>" };

			for (int i = outputHeaders.size() - 1; i > 0; i--)
				Assert::AreEqual(outputHeaders[i], sampleOutputHeaders[i]);
		}

		TEST_METHOD(severalHeadersOfTheSameLevelsAreHighlighted)
		{
			headers headerList11 = { { "Заголовок 1", "Заголовок 2", "Заголовок 3" }, {"3", "3", "3"} };
			vector<string> outputHeaders = {};
			insertNestsForHeadersInOutputVector(&headerList11, outputHeaders);

			vector<string> sampleOutputHeaders = { "<ul>","<ul>","<ul>", "<li><a href=\"#\">Заголовок 1</a></li>", "<li><a href=\"#\">Заголовок 2</a></li>", "<li><a href=\"#\">Заголовок 3</a></li>", "</ul>", "</ul>", "</ul>" };

			for (int i = outputHeaders.size() - 1; i > 0; i--)
				Assert::AreEqual(outputHeaders[i], sampleOutputHeaders[i]);
		}

		// Тесты для функции insertULTagsInOutputVector
		TEST_METHOD(addOpeningTagsForHeaderWithLevel0)
		{
			int levelOfHeader = 0;
			bool isOpeningTag = true;
			vector<string> outputHeaders = { "" };
			vector<string> sampleOutputHeaders = { "" };

			insertULTagsInOutputVector(levelOfHeader, outputHeaders, isOpeningTag);

			for (int i = outputHeaders.size() - 1; i > 0; i--)
				Assert::AreEqual(outputHeaders[i], sampleOutputHeaders[i]);
		}

		TEST_METHOD(addOpeningTagsForHeaderWithLevel1)
		{
			int levelOfHeader = 1;
			bool isOpeningTag = true;
			vector<string> outputHeaders = {""};
			vector<string> sampleOutputHeaders = { "", "<ul>" };

			insertULTagsInOutputVector(levelOfHeader, outputHeaders, isOpeningTag);

			for (int i = outputHeaders.size() - 1; i > 0; i--)
				Assert::AreEqual(outputHeaders[i], sampleOutputHeaders[i]);
		}

		TEST_METHOD(addClosingTagsForHeaderWithLevel1)
		{
			int levelOfHeader = 1;
			bool isOpeningTag = false;
			vector<string> outputHeaders = { "" };
			vector<string> sampleOutputHeaders = { "", "</ul>" };

			insertULTagsInOutputVector(levelOfHeader, outputHeaders, isOpeningTag);

			for (int i = outputHeaders.size() - 1; i > 0; i--)
				Assert::AreEqual(outputHeaders[i], sampleOutputHeaders[i]);
		}

		TEST_METHOD(addOpeningTagsForHeaderWithLevel6)
		{
			int levelOfHeader = 6;
			bool isOpeningTag = true;
			vector<string> outputHeaders = { "" };
			vector<string> sampleOutputHeaders = { "", "<ul>", "<ul>", "<ul>", "<ul>", "<ul>", "<ul>" };

			insertULTagsInOutputVector(levelOfHeader, outputHeaders, isOpeningTag);

			for (int i = outputHeaders.size() - 1; i > 0; i--)
				Assert::AreEqual(outputHeaders[i], sampleOutputHeaders[i]);
		}

		TEST_METHOD(addClosingTagsForHeaderWithLevel6)
		{
			int levelOfHeader = 6;
			bool isOpeningTag = false;
			vector<string> outputHeaders = { "" };
			vector<string> sampleOutputHeaders = { "", "</ul>", "</ul>", "</ul>", "</ul>", "</ul>", "</ul>" };

			insertULTagsInOutputVector(levelOfHeader, outputHeaders, isOpeningTag);

			for (int i = outputHeaders.size() - 1; i > 0; i--)
				Assert::AreEqual(outputHeaders[i], sampleOutputHeaders[i]);
		}

		// Тесты для функции formOutputHtmlCode
		TEST_METHOD(insertInOutputCodeOneHeaderWithLevel2)
		{
			vector<string> outputHeaders = { "<ul>", "<ul>", "<li><a href=\"#\">Заголовок 1</a></li>", "</ul>", "</ul>" };
			vector<string> sampleOutputHeaders = { 
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
				"<ul>",
				"<ul>", "<ul>", "<li><a href=\"#\">Заголовок 1</a></li>", "</ul>", "</ul>",
				"</ul>", "</body>", "</html>"
			};

			formOutputHtmlCode(outputHeaders);

			for (int i = outputHeaders.size() - 1; i > 0; i--)
				Assert::AreEqual(outputHeaders[i], sampleOutputHeaders[i]);
		}

		TEST_METHOD(insertInOutputCodeTwoHeadersWithLevel2)
		{
			vector<string> outputHeaders = { "<ul>", "<ul>", "<li><a href=\"#\">Заголовок 1</a></li>", "<li><a href=\"#\">Заголовок 1</a></li>", "</ul>", "</ul>" };
			vector<string> sampleOutputHeaders = {
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
				"<ul>",
				"<ul>", "<ul>", "<li><a href=\"#\">Заголовок 1</a></li>", "<li><a href=\"#\">Заголовок 1</a></li>", "</ul>", "</ul>",
				"</ul>", "</body>", "</html>"
			};

			formOutputHtmlCode(outputHeaders);

			for (int i = outputHeaders.size() - 1; i > 0; i--)
				Assert::AreEqual(outputHeaders[i], sampleOutputHeaders[i]);
		}

		TEST_METHOD(insertInOutputCodeThreeHeadersWithDifferentLevels)
		{
			vector<string> outputHeaders = { "<ul>", "<li><a href=\"#\">Заголовок 1</a></li>", "<ul>", "<li><a href=\"#\">Заголовок 2</a></li>", "<ul>", "<ul>", "<li><a href=\"#\">Заголовок 3</a></li>", "</ul>", "</ul>", "</ul>", "</ul>" };
			vector<string> sampleOutputHeaders = {
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
				"<ul>",
				"<ul>", "<li><a href=\"#\">Заголовок 1</a></li>", "<ul>", "<li><a href=\"#\">Заголовок 2</a></li>", "<ul>", "<ul>", "<li><a href=\"#\">Заголовок 3</a></li>", "</ul>", "</ul>", "</ul>", "</ul>",
				"</ul>", "</body>", "</html>"
			};

			formOutputHtmlCode(outputHeaders);

			for (int i = outputHeaders.size() - 1; i > 0; i--)
				Assert::AreEqual(outputHeaders[i], sampleOutputHeaders[i]);
		}
	};
}