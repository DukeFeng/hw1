#include<iostream>
#include<fstream>
#include<string>
using namespace std;
void Res_init();
void deal_ins(unsigned long num,int c_num);
string instucts[5000];
unsigned long datas[5000];
int ins_num,data_num;
unsigned char buffer[5000];
unsigned long res[32], Lo, Hi, pc,moto_pc;

unsigned long BtoD(string st);
long BtoDs(string st);
void HtoB(int i, int j, int num);
string DtoH(unsigned long number);
unsigned long HtoD(int n,int byt_num,bool isInit);
void save(int addr, int byt_num,unsigned long input);