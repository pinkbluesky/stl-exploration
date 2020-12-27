#include <iostream>

#include <vector>


// implementation of a heap data structure
// heap property: parent node greater than child nodes

class Heap
{

	// node = i
	// parent node = floor(i/2)
	// left child node = i * 2
	// right child node = i * 2 + 1
private:
	std::vector<int> heap;

public:
	Heap();
	void insert(int x);
	int peek();
	void pop();
	int sift_up(int i);
	int sift_down(int i);
};

Heap::Heap(void)
{
	heap.push_back(0);
}
// insert value into heap
void Heap::insert(int x)
{
	// add to end of heap
	heap.push_back(x);
	sift_up(heap.size() - 1);
}

int Heap::peek()
{
	return heap[1];
}

// pop the root of heap off
void Heap::pop()
{
	// swap root w/ last leaf to maintain structure
	std::swap(heap[1], heap[heap.size() - 1]);
	// pop off the last leaf (formerly the root)
	heap.pop_back();

	// sift
	sift_down(1);
}


// resets heap by traversing down through heap	
int Heap::sift_down(int index)
{
	int key = heap[index];

	// swap if less than child nodes
	while (index * 2 < (int)heap.size())
	{
		// figure out which one is the greater child
		int greater_child = index * 2;
		if (greater_child + 1 < (int)heap.size() && heap[greater_child + 1] > heap[greater_child])
		{
			greater_child += 1;
		}

		// if need to swap
		if (heap[index] < heap[greater_child])
		{
			std::swap(heap[greater_child], heap[index]);
			index = greater_child;
		}
		else
		{
			break;
		}
	}

	return index;
}

// to move newly inserted key up if needed
// returns new index of key
int Heap::sift_up(int index)
{
	int key = heap[index];

	// find appropriate swap
	while (index > 1 && heap[index] > heap[index / 2])
	{
		// swap
		std::swap(heap[index / 2], heap[index]);

		// next parent node
		index /= 2;
	}

	return index;
}

int main()
{
	Heap h;

	h.insert(1);
	h.insert(2);
	h.insert(3);
	h.insert(4);
	h.insert(5);
	h.insert(6);
	h.insert(7);
	h.insert(8);
	h.insert(9);

	std::cout << h.peek();
	h.pop();
	std::cout << h.peek();
	h.pop();
	std::cout << h.peek();
	h.pop();
	std::cout << h.peek();
	h.pop();
	std::cout << h.peek();
	h.insert(0);

	std::cout << h.peek();
}