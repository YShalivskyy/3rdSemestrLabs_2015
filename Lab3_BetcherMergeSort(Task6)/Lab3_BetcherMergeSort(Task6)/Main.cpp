//#include<iostream>
//#include"Parallel_sort.h"
//using namespace std;
//
//int main()
//{
//	Parallel_sort<8> p(2);
//	p.Parallel_hsort();
//	return 0;
//}
#include<iostream>
#include<vector>
#include"BetcherMergeSort.h"

using namespace std;

int main()
{
	srand(time(0));
	BMergeSort Array(100, 8);
	system("pause");
	return 0;
}