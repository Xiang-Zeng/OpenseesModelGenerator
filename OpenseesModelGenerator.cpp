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


void OpenseesModelGenerator::WriteModel(int id){
    stringstream ss;
    ss<<id;
    mkdir(ss.str().c_str());
    //make dir, name=ss.str();
    ofstream fout(ss.str()+"/ModelParameters.tcl");
    fout<<"# ModelParameters.tcl\n"
        <<"# Units: [N,mm,C]\n\n"
        <<"# Define general parameters\n"
        <<"# -------------------------\n"
        <<"set pi [expr acos(-1.0)]\n"
        <<"# Define unconfined concrete parameters\n"
        <<"# -------------------------\n\n";

    if(random()>0.5)    //concrete01
        fout<<"set concreteType \"Concrete01\"\n";
    else
        fout<<"set concreteType \"Concrete02\"\n";

    fout<<"set fc  "<<random(_randParas["fpc"].min,_randParas["fpc"].max)<<"\n"
        <<"set epsc "<<random(_randParas["epsc0"].min,_randParas["epsc0"].max)<<"\n"
        <<"set Kres "<<random(_randParas["Kres"].min,_randParas["Kres"].max)<<"\n"
        <<"set fcu [expr $fc*$Kres]\n"
        <<"set epscu "<<random(_randParas["epsU"].min,_randParas["epsU"].max)<<"\n"
        <<"set lambda "<<random(_randParas["lambda"].min,_randParas["lambda"].max)<<"\n"
        <<"set ft "<<random(_randParas["ft"].min,_randParas["ft"].max)<<"\n"
        <<"set Ets "<<random(_randParas["Ets"].min,_randParas["Ets"].max)<<"\n\n";

    fout<<"# Define steel parameters\n"
        <<"# -----------------------\n";

    if(random()>0.5)
        fout<<"set steelType \"Steel02\"\n";
    else
        fout<<"set steelType \"ReinforcingSteel\"\n";

    fout<<"set fy "<<random(_randParas["fy"].min,_randParas["fy"].max) <<"\n"
        <<"set fyh "<<random(_randParas["fyh"].min,_randParas["fyh"].max) <<"\n"
        <<"set fu "<<random(_randParas["fu"].min,_randParas["fu"].max) <<"\n"
		<< "set fuh " << random(_randParas["fuh"].min, _randParas["fuh"].max) << "\n"
        <<"set E "<<random(_randParas["E0"].min,_randParas["E0"].max) <<"\n"
        <<"set b "<<random(_randParas["b"].min,_randParas["b"].max) <<"\n"
        <<"set R0 "<<random(_randParas["R0"].min,_randParas["R0"].max) <<"\n"
        <<"set Esh [expr $E*$b]\n"
        <<"set epssh "<<random(_randParas["esh"].min,_randParas["esh"].max) <<"\n"
        <<"set epssu "<<random(_randParas["eult"].min,_randParas["eult"].max) <<"\n\n";

    fout<<"# Define section parameters\n"
        <<"# -----------------------\n"
        <<"set numDiv "<<round(random(_randParas["NumSubdivision"].min,_randParas["NumSubdivision"].max) )<<"\n"
        <<"set cover "<<random(_randParas["ConcreteCover"].min,_randParas["ConcreteCover"].max) <<"\n"
        <<"set flangeWidth "<<random(_randParas["FlangeWidth"].min,_randParas["FlangeWidth"].max) <<"\n"
        <<"# Define element parameters\n"
        <<"# -----------------------\n"
        <<"set numIntPt "<<round(random(_randParas["numIntPt"].min,_randParas["numIntPt"].max) )<<"\n"
        <<"set factorIg "<<random(_randParas["Ig"].min,_randParas["Ig"].max) <<"\n"
        <<"set hingeLengthCol "<<random(_randParas["hingeLengthCol"].min,_randParas["hingeLengthCol"].max) <<"\n"
        <<"set hingeLengthBeam "<<random(_randParas["hingeLengthBeam"].min,_randParas["hingeLengthBeam"].max) <<"\n";

    if(random()>0.5)
        fout<<"set colTransfType \"PDelta\"\n";
    else
        fout<<"set colTransfType \"Corotational\"\n";

    if(random()>0.5)
        fout<<"set beamTransfType \"PDelta\"\n";
    else
        fout<<"set beamTransfType \"Linear\"\n";

    fout.close();

}

int OpenseesModelGenerator::round(double r)
{
	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}




