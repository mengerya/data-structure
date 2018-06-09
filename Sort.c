#include<stdio.h>
#include<Windows.h>
#include<iostream>

using namespace std;

void InsertSort(int array[], size_t size){
	for (size_t i = 1; i < size; ++i){
		int key = array[i];
		int cur = i - 1;
		while (cur >= 0 && key < array[cur]){
			array[cur + 1] = array[cur];
			cur--;
		}
		array[cur + 1] = key;
	}
}

int BinSearch(int array[],int key, int start, int last){
	int begin = start;
	int end = last;
	int mid;
	while (begin <= end){
		mid = (begin + end) / 2;
		if (key < array[mid]){
			end = mid-1;
		}
		else{
			begin = mid+1;
		}
	}
	return begin;
}


void InsertSort_op (int array[], size_t size){
	for (size_t i = 1; i < size; ++i){
		int key = array[i];
		int cur = i - 1;
		//折半查找法查找位置
		int find = BinSearch(array, key, 0, cur);

		//搬移元素
		for (size_t j = i; j > find; --j) {
			array[j] = array[j - 1];
		}
		//插入元素
		array[find] = key;
	}
}

void Shellsort(int array[], int size){
	int gap = size;
	while (gap > 1){
		gap = gap >> 1;
		for (size_t i = gap; i < size; ++i){
			int key = array[i];
			int cur = i - gap;
			while (cur >= 0 && key < array[cur]){
				array[cur + gap] = array[cur];
				cur-=gap;
			}
			array[cur+gap] = key;
		}
	}

}

//void selectsort(int array[], int size){
//	for (size_t i = 0; i < size; ++i){
//		int max = 0;
//		int max_dex = 0;
//		for (size_t j = 0; j < size - i; ++j){
//			if (array[j]>max){
//				max = array[j];
//				max_dex = j;
//			}
//
//		}
//		array[max_dex] = array[size - 1 - i];
//		array[size - 1 - i] = max;
//	}
//}

void selectsort(int array[], int size){
	int start = 0;
	int end = size-1;
	while (start < end){
		int max = 0;
		int max_dex = 0;
		int min=array[start];
		int min_dex = start;
		for (size_t j = start; j <= end; ++j){
			if (array[j]>max){
				max = array[j];
				max_dex = j;
			}
			if (array[j] < min){
				min = array[j];
				min_dex = j;
			}

		}
		array[max_dex] = array[end];
		array[end] = max;
		if (min_dex == end)
			min_dex = max_dex;
		array[min_dex] = array[start];
		array[start] = min;
		start++;
		end--;
	}
}

void Print(int array[], size_t size){
	for (size_t i = 0; i < size; ++i){
		cout << array[i] << "  ";
	}
	cout << endl;
}

void test_InsertSort(){
	int array[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	Print(array, sizeof(array) / sizeof(array[0]));
	selectsort(array, sizeof(array) / sizeof(array[0]));
	Print(array, sizeof(array) / sizeof(array[0]));
}

int main(){

	test_InsertSort();
	system("pause");
	return 0;
}
