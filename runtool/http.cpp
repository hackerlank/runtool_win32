#include "http.h"
#include <TCHAR.H>

/*
whr: = ComObjCreate("WinHttp.WinHttpRequest.5.1")
whr.Open("GET", "http://172.16.1.100:5360/token.php?s=1")
whr.Send()
version : = whr.ResponseText
MsgBox % version
*/

#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")

bool httpget(TCHAR *szUrl,BYTE *recv,DWORD &size)
{
	URL_COMPONENTS uc = { 0 };
	uc.dwStructSize = sizeof(uc);
	const DWORD BUF_LEN = 256;
	TCHAR host[BUF_LEN];
	uc.lpszHostName = host;
	uc.dwHostNameLength = BUF_LEN;
	TCHAR path[BUF_LEN];
	uc.lpszUrlPath = path;
	uc.dwUrlPathLength = BUF_LEN;
	TCHAR extra[BUF_LEN];
	uc.lpszExtraInfo = extra;
	uc.dwExtraInfoLength = BUF_LEN;
	//BYTE recv[1024] = "";
	if (WinHttpCrackUrl(szUrl, 0, ICU_ESCAPE, &uc)) {
		auto hSession = WinHttpOpen(TEXT("A WinHTTP Example Program/1.0"),
			WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
			WINHTTP_NO_PROXY_NAME,
			WINHTTP_NO_PROXY_BYPASS, 0);
		if (hSession) {
			auto hConnect = WinHttpConnect(hSession, host, uc.nPort, 0);
			if (hConnect) {
				TCHAR urlPath[1024] = TEXT("");
				_tcscpy_s(urlPath, path);
				if (_tcslen(extra)> 0) {
					_tcscat_s(urlPath, extra);
				}
				auto hRequest = WinHttpOpenRequest(hConnect, TEXT("GET"), urlPath, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
				if (hRequest) {
					
					bool bResults;
					if (hRequest)
						bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
					// End the request.
					if (bResults) bResults = WinHttpReceiveResponse(hRequest, NULL);
					// Keep checking for data until there is nothing left.
					
					if (bResults) {
						// Check for available data.
						//DWORD dwSize = 0;
						bResults = WinHttpQueryDataAvailable(hRequest, &size);
						if (bResults && size > 0) {
							// Allocate space for the buffer.
							WinHttpReadData(hRequest, recv, size, 0);
							return true;
						}
					}

					WinHttpReceiveResponse(hRequest, 0);
					WinHttpCloseHandle(hRequest);
				}
				WinHttpCloseHandle(hConnect);
			}
			WinHttpCloseHandle(hSession);
		}
	}
	return false;
}

/*
TCHAR *gettoken(TCHAR *szUrl)
{
	BOOL  bResults = FALSE;
	HINTERNET hSession = NULL,
		hConnect = NULL,
		hRequest = NULL;

	// Use WinHttpOpen to obtain a session handle.
	hSession = WinHttpOpen(TEXT("A WinHTTP Example Program/1.0"),
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);

	// Specify an HTTP server.
	if (hSession)
		hConnect = WinHttpConnect(hSession, TEXT("172.16.1.100:5360"),
			INTERNET_DEFAULT_HTTP_PORT, 0);

	// Create an HTTP Request handle.
	if (hConnect)
		hRequest = WinHttpOpenRequest(hConnect, TEXT("GET"),
			L"/token.php?s=1",
			NULL, WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			0);

	// Send a Request.
	if (hRequest)
		bResults = WinHttpSendRequest(hRequest,
			WINHTTP_NO_ADDITIONAL_HEADERS,
			0, WINHTTP_NO_REQUEST_DATA, 0,
			0, 0);

	// PLACE ADDITIONAL CODE HERE.

	// Report any errors.
	//if (!bResults)
	//printf("Error %d has occurred.\n", GetLastError());

	// Close any open handles.
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);
	return NULL;

}
*/
