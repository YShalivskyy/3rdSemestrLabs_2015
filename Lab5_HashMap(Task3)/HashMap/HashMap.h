#pragma once
#include <functional>
#include "HashNode.h"
#include <iostream>
#include <string>

#define _TSIZE 100

template <typename KEY>
class KeyHash {
public:
	unsigned long operator()(const KEY& key) const
	{
		return std::hash<KEY>()(key) % _TSIZE;
	}
};

template <typename KEY, typename VALUE, typename FUNC = KeyHash<KEY>>
class HashMap {
private:
	HashNode<KEY, VALUE> **hashTable;
	FUNC hashFunc;
public:
	HashMap() {
		hashTable = new HashNode<KEY, VALUE> *[_TSIZE]();
	}
	~HashMap() {
		for (int i(0); i < _TSIZE; i++) {
			HashNode<KEY, VALUE>* help = hashTable[i];
			while (help) {
				HashNode<KEY, VALUE>* tmp = help;
				help = help->getNext();
				delete tmp;
			}
		}

		delete[] hashTable;
	}
	bool getData(const KEY &key, VALUE &value) {
		unsigned long hashValue = hashFunc(key);
		HashNode<KEY, VALUE> *help = hashTable[hashValue];

		while (help) {
			if (help->getKey() == key) {
				value = help->getValue();
				return true;
			}
			help = help->getNext();
		}
		cout << "The element with such a key doesn't exist" << endl;
		return false;
	}
	void putNode(const KEY &key, const VALUE &value) {
		unsigned long hashValue = hashFunc(key);
		HashNode<KEY, VALUE> *prev = nullptr;
		HashNode<KEY, VALUE> *help = hashTable[hashValue];

		while (help && help->getKey() != key) {
			prev = help;
			help = help->getNext();
		}

		if (!help) {
			help = new HashNode<KEY, VALUE>(key, value);
			if (!prev) {
				// insert as first bucket
				hashTable[hashValue] = help;
			}
			else {
				prev->setNext(help);
			}
		}
		else {
			// just update the value
			help->setValue(value);
		}
	}
	void removeNode(const KEY &key) {
		bool alone = true;
		unsigned long hashValue = hashFunc(key);
		HashNode<KEY, VALUE>* prev = nullptr;
		HashNode<KEY, VALUE>* help = hashTable[hashValue];
		while (help && help->getKey() != key) {
			prev = help;
			help = help->getNext();
			alone = false;
		}

		if (help) {
			if (!prev && help->getNext()) {
				hashTable[hashValue] = help->getNext();
			}
			else {
				if (!help->getNext() && prev)
					prev->setNext(help->getNext());
			}
			delete help;
			help = nullptr;
			prev = nullptr;
			if (alone)
				hashTable[hashValue] = nullptr;
		}
		else {
			cout << "Value with such key have not been found" << endl;
			return;
		}
	}

	void printHashTable() {
		HashNode<KEY,VALUE>* current;
		for (int i(0); i < _TSIZE; i++) {
			current = hashTable[i];
			if (current) {
				cout << "Hash: " << i << endl;
				while (current) {
					cout << "   Key: '" << current->getKey() << "' Value: " << current->getValue() << " ";
					current = current->getNext();
				}
				cout << endl;
			}
		}
	}
};

