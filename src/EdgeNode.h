#pragma once
class EdgeNode
{
public:
	~EdgeNode();
	EdgeNode(int = -1, float = 0.0);       // 构造函数
	int adjVertex;                    // 该边中的邻接顶点在顶点表中的序号
	float weight;                       // 该边的权值
	EdgeNode *next;
};
