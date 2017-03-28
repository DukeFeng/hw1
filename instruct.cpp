//--------------------------------------ins----------------------------
#include<iostream>
#include<fstream>
#include<string>
#include "head.h"
using namespace std;
bool multy_deal = false;	bool go_halt = false;
void deal_ins(unsigned int num,int c_num) {
	string ins ;
  if(((int)num-(int)moto_pc)>=0)ins=instucts[(num-moto_pc)/4 + 2];else ins="00000000000000000000000000000000";

	unsigned int Tres[32],TLo = Lo, THi = Hi, Tpc = pc;
	for (int i = 0; i < 32; i++) Tres[i] = res[i];
 //cout<<c_num<<"  "<<(int)Tres[17] <<" "<<endl;
	Tpc += 4;
	string opcode = ins.substr(0, 6);
	if (opcode == "000000") {
		string func = ins.substr(26);
		/*00sll*/if (func == "000000") { int C = BtoD(ins.substr(21, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0&& !(rd==0&&C==0&&rt==0)) errorfile << "In cycle "<<c_num<<": Write $0 Error" << endl;else  Tres[rd] = Tres[rt] << C; }
		/*02srl*/if (func == "000010") { int C = BtoD(ins.substr(21, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;
     else Tres[rd] = Tres[rt] >> C; }
		/*03sra*/if (func == "000011") { int C = BtoD(ins.substr(21, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; 
    else { Tres[rd] =(int) Tres[rt] >> C; } }
		/*08jr*/if (func == "001000") { int rs = BtoD(ins.substr(6, 5)); Tpc = Tres[rs];}
		/*10mfhi*/if (func == "010000") { multy_deal = false; int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = THi; }
		/*12mflo*/if (func == "010010") { multy_deal = false; int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = TLo; }
		/*18mult*/if (func == "011000") { if (multy_deal)errorfile << "In cycle " << c_num << ": Overwrite HI-LO registers" << endl;  { multy_deal = true; int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5));  unsigned long re = (long)(int)Tres[rs] *(long) (int)Tres[rt]; THi = re / 0x100000000; TLo = re % 0x100000000; } }
		/*19multu*/if (func == "011001") { if (multy_deal)errorfile << "In cycle " << c_num << ": Overwrite HI-LO registers" << endl;  { multy_deal = true; int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); unsigned long re = (unsigned long)Tres[rs] * (unsigned long) Tres[rt];  THi = re / 0x100000000; TLo = re % 0x100000000; }}
		/*20add*/if (func == "100000") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  { 
			long re = (long)(int)Tres[rs] + (long)(int)Tres[rt];
			if (re>2147483647||re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; 
			Tres[rd] = (unsigned int)((int)Tres[rs] + (int)Tres[rt]); } }
	    /*21addu*/if (func == "100001") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = Tres[rs] + Tres[rt];}
		/*22sub*/if (func == "100010") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  { long re = (long)(int)Tres[rs] - (long)(int)Tres[rt];  if (re>2147483647 || re<intmin||(long)(int)Tres[rt]<-2147483647)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; Tres[rd] = (unsigned int)((int)Tres[rs] - (int)Tres[rt]); } }
		/*24and*/if (func == "100100") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = Tres[rs] & Tres[rt]; }
		/*25or*/if (func == "100101") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = Tres[rs] | Tres[rt]; }
		/*26xor*/if (func == "100110") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = Tres[rs] ^ Tres[rt]; }
		/*27nor*/if (func == "100111") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = ~(Tres[rs] | Tres[rt]); }
		/*28nand*/if (func == "101000") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = ~(Tres[rs] & Tres[rt]); }
		/*2Aslt*/if (func == "101010") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rd] = (int)Tres[rs] < (int)Tres[rt]; }
	}


	/*02j*/if (opcode == "000010") { int add = BtoD(ins.substr(6)); Tpc = Tpc & 0xF0000000; Tpc = Tpc | (add * 4); }
	/*03jal*/if (opcode == "000011") { int add = BtoD(ins.substr(6)); Tres[31] = Tpc; Tpc = Tpc & 0xF0000000; Tpc = Tpc | (add * 4); }
	/*04beq*/if (opcode == "000100") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); long re=Tpc+4*imm;if (re>2147483647)errorfile << "In cycle " << c_num << ": Number Overflow" << endl;if (Tres[rs] == Tres[rt])Tpc += 4 * imm; }
	/*05bne*/if (opcode == "000101") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); long re=Tpc+4*imm;if (re>2147483647)errorfile << "In cycle " << c_num << ": Number Overflow" << endl;if (Tres[rs] != Tres[rt])Tpc += 4 * imm; }
	/*07bgtz*/if (opcode == "000111") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); long re=Tpc+4*imm;if (re>2147483647)errorfile << "In cycle " << c_num << ": Number Overflow" << endl;if ((int)Tres[rs]>0)Tpc += 4 * imm; }
	/*08addi*/if (opcode == "001000") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); 
	if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  {
		long re = ((long)(int)Tres[rs] + (long)(int)imm); 
		if (re>2147483647 || re<intmin)
		{	errorfile << "In cycle " << c_num << ": Number Overflow" << endl; }
		Tres[rt] = (int)Tres[rs] + (int)imm; } }
	/*09addiu*/if (opcode == "001001") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16));  if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rt] = Tres[rs] + (unsigned int)imm; }
	/*0Aslti*/if (opcode == "001010") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;   Tres[rt] =( (int)Tres[rs]) < imm;}
	/*0Candi*/if (opcode == "001100") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); unsigned int imm = BtoD(ins.substr(16)); if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rt] = Tres[rs] & imm;}
	/*0Dori*/if (opcode == "001101") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); unsigned int imm = BtoD(ins.substr(16)); if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rt] = Tres[rs] | imm; }
	/*0Enori*/if (opcode == "001110") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); unsigned int imm = BtoD(ins.substr(16)); if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rt] =~( Tres[rs] | imm); }
	/*0Flui*/if (opcode == "001111") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoD(ins.substr(16)); if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  Tres[rt] = imm<<16; }
	/*20lb*/if (opcode == "100000") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); long addr =(long) Tres[rs] +(long) imm + 8; if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  { long re = (long)Tres[rs] + (long)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if ((unsigned int)(addr - 8) > 1023||addr - 8 <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else { Tres[rt] = HtoD(addr, 1, false); if (Tres[rt] >= 128) Tres[rt] = Tres[rt] | 0xFFFFFF00; } } }
	/*21lh*/if (opcode == "100001") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); long addr =(long) Tres[rs] +(long) imm + 8; if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  { long re = (long)(int)Tres[rs] + (long)(int)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl;if ((unsigned int)(addr - 8 + 1) > 1023||addr - 8 <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; }  if ((addr - 8) % 2 != 0) { errorfile << "In cycle " << c_num << ": Misalignment Error" << endl; go_halt = true; } else { Tres[rt] = HtoD(addr, 2, false); if (Tres[rt] > 32767) Tres[rt] = Tres[rt] | 0xFFFF0000; } } }
	/*23lw*/if (opcode == "100011") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16));  long addr = (long)Tres[rs] +(long) imm + 8; if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  { long re = (long)(int)Tres[rs] + (long)(int)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if ((unsigned int)(addr - 8 + 3) > 1023||addr - 8 <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; }  if ((addr - 8) % 4 != 0) { errorfile << "In cycle " << c_num << ": Misalignment Error" << endl; go_halt = true; } else Tres[rt] = HtoD(addr, 4, false); } }
	/*24lbu*/if (opcode == "100100") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); long addr =(long) Tres[rs] +(long) imm + 8; if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  { long re = (long)(int)Tres[rs] + (long)(int)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if ((unsigned int)(addr - 8) > 1023||addr - 8 <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else Tres[rt] = HtoD(addr, 1, false); } }
	/*25lhu*/if (opcode == "100101") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoDs(ins.substr(16)); long addr =(long) Tres[rs] +(long) imm + 8; if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl;  { long re = (long)(int)Tres[rs] + (long)(int)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if ((unsigned int)(addr - 8 + 1) > 1023||addr - 8 <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; }  if ((addr - 8) % 2 != 0) { errorfile << "In cycle " << c_num << ": Misalignment Error" << endl; go_halt = true; } else Tres[rt] = HtoD(addr, 2, false); } }
	/*28sb*/if (opcode == "101000") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoD(ins.substr(16)); long addr =(long) Tres[rs] +(long) imm + 8; {long re = (long)(int)Tres[rs] + (long)(int)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if ((unsigned int)(addr - 8) > 1023||addr - 8 <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; }  save(addr, 4,( Tres[rt] & 0x000000FF)<<24); } cout<<addr<<" "<<(int)buffer[addr]<<" "<<(int)buffer[addr+1]<<" "<<(int)buffer[addr+2]<<" "<<(int)buffer[addr+3];
  }
	/*29sh*/if (opcode == "101001") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoD(ins.substr(16)); long addr =(long) Tres[rs] +(long) imm + 8; {long re = (long)(int)Tres[rs] + (long)(int)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if ((unsigned int)(addr - 8 + 1) > 1023||addr - 8 <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; }  if ((addr - 8) % 2 != 0) { errorfile << "In cycle " << c_num << ": Misalignment Error" << endl; go_halt = true; } else save(addr, 4,( Tres[rt] & 0x0000FFFF)<<16); }int kk= (Tres[rt] & 0x0000FFFF)<<16;cout<<Tres[rt]<<" "<<kk<<endl;
  cout<<addr<<" "<<(int)buffer[addr]<<" "<<(int)buffer[addr+1]<<" "<<(int)buffer[addr+2]<<" "<<(int)buffer[addr+3];
   }
	/*2Bswv */if (opcode == "101011") { int rs = BtoD(ins.substr(6, 5)); int rt = BtoD(ins.substr(11, 5)); int imm = BtoD(ins.substr(16)); long addr =(long) Tres[rs] +(long) imm + 8; {long re = (long)(int)Tres[rs] + (long)(int)imm; if (re>2147483647 || re<intmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if ((unsigned int)(addr - 8 + 3) > 1023||addr - 8 <0) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; }  if ((addr - 8) % 4 != 0) { errorfile << "In cycle " << c_num << ": Misalignment Error" << endl; go_halt = true; } else  save(addr, 4, Tres[rt]); } cout<<addr<<" "<<(int)buffer[addr]<<" "<<(int)buffer[addr+1]<<" "<<(int)buffer[addr+2]<<" "<<(int)buffer[addr+3];
   }

cout<<"cycle "<<c_num <<" " <<ins<<endl;
Tres[0]=0;
if (opcode == "111111" || go_halt) { 
		go_halt = true; return; }

	
	if (outfile.is_open()) {
	outfile << "cycle "<<c_num << endl;
	for (int i = 0; i < 32; i++) if (Tres[i] != res[i]) { res[i] = Tres[i]; outfile << "$"; if (i < 10) outfile << "0"; outfile << i << ": " << DtoH(res[i]) << endl;  }
	if (THi != Hi) { Hi = THi; outfile << "$HI: " << DtoH(Hi) << endl;  }
	if (TLo != Lo) { Lo = TLo; outfile << "$LO: " << DtoH(Lo) << endl; }
	if (Tpc != pc) { pc = Tpc; outfile << "PC: " << DtoH(pc) << endl;  }
	outfile << endl;
	outfile << endl;
	
	}


	

}
