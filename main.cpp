#include <iostream>
#include <string>
#include <fstream>
#include <omp.h>
#include <windows.h>
#include <Shellapi.h>
#include "OpenseesModelGenerator.h"


using namespace std;

void run(int nor);
void run2(int nor);

int main()
{
	cout << "Input number of realization: ";
    int nor=100;  // number of realization
	cin >> nor;
    OpenseesModelGenerator osm(0);

    //string dir="";

    //for(int i=0;i<nor;++i)
    //{
    //    osm.randPara();
    //    osm.writeModel();
    //}


    //osm.GenRandPara();
    for(int i=0;i<nor;++i)
    {
        cout<<i<<"\t";
        //osm.WriteModel(i);
		osm.WriteModelHan(i);
    }
	run2(nor);
	
	system("pause");
    return 0;
}

void run(int nor)
{
	//int num_omp_threads = omp_get_num_procs() - 2;
	int nomp = 0;
	cout << "\nInput number of cores for parallel computing: ";
	cin >> nomp;
	if (nomp < 1)
	{
		nomp = 1;
	}
	string path = "";
	cout << "\nInput file name of source tcl:  ";
	cin >> path;
	//omp_set_num_threads(nomp);
	//#pragma omp parallel for
	//for (int i = 0; i < nor; ++i)
	//{
	//	stringstream ss;
	//	ss << i;

	//	SHELLEXECUTEINFO shell = { sizeof(shell) };
	//	shell.fMask = SEE_MASK_FLAG_DDEWAIT;
	//	shell.lpVerb = "open";

	//	string path = "run.bat";
	//	//string path = "OpenSees.exe";
	//	//shell.lpParameters = "frame.tcl";
	//	shell.lpFile = path.c_str();
	//	shell.nShow = SW_SHOWNORMAL;
	//	shell.lpDirectory = ss.str().c_str();
	//	//string s = getcwd(NULL, 0);
	//	//s=s+"\\" + ss.str();
	//	//shell.lpDirectory = s.c_str();
	//	BOOL ret = ShellExecuteEx(&shell);
	//	DWORD D = WaitForSingleObject(shell.hProcess, INFINITE);
	//	cout << D;

	//}

	int seg = nor / nomp;
	string batPath = "runParallel.bat";
	ofstream ss(batPath);
	ss << "@echo off\n";
	for (int i=0;i<seg;++i)
	{
		ss << "FOR /L %%j IN (" << i*nomp << ",1," << (i+1)*nomp - 2 << ") DO (\n"		//	FOR /L %%j IN (0,1,23) DO (
			<< "  cd %%j\n"
			<< "  echo Starting %%j\n"
			<< "  start OpenSees.exe "+path+"\n"
			<< "  cd..\n"
			<< ")\n\n"
			<< "cd " << (i + 1)*nomp-1 << "\n"
			<< "echo Starting " << (i + 1)*nomp-1 << "\n"
			<< "call OpenSees.exe " + path + "\n"
			<< "  cd..\n\n";
	}
	for (int i = seg*nomp; i < nor; ++i)
	{
		ss << "FOR /L %%j IN (" << i << ",1," << nor - 1 << ") DO (\n"		//	FOR /L %%j IN (24,1,26) DO (
			<< "  cd %%j\n"
			<< "  echo Starting %%j\n"
			<< "  start OpenSees.exe " + path + "\n"
			<< "  cd..\n"
			<< ")\n\n";
	}
	ss.close();
	
	system(batPath.c_str());

}

void run2(int nor)
{
	//int num_omp_threads = omp_get_num_procs() - 2;
	int nomp = 0;
	cout << "\nInput number of cores for parallel computing: ";
	cin >> nomp;
	if (nomp < 1)
	{
		nomp = 1;
	}
	string path = "";
	cout << "\nInput file name of source tcl:  ";
	cin >> path;

	int m = nor / nomp;
	vector <string> bats;
	bats.resize(nomp + 1);
	for (unsigned int i=0;i<bats.size();i++)
	{
		bats[i]= "runParallel_";
		stringstream s;
		s << i;	
		bats[i] = bats[i] + s.str() + ".bat";
	}

	for (int i = 0; i < nomp; ++i)
	{
		ofstream ss(bats[i]);
		ss << "@echo off\n";
		ss << "FOR /L %%j IN (" << i*m << ",1," << (i + 1)*m - 1 << ") DO (\n"		//	FOR /L %%j IN (0,1,23) DO (
			<< "  cd %%j\n"
			<< "  echo Starting %%j\n"
			<< "  call OpenSees.exe " + path + "\n"
			<< "  cd..\n"
			<< ")\n";
		ss.close();

		//system(batPath.c_str());
	}
	
	{
		ofstream ss(bats[nomp]);
		ss << "FOR /L %%j IN (" << nomp*m << ",1," << nor - 1 << ") DO (\n"		//	FOR /L %%j IN (24,1,26) DO (
			<< "  cd %%j\n"
			<< "  echo Starting %%j\n"
			<< "  call OpenSees.exe " + path + "\n"
			<< "  cd..\n"
			<< ")\n\n";
		ss.close();

		//system(batPath.c_str());
	}

	string batPath = "runParallel.bat";
	ofstream fout(batPath);
	fout << "@echo off\n";
	for (unsigned int i = 0; i < bats.size(); i++)
	{
		fout << "start "<<bats[i].c_str()<<"\n";
	}
	fout.close();
	system(batPath.c_str());
}