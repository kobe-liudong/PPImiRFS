#include "TreeVertexNode.h"


TreeVertexNode::TreeVertexNode()
{
	level = -1;
}


TreeVertexNode::~TreeVertexNode()
{
	ClearedgeList();
}


/* 在这个顶点的邻接表中加入一条边
参数v为加入边中邻接顶点序号，w为加入边的权值*/
bool TreeVertexNode::AppendTreeEdge(int v, float w)
{
	TreeEdgeNode *p = edgeList;
	TreeEdgeNode *q = nullptr;
	// 找到链接表中末节点，末节点的指针赋值给q。如果发现有一个节点的adjVex的值和v相同，则返回false
	while (p != nullptr)
	{
		if (p->adjTreeVertex == v)
			return false;
		q = p;
		p = p->next;
	}
	// 在邻接表的最后加上一条边
	p = new TreeEdgeNode(v, w);
	if (q == nullptr)
		edgeList = p;
	else
		q->next = p;
	return true;
}


/*清空一个顶点的邻接表，释放邻接表各节点*/
void TreeVertexNode::ClearedgeList()
{
	TreeEdgeNode *p, *q;
	p = edgeList;
	while (p != nullptr)
	{
		q = p->next;
		delete p;
		p = q;
	}
	edgeList = nullptr;
}