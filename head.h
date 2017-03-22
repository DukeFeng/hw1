#include<iostream>
#include<fstream>
#include<string>
using namespace std;
void Res_init();
void deal_ins(unsigned long num,int c_num);
extern string instucts[5000];
extern unsigned long datas[5000];
extern int ins_num,data_num;
extern unsigned char buffer[5000];
extern unsigned long res[32], Lo, Hi, pc,moto_pc;
extern long long longmin;
extern ofstream outfile;
extern ofstream errorfile;

unsigned long BtoD(string st);
long BtoDs(string st);
void HtoB(int i, int j, int num);
string DtoH(unsigned long number);
unsigned long HtoD(int n,int byt_num,bool isInit);
void save(int addr, int byt_num,unsigned long input);