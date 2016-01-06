#ifndef WXMLPARSE_H
#define WXMLPARSE_H

//#include "runtool.h"

class wConfigs;

class wXMlParse
{
private:
	//bool ParseButtonConfig(TiXmlElement *root, wConfigs &configs);
public:
	wXMlParse();
	bool ParseConfing(const char * filename, wConfigs &configs);
	bool ParseConfing(const wchar_t * filename, wConfigs &configs);
	bool SaveConfing(const char * filename, wConfigs &configs);
	bool SaveConfing(const wchar_t * filename, wConfigs &configs);
};

#endif // WXMLPARSE_H
