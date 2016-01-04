#include "Simplex.h"

int main() {
	Simplex simplex("Matrix.txt");
	simplex.findOptimalPolinom();
	system("pause");
}