#include <stdio.h>
#include <string.h>
#include "BinarySearchD.h"

BinarySearchD::BinarySearchD(int maxSize) {
	size = maxSize;
	currSize = 0;
	table = new BinarySearchDE[size];
	sorted = true;
}

void BinarySearchD::find(char *key) {
	if (sorted == false) {
		sorted = true;
	}
	int min = 0;
	int max = currSize - 1;
	while (min < max) {
		int mid = (min + max) / 2;
		int result = strcmp(key, table[mid].key);
		if (result == 0) {
			return table[mid].item;
		}
		else if (result < 0) { 
			max = mid - 1;
		}
		else if (result > 0) { 
			low = mid + 1;
		}
	}
	return NULL;
}