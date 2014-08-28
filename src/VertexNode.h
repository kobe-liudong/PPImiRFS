#pragma once
#include <string>
#include "EdgeNode.h"

using namespace std;

class VertexNode
{
public:
	VertexNode();
	~VertexNode();
	void ClearedgeList();           // 删除这个顶点的邻接表
	bool Appendedge(int, float = 0);  // 在这个顶点的邻接表中加入一条边
	bool Removeedge(int);           // 在这个顶点的邻接表中删除一条边
	string data;                    // 顶点的数据
	EdgeNode *edgeList;             // 顶点邻接表的首节点指针
};

