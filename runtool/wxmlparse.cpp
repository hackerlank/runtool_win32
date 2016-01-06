#include "runtool.h"

#include "wxmlparse.h"

#include "tinyxml/tinyxml.h"

#include <iostream>

#include "stringex.h"


wXMlParse::wXMlParse()
{

}

bool ParseButtonConfig(TiXmlElement *root, wConfigs &configs)
{
	auto config = configs.newConfig();
	if(config){
		//char configName[128] = "";
		TiXmlAttribute *rootAttribute = root->FirstAttribute();
		while(rootAttribute){
			if(strcmp(rootAttribute->Name(),"name") == 0){
				strcpy_s(config->name,rootAttribute->Value());
			}
			rootAttribute = rootAttribute->Next();
		}
		std::cout << "config:" << config->name;

		TiXmlElement *node = root->FirstChildElement();
		while(node){
			//std::cout << cnt++ <<" " << node->Value();
			if(strcmp(node->Value(),"button") == 0){
				stButton *button = new stButton();
				int id = 0;
				TiXmlAttribute *nodeAttribute = node->FirstAttribute();
				while(nodeAttribute){
					//std::cout << QString(nodeAttribute->Name()) <<":" << QString(nodeAttribute->Value());// << endl;
					if(strcmp(nodeAttribute->Name(),"id") == 0){
						id = atoi(nodeAttribute->Value());
					}else if(strcmp(nodeAttribute->Name(),"name") == 0){
						strcpy_s(button->m_name, nodeAttribute->Value());
					}
					nodeAttribute = nodeAttribute->Next();
				}
				button->id = id;
				if(node->FirstChild()){
				   strcpy_s(button->m_action, node->FirstChild()->Value());
				   //kill = QString::fromLocal8Bit(node->FirstChild()->Value());
				}
                std::cout << id <<"," << button->m_name << "," << button->m_action << std::endl;
				config->buttons[id] = button;

			}else if(strcmp(node->Value(),"url") == 0){
				strcpy_s(config->url,node->FirstChild()->Value());
			}else if(strcmp(node->Value(),"workdir") == 0){
				strcpy_s(config->dir,node->FirstChild()->Value());
			}
			node = node->NextSiblingElement();
		}
		configs.push_back(config);
		return true;
	}
	return false;
}



bool wXMlParse::ParseConfing(const char * filename, wConfigs &configs)
{

	configs.clear();
	TiXmlDocument myDocument(filename);
    bool bRet = myDocument.LoadFile();

	if(bRet){
		TiXmlElement *RootElement = myDocument.RootElement();
		if(RootElement && strcmp(RootElement->Value(),"config") == 0){
			//char useConfigName[RUNTOOL_CONFIG_BUFF_SIZE] = "";
			TiXmlElement *node = RootElement->FirstChildElement();
			while(node){
				if(strcmp(node->Value(),"config") == 0){
					ParseButtonConfig(node,configs);
				}else if(strcmp(node->Value(),"useconfig") == 0){
					strcpy_s(configs.useConfigName,node->FirstChild()->Value());
				}
				node = node->NextSiblingElement();
			}
			return true;
		}
	}
	else
	{
		std::cout << myDocument.ErrorDesc();
	}
	return false;
}

bool wXMlParse::ParseConfing(const wchar_t * filename, wConfigs &configs)
{
	return ParseConfing(UnicodeToUTF8(filename).c_str(), configs);
	
}

bool wXMlParse::SaveConfing(const char * filename, wConfigs &configs)
{
	TiXmlDocument myDocument;

	TiXmlElement *RootElement = new TiXmlElement("config");
	myDocument.LinkEndChild(RootElement);
	
	TiXmlElement *element = new TiXmlElement("useconfig");
	element->LinkEndChild(new TiXmlText(configs.useConfigName));
	RootElement->LinkEndChild(element);
	
	for(auto it = configs.begin();it!=configs.end();it++){
		TiXmlElement *ConfigRootElement = new TiXmlElement("config");
		if(ConfigRootElement){
			//name
			ConfigRootElement->SetAttribute("name", (*it)->name);
			//url
			element = new TiXmlElement("url");
			element->LinkEndChild(new TiXmlText((*it)->url));
			ConfigRootElement->LinkEndChild(element);
			//workdir
			element = new TiXmlElement("workdir");
			element->LinkEndChild(new TiXmlText((*it)->dir));
			ConfigRootElement->LinkEndChild(element);
			//button
			for(auto it_button = (*it)->buttons.begin(); it_button!=(*it)->buttons.end();it_button++){
				element = new TiXmlElement("button");
				element->SetAttribute("name", it_button->second->m_name);
				element->SetAttribute("id", it_button->first);
				element->LinkEndChild(new TiXmlText(it_button->second->m_action));
				ConfigRootElement->LinkEndChild(element);
			}
			RootElement->LinkEndChild(ConfigRootElement);
		}
		//std::tstring fullPath = QDir::currentPath() + QString::fromLocal8Bit("\\")  + QString::fromLocal8Bit(filename);
       // myDocument.SaveFile(fullPath.toLocal8Bit());
	}
	return true;
}

bool wXMlParse::SaveConfing(const wchar_t * filename, wConfigs &configs)
{
	return SaveConfing(UnicodeToUTF8(filename).c_str(), configs);
}
