#pragma once
#include "TreeEdgeNode.h"

class TreeVertexNode
{
public:
	TreeVertexNode();
	~TreeVertexNode();
	bool AppendTreeEdge(int, float = 0.0);  // 在这个顶点的邻接表中加入一条边
	void ClearedgeList();           //清空一个顶点的邻接表，释放邻接表各节点
	int level;                    // 顶点在树中的层数
	int search = 0;
	double dAccumFs = 0.0;         //到达该顶点的多条路径中累积权重最大值
	TreeEdgeNode *edgeList = nullptr;             // 顶点邻接表的首节点指针
};

