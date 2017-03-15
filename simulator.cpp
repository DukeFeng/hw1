
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
string instucts[5000];
int ins_num;
unsigned char buffer[5000];

int BtoD(string st) {

	return 0;
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


void input() {
	ifstream fin;
	fin.open("iimage.bin", ios::binary);
	if (!fin) {
		cout << "open error!" << endl;
	}
	//char buffer[5000];
	int len = 0;
	while (!fin.eof() && fin.peek() != EOF) {
		fin >> buffer[len];
		len++;
	}
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
	for (int i = 0; i < ins_num; i++) cout << instucts[i]<< endl;
}


//-----------------------------Res----------------------------------
unsigned char res[32], Lo, Hi, pc;


//------------------------------------------------------------------
int main()
{
	input();
	int i;
	cin >> i;
    return 0;
}

