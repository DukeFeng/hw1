
#include<iostream>
#include<fstream>
#include<string>
#include "head.h"
using namespace std;
string instucts[5000];
unsigned long datas[5000];
int ins_num,data_num;
unsigned char buffer[5000];
long long longmin = -1 * (long long)2147483648;
ofstream outfile("snapshot.rpt");
ofstream errorfile("error_dump.rpt");

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










//---------------------------------------------------------------------
int main()
{
	input();
	Res_init();
	int inum = BtoD(instucts[1]);
	deal_ins(pc,1);
	outfile.close();
	errorfile.close();
    return 0;
}

