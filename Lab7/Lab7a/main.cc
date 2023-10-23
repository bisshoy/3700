#include <iostream>
#include "sampler.h"

using namespace std;

int main() {
	int num = 20;

	Sampler test1(num);

	for (int i = 0; i < num; i++) {
		int s = test1.getSample();
		cout << s << endl;
	}

	return 0;

}

