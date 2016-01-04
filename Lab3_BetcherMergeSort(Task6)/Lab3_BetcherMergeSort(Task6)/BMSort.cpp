#include "BetcherMergeSort.h"


BMergeSort::BMergeSort(int number, int threadNumber)
{
	vector<int> vectorValues;
	for (int i(0); i < number; i++)
		vectorValues.push_back(rand() % 1000);

	vector<thread> threads;
	this->threadNumber = pow(2, threadNumber);
	const int MAX_INT = 100000;
	int originalElementsNumber = vectorValues.size();
	size = originalElementsNumber + (this->threadNumber - (originalElementsNumber % this->threadNumber));

	// filling vector of values with auxiliary max values to receive an array with numberBucketse of power 2
	for (int i(0); i < size - originalElementsNumber; i++)
		vectorValues.push_back(MAX_INT);
	int bucketNumber = size / this->threadNumber;

	// dividing the input vector between buckets and sorting them with merge sort
	for (int j(0); j < this->threadNumber; j++)
	{
		threads.push_back(thread(&BMergeSort::heap_sort, this, ref(vectorValues), j*bucketNumber, (j + 1)*bucketNumber));
		if (threads[j].joinable())
			threads[j].join();
	}
	merge_sort(vectorValues, 0, this->threadNumber - 1, bucketNumber);																																			heap_sort(vectorValues, 0, size);
	printResult(vectorValues, number);
}

void BMergeSort::printResult(vector<int> array, int number) {
	for (int i(0); i < number; i++)
		cout << array[i] << " ";
}

void BMergeSort::heap_sort(vector<int> &array, int  begin, int  end)
{
	int current;
	int count = end - begin;
	for (int i (count / 2 - 1); i >= 0; i--) {
		shiftDown(array, i, count, begin);
	}
	for (int i(count - 1); i >= 1; i--) {
		current = array[begin];
		array[begin] = array[i + begin];
		array[i + begin] = current;

		shiftDown(array, 0, i, begin);
	}
}

void BMergeSort::shiftDown(vector<int> &array, int i, int j, int shift)
{
	int maxChild;
	int current;
	bool done = false;
	while ((i * 2 + 1 < j) && (!done))
	{
		if (i * 2 + 1 == j - 1)
			maxChild = i * 2 + 1;
		else if (array[i * 2 + 1 + shift] > array[i * 2 + 2 + shift])
			maxChild = i * 2 + 1;
		else
			maxChild = i * 2 + 2;

		if (array[i + shift] < array[maxChild + shift]) {
			current = array[i + shift];
			array[i + shift] = array[maxChild + shift];
			array[maxChild + shift] = current;

			i = maxChild;
		}
		else
			done = true;
	}
}

void BMergeSort::mergeTwoBuckets(vector<int> &array, int left1, int right1, int left2, int right2)
{
	vector<int> helpArray; // the result of merging
	helpArray.resize(10000);
	
	int increment = 0; // helps to make helpAraay vector
	int i = left1;
	int j = left2;

	while (i <= right1 && j <= right2) {
		if (array[i] < array[j]) {
			helpArray[increment] = array[i];
			increment++;
			i++;
		}
		else {
			helpArray[increment] = array[j];
			increment++;
			j++;
		}
	}
	while (i <= right1) {
		helpArray[increment] = array[i];
		increment++;
		i++;
		if (increment == right1)
			increment = left2;
	}
	while (j <= right2) {
		helpArray[increment] = array[j];
		increment++;
		j++;
	}
	j = left1;

	// rewriting the vector 
	for (int i(0); i < increment; i++)
	{
		array[j] = helpArray[i];
		if (j == right1) 
			j = left2;
		else 
			j++;
	}
}

// merge sort which uses Betcher's web to merge the buckets
// all actions are made using thread so the sort is done in parallel time
void BMergeSort::merge_sort(vector<int> array, int left, int right, int numberBuckets)
{
	vector<thread> threads;
	if ((right - left) == 0) 
		return;
	else
	{
		for (int i(0); i <= (right - left) / 2; i++)
			threads.push_back(thread(&BMergeSort::mergeTwoBuckets, this, ref(array), (left + i)*numberBuckets, (left + i)*numberBuckets, (right - i)*numberBuckets, (right - i)*numberBuckets));
		for (int i(0); i <= (right - left) / 2; i++)
			threads[i].join();
		threads.push_back(thread(&BMergeSort::merge_sort, this, ref(array), left, (right - left) / 2 + left, numberBuckets));
		threads.push_back(thread(&BMergeSort::merge_sort, this, ref(array), (right - left) / 2 + left + 1, right, numberBuckets));
		threads[threads.size() - 1].join();
		threads[threads.size() - 2].join();
	}
}



