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
	string cmd = "Xcopy data " + ss.str() + "  /s /e /y";
	system(cmd.c_str());
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
        //fout<<"set steelType \"ReinforcingSteel\"\n";
		fout << "set steelType \"Steel01\"\n";

	fout << "set fy " << random(_randParas["fy"].min, _randParas["fy"].max) << "\n"
		<< "set fyh " << random(_randParas["fyh"].min, _randParas["fyh"].max) << "\n"
		<< "set fu " << random(_randParas["fu"].min, _randParas["fu"].max) << "\n"
		<< "set fuh " << random(_randParas["fuh"].min, _randParas["fuh"].max) << "\n"
		<< "set E " << random(_randParas["E0"].min, _randParas["E0"].max) << "\n"
		<< "set epssh " << random(_randParas["esh"].min, _randParas["esh"].max) << "\n"
		<< "set epssu " << random(_randParas["eult"].min, _randParas["eult"].max) << "\n"
		//<<"set b "<<random(_randParas["b"].min,_randParas["b"].max) <<"\n"
		<< "set b [expr ($fu-$fy)/($epssu-$fy/$E)/$E]\n"
		<< "set Esh [expr $E*4.0*$b]\n"
		<< "set R0 " << random(_randParas["R0"].min, _randParas["R0"].max) << "\n\n";

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

void OpenseesModelGenerator::WriteModelHan(int id) {
	stringstream ss;
	ss << id;
	mkdir(ss.str().c_str());
	string cmd = "Xcopy data " + ss.str() + "  /s /e /y";
	system(cmd.c_str());
	ofstream fout(ss.str() + "/ModelParameters.tcl");
	fout << "# ModelParameters.tcl\n";
	fout << "set ES  " << random(_randParas["ES"].min, _randParas["ES"].max) << "\n"
		<< "set FYL(1) " << random(_randParas["FYL(1)"].min, _randParas["FYL(1)"].max) << "\n"
		<< "set FU(1) " << random(_randParas["FU(1)"].min, _randParas["FU(1)"].max) << "\n"
		<< "set ELONG(1) " << random(_randParas["ELONG(1)"].min, _randParas["ELONG(1)"].max) << "\n";
	
	if (random() > 0.5)
		fout << "set STEELTYPE(1) \"Steel01\"\n";
	else
		fout << "set STEELTYPE(1) \"Steel02\"\n";

	fout << "set R0(1) " << random(_randParas["R0(1)"].min, _randParas["R0(1)"].max) << "\n"
		<< "set FYL(2) " << random(_randParas["FYL(2)"].min, _randParas["FYL(2)"].max) << "\n"
		<< "set FU(2)  " << random(_randParas["FU(2)"].min, _randParas["FU(2)"].max) << "\n"
		<< "set ELONG(2)  " << random(_randParas["ELONG(2)"].min, _randParas["ELONG(2)"].max) << "\n";

	if (random() > 0.5)
		fout << "set STEELTYPE(2) \"Steel01\"\n";
	else
		fout << "set STEELTYPE(2) \"Steel02\"\n";

	fout << "set R0(2)  " << random(_randParas["R0(2)"].min, _randParas["R0(2)"].max) << "\n"
		<< "set nfdy1  " << round( random(_randParas["nfdy1"].min, _randParas["nfdy1"].max) )<< "\n"
		<< "set nfty1  " << round( random(_randParas["nfty1"].min, _randParas["nfty1"].max)) << "\n"
		<< "set nfdz1  " << round(random(_randParas["nfdz1"].min, _randParas["nfdz1"].max)) << "\n"
		<< "set nftz1  " << round(random(_randParas["nftz1"].min, _randParas["nftz1"].max)) << "\n"
		<< "set nfdw1  " << round(random(_randParas["nfdw1"].min, _randParas["nfdw1"].max)) << "\n"
		<< "set nftw1  " << round(random(_randParas["nftw1"].min, _randParas["nftw1"].max)) << "\n"
		<< "set nfbf1  " << round(random(_randParas["nfbf1"].min, _randParas["nfbf1"].max)) << "\n"
		<< "set nftf1  " << round(random(_randParas["nftf1"].min, _randParas["nftf1"].max)) << "\n"
		<< "set nfdy2  " << round(random(_randParas["nfdy2"].min, _randParas["nfdy2"].max)) << "\n"
		<< "set nfty2  " << round(random(_randParas["nfty2"].min, _randParas["nfty2"].max)) << "\n"
		<< "set nfdz2  " << round(random(_randParas["nfdz2"].min, _randParas["nfdz2"].max)) << "\n"
		<< "set nftz2  " << round(random(_randParas["nftz2"].min, _randParas["nftz2"].max)) << "\n"
		<< "set nfdw2  " << round(random(_randParas["nfdw2"].min, _randParas["nfdw2"].max)) << "\n"
		<< "set nftw2  " << round(random(_randParas["nftw2"].min, _randParas["nftw2"].max)) << "\n"
		<< "set nfbf2  " << round(random(_randParas["nfbf2"].min, _randParas["nfbf2"].max)) << "\n"
		<< "set nftf2  " << round(random(_randParas["nftf2"].min, _randParas["nftf2"].max)) << "\n";

	if (random() > 0.5)
		fout << "set Col_Transf \"PDelta\"\n";
	else
		fout << "set Col_Transf \"Corotational\"\n";

	if (random() > 0.5)
		fout << "set Beam_Transf \"PDelta\"\n";
	else
		fout << "set Beam_Transf \"Linear\"\n";

	fout << "set nip(1)  " << round( random(_randParas["nip(1)"].min, _randParas["nip(1)"].max) )<< "\n"
		<< "set nip(2)  " << round(random(_randParas["nip(2)"].min, _randParas["nip(2)"].max) )<< "\n"
		<< "set jointKMod  " << random(_randParas["jointKMod"].min, _randParas["jointKMod"].max) << "\n"
		<< "set beamKMod  " << random(_randParas["beamKMod"].min, _randParas["beamKMod"].max) << "\n"
		<< "set girderKMod  " << random(_randParas["girderKMod"].min, _randParas["girderKMod"].max) << "\n";

	if (random() > 0.5)
		fout << "set dampingType \"initial\"\n";
	else
		fout << "set dampingType \"committed\"\n";

	fout << "set zeta2  " << random(_randParas["zeta2"].min, _randParas["zeta2"].max) << "\n"
		<< "set MYMYP  " << random(_randParas["MYMYP"].min, _randParas["MYMYP"].max) << "\n"
		<< "set MCMY  " << random(_randParas["MCMY"].min, _randParas["MCMY"].max) << "\n"
		<< "set theta_u  " << random(_randParas["theta_u"].min, _randParas["theta_u"].max) << "\n"
		<< "set Lamda1(1)  " << random(_randParas["Lamda1(1)"].min, _randParas["Lamda1(1)"].max) << "\n"
		<< "set theta_p1(1)  " << random(_randParas["theta_p1(1)"].min, _randParas["theta_p1(1)"].max) << "\n"
		<< "set theta_pc1(1)  " << random(_randParas["theta_pc1(1)"].min, _randParas["theta_pc1(1)"].max) << "\n"
		<< "set Lamda1(2)  " << random(_randParas["Lamda1(2)"].min, _randParas["Lamda1(2)"].max) << "\n"
		<< "set theta_p1(2)  " << random(_randParas["theta_p1(2)"].min, _randParas["theta_p1(2)"].max) << "\n"
		<< "set theta_pc1(2)  " << random(_randParas["theta_pc1(2)"].min, _randParas["theta_pc1(2)"].max) << "\n"
		<< "set Lamda1(3)  " << random(_randParas["Lamda1(3)"].min, _randParas["Lamda1(3)"].max) << "\n"
		<< "set theta_p1(3)  " << random(_randParas["theta_p1(3)"].min, _randParas["theta_p1(3)"].max) << "\n"
		<< "set theta_pc1(3)  " << random(_randParas["theta_pc1(3)"].min, _randParas["theta_pc1(3)"].max) << "\n"
		<< "set Lamda2(1)  " << random(_randParas["Lamda2(1)"].min, _randParas["Lamda2(1)"].max) << "\n"
		<< "set theta_p2(1)  " << random(_randParas["theta_p2(1)"].min, _randParas["theta_p2(1)"].max) << "\n"
		<< "set theta_pc2(1)  " << random(_randParas["theta_pc2(1)"].min, _randParas["theta_pc2(1)"].max) << "\n";

	fout.close();

}


int OpenseesModelGenerator::round(double r)
{
	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}




