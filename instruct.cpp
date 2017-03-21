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
		/*00*/if (func == "000000") { long C = BtoD(ins.substr(21, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0&& !(rd==0&&C==0&&rt==0)) cout << "In cycle "<<c_num<<": Write $0 Error" << endl;else  Tres[rd] = Tres[rt] << C; }
		/*02*/if (func == "000010") { long C = BtoD(ins.substr(21, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = Tres[rt] >> C; }
		/*03*/if (func == "000011") { long C = BtoD(ins.substr(21, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = Tres[rt] >> C; }
		/*08*/if (func == "001000") { long rs = BtoD(ins.substr(6, 5)); Tpc = Tres[rs];}
		/*10*/if (func == "010000") { multy_deal = false; long rd = BtoD(ins.substr(16, 5)); if (rd == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = THi; }
		/*12*/if (func == "010010") { multy_deal = false; long rd = BtoD(ins.substr(16, 5)); if (rd == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = TLo; }
		/*18*/if (func == "011000") { if (multy_deal)cout << "In cycle " << c_num << ": Overwrite HI-LO registers" << endl;  { multy_deal = true; long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5));  long long re = (long)Tres[rs] * (long)Tres[rt];if (re>0x7FFFFFFFFFFFFFFF||re<-0x1000000000000000)cout << "In cycle " << c_num << ": Number Overflow" << endl; THi = re / 0x100000000; TLo = re % 0x100000000; } }
		/*19*/if (func == "011001") { if (multy_deal)cout << "In cycle " << c_num << ": Overwrite HI-LO registers" << endl;  { multy_deal = true; long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); unsigned long long re = (unsigned long long)Tres[rs] * (unsigned long long) Tres[rt];  THi = re / 0x100000000; TLo = re % 0x100000000; }}
		/*20*/if (func == "100000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else { unsigned long re = (long)Tres[rs] + (long)Tres[rt]; if (re>2147483647||re<-2147483648)cout << "In cycle " << c_num << ": Number Overflow" << endl; Tres[rd] = (unsigned long)re; } }
	    /*21*/if (func == "100001") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = Tres[rs] + Tres[rt];}
		/*22*/if (func == "100010") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else { long long re = Tres[rs] - Tres[rt]; if (re>2147483647 || re<-2147483648)cout << "In cycle " << c_num << ": Number Overflow" << endl; Tres[rd] = (unsigned long)re; } }
		/*24*/if (func == "100100") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = Tres[rs] & Tres[rt]; }
		/*25*/if (func == "100101") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = Tres[rs] | Tres[rt]; }
		/*26*/if (func == "100110") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = Tres[rs] ^ Tres[rt]; }
		/*27*/if (func == "100111") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = ~(Tres[rs] | Tres[rt]); }
		/*28*/if (func == "101000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); if (rd == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = ~(Tres[rs] & Tres[rt]); }
		/*2A*/if (func == "101010") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoDs(ins.substr(11, 5)); long rd = BtoDs(ins.substr(16, 5)); if (rd == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rd] = Tres[rs] < Tres[rt]; }
	}


	/*02*/if (opcode == "000010") { long add = BtoD(ins.substr(6)); Tpc = Tpc & 0xF0000000; Tpc = Tpc | (add * 4); }
	/*03*/if (opcode == "000011") { long add = BtoD(ins.substr(6)); Tres[31] = Tpc; Tpc = Tpc & 0xF0000000; Tpc = Tpc | (add * 4); }
	/*04*/if (opcode == "000100") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); if (Tres[rs] == Tres[rt])Tpc += 4 * imm; }
	/*05*/if (opcode == "000101") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); if (Tres[rs] != Tres[rt])Tpc += 4 * imm; }
	/*07*/if (opcode == "000111") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); if (Tres[rs]>0)Tpc += 4 * imm; }
	/*08*/if (opcode == "001000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16));  if (rt == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else {unsigned long re = ((long)Tres[rs] + (long)imm); if (re>2147483647 || re<-2147483648)cout << "In cycle " << c_num << ": Number Overflow" << endl; Tres[rt] = re; } }
	/*09*/if (opcode == "001001") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16));  if (rt == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rt] = Tres[rs] + (unsigned long)imm; }
	/*0A*/if (opcode == "001010") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16)); if (rt == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else  Tres[rt] =( (long)Tres[rs]) < imm;}
	/*0C*/if (opcode == "001100") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); unsigned long imm = BtoDs(ins.substr(16)); if (rt == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rt] = Tres[rs] & imm;}
	/*0D*/if (opcode == "001101") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); unsigned long imm = BtoD(ins.substr(16)); if (rt == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rt] = Tres[rs] | imm; }
	/*0E*/if (opcode == "001110") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); unsigned long imm = BtoD(ins.substr(16)); if (rt == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rt] =~( Tres[rs] | imm); }
	/*0F*/if (opcode == "001111") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); if (rt == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else Tres[rt] = imm<<16; }
	/*20*/if (opcode == "100000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16)); long addr = Tres[rs] + imm + 8; if (rt == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else { unsigned long re = (long)Tres[rs] + (long)imm; if (re>2147483647 || re<-2147483648)cout << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 > 1023) { cout << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else { Tres[rt] = HtoD(addr, 1, false); if (Tres[rt] >= 128) Tres[rt] = Tres[rt] | 0xFFFFFF00; } } }
	/*21*/if (opcode == "100001") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16)); long addr = Tres[rs] + imm + 8; if (rt == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else { unsigned long re = (long)Tres[rs] + (long)imm; if (re>2147483647 || re<-2147483648)cout << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 + 1 > 1023) { cout << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else if ((addr - 8) % 2 != 0) { cout << "In cycle " << c_num << ": Data misaligned" << endl; go_halt = true; } else { Tres[rt] = HtoD(addr, 2, false); if (Tres[rt] > 32767) Tres[rt] = Tres[rt] | 0xFFFF0000; } } }
	/*23*/if (opcode == "100011") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16)); long addr = Tres[rs] + imm + 8; if (rt == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else { unsigned long re = (long)Tres[rs] + (long)imm; if (re>2147483647 || re<-2147483648)cout << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 + 3 > 1023) { cout << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else if ((addr - 8) % 4 != 0) { cout << "In cycle " << c_num << ": Data misaligned" << endl; go_halt = true; } else Tres[rt] = HtoD(addr, 4, false); } }
	/*24*/if (opcode == "100100") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16)); long addr = Tres[rs] + imm + 8; if (rt == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else { unsigned long re = (long)Tres[rs] + (long)imm; if (re>2147483647 || re<-2147483648)cout << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 > 1023) { cout << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else Tres[rt] = HtoD(addr, 1, false); } }
	/*25*/if (opcode == "100101") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16)); long addr = Tres[rs] + imm + 8; if (rt == 0) cout << "In cycle " << c_num << ": Write $0 Error" << endl; else { unsigned long re = (long)Tres[rs] + (long)imm; if (re>2147483647 || re<-2147483648)cout << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 + 1 > 1023) { cout << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else if ((addr - 8) % 2 != 0) { cout << "In cycle " << c_num << ": Data misaligned" << endl; go_halt = true; } else Tres[rt] = HtoD(addr, 2, false); } }
	/*28*/if (opcode == "101000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); long addr = Tres[rs] + imm + 8; {unsigned long re = (long)Tres[rs] + (long)imm; if (re>2147483647 || re<-2147483648)cout << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 > 1023) { cout << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else save(addr, 1, Tres[rt] & 0x000000FF); } }
	/*29*/if (opcode == "101001") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); long addr = Tres[rs] + imm + 8; {unsigned long re = (long)Tres[rs] + (long)imm; if (re>2147483647 || re<-2147483648)cout << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 + 1 > 1023) { cout << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else if ((addr - 8) % 2 != 0) { cout << "In cycle " << c_num << ": Data misaligned" << endl; go_halt = true; } else save(addr, 2, Tres[rt] & 0x0000FFFF); } }
	/*2B*/if (opcode == "101011") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); long addr = Tres[rs] + imm + 8; {unsigned long re = (long)Tres[rs] + (long)imm; if (re>2147483647 || re<-2147483648)cout << "In cycle " << c_num << ": Number Overflow" << endl; if (addr - 8 + 3 > 1023) { cout << "In cycle " << c_num << ": Address Overflow" << endl; go_halt = true; } else if ((addr - 8) % 4 != 0) { cout << "In cycle " << c_num << ": Data misaligned" << endl; go_halt = true; } else  save(addr, 4, Tres[rt]); } }



	if (opcode == "111111"||go_halt) return;
	cout << "cycle "<<c_num << endl;
	for (int i = 0; i < 32; i++) if (Tres[i] != res[i]) { res[i] = Tres[i]; cout << "$"; if (i < 10) cout << "0"; cout << i << ": " << DtoH(res[i]) << endl;  }
	if (THi != Hi) { Hi = THi; cout << "$HI: " << DtoH(Hi) << endl;  }
	if (TLo != Lo) { Lo = TLo; cout << "$LO: " << DtoH(Lo) << endl; }
	if (Tpc != pc) { pc = Tpc; cout << "PC: " << DtoH(pc) << endl;  }
	cout << endl;
	cout << endl;
	unsigned int ii=ins_num;
	if ((pc - moto_pc) / 4 < ii) deal_ins(pc,c_num+1);

}
