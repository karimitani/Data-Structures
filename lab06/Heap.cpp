#include <stdio.h>
#include "Heap.h"

Heap::Heap(int maxSize) {
	max = maxSize;
	heap = new int[max];
	last = 0;
}

void Heap::insert(i) {
	// make sure there is space
	if (list >= max) {
		exit(1);
	}
	heap[last] = key;
	last++;
	
	int child = last - 1;
	int parent = hparent(child);	
	while (child > 0) {
		if (heap[child] > heap[parent]) {
			break;
		}
		int tmp = heap[child];
		heap[child] = heap[parent];
		heap[parent] = tmp;
		child = parent;
		parent = hparent(child);
	}
}

int Heap:removeMin() {
	if (list <= 0) {
		exit(1);
	}
	int minKey = heap[0];
	heap[0] = heap[last - 1];
	last--;
	int parent = 0;
	int left = hleft(parent);
	int right = hright(parent);
	while (left < last) {
		int minChild = left;		
		if ((right < last) && (heap[right] <= heap[left])) {
			minChild = right;
		}
		if (heap[parent] <= heap[minChild]) {
			break;
		}
		int tmp = heap[minChild];
		heap[minChild] = heap[parent];
		heap[parent] = tmp;
		parent = minChild;
		left = hleft(parent);
		right = hright(parent);
	}	
	return minKey;
}
