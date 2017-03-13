
#include<iostream>
#include<fstream>
using namespace std;
void input() {
	ifstream fin;
	fin.open("iimage.bin", ios::binary);
	if (!fin) {
		cout << "open error!" << endl;
	}
	char buffer[3073];
	fin.read(buffer, 3073 * sizeof(char));
	for (int i = 0; i < 17; i++) {
		unsigned char tmp = (unsigned char)buffer[i];
		cout << (unsigned short)tmp << endl;
	}
}
int main()
{
	input();
	int i;
	cin >> i;
    return 0;
}

