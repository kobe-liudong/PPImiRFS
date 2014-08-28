#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "WPin.h"

using namespace std;

extern ofstream olog;

class DataGlobal
{
public:
	DataGlobal();
	~DataGlobal();
	void InputWppin(const string filePin, WPin &wpin);          //输入wppin数据
	void GetMirTar(const string, vector<string> &);             //获取miRNA的靶基因集信息
};

