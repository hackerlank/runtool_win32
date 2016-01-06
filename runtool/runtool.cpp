#include "runtool.h"
#include "http.h"
#include "tchar.h"


void RunTool::gettoken()
{
	ZeroMemory(m_token, sizeof(m_token));
	httpget(m_url, m_token, m_tokeSize);
	//auto pDate = httpget(m_url);
	//strcpy_s((char *)m_token, sizeof(m_token), (char *)pDate);
}

#include <iostream>

RunTool::RunTool()
{
	std::cout << "RunTool";
	_tcscpy_s(m_url, TEXT(""));
	//strcpy_s(configFileName,RUNTOOL_CONFIGFILE);
	//RunTool_GUI w;

	if (m_parse.ParseConfing(m_configFileName, m_configs)) {
		//m_Log = new WLog(*gui->ui->logView);
		//if (m_configs.size()>0) LoadConfing();
	}
	else {
		exit(-1);
	}
}

RunTool::~RunTool()
{
	//delete ui;
	//delete m_Log;
	m_configs.clear();
}



void RunTool::RunCmd(char *cmd)
{

	//QString olddir(QDir::currentPath());
	//QDir::setCurrent(codec->toUnicode(pUsedCongfig->dir));
	//char buf[RUNTOOL_CONFIG_BUFF_SIZE];
	//sprintf_s(buf,"cmd /c start %s",cmd);
	//m_Log->addLog(QDir::currentPath() + QString(codec->toUnicode(" Run:") + cmd));
	system(cmd);
	//WinExec(cmd,SW_HIDE);
	//QDir::setCurrent(olddir);
	//m_Log->addLog(QDir::currentPath());
}

/*

bool RunTool::LoadConfing(stConfig *pConfig)
{
	if (m_pUsedCongfig == pConfig) return true;
	if (m_pUsedCongfig) {
		for (auto it_button = m_pUsedCongfig->buttons.begin(); it_button != pUsedCongfig->buttons.end(); it_button++) {
			//auto pButton = it_button->second.button;
			if (it_button->second->button) {
				gui->ui->horizontalLayout->removeWidget(it_button->second->button);
				delete it_button->second->button;
				it_button->second->button = 0;
			}
		}
	}
	m_pUsedCongfig = pConfig;
	strcpy_s(m_configs.useConfigName, pConfig->name);
	if (!pUsedCongfig && configs.size()>0) pUsedCongfig = configs[0];
	if (pUsedCongfig) {
		//gui->ui->horizontalLayout->removeWidget(0);
		for (auto it_button = pUsedCongfig->buttons.begin(); it_button != pUsedCongfig->buttons.end(); it_button++) {
			auto pButton = it_button->second->button;
			if (!pButton) {
				pButton = new QPushButton(gui->ui->layoutWidget);
				gui->ui->horizontalLayout->addWidget(pButton);
				//button->setText(QApplication::translate("RunTool", it_button->second.m_name, 0));
				pButton->setText(QString::fromLocal8Bit(it_button->second->m_name));
				it_button->second->button = pButton;
				gui->connect(pButton, SIGNAL(clicked()), it_button->second, SLOT(on_button_clicked()));
				//connect(this, SIGNAL(clicked()), this, SLOT(on_button4_clicked()));
			}
			else {
				pButton->setText(QString::fromLocal8Bit(it_button->second->m_name));
			}
		}

		ShowCanSel();
		m_Log->addLog(string("select:") + pUsedCongfig->name);
		return true;
	}
	return false;
}

bool RunTool::LoadConfing()
{
	for (auto ite = configs.begin(); ite != configs.end(); ite++) {
		//std::cout << QString::fromLocal8Bit((*ite)->name) << "," << QString::fromLocal8Bit(configs.useConfigName);
		if (strcmp((*ite)->name, configs.useConfigName) == 0) {
			return LoadConfing(*ite);
		}
	}
	return false;
}

void RunTool::ShowCanSel()
{
	gui->ui->comboBox->disconnect();
	gui->ui->comboBox->clear();
	for (auto ite = configs.begin(); ite != configs.end(); ite++) {
		gui->ui->comboBox->addItem(codec->toUnicode((*ite)->name));
		if (strcmp(pUsedCongfig->name, (*ite)->name) == 0) {
			gui->ui->comboBox->setCurrentText(codec->toUnicode((*ite)->name));
		}
	}
	gui->connect(gui->ui->comboBox, SIGNAL(currentIndexChanged(int)), gui, SLOT(on_comboBox_currentIndexChanged(int)));
}

void stButton::on_button_clicked()
{
	std::cout << "button cliecked";

	 RunTool::getMe().gui->getArgs(RunTool::getMe().pUsedCongfig->url, 1);

	char cmd[RUNTOOL_CONFIG_BUFF_SIZE];
	sprintf_s(cmd, "%s %s", m_action, RunTool::getMe().key);
	RunTool::getMe().RunCmd(cmd);
}

*/
