#include "PPImiRFS.h"

int main(int argc, char* argv[])
{
	/*处理命令行参数，根据参数执行后续操作*/

	clock_t start;
	clock_t finish;

	start = clock();

	if (argc == 1)
	{
		fprintf(stderr, "Usage:%s [-i value] [-o value] [-p value] [-h]  arglist ... \nparameters are necessary!!!!", argv[0]);
		exit(1);
	}

	for (int i = 1; i < argc; ++i)
	{
		char *para = argv[i];

		if (para[0] == '-')
		{
			switch (para[1])
			{
			case 'i':           //待预测miRNA文件
				fileMirPredict = argv[++i];
				break;
			case 'p':           //WPPIN文件
				filewppin = argv[++i];
				break;
			case 'o':           //输出文件
				fileMirFs = argv[++i];
				break;
			case 'v':           //版本信息
				cout << prog_version << endl;
				return 0;
			case 'h':           //帮助信息
				usage();
			default:            //参数输入存在错误，打印帮助信息
				usage();
				break;
			}
		}
		else
		{
			fprintf(stderr, "Usage:%s [-i value] [-o value] [-p value] [-h]  arglist ... ", argv[0]);
			exit(1);
		}
	}
	
	if (fileMirPredict != "" && filewppin != "" && fileMirFs != "")
	{
		clock_t start1 = clock();

		cout << "inputing datas from input files..." << endl;
		olog << "inputing datas from input files..." << endl;

		char cmd[100];
		sprintf_s(cmd, 100, "count_protein.pl .\\inputfile\\%s .\\inputfile\\c_p.txt .\\result\\log.txt", filewppin.c_str());
		system(cmd);
		memset(cmd, 0, sizeof(cmd));

		ifstream icprotein(".\\inputfile\\c_p.txt");
		int count_protein = 0;
		icprotein >> count_protein;
		icprotein.close();

		sprintf_s(cmd, 100, ".\\inputfile\\%s", fileMirPredict.c_str());
		ifstream mirpredict(cmd);
		memset(cmd, 0, sizeof(cmd));

		sprintf_s(cmd, 100, ".\\result\\%s", fileMirFs.c_str());
		_mkdir("result");
		ofstream fMirFs(cmd);
		memset(cmd, 0, sizeof(cmd));	

		DataGlobal dg;
		WPin wpin(count_protein);
		
		sprintf_s(cmd, 100, ".\\inputfile\\%s", filewppin.c_str());
		dg.InputWppin(cmd, wpin);
		memset(cmd, 0, sizeof(cmd));
		
		clock_t finish1 = clock();
		cout << "Running time is: " << static_cast<double>(finish1 - start1) / CLOCKS_PER_SEC << "s" << endl;
		olog << "Running time is: " << static_cast<double>(finish1 - start1) / CLOCKS_PER_SEC << "s" << endl;

		cout << endl;
		olog << endl;
		cout << "Computing..." << endl;
		olog << "Computing..." << endl;
		cout << endl;
		olog << endl;

		int predict_num = 0;

		while (!mirpredict.eof())
		{
			clock_t start3 = clock();
			cout << "computing the " << ++predict_num << "pair miRNAs' function similirity..." << endl;
			olog << "computing the " << predict_num << "pair miRNAs' function similirity..." << endl;

			string x;                  //miRNA-a名字
			string y;                  //miRNA-b名字

			/*获取待预测的两个miRNA名字*/

			cout << "extract miRNA name..." << endl;
			olog << "extract miRNA name..." << endl;

			mirpredict >> x >> y;
			if ("" == x || "" == y)
			{
				continue;
			}


			if (x == y)
			{
				fMirFs << x << "	" << y << "	" << 1.0 << endl;
				continue;
			}

			//获取miRNA靶基因集信息

			cout << "extract miRNA-Target informations..." << endl;
			olog << "extract miRNA-Target informations..." << endl;

			vector<string> tara;            //miRNA-a对应的靶基因集信息，包括mRNA名字，相应的靶序列，可接近性值
			vector<string> tarb;            //miRNA-b对应的靶基因集信息，内容同上
			dg.GetMirTar(x, tara);
			dg.GetMirTar(y, tarb);

			if (tara.size() == 0 || tarb.size() == 0)
			{
				fMirFs << x << "	" << y << "	" << 0.0 << endl;
				continue;
			}

			Compute com;

			com.computeTarNset(tara, tarb, wpin);

			//计算两个miRNA靶基因集间的功能相似性

			cout << "computing the function similirity of the target sets of miRNAs..." << endl;
			olog << "computing the function similirity of the target sets of miRNAs..." << endl;

			float mrnafs = 0.0;
			com.computeMrnaSetFs(wpin, mrnafs, tara, tarb);

			fMirFs << x << "	" << y << "	" << mrnafs << endl;

			clock_t finish3 = clock();
			cout << "Running time is: " << static_cast<double>(finish3 - start3) / CLOCKS_PER_SEC << "s" << endl;
			cout << endl;
			olog << "Running time is: " << static_cast<double>(finish3 - start3) / CLOCKS_PER_SEC << "s" << endl;
			olog << endl;
		}

		fMirFs.close();
		mirpredict.close();

	}
	else
	{
		fprintf(stderr, "Usage:%s [-i value] [-r value] [-p value] [-h]  arglist ... \nparameters are enough!!!!", argv[0]);
		exit(1);
	}

	finish = clock();
	cout << "Whole Running time is: " << static_cast<double>(finish - start) / CLOCKS_PER_SEC << "s" << endl;
	olog << "Whole Running time is: " << static_cast<double>(finish - start) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}