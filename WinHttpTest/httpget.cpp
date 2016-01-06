// WinHttpTest.cpp : 定义控制台应用程序的入口点。

//

//#include <stdafx.h>

#include <vector>

#include <winsock2.h>

#include <Winhttp.h>
#pragma comment(lib, "winhttp.lib")

//#include <urlmon.h>

#include <windows.h>

#include <iostream>

#include <fstream>

#include <string>

#include "AtlBase.h"

#include "AtlConv.h"

using namespace std;

string GetHost(string strUrl)

{

	int indexHttp = strUrl.find("http://");

	if (indexHttp != -1)

	{

		strUrl = strUrl.substr(7);

	}

	else

		return "";

	int indexSlash = strUrl.find("/");

	if (indexSlash != -1)

	{

		return strUrl.substr(0, indexSlash);

	}

	else

		return strUrl;

	return "";

}



string GetRequestStr(string strUrl)

{

	int indexHttp = strUrl.find("http://");

	if (indexHttp != -1)

	{

		strUrl = strUrl.substr(7);

	}

	else

		return "";

	int indexSlash = strUrl.find("/");

	if (indexSlash == -1)

	{

		return "";

	}

	else

		return strUrl.substr(indexSlash);

}



string GetHtml(string strUrl)

{

	string strHost = GetHost(strUrl);

	string strRequestStr = GetRequestStr(strUrl);

	USES_CONVERSION;

	LPCWSTR host = A2CW(strHost.c_str());

	LPCWSTR requestStr = A2CW(strRequestStr.c_str());



	//Variables 

	DWORD dwSize = 0;

	DWORD dwDownloaded = 0;

	LPSTR pszOutBuffer;

	vector <string>  vFileContent;

	BOOL  bResults = FALSE;

	HINTERNET  hSession = NULL,

		hConnect = NULL,

		hRequest = NULL;



	// Use WinHttpOpen to obtain a session handle.

	hSession = WinHttpOpen(L"WinHTTP Example/1.0",

		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,

		WINHTTP_NO_PROXY_NAME,

		WINHTTP_NO_PROXY_BYPASS, 0);



	// Specify an HTTP server.

	if (hSession)

		hConnect = WinHttpConnect(hSession, host,

			INTERNET_DEFAULT_HTTP_PORT, 0);



	// Create an HTTP request handle.

	if (hConnect)

		hRequest = WinHttpOpenRequest(hConnect, L"GET", requestStr,

			NULL, WINHTTP_NO_REFERER,

			NULL,

			NULL);



	// Send a request.

	if (hRequest)

		bResults = WinHttpSendRequest(hRequest,

			WINHTTP_NO_ADDITIONAL_HEADERS,

			0, WINHTTP_NO_REQUEST_DATA, 0,

			0, 0);





	// End the request.

	if (bResults)

		bResults = WinHttpReceiveResponse(hRequest, NULL);



	// Keep checking for data until there is nothing left.

	if (bResults)

		do

		{



			// Check for available data.

			dwSize = 0;

			if (!WinHttpQueryDataAvailable(hRequest, &dwSize))

				printf("Error %u in WinHttpQueryDataAvailable.\n",

					GetLastError());



			// Allocate space for the buffer.

			pszOutBuffer = new char[dwSize + 1];

			if (!pszOutBuffer)

			{

				printf("Out of memory\n");

				dwSize = 0;

			}

			else

			{

				// Read the Data.

				ZeroMemory(pszOutBuffer, dwSize + 1);



				if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,

					dwSize, &dwDownloaded))

				{

					printf("Error %u in WinHttpReadData.\n",

						GetLastError());

				}

				else

				{

					printf("%s", pszOutBuffer);

					// Data in vFileContent

					vFileContent.push_back(pszOutBuffer);

				}



				// Free the memory allocated to the buffer.

				delete[] pszOutBuffer;

			}



		} while (dwSize>0);





		// Report any errors.

		if (!bResults)

			printf("Error %d has occurred.\n", GetLastError());



		// Close any open handles.

		if (hRequest) WinHttpCloseHandle(hRequest);

		if (hConnect) WinHttpCloseHandle(hConnect);

		if (hSession) WinHttpCloseHandle(hSession);

		string strHtml = "";

		for (int i = 0; i < (int)vFileContent.size(); i++)

		{

			strHtml += vFileContent[i];

		}

		// Write vFileContent to file

		//写入文件

		//ofstream out("test.txt",ios::binary);



		//for (int i = 0; i < (int) vFileContent.size();i++)

		//{

		//    string str = vFileContent[i];

		//    out << str;

		//    //cout << str << endl;

		//}

		//out.close();

		//int iTest;

		//cin >> iTest;

		return strHtml;

}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)

{

	string str = GetHtml("http://172.16.1.100:5360/token.php?s=1");

	cout << str << endl;

	system("pause");

	return 0;

}