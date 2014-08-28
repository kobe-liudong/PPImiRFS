#include "Compute.h"


Compute::Compute()
{
}


Compute::~Compute()
{
}


/*计算给定的两个mRNA间的功能相似性*/
void Compute::computeMrnaFs(const string tara, const string tarb, WPin &wpin, float &fs)
{
	int locala = 0;
	int localb = 0;

	locala = wpin.LocateVertex(tara);
	localb = wpin.LocateVertex(tarb);

	/*两个mRNA全部都在PIN中*/
	if (locala != -1 && localb != -1)
	{
		double fs_temp = 0.0;
		wpin.ComputeFs(locala, localb, fs_temp);
		fs = static_cast<float> (fs_temp);
	}

	else
		fs = 0.0;
}


/*计算两个mRNA集间的综合功能相似性*/
/*ABM_contain方法*/
void Compute::computeMrnaSetFs(WPin &wpin, float &fs, vector<string> &tara, vector<string> &tarb)
{
	int numa = tara.size();
	int numb = tarb.size();

	//ABM and BMA辅助数组
	vector<vector<double>> matrix;

	if (numa == 0 || numb == 0)
		fs = 0.0;
	else
	{
		float sum = 0.0;
		int num_contain = 0;           //子网中存在的路径数

		int i = 0;
		int j = 0;

		for (auto it1 = tara.begin(); it1 != tara.end(); ++it1)
		{
			if (*it1 == "")
				continue;

			//ABM and BMA
			vector<double> matrix_col;

			for (auto it2 = tarb.begin(); it2 != tarb.end(); ++it2)
			{
				if (*it2 == "")
					continue;

				int flag1 = 0;
				int flag2 = 0;
				for (auto it3 = tarn.begin(); it3 != tarn.end(); ++it3)
				{
					if (*it3 == *it1)
						flag1 = 1;
					if (*it3 == *it2)
						flag2 = 1;
					if (flag1 == 1 && flag2 == 1)
						break;
				}

				if (flag1 == 1 && flag2 == 1)
				{
					//ABM and BMA
					matrix_col.push_back(1.0);
				}

				else
				{
					//BMA and ABM
					float temp_fs = 0.0;
					if (*it1 != "" && *it2 != "")
						computeMrnaFs(*it1, *it2, wpin, temp_fs);
					matrix_col.push_back(temp_fs);
				}
			}

			//ABM and BMA
			matrix.push_back(matrix_col);
		}

		//ABM and BMA
		double sum_a = 0.0;
		double sum_b = 0.0;
		int miss_row = 0;
		int miss_colu = 0;

		for (int i = 0; i < numa; ++i)
		{
			double max_row = 0.0;

			for (int j = 0; j < numb; ++j)
			{
				if (matrix[i][j] > max_row)
					max_row = matrix[i][j];
			}

			if (max_row == 0)
				miss_row++;

			sum_a += max_row;
		}

		for (int i = 0; i < numb; ++i)
		{
			double max_colu = 0.0;

			for (int j = 0; j < numa; ++j)
			{
				if (matrix[j][i] > max_colu)
					max_colu = matrix[j][i];
			}

			if (max_colu == 0)
				miss_colu++;

			sum_b += max_colu;
		}

		//ABM_contain
		if (sum_a == 0 && sum_b == 0)
			fs = 0.0;
		else
			fs = static_cast<float> ((sum_a + sum_b) / (numa + numb - miss_row - miss_colu));
	}
}


/*计算两个miRNA靶基因的交集*/
void Compute::computeTarNset(vector<string> &tara, vector<string> &tarb, WPin &wpin)
{
	for (auto it1 = tara.begin(); it1 != tara.end(); ++it1)
	{
		for (auto it2 = tarb.begin(); it2 != tarb.end(); ++it2)
		{
			if (*it1 == *it2 && *it1 != "" && *it2 != "")
			{
				tarn.push_back(*it1);
			}
		}
	}
}