// Reference to the Batcher's web: http://bekbolatov.github.io/sorting/
#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
#include<thread>

using namespace std;

class BMergeSort
{
private:
	int threadNumber;
	int size; // size of an array
public:
	// merge sort which uses Betcher's web to merge the buckets
	// all actions are made using thread so the sort is done in parallel time
	void merge_sort(vector<int> array, int left, int rigth, int numberBuckets);
	void mergeTwoBuckets(vector<int>& array, int left1, int right1, int left1, int right1);

	void heap_sort(vector<int>&, int begin, int end);
	//recovering heap
	void shiftDown(vector<int>&, int i, int j, int shift);
	void printResult(vector<int> array, int number);
	BMergeSort(int number, int threadNumber);
	~BMergeSort() {

	}
};
