#pragma once
#include <string>
#include <queue>
#include <vector>
#include "EdgeNode.h"
#include "VertexNode.h"
#include "Tree.h"

using namespace std;

class WPin
{
public:
	~WPin();
	WPin(int);
	void ComputeFs(const int, const int, double &fs);
	bool Insertedge(const string &, const string &, float wgh);
	bool InsertVertex(const string &);
	int LocateVertex(const string &);
	bool SetVertex(int v, const string &);
private:
	VertexNode *vertices;                           // 顶点表
	int numVertices;                                            // 顶点个数
	int numedges;                                                // 边数
	int maxVertices;                                            // 最多可存放的顶点个数
};