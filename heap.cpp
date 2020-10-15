#include <iostream>

#define MAX_ELEMENT 200

struct element
{
	int key;
};

struct HeapType
{
	element heap[MAX_ELEMENT];
	int heap_size;


	//삽입 함수
	static void insert_max_heap(HeapType* h, element item)
	{
		int i;
		i = ++(h->heap_size);

		//트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
		while ((i != 1) && (item.key > h->heap[i/2].key))
		{
			h->heap[i] = h->heap[i / 2];
			i /= 2;
		}
		h->heap[i] = item;//새로운 노드를 삽입
	}

	//
	static element delete_max_heap(HeapType * h)
	{
		int parent, child;
		element item, temp;

		item = h->heap[1];
		temp = h->heap[(h->heap_size)--];
		parent = 1;
		child = 2;

		while (child <= h->heap_size)
		{
			if ((child < h->heap_size) && (h->heap[child + 1].key < h->heap[child].key))//현재의 자식 노드 중 더 큰 자식 노드를 찾는다
				child++;
			if (temp.key >= h->heap[child].key)break;

			h->heap[parent] = h->heap[child];
			parent = child;
			child *= 2;
		}

		h->heap[parent] = temp;
		return item;
	}
};



void init(HeapType* h)
{
	h->heap_size = 0;
}


void main()
{
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 };

	HeapType heap;
	init(&heap);

	HeapType::insert_max_heap(&heap, e1);
	HeapType::insert_max_heap(&heap, e2);
	HeapType::insert_max_heap(&heap, e3);

	printf("<%d> ", HeapType::delete_max_heap(&heap).key);
	printf("<%d> ", HeapType::delete_max_heap(&heap).key);
	printf("<%d> \n", HeapType::delete_max_heap(&heap).key);
}