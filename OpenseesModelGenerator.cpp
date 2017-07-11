#include "OpenseesModelGenerator.h"

OpenseesModelGenerator::OpenseesModelGenerator
    (int seed,string randPath, string framePath, string nodePath, string elementPath)
{
    _seed=seed;
    _randPath=randPath;
    _framePath=framePath;
    _nodePath=nodePath;
    _elementPath=elementPath;

    if(_seed==0)
        srand((unsigned)time(NULL));
    else
        srand(_seed);

    ReadRandPara();
}

void OpenseesModelGenerator::ReadRandPara()
{
    ifstream fin(_randPath);
    if(!fin.good())
    {
        cout<<"Failed to open file "<<_randPath.c_str()<<"!\n";
        exit(1);
    }
    _randParas.clear();

    string name="";
    Bound bound;
    getline(fin,name);
    while(!fin.eof())
    {
        fin>>name>>bound.min>>bound.max;
        if(name.compare("")!=0)
            _randParas.insert(make_pair(name,bound));
    }

}

double OpenseesModelGenerator::random(double min, double max)
{
//    if(_seed==0)
//        srand((unsigned)time(NULL));
//    else
//        srand(_seed);

    double r=(double)rand() / (double)RAND_MAX;
    r=(max-min)*r+min;
    return r;
}

void OpenseesModelGenerator::GenRandPara(){

    //steel
    for(unsigned int i=0;i<steel.size();++i)
    {
        delete steel[i];
    }
    steel.clear();
    if(random()>0.5)    //steel02
    {
        Steel02 *s=new Steel02;
        s->tag=101;
        s->E0=random(_randParas["E0"].min,_randParas["E0"].max);
        s->fy=random(_randParas["fy"].min,_randParas["fy"].max);
        s->b=random(_randParas["b"].min,_randParas["b"].max);
        s->R0=random(_randParas["R0"].min,_randParas["R0"].max);
        steel.push_back(s);
    }
    else    //reinforcing steel
    {
        ReinforcingSteel *s=new ReinforcingSteel;
        s->tag=10;
        s->E0=random(_randParas["E0"].min,_randParas["E0"].max);
        s->fy=random(_randParas["fy"].min,_randParas["fy"].max);
        s->fu=random(_randParas["fu"].min,_randParas["fu"].max);
        s->Esh=random(_randParas["Esh"].min,_randParas["Esh"].max);
        s->esh=random(_randParas["esh"].min,_randParas["esh"].max);
        s->eult=random(_randParas["eult"].min,_randParas["eult"].max);
        steel.push_back(s);
    }

    // unconfined concrete
    for(unsigned int i=0;i<concrete.size();++i)
    {
        delete concrete[i];
    }
    concrete.clear();
    if(random()>0.5)    //concrete01
    {
        Concrete01 *con=new Concrete01;
        con->tag=1;
        con->fpc=random(_randParas["fpc"].min,_randParas["fpc"].max);
        con->epsc0=random(_randParas["epsc0"].min,_randParas["epsc0"].max);
        con->fpcu = con->fpc * random(_randParas["Kres"].min,_randParas["Kres"].max);
        con->epsU=random(_randParas["epsU"].min,_randParas["epsU"].max);
        concrete.push_back(con);
    }
    else    //concrete02
    {
        Concrete02 *con=new Concrete02;
        con->tag=1;
        con->fpc=random(_randParas["fpc"].min,_randParas["fpc"].max);
        con->epsc0=random(_randParas["epsc0"].min,_randParas["epsc0"].max);
        con->fpcu = con->fpc * random(_randParas["Kres"].min,_randParas["Kres"].max);
        con->epsU=random(_randParas["epsU"].min,_randParas["epsU"].max);
        con->lambda=random(_randParas["lambda"].min,_randParas["lambda"].max);
        con->ft=random(_randParas["ft"].min,_randParas["ft"].max);
        con->Ets=random(_randParas["Ets"].min,_randParas["Ets"].max);
        concrete.push_back(con);
    }

    //confined concrete
    //TODO
}


void OpenseesModelGenerator::WriteModel(){
    WriteMain();
    WriteSteel();
    WriteConcrete();

}

void OpenseesModelGenerator::WriteMain(){
    //TODO: Copy files
}

void OpenseesModelGenerator::WriteSteel(){
    ofstream fout("steel.tcl");
    for(unsigned int i=0; i<steel.size();++i)
    {
        fout<<steel[i]->toTcl().c_str();
    }

    fout.close();
}

void OpenseesModelGenerator::WriteConcrete(){
    ofstream fout("concrete.tcl");
    for(unsigned int i=0; i<concrete.size();++i)
    {
        fout<<concrete[i]->toTcl().c_str();
    }
    for(unsigned int i=0; i<confinedCon.size();++i)
    {
        fout<<confinedCon[i]->toTcl().c_str();
    }
    fout.close();
}

void OpenseesModelGenerator::WriteSection(){

}
















