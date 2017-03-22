#include<iostream>
#include<fstream>
#include<string>
using namespace std;
void Res_init();
void deal_ins(unsigned int num,int c_num);
extern string instucts[5000];
extern unsigned int datas[5000];
extern int ins_num,data_num;
extern unsigned char buffer[5000];
extern unsigned int res[32], Lo, Hi, pc,moto_pc;
extern long intmin;
extern ofstream outfile;
extern ofstream errorfile;

unsigned int BtoD(string st);
int BtoDs(string st);
void HtoB(int i, int j, int num);
string DtoH(unsigned int number);
unsigned int HtoD(int n,int byt_num,bool isInit);
void save(int addr, int byt_num,unsigned int input);