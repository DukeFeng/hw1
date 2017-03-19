
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
string instucts[5000];
unsigned long datas[5000];
int ins_num,data_num;
unsigned char buffer[5000];

unsigned long BtoD(string st) {
	int result = 0, ratio = 1;
	for (int i = st.length()-1; i >= 0; i--) {
		result += ratio*(st[i] - 48);
		ratio *= 2;
	}
	return result;
}
long BtoDs(string st) {
	int result = 0, ratio = 1;
	string s = st.substr(1);
	if (st[0] == '1')  for (int i = 0; i < s.length(); i++) if (s[i] == '0') s[i] = '1'; else s[i] = '0';
	result = BtoD(s);
	if (st[0]== '1') result = -1 * (result+1);
	return result;
}
void HtoB(int i, int j, int num) {
	unsigned short chr = (unsigned short)buffer[num];
	int kara = j * 8, made = (j + 1) * 8 - 1;
	if (chr != 0) 
		chr = chr;
	for (int ii = made; ii >= kara; ii--) {
		int out = chr % 2;
		instucts[i][ii] = out + '0';
		chr = chr / 2;
	}
}

string DtoH(unsigned long number) {
	string result="00000000";
	unsigned long temp=number;
	for (int i = 7; i >= 0; i--) {
		int k = temp % 16;
		if (k < 10) result[i] = k + '0'; else result[i] = k - 10 + 'A';
		temp /= 16;
	}
	return "0x" + result;
}
unsigned long HtoD(int n,int byt_num,bool isInit) {
	int kara; if (isInit)kara = n * byt_num; else kara = n;
	int made = kara + byt_num-1;
	unsigned long ratio = 1;
	unsigned long result = 0;
	for (int i = made; i >= kara; i--) {
		result += buffer[i] * ratio;
		ratio *= 256;
	}
	return result;
}

void save(int addr, int byt_num,unsigned long input) {
	int kara = addr; int made = kara + byt_num - 1;
	unsigned long inn = input;
	for (int i = made; i >= kara; i--) {
		buffer[i] = input % 256;
		input /= 256;
	}

}

void input() {
	ifstream fin;
	fin.open("iimage.bin", ios::binary);
	if (!fin) {
		cout << "open error!" << endl;
	}
	//char buffer[5000];
	int len = 0;
	while (!fin.eof()/* && fin.peek() != EOF*/) {
		char tt;
		fin.get(tt); buffer[len] = (unsigned char)tt;
		len++;
	}
	buffer[len] = EOF; len++;
	//fin.read(buffer, 3073 * sizeof(char));
	ins_num = len / 4;
	int temp=0;
	for (int i = 0; i < ins_num; i++) {
		instucts[i] = "00000000000000000000000000000000";  
		for (int j = 0; j < 4; j++) {
			HtoB(i, j, temp);
			temp++;
		}
	}
	//for (int i = 0; i < ins_num; i++) cout << instucts[i]<< endl;
	ifstream fin2;
	fin2.open("dimage.bin", ios::binary);
	if (!fin2) {
		cout << "open error!" << endl;
	}
	//char buffer[5000];
	len = 0;
	while (!fin2.eof()/* && fin.peek() != EOF*/) {
		char tt;
		fin2.get(tt); buffer[len] = (unsigned char)tt;
		len++;
	}
	buffer[len] = EOF; len++;
	//fin.read(buffer, 3073 * sizeof(char));
	data_num = len / 4;
	temp = 0;
	for (int i = 0; i < data_num; i++) {
		datas[i] = HtoD(i,4,true);
		
	}
	//for (int i = 0; i < data_num; i++) cout <<DtoH( datas[i] )<< endl;

}


//-----------------------------Res----------------------------------
unsigned long res[32], Lo=0, Hi=0, pc=0,moto_pc=0;
void Res_init() {
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





//--------------------------------------ins----------------------------

void deal_ins(unsigned long num,int c_num) {
	string ins = instucts[(num-moto_pc)/4 + 2];
	unsigned long Tres[32],TLo = Lo, THi = Hi, Tpc = pc;
	for (int i = 0; i < 32; i++) Tres[i] = res[i];
	Tpc += 4;
	string opcode = ins.substr(0, 6);
	if (opcode == "000000") {
		string func = ins.substr(26);
		/*00*/if (func == "000000") { long C = BtoD(ins.substr(21, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); Tres[rd] =Tres[rt]<<C; }
		/*02*/if (func == "000010") { long C = BtoD(ins.substr(21, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); Tres[rd] = Tres[rt] >> C; }
		/*03*/if (func == "000011") { long C = BtoD(ins.substr(21, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); Tres[rd] = Tres[rt] >> C; }
		/*08*/if (func == "101000") {long rs = BtoD(ins.substr(6, 5)); Tpc = rs;}
		/*10*/if (func == "010000") { long rd = BtoD(ins.substr(16, 5)); Tres[rd] = THi; }
		/*12*/if (func == "010010") { long rd = BtoD(ins.substr(16, 5)); Tres[rd] = TLo; }
		/*18*/if (func == "011000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long long re = rs*rt; THi = re / 0x100000000; TLo = re % 0x100000000; }
		/*19*/if (func == "011001") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long long re = rs*rt; THi = re / 0x100000000; TLo = re % 0x100000000;}
		/*20*/if (func == "100000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); Tres[rd] = Tres[rs] + Tres[rt];}
	    /*21*/if (func == "100001") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); Tres[rd] = Tres[rs] + Tres[rt];}
		/*22*/if (func == "100010") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); Tres[rd] = Tres[rs] - Tres[rt]; }
		/*24*/if (func == "100100") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); Tres[rd] = Tres[rs] & Tres[rt]; }
		/*25*/if (func == "100101") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); Tres[rd] = Tres[rs] | Tres[rt]; }
		/*26*/if (func == "100110") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); Tres[rd] = Tres[rs] ^ Tres[rt]; }
		/*27*/if (func == "100111") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); Tres[rd] = ~(Tres[rs] | Tres[rt]); }
		/*28*/if (func == "101000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long rd = BtoD(ins.substr(16, 5)); Tres[rd] = ~(Tres[rs] & Tres[rt]); }
		/*2A*/if (func == "101010") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoDs(ins.substr(11, 5)); long rd = BtoDs(ins.substr(16, 5)); Tres[rd] = Tres[rs] < Tres[rt]; }
	}


	/*02*/if (opcode == "000010") { long add = BtoD(ins.substr(6)); Tpc = Tpc & 0xF0000000; Tpc = Tpc | (add * 4); }
	/*03*/if (opcode == "000011") { long add = BtoD(ins.substr(6)); Tres[31] = Tpc; Tpc = Tpc & 0xF0000000; Tpc = Tpc | (add * 4); }
	/*04*/if (opcode == "000100") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); if (Tres[rs] == Tres[rt])Tpc += 4 * imm; }
	/*05*/if (opcode == "000101") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); if (Tres[rs] != Tres[rt])Tpc += 4 * imm; }
	/*07*/if (opcode == "000111") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); if (Tres[rs]>0)Tpc += 4 * imm; }
	/*08*/if (opcode == "001000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16)); Tres[rt] = (unsigned long)(Tres[rs] + (unsigned long)imm);	}
	/*09*/if (opcode == "001001") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); Tres[rt] = Tres[rs] + imm; }
	/*0A*/if (opcode == "001010") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16));  Tres[rt] =( (long)Tres[rs]) < imm;}
	/*0C*/if (opcode == "001100") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoDs(ins.substr(16));  Tres[rt] = Tres[rs] & imm;}
	/*0D*/if (opcode == "001101") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); Tres[rt] = Tres[rs] | imm; }
	/*0E*/if (opcode == "001110") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); Tres[rt] =~( Tres[rs] | imm); }
	/*0F*/if (opcode == "001111") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); Tres[rt] = imm<<16; }
	/*20*/if (opcode == "100000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); long addr = Tres[rs] + imm + 8; Tres[rt] = HtoD(addr, 1, false); if (Tres[rt] >= 128) Tres[rt]=Tres[rt]|0xFFFFFF00; }
	/*21*/if (opcode == "100001") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); long addr = Tres[rs] + imm + 8; Tres[rt] = HtoD(addr, 2, false); if (Tres[rt] >32767) Tres[rt] = Tres[rt] | 0xFFFF0000; }
	/*23*/if (opcode == "100011") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); long addr = Tres[rs] + imm + 8; Tres[rt] = HtoD(addr, 4, false); }
	/*24*/if (opcode == "100100") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); long addr = Tres[rs] + imm + 8; Tres[rt] = HtoD(addr, 1, false);  }
	/*25*/if (opcode == "100101") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); long addr = Tres[rs] + imm + 8; Tres[rt] = HtoD(addr, 2,false); }
	/*28*/if (opcode == "101000") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); long addr = Tres[rs] + imm + 8; save(addr, 1, Tres[rt] & 0x000000FF); }
	/*29*/if (opcode == "101001") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); long addr = Tres[rs] + imm + 8; save(addr, 2, Tres[rt] & 0x0000FFFF); }
	/*2B*/if (opcode == "101011") { long rs = BtoD(ins.substr(6, 5)); long rt = BtoD(ins.substr(11, 5)); long imm = BtoD(ins.substr(16)); long addr = Tres[rs] + imm + 8; save(addr, 4,Tres[rt]); }



	if (opcode == "111111") return;
	cout << "cycle "<<c_num << endl;
	for (int i = 0; i < 32; i++) if (Tres[i] != res[i]) { res[i] = Tres[i]; cout << "$"; if (i < 10) cout << "0"; cout << i << ": " << DtoH(res[i]) << endl;  }
	if (TLo != Lo) { Lo = TLo; cout << "$LO: " << DtoH(Lo) << endl;  }
	if (THi != Hi) { Hi = THi; cout << "$HI: " << DtoH(Hi) << endl;  }
	if (Tpc != pc) { pc = Tpc; cout << "PC: " << DtoH(pc) << endl;  }
	cout << endl;
	cout << endl;
	unsigned int ii=ins_num;
	if ((pc - moto_pc) / 4 < ii) deal_ins(pc,c_num+1);

}


//---------------------------------------------------------------------
int main()
{
	input();
	Res_init();
	int inum = BtoD(instucts[1]);
	deal_ins(pc,1);
	int i;
	cin >> i;
    return 0;
}

