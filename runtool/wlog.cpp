#include <QDateTime>

#include "wlog.h"

#include "runtool.h"

WLog::WLog(QTableView &view)
{
    //static auto codec = QTextCodec::codecForName("GB2312");
    //codec = QTextCodec::codecForName("UTF-8");
	setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("Time")));
	setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("LOG")));

	//利用setModel()方法将数据模型与QTableView绑定
	view.setModel(this);

	//设置表格的各列的宽度值
	view.setColumnWidth(0,80);
	view.setColumnWidth(1,396);

	//默认显示行头，如果你觉得不美观的话，我们可以将隐藏
	view.verticalHeader()->hide();

	//设置选中时为整行选中
	view.setSelectionBehavior(QAbstractItemView::SelectRows);

	//设置表格的单元为只读属性，即不能编辑
	view.setEditTriggers(QAbstractItemView::NoEditTriggers);

	//如果你用在QTableView中使用右键菜单，需启用该属性
	view.setContextMenuPolicy(Qt::CustomContextMenu);
}

//yyyy:MM:dd hh:mm:ss.zzz
void WLog::addLog(const char *log)
{
	QList<QStandardItem*> Lines({new QStandardItem(QDateTime::currentDateTime().toString("hh:mm:ss.zzz")), new QStandardItem(codec->toUnicode(log))});
	if(rowCount()>LogSize) this->removeRow(0);
	appendRow(Lines);
	//return true;
}

void WLog::addLog(QString log)
{
	QList<QStandardItem*> Lines({new QStandardItem(QDateTime::currentDateTime().toString("hh:mm:ss.zzz")), new QStandardItem(codec->toUnicode(log.toLocal8Bit()))});
	//if(this->)
	//clear();
	if(rowCount()>LogSize) this->removeRow(0);
	appendRow(Lines);
	//return true;
}

void WLog::addLog(std::string log)
{
	addLog(log.c_str());
}

void WLog::ClearLog()
{
	removeRows(0,rowCount());
}

