//--------------------------------------ins----------------------------
#include<iostream>
#include<fstream>
#include<string>
#include "head.h"
using namespace std;
bool multy_deal = false;
void deal_ins(unsigned long num,int c_num) {
	string ins = instucts[(num-moto_pc)/4 + 2];
	bool go_halt = false;
	unsigned long Tres[32],TLo = Lo, THi = Hi, Tpc = pc;
	for (int i = 0; i < 32; i++) Tres[i] = res[i];
	Tpc += 4;
	string opcode = ins.substr(0, 6);
	if (opcode == "000000") {
		string func = ins.substr(26);
		/*00sll*/if (func == "000000") { long C = BtoD(ins.substr(21, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0&& !(rd==0&&C==0&&rt==0)) errorfile << "In cycle "<<c_num<<": Write $0 Error" << endl;else  Tres[rd] = Tres[rt] << C; }
		/*02srl*/if (func == "000010") { long C = BtoD(ins.substr(21, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = Tres[rt] >> C; }
		/*03sra*/if (func == "000011") { long C = BtoD(ins.substr(21, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = Tres[rt] >> C; }
		/*08jr*/if (func == "001000") { long rs = BtoD(ins.substr(6, 5)); Tpc = Tres[rs];}
		/*10mfhi*/if (func == "010000") { multy_deal = false; long rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = THi; }
		/*12mflo*/if (func == "010010") { multy_deal = false; long rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = TLo; }
		/*18mult*/if (func == "011000") { if (multy_deal)errorfile << "In cycle " << c_num << ": Overwrite HI-LO registers" << endl;  { multy_deal = true; long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5));  unsigned long long re = (long)Tres[rs] * (long)Tres[rt];if (re>0x7FFFFFFFFFFFFFFF)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; THi = re / 0x100000000; TLo = re % 0x100000000; } }
		/*19multu*/if (func == "011001") { if (multy_deal)errorfile << "In cycle " << c_num << ": Overwrite HI-LO registers" << endl;  { multy_deal = true; long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); unsigned long long re = (unsigned long long)Tres[rs] * (unsigned long long) Tres[rt];  THi = re / 0x100000000; TLo = re % 0x100000000; }}
		/*20add*/if (func == "100000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else { 
			long long re = (long long)Tres[rs] + (long long)Tres[rt];
			if (re>2147483647||re<longmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; 
			Tres[rd] = (unsigned long)((long)Tres[rs] + (long)Tres[rt]); } }
	    /*21addu*/if (func == "100001") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = Tres[rs] + Tres[rt];}
		/*22sub*/if (func == "100010") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else { long long re = (long long)Tres[rs] - (long long)Tres[rt]; if (re>2147483647 || re<longmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; Tres[rd] = (unsigned long)((long)Tres[rs] - (long)Tres[rt]); } }
		/*24and*/if (func == "100100") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = Tres[rs] & Tres[rt]; }
		/*25or*/if (func == "100101") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = Tres[rs] | Tres[rt]; }
		/*26xor*/if (func == "100110") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = Tres[rs] ^ Tres[rt]; }
		/*27nor*/if (func == "100111") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = ~(Tres[rs] | Tres[rt]); }
		/*28nand*/if (func == "101000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = ~(Tres[rs] & Tres[rt]); }
		/*2Aslt*/if (func == "101010") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoDs(ins.substr(11, 5)); long rd = BtoDs(ins.substr(16, 5)); if (rd == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = Tres[rs] < Tres[rt]; }
	}


	/*02j*/if (opcode == "000010") { long add = BtoD(ins.substr(6)); Tpc = Tpc & 0xF0000000; Tpc = Tpc | (add * 4); }
	/*03jal*/if (opcode == "000011") { long add = BtoD(ins.substr(6)); Tres[31] = Tpc; Tpc = Tpc & 0xF0000000; Tpc = Tpc | (add * 4); }
	/*04beq*/if (opcode == "000100") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); if (Tres[rs] == Tres[rt])Tpc += 4 * imm; }
	/*05bne*/if (opcode == "000101") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); if (Tres[rs] != Tres[rt])Tpc += 4 * imm; }
	/*07bgtz*/if (opcode == "000111") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); if (Tres[rs]>0)Tpc += 4 * imm; }
	/*08addi*/if (opcode == "001000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16));  if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else {
		long long re = ((long long)Tres[rs] + (long long)imm); 
		if (re>2147483647 || re<longmin)
			errorfile << "In cycle " << c_num << ": Number Overflow" << endl; 
		Tres[rt] = (long)Tres[rs] + (long)imm; } }
	/*09addiu*/if (opcode == "001001") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16));  if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rt] = Tres[rs] + (unsigned long)imm; }
	/*0Aslti*/if (opcode == "001010") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16)); if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else  Tres[rt] =( (long)Tres[rs]) < imm;}
	/*0Candi*/if (opcode == "001100") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); unsigned long imm = BtoDs(ins.substr(16)); if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rt] = Tres[rs] & imm;}
	/*0Dori*/if (opcode == "001101") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); unsigned long imm = BtoD(ins.substr(16)); if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rt] = Tres[rs] | imm; }
	/*0Enori*/if (opcode == "001110") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); unsigned long imm = BtoD(ins.substr(16)); if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rt] =~( Tres[rs] | imm); }
	/*0Flui*/if (opcode == "001111") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rt] = imm<<16; }
	/*20lb*/if (opcode == "100000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16)); long addr = (long)Tres[rs] + imm + 8; if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else { long long re = (long long)Tres[rs] + (long long)imm; if (re>2147483647 || re<longmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 > 1023) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else { Tres[rt] = HtoD(addr, 1, false); if (Tres[rt] >= 128) Tres[rt] = Tres[rt] | 0xFFFFFF00; } } }
	/*21lh*/if (opcode == "100001") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16)); long addr = (long)Tres[rs] + imm + 8; if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else { long long re = (long long)Tres[rs] + (long long)imm; if (re>2147483647 || re<longmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 + 1 > 1023) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else if ((addr - 8) % 2 != 0) { errorfile << "In cycle " << c_num << ": Data misaligned" << endl; go_halt = true; } else { Tres[rt] = HtoD(addr, 2, false); if (Tres[rt] > 32767) Tres[rt] = Tres[rt] | 0xFFFF0000; } } }
	/*23lw*/if (opcode == "100011") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16)); long addr = (long)Tres[rs] + imm + 8; if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else { long long re = (long long)Tres[rs] + (long long)imm; if (re>2147483647 || re<longmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 + 3 > 1023) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else if ((addr - 8) % 4 != 0) { errorfile << "In cycle " << c_num << ": Data misaligned" << endl; go_halt = true; } else Tres[rt] = HtoD(addr, 4, false); } }
	/*24lbu*/if (opcode == "100100") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16)); long addr = (long)Tres[rs] + imm + 8; if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else { long long re = (long long)Tres[rs] + (long long)imm; if (re>2147483647 || re<longmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 > 1023) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else Tres[rt] = HtoD(addr, 1, false); } }
	/*25lhu*/if (opcode == "100101") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16)); long addr = (long)Tres[rs] + imm + 8; if (rt == 0) errorfile << "In cycle " << c_num << ": Write $0 Error" << endl; else { long long re = (long long)Tres[rs] + (long long)imm; if (re>2147483647 || re<longmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 + 1 > 1023) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else if ((addr - 8) % 2 != 0) { errorfile << "In cycle " << c_num << ": Data misaligned" << endl; go_halt = true; } else Tres[rt] = HtoD(addr, 2, false); } }
	/*28sb*/if (opcode == "101000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); long addr = (long)Tres[rs] + imm + 8; {long long re = (long long)Tres[rs] + (long long)imm; if (re>2147483647 || re<longmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 > 1023) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else save(addr, 1, Tres[rt] & 0x000000FF); } }
	/*29sh*/if (opcode == "101001") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); long addr = (long)Tres[rs] + imm + 8; {long long re = (long long)Tres[rs] + (long long)imm; if (re>2147483647 || re<longmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 + 1 > 1023) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else if ((addr - 8) % 2 != 0) { errorfile << "In cycle " << c_num << ": Data misaligned" << endl; go_halt = true; } else save(addr, 2, Tres[rt] & 0x0000FFFF); } }
	/*2Bswv */if (opcode == "101011") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); long addr = (long)Tres[rs] + imm + 8; {long long re = (long long)Tres[rs] + (long long)imm; if (re>2147483647 || re<longmin)errorfile << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 + 3 > 1023) { errorfile << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else if ((addr - 8) % 4 != 0) { errorfile << "In cycle " << c_num << ": Data misaligned" << endl; go_halt = true; } else  save(addr, 4, Tres[rt]); } }



	if (opcode == "111111"||go_halt) return;

	
	if (outfile.is_open()) {
	outfile << "cycle "<<c_num << endl;
	for (int i = 0; i < 32; i++) if (Tres[i] != res[i]) { res[i] = Tres[i]; outfile << "$"; if (i < 10) outfile << "0"; outfile << i << ": " << DtoH(res[i]) << endl;  }
	if (THi != Hi) { Hi = THi; outfile << "$HI: " << DtoH(Hi) << endl;  }
	if (TLo != Lo) { Lo = TLo; outfile << "$LO: " << DtoH(Lo) << endl; }
	if (Tpc != pc) { pc = Tpc; outfile << "PC: " << DtoH(pc) << endl;  }
	outfile << endl;
	outfile << endl;
	
	}


	unsigned int ii=ins_num;
	if ((pc - moto_pc) / 4 < ii) deal_ins(pc,c_num+1);

}
