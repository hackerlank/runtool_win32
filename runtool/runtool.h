#pragma once

#include <windows.h>


#define RUNTOOL_BUTTON_NUM 5
#define RUNTOOL_CONFIG_BUFF_SIZE 1024

#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif

class stButton  {
public:
	int id = 0;
	char m_name[RUNTOOL_CONFIG_BUFF_SIZE];
	char m_action[RUNTOOL_CONFIG_BUFF_SIZE];
	HWND *m_hButton;
	stButton() :m_hButton(NULL) {
		id = 0;
		memset(m_name, 0, sizeof(m_name));
		memset(m_action, 0, sizeof(m_action));
	}
};


#include <map>
class stConfig {
public:
	char name[RUNTOOL_CONFIG_BUFF_SIZE];
	char url[RUNTOOL_CONFIG_BUFF_SIZE];
	char dir[RUNTOOL_CONFIG_BUFF_SIZE];
	std::map<int, stButton *>buttons;
	stConfig() {
		memset(name, 0, sizeof(name));
		memset(url, 0, sizeof(url));
		memset(dir, 0, sizeof(dir));
	}
	~stConfig() {
		//buttons.clear();
	}
};

#include <vector>
class wConfigs : public std::vector<stConfig *> {
public:
	char useConfigName[RUNTOOL_CONFIG_BUFF_SIZE];
	stConfig * newConfig() { return new stConfig(); }
	void delConfig(stConfig* config) { delete config; }
	void clear() {
		strcpy_s(useConfigName, "");
		for (auto it = begin(); it != end(); it++) {
			delConfig(*it);
		}
		__super::clear();
	}
	wConfigs() {
		strcpy_s(useConfigName, "");
		__super::clear();
	};
};



#include "zSingleton.h"
//#include "wLog.h"
#include "wXmlparse.h"
class RunTool : public Singleton<RunTool>
{
#define RUNTOOL_URLSIZE 1024
#define RUNTOOL_TOKENSIZE 1024
#define RUNTOOL_CONFIGFILE TEXT("RunTool.xml")
public:
	RunTool();
	~RunTool();
	void RunCmd(char *cmd = 0);
	//void getArgs(const char *url = 0, int ntype = 0);
	//bool LoadConfing(stConfig *config);
	//bool LoadConfing();
	//bool ParseConfing();
	//void ShowCanSel();
	void gettoken();
public:
	
	TCHAR * m_configFileName = RUNTOOL_CONFIGFILE;
	//void RunCmd(QString cmd);
	//WLog * m_Log = 0;
	wXMlParse m_parse;
	wConfigs m_configs;
	stConfig *m_pUsedCongfig = 0;
	TCHAR m_url[RUNTOOL_URLSIZE];
	BYTE m_token[RUNTOOL_TOKENSIZE];
	DWORD m_tokeSize;
};


