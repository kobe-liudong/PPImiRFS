#include "Tree.h"


Tree::Tree(const int v) :maxVertices(v)
{
	if (v > 0)
		vertices = new TreeVertexNode[v];
}


Tree::~Tree()
{
	delete[] vertices;
}


/*根据顶点的序号，设置顶点的层数
参数v为顶点序号；参数level用于设置顶点的层数*/
bool Tree::SetTreeVertex(const int v, const int level, const double fs)
{
	if (v < 0 || v >= maxVertices)
		return false;
	vertices[v].level = level;
	vertices[v].dAccumFs = fs;
	return true;
}


/*在树中插入一条边
参数v1为父亲节点、v2为孩子节点；参数w为父亲和孩子节点间的权值，默认值为0*/
bool Tree::InsertTreeEdge(const int v1, const int v2, float w)
{
	if (v1 == -1 || v2 == -1)
		return false;
	// 为第一个顶点的邻接表中增加一条边
	vertices[v1].AppendTreeEdge(v2, w);
	return true;
}


/* 取得树中第v个顶点的第一个孩子顶点序号*/
int Tree::GetFirstAdjTreeVex(int v)
{
	if (v < 0 || v >= maxVertices)
		return -1;
	if (vertices[v].edgeList == nullptr)
		return -1;
	else
		return vertices[v].edgeList->adjTreeVertex;
}


/* 根据序号，取得父节点v(相对于孩子节点w)的下一个邻接顶点序号*/
int Tree::GetNextAdjTreeVex(int v, int w)
{
	if (v < 0 || v >= maxVertices)
		return -1;
	TreeEdgeNode *p = vertices[v].edgeList;
	while (p != nullptr)
	{
		if (p->adjTreeVertex == w)
			break;
		p = p->next;
	}
	if (p == nullptr || p->next == nullptr)
		return -1;
	return p->next->adjTreeVertex;
}


/* 根据顶点序号，取得两顶点之间的边的权重*/
float Tree::GetTreeEdge(int v, int w)
{
	float weight = 0.0;
	if (v < 0 || v >= maxVertices)
		return 0.0;
	if (w < 0 || w >= maxVertices)
		return 0.0;
	TreeEdgeNode *edge = vertices[v].edgeList;
	while (edge != nullptr)
	{
		if (edge->adjTreeVertex == w)
		{
			weight = edge->weight;
			break;
		}
		edge = edge->next;
	}
	return weight;
}


/*获取顶点层数*/
int Tree::GetLevel(const int v)
{
	if (v < 0 || v >= maxVertices)
		return false;
	int level = vertices[v].level;
	return level;
}


/*计算给定两个mRNA间的功能相似性*/

/*边权值累乘方法*/
//void Tree::ComputeMrFs(const int v, const int w, float &fs)                   
//{
//	float maxfs = 0.0;                                                        //保存同等路径数下最大功能相似性值
//	float temp_fs = 1.0;                                                      //暂存当前路径的权值乘积
//	stack<int> stack_path;                                                    //树的先序遍历辅助栈
//	stack_path.push(v);
//	int temp_parent = stack_path.top();                                       //暂存祖先节点
//	int temp_child = GetFirstAdjTreeVex(temp_parent);                         //暂存孩子节点
//
//	/*先搜索从根节点到树的最左叶子节点的路径，并保存在栈中*/
//	while (temp_child != -1 && temp_child != w)
//	{
//		//边权值累乘方法
//		temp_fs *= GetTreeEdge(temp_parent, temp_child);
//		stack_path.push(temp_child);
//		temp_parent = stack_path.top();
//		temp_child = GetFirstAdjTreeVex(temp_parent);
//	}
//
//	/*若树的最左叶子节点是目标节点，则初始化maxfs值*/
//	if (temp_child == w)
//	{
//		//边权值累乘方法
//		maxfs = temp_fs * GetTreeEdge(temp_parent,temp_child);
//	}
//
//	int end = 0;                                                              //树遍历结束标志位
//
//	/*先序遍历树，统计出所有包含目标节点路径的权重乘积中最大的值*/
//	while (!stack_path.empty())
//	{
//		int temp_brother = stack_path.top();                                  //当前栈尾节点的所有子树都搜索完，将栈尾节点出栈，作为兄弟节点
//		stack_path.pop();
//		if (stack_path.empty())
//			break;
//		temp_parent = stack_path.top();                                       //当前栈尾节点为待搜索的子树的祖先节点
//		temp_child = GetNextAdjTreeVex(temp_parent, temp_brother);            //当前祖先节点的紧邻上面兄弟节点的下一个孩子节点
//
//		//边权值累乘方法
//		temp_fs /= GetTreeEdge(temp_parent, temp_brother);                    //当前栈中保存的路径的权重乘积
//
//		/*若最近一次搜索到了当前祖先节点的最右子树，则向上回溯，直到找到一个没搜索完的祖先节点*/
//		while (temp_child == -1)
//		{
//			temp_brother = stack_path.top();
//			stack_path.pop();
//
//			/*整个树都搜索结束，则推出循环*/
//			if (stack_path.empty())
//			{
//				end = 1;
//				break;
//			}
//			temp_parent = stack_path.top();
//			temp_child = GetNextAdjTreeVex(temp_parent, temp_brother);
//
//			//边权值累乘方法
//			temp_fs /= GetTreeEdge(temp_parent, temp_brother);
//		}
//
//		if (end == 1)
//			break;
//
//		/*当前祖先节点的所有子树并没有遍历完，则先序遍历子树*/
//		while (temp_child != -1 && temp_child != w)
//		{
//			//边权值累乘方法
//			temp_fs *= GetTreeEdge(temp_parent, temp_child);
//
//			stack_path.push(temp_child);
//			temp_parent = stack_path.top();
//			temp_child = GetFirstAdjTreeVex(temp_parent);
//		}
//
//		/*找到目标节点，则计算该条路径下目标节点的累积权重值是否大于maxfs，若大于，则更新maxfs为当前值，否则不更新*/
//		if (temp_child == w)
//		{
//			//边权值累乘方法
//			maxfs = temp_fs * GetTreeEdge(temp_parent, temp_child) > maxfs ? temp_fs*GetTreeEdge(temp_parent, temp_child) : maxfs;
//		}
//	}
//
//	fs = maxfs;
//}


/*边权值累加平均方法*/
void Tree::ComputeMrFs(const int v, const int w, float &fs)
{
	float maxfs = 0.0;                                                        //保存同等路径数下最大功能相似性值
	float temp_fs = 0.0;                                                      //暂存当前路径的权值累加平均值
	stack<int> stack_path;                                                    //树的先序遍历辅助栈
	stack_path.push(v);
	int temp_parent = stack_path.top();                                       //暂存祖先节点
	int temp_child = GetFirstAdjTreeVex(temp_parent);                         //暂存孩子节点

	//边权值累加平均方法
	int level = 0;

	/*先搜索从根节点到树的最左叶子节点的路径，并保存在栈中*/
	while (temp_child != -1 && temp_child != w)
	{
		//边权值累加平均方法
		level = GetLevel(temp_child);
		//temp_fs += GetTreeEdge(temp_parent, temp_child) * pow(0.5, level - 1);
		temp_fs += GetTreeEdge(temp_parent, temp_child);

		stack_path.push(temp_child);
		temp_parent = stack_path.top();
		temp_child = GetFirstAdjTreeVex(temp_parent);
	}

	/*若树的最左叶子节点是目标节点，则初始化maxfs值*/
	if (temp_child == w)
	{
		//边权值累加平均方法
		level = GetLevel(temp_child);
		//maxfs = temp_fs + GetTreeEdge(temp_parent, temp_child) * pow(0.5, level - 1);
		maxfs = temp_fs + GetTreeEdge(temp_parent, temp_child) > maxfs ? temp_fs + GetTreeEdge(temp_parent, temp_child) : maxfs;
	}

	int end = 0;                                                              //树遍历结束标志位

	/*先序遍历树，统计出所有包含目标节点路径的权重乘积中最大的值*/
	while (!stack_path.empty())
	{
		int temp_brother = stack_path.top();                                  //当前栈尾节点的所有子树都搜索完，将栈尾节点出栈，作为兄弟节点
		stack_path.pop();
		if (stack_path.empty())
			break;
		temp_parent = stack_path.top();                                       //当前栈尾节点为待搜索的子树的祖先节点
		temp_child = GetNextAdjTreeVex(temp_parent, temp_brother);            //当前祖先节点的紧邻上面兄弟节点的下一个孩子节点

		//边权值累加平均方法
		level = GetLevel(temp_child);
		//temp_fs -= GetTreeEdge(temp_parent, temp_brother)*pow(0.5, level - 1);
		temp_fs -= GetTreeEdge(temp_parent, temp_brother);

		/*若最近一次搜索到了当前祖先节点的最右子树，则向上回溯，直到找到一个没搜索完的祖先节点*/
		while (temp_child == -1)
		{
			temp_brother = stack_path.top();
			stack_path.pop();

			/*整个树都搜索结束，则推出循环*/
			if (stack_path.empty())
			{
				end = 1;
				break;
			}
			temp_parent = stack_path.top();
			temp_child = GetNextAdjTreeVex(temp_parent, temp_brother);

			//边权值累加平均方法
			level = GetLevel(temp_child);
			//temp_fs -= GetTreeEdge(temp_parent, temp_brother)*pow(0.5, level - 1);
			temp_fs -= GetTreeEdge(temp_parent, temp_brother);
		}

		if (end == 1)
			break;

		/*当前祖先节点的所有子树并没有遍历完，则先序遍历子树*/
		while (temp_child != -1 && temp_child != w)
		{
			//边权值累加平均方法
			level = GetLevel(temp_child);
			//temp_fs += GetTreeEdge(temp_parent, temp_brother)*pow(0.5, level - 1);
			temp_fs += GetTreeEdge(temp_parent, temp_child);

			stack_path.push(temp_child);
			temp_parent = stack_path.top();
			temp_child = GetFirstAdjTreeVex(temp_parent);
		}

		/*找到目标节点，则计算该条路径下目标节点的累积权重值是否大于maxfs，若大于，则更新maxfs为当前值，否则不更新*/
		if (temp_child == w)
		{

			//边权值累加平均方法
			level = GetLevel(temp_child);
			//maxfs = temp_fs + GetTreeEdge(temp_parent, temp_child) * pow(0.5, level - 1) > maxfs ? temp_fs*GetTreeEdge(temp_parent, temp_child) : maxfs;
			maxfs = temp_fs + GetTreeEdge(temp_parent, temp_child) > maxfs ? temp_fs + GetTreeEdge(temp_parent, temp_child) : maxfs;
		}
	}

	fs = maxfs / GetLevel(w);
}


double Tree::GetAccumFs(const int ver)
{
	if (ver < 0 || ver >= maxVertices)
		return false;
	double fs = vertices[ver].dAccumFs;
	return fs;
}


bool Tree::SetTreeSearchFlag(const int ver)
{
	if (ver < 0 || ver >= maxVertices)
		return false;
	vertices[ver].search = 1;
	return true;
}


int Tree::GetSearchFlag(const int ver)
{
	if (ver < 0 || ver >= maxVertices)
		return false;
	int flag = vertices[ver].search;
	return flag;
}