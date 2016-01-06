#ifndef WLOG_H
#define WLOG_H

//#include <string>

#include <QStandardItemModel>
#include <QTextCodec>
#include <QTableView>
#include <QHeaderView>

//using std::string;

class WLog : public QStandardItemModel
{

public:
	const static int LogSize = 7;
    //QTextCodec *codec = 0;
	WLog(QTableView &view);
	void addLog(QString log);
	void addLog(const char* log);
	void addLog(std::string log);
	//bool addLog(string log);
	void ClearLog();
};

#endif // WLOG_H
