#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
using	namespace std;

int get_k_of_info(string info) {

	int n = info.size();
	int k = 0;
	while ((n + k) > pow(2, k) + 1) {
		k++;
	}
	return k;
}
int get_k_of_code(string code) {
	int l = code.size();
	int k = 0;
	while (l > pow(2, k) + 1) {
		k++;
	}
	return k;
}
string encode(string info) {
	int k = get_k_of_info(info);
	int new_size = info.size() + k;	//编码后的size
	for (int j = 0; j < k; j++) {
		//先形成未求得校验位的新串
		info.insert(info.end() - pow(2, j) + 1, '0');
	}
	for (int j = 0; j < k; j++) {
		int p = 0;				//第j个校验位
		int p_order = 1 << j;	//校验位是第几个，以1开始，从info后往前数
		for (int i = 0; i != new_size; i++) {
			int order = new_size - i;
			int if_info_location = 1;
			for (int j = 0; j < k; j++) {
				if (order == pow(2, j)) {
					if_info_location = 0;		//不是信息位
					break;
				}
			}
			if (!if_info_location) {			//不是信息位就找下一位信息位
				continue;
			}
			if ((order & p_order) != 0) {		//如果order的p_order位不为0的话
				p = p ^ int(info.at(i) - '0');  //int(1) == '1' - '0' 但是 ！= int ('1')
			}
		}

		info.at(new_size - p_order) = '0'+p;//'0'+1 // char (1) 
	}
	return info;
}

int decode(string code) {			//返回出错的位置
	int k = get_k_of_code(code);
	int new_size = code.size();
	int s = 0;
	int location = 0;				//出错的位置数
	for (int j = 0; j < k; j++) {
		
		int p_order = 1 << j;	//校验位是第几个，以1开始，从code后往前数
		int p = code.at(new_size - p_order) - '0';
		s = p;
		for (int i = 0; i != new_size; i++) {
			int order = new_size - i;
			int if_code_location = 1;
			for (int j = 0; j < k; j++) {
				if (order == pow(2, j)) {
					if_code_location = 0;		//不是信息位
					break;
				}
			}
			if (!if_code_location) {			//不是信息位就找下一位信息位
				continue;
			}
			if ((order & p_order) != 0) {		//如果order的p_order位不为0的话
				s = s ^ int(code.at(i) - '0');  //int(1) == '1' - '0' 但是 ！= int ('1')
			}
		}
		s = s << j;
		location += s;
	}
	return location;
}
int main() {
	string bunch= "1010";
	string code = "1010010";
	int choice = 0;

	cout << "Please input the choice order, input 0 to quit!" << endl;
	cout << "1.encode" << endl;
	cout << "2.decode" << endl;
	while (cin >> choice && choice != 0) {
		if (choice == 1) {
			cout << "Please input the info string consist of 0 or 1, like 1010" << endl;
			cin >> bunch;
			cout << "The code of" << bunch << "is " << encode(bunch) << endl;
			cout << "Please input the choice continue:" << endl;
		}
		else {
			cout << "Please input the code of some infomation consist of 0 or 1, like 1010010" << endl;
			cin >> code;
			if (decode(code) != 0) {
				int num = decode(code);
				if (code.at(code.size() - num) == '1') {
					code.at(code.size() - num) = '0';
				}
				else {
					code.at(code.size() - num) = '1';
				}
				cout << "The right code is:" << code << endl;
			}
			else {
				cout << "This bunch does't not have any wrong bit" << endl;
			}
			cout << "Please input the choice continue:" << endl;
		}

	}
	
	//test
	//printf("%#x", char(1));
	//printf("%#x", '0' + 1);
	system("pause");
	return 0;
}