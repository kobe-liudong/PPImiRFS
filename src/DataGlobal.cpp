#include "DataGlobal.h"


DataGlobal::DataGlobal()
{
}


DataGlobal::~DataGlobal()
{
}


/*输入wppin数据*/
void DataGlobal::InputWppin(const string filePin, WPin &wpin)
{
	ifstream ippi(filePin);
	int num = 0;

	if (ippi.is_open())
	{
		cout << "inputing the wppin data..." << endl;
		olog << "inputing the wppin data..." << endl;
		while (!ippi.eof())
		{
			string x;
			string y;
			float weight = 0.0;
			ippi >> x >> y >> weight;
			wpin.InsertVertex(x);
			wpin.InsertVertex(y);
			wpin.Insertedge(x, y, weight);
			cout << ++num << "\r";
		}
		cout << endl;
	}

	ippi.close();
}


/*获取miRNA的靶基因集信息*/
void DataGlobal::GetMirTar(const string mirname, vector<string> &tar)
{
	int flag = 0;
	int num = 0;
	char str[100];
	sprintf_s(str, 100, ".\\mRNA\\%s", mirname.c_str());
	ifstream ifile_mrna(str);

	if (ifile_mrna.is_open())
	{
		while (!ifile_mrna.eof())
		{
			string mrna_name;
			ifile_mrna >> mrna_name;
			if ("" != mrna_name)
			{
				tar.push_back(mrna_name);
			}
		}
	}
}