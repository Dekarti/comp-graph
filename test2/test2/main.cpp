#include <iostream>

#define ARGS int a, int b

using namespace std;

int plus(ARGS) {
	return a + b;
}

int main() {
	float a = 0x2;
	float b = 0x7;
	//cout << plus(a, b);
	cout << a + b;
	return 0;
}