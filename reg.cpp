#include<iostream>
#include<fstream>
#include<string>
#include "head.h"
using namespace std;
//-----------------------------Res----------------------------------

void Res_init() {
	Lo=0, Hi=0, pc=0,moto_pc=0;
	pc = BtoD(instucts[0]); moto_pc = pc;
	res[29] = datas[0];
	cout << "cycle 0" << endl;
	for (int i = 0; i < 32; i++) { cout << "$"; if (i < 10) cout << "0"; cout << i << ": " << DtoH(res[i]) << endl; }
	cout << "$LO: " << DtoH(Lo) << endl;
	cout << "$HI: " << DtoH(Hi) << endl;
	cout << "PC: " << DtoH(pc) << endl;
	cout << endl;
	cout << endl;
}

//------------------------------------------------------------------