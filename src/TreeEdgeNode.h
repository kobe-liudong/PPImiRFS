#pragma once
class TreeEdgeNode
{
public:
	~TreeEdgeNode();
	TreeEdgeNode(int = -1, float = 0.0);       // 构造函数
	int adjTreeVertex;                    // 该边中的邻接顶点在顶点表中的序号
	float weight;                       // 该边的权值
	TreeEdgeNode *next;
};

