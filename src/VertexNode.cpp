#include "VertexNode.h"


VertexNode::VertexNode()
{
}


VertexNode::~VertexNode()
{
//	ClearedgeList();
}


/*清空一个顶点的邻接表，释放邻接表各节点*/
void VertexNode::ClearedgeList()
{
	EdgeNode *p, *q;
	p = edgeList;
	while (p != nullptr)
	{
		q = p->next;
		delete p;
		p = q;
	}
	edgeList = nullptr;
}


/* 在这个顶点的邻接表中加入一条边
参数v为加入边中邻接顶点序号，wgh为加入边的权值*/
bool VertexNode::Appendedge(int v, float wgh)
{
	EdgeNode *p = edgeList;
	EdgeNode *q = nullptr;
	// 找到链接表中末节点，末节点的指针赋值给q。如果发现有一个节点的adjVex的值和v相同，则返回false
	while (p != nullptr)
	{
		if (p->adjVertex == v)
			return false;
		q = p;
		p = p->next;
	}
	// 在邻接表的最后加上一条边
	p = new EdgeNode(v, wgh);
	if (q == nullptr)
		edgeList = p;
	else
		q->next = p;
	return true;
}


/* 在顶点的邻接表中删除一条边
参数v为要删除边的邻接顶点序号*/
bool VertexNode::Removeedge(int v)
{
	EdgeNode *p = edgeList;
	EdgeNode *q = nullptr;
	// 遍历邻接表，如果发现这条边，则删除
	while (p != nullptr)
	{
		if (p->adjVertex == v)
		{
			if (p == edgeList)
				edgeList = p->next;
			else
				q->next = p->next;
			delete p;
			return true;
		}
		q = p;
		p = p->next;
	}
	return false;
}
