#include "WPin.h"


/* 构造函数
参数s为该图最多可存放的顶点个数*/
WPin::WPin(int s) : numVertices(0), numedges(0), maxVertices(s)
{
	if (s > 0)
		vertices = new VertexNode[s];
}


/* 析构函数 */
WPin::~WPin()
{
	for (int i = 0; i < numVertices; i++)
		vertices[i].ClearedgeList();
	if (maxVertices != 0)
		delete[] vertices;
}


 /*根据顶点的数据，找到顶点在顶点表中的序号
 参数vex为顶点的数据
 返回值为顶点的序号。如返回-1，未找到相关的顶点*/
int WPin::LocateVertex(const string & vex)
{
	for (int i = 0; i < numVertices; i++)
	if (vertices[i].data == vex)
		return i;
	return -1;
}


 /*根据顶点的序号，设置顶点的数据
 参数v为顶点序号；参数vex用于设置的顶点数据*/
bool WPin::SetVertex(int v, const string &vex)
{
	if (v < 0 || v >= numVertices)
		return false;
	vertices[v].data = vex;
	return true;
}


 /*在图中插入一个顶点
 参数vex为要插入的顶点数据*/
bool WPin::InsertVertex(const string &vex)
{
	// 如果存在的顶点个数已达最大值，则返回
	if (numVertices == maxVertices)
		return false;
	// 判断相同的顶点是否存在，如存在，则返回
	for (int i = 0; i < numVertices; i++)
	if (vertices[i].data == vex)
		return false;
	// 增加一个顶点项
	vertices[numVertices].data = vex;
	vertices[numVertices++].edgeList = nullptr;
	return true;
}


 /*在图中插入一条边
 参数vex1、vex2为要插入边的两个顶点的值；参数wgh为欲插入边的权值，默认值为0*/
bool WPin::Insertedge(const string &vex1, const string &vex2, float wgh)
{
	// 找到两个顶点在顶点表中的序号，分别赋值给v1、v2
	// 两个顶点中只要有一个在图的顶点表中未找到，则返回
	int v1 = LocateVertex(vex1);
	int v2 = LocateVertex(vex2);
	if (v1 == -1 || v2 == -1)
		return false;
	// 为第一个顶点的邻接表中增加一条边
	bool a = vertices[v1].Appendedge(v2, wgh);
	// 无向图，则必须在另一顶点的邻接表中增加一条边
	bool b = vertices[v2].Appendedge(v1, wgh);
	if (a && b)
	{
		numedges++;
		return true;
	}
	else
		return false;
}


//采用改进的广度优先搜索计算给定的两个靶基因间的功能相似性
void WPin::ComputeFs(const int root, const int goal, double &fs)
{

	Tree tree(numVertices);
	queue<int> path_queue;

	int flag = 0;
	int find_level = -1;
	double fs_temp = 1.0;

	if (goal != -1 && root != -1)
	{
		path_queue.push(root);

		tree.SetTreeVertex(root, 0, 1.0);

		while (!path_queue.empty())
		{
			int parent = path_queue.front();
			path_queue.pop();

			int parent_level = tree.GetLevel(parent);
			int search_flag = tree.GetSearchFlag(parent);
			
			if (1 == search_flag || parent_level == find_level)
				continue;
			tree.SetTreeSearchFlag(parent);

			fs_temp = tree.GetAccumFs(parent);

			EdgeNode *p = vertices[parent].edgeList;
			while (p != nullptr)
			{
				int child_level = tree.GetLevel(p->adjVertex);

				if (child_level == -1 || parent_level + 1 == child_level)
				{
					if (p->adjVertex == goal)
					{
						double AccumFs = fs_temp * (p->weight);

						if (flag == 0)
						{
							flag = 1;
							find_level = parent_level + 1;
						}
						if (-1 != child_level)
						{
							double temp = tree.GetAccumFs(p->adjVertex);
							AccumFs = temp >= AccumFs ? temp : AccumFs;
						}

						tree.SetTreeVertex(p->adjVertex, parent_level + 1, AccumFs);
						break;
					}
					else
				    {
						double AccumFs = fs_temp * (p->weight);
						if (-1 != child_level)
						{
							double temp = tree.GetAccumFs(p->adjVertex);
							AccumFs = temp >= AccumFs ? temp : AccumFs;
						}

						path_queue.push(p->adjVertex);
						tree.SetTreeVertex(p->adjVertex, parent_level + 1, AccumFs);
					}
				}
				p = p->next;
			}
		}
	}
	if (1 == flag)
		fs = tree.GetAccumFs(goal);
	else
		fs = 0.0;
}