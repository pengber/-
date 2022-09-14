#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

int fromBin(const char * szb) {
	if (!szb) return 0;
	int ic = strlen(szb), i = 0, h = 0, b = 1;
	// for(i=0;i<ic;i++){ if(szb[i]=='1') h+=b; b<<=1;} // 高位答在右
	for (i = ic - 1; i >= 0; i--) { if (szb[i] == '1') h += b; b <<= 1; } // 高位在左
	return h;
} // fromBin

int t_fromBin() {
	char sb[64] = "1010";
	char c;
	int i = 0;
	
	while (c = getchar()) {
		if (c == '\n') break;
		sb[i++] = c;
	}
	int ib = fromBin(sb);
	return ib;
}
unsigned int get_dividor() {
	cout << "Please input the polynomial power like 3 2 0 which represent x^3 + x^2 +1:" << endl;
	cout << "(the first bit and last bit must be 1 in CRC, so you must end the input in zero)" << endl;;
	int temp;
	unsigned int result = 0;
	while (cin >> temp && temp != 0) {
		result += (1 << temp);
	}
	result += 1;
	return result;
}
unsigned int get_length(unsigned int num) {
	//一个无符号整数最高的有多少位有效二进制位,10两位，101三位
	unsigned int k = 0;
	while(num != 0) {
		num = num >> 1;
		k++;
	}
	return k;
}
unsigned int divide_mode_two(unsigned int num, unsigned int dividor) {
	//返回模2除的商,输入除数和被除数例如101001000,1101，返回001
	int r = get_length(dividor) - 1;		//得到多项式的阶
	int l = get_length(num) - r;				//num刚没有扩展阶的时候的位数
	int count = 0;							//计数，除了多少次，除了num刚开始的长度的话，就退出循环
	unsigned int beiChuShu = num;
	unsigned int chuShu = dividor << (l - 1);
	unsigned int shang = 0;
	while (l != 0) {

		
		while (get_length(beiChuShu) < get_length(chuShu)) {
			chuShu = chuShu >> 1;
			l = l - 1;
		}
		shang = beiChuShu ^ chuShu;
		beiChuShu = shang;
		chuShu = chuShu >> 1;
		l--;

	}
	return beiChuShu;

}

int main() {

	char choice = 0;

	cout << "Please input the choice order, input 0 to quit!" << endl;
	cout << "1.encode" << endl;
	cout << "2.decode" << endl;
	while (choice = getchar()) {
		if (choice == '0') {
			return 0;
		}
		while (getchar() != '\n')
			continue;
		if (choice == '1') {
			cout << "Please input the info string consist of 0 or 1, like 101001" << endl;
			unsigned int  info = t_fromBin();
			unsigned int dividor = get_dividor();
			unsigned int ex_info = info << (get_length(dividor) - 1);
			unsigned int yushu = divide_mode_two(ex_info, dividor);
			unsigned int code = (info << (get_length(dividor) - 1)) + yushu;
			printf("code is %#x", code);
			cout << endl;
			cout << "Please input the choice continue" << endl;
		}
		else {
			cout << "Please input the info string consist of 0 or 1, like 101001000" << endl;
			unsigned int code = t_fromBin();
			unsigned int dividor = get_dividor();
			unsigned int yushu = divide_mode_two(code, dividor);
			if (yushu == 0) {
				cout << "There is no wrong bit;" << endl;
			}
			else {
				cout << "There is wrong bit!" << endl;
			}
			cout << "Please input the choice continue" << endl;
		}

	}
	system("pause");
	return 0;
}