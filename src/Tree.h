#pragma once
#include <stack>
#include "TreeEdgeNode.h"
#include "TreeVertexNode.h"

using namespace std;

class Tree
{
public:
	Tree(const int);
	~Tree();
	bool SetTreeVertex(const int, const int, const double fs);                     // 根据序号，设置顶点的层数, 最大累积权重
	bool InsertTreeEdge(const int, const int, float = 0.0);       // 插入一条边
	int GetFirstAdjTreeVex(int);                                    // 根据序号，取得顶点的第一个邻接顶点的序号
	int GetNextAdjTreeVex(int v, int w);                            // 根据序号，取得v(相对于w)的下一个邻接顶点序号
	float GetTreeEdge(int, int);                            // 根据顶点序号，取得两顶点之间的边的权重
	int GetLevel(const int);                             //根据顶点序号获取该顶点的层数
	double GetAccumFs(const int);                         //根据顶点序号获取该顶点最大累积权重值
	void ComputeMrFs(const int, const int, float &);                //计算给定两个mRNA间的功能相似性
	bool SetTreeSearchFlag(const int);
	int GetSearchFlag(const int);

private:
	TreeVertexNode *vertices;                                   // 顶点表
	int maxVertices;                                            // 最多可存放的顶点个数 
};

