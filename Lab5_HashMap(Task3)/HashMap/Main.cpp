#include "HashMap.h"
#include <conio.h>

using namespace std;

int main() {

	KeyHash<string> keyFunc;

	HashMap<string, int, KeyHash<string>> hmap1;
	hmap1.putNode("aaa", 100);
	hmap1.putNode("a", 101);
	hmap1.putNode("aaa", 50);
	hmap1.putNode("bbb", 200);
	hmap1.putNode("ccc", 300);

	hmap1.printHashTable();

	int data;
	if (hmap1.getData("bbb", data))
		cout << data << endl;
	hmap1.removeNode("bbb");

	if (hmap1.getData("bbb", data))
		cout << data << endl;

	if (hmap1.getData("ccc", data))
		cout << data << endl;

	hmap1.printHashTable();

	_getch();
}