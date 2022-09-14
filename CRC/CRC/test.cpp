#include <iostream>
#include <stdio.h>
using namespace std;

int main() {
	char a[3] = { 'a','b','c' };
	unsigned int result = 0;
	for (int i = 0; i < 3; i++) {
		result = result << 8;
		result = result | a[i];
	}
	printf("%#x", result);
	return 0;
}