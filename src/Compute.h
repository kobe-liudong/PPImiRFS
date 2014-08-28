#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "DataGlobal.h"
#include "Tree.h"
#include "WPin.h"

using namespace std;

class Compute
{
public:
	Compute();
	~Compute();
	void computeMrnaSetFs(WPin &, float &, vector<string> &, vector<string> &);                        //计算两个miRNA靶基因集间的功能相似性
	void computeMrnaFs(const string, const string, WPin &, float &);                //计算给定的两个mRNA间的功能相似性
	void computeTarNset(vector<string> &, vector<string> &, WPin &);                 //计算两个miRNA靶基因的交集
private:
	vector<string> tar;                     //保存两miRNA靶基因集的并集
	vector<string> tarn;                    //保存两miRNA靶基因集的交集
};

