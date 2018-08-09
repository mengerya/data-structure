#include<stdio.h>
#include<iostream>
#include<stack>

using namespace std;

//插入排序
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

//归并
void MergeData(int arr[], int left, int mid, int right, int* temp){
    int begin1 = left;
    int end1 = mid;
    int begin2 = mid;
    int end2 = right;
    int index = 0;
    while (begin1 < end1 && begin2 < end2){
        if (arr[begin1] <= arr[begin2])
            temp[index++] = arr[begin1++];
        else
            temp[index++] = arr[begin2++];
    }
    while (begin1<end1)
        temp[index++] = arr[begin1++];
    while (begin2<end2)
        temp[index++] = arr[begin2++];
    for (int i = 0; i < index; i++)
        arr[left + i] = temp[i];
}

int min(int left, int right){
    if (left>right)
        return right;
    else
        return left;
}

// 划分
void _MergeSort(int arr[], int left, int right, int * temp){
    int len = right - left;
    for (int step = 1; step < len; step <<= 1){
        int offset = step + step;
        for (int index = 0; index < len; index += offset){
            MergeData(arr, index, min(index + step, len - 1), min(index + offset, len - 1),temp);
        }
    }
}

void MergeSort(int arr[], int size){
    int * temp = new int[size];
    _MergeSort(arr, 0, size, temp);
    delete[] temp;
}

void Print(int arr[], int len){
    for (int i = 0; i < len; ++i){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(){
    int arr[] = { 2, 5, 9, 3, 1, 7, 0, 4, 8, 1, 9, 4, 2, 7, 9, 12, 3, 8, 2, 34, 6, 7, 95, 24, 1, 34, 58, 21, 9, 23, 75, 43, 54, 65, 23, 44, 41, 67, 34, 91, 34, 78, 90, 34, 66, 44, 22, 11, 44, 66, 23, 77, 45, 92, 12, 101 };
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << "排序前：" << endl;
    Print(arr, size);
    MergeSort(arr, size);
    cout << "归并排序：" << endl;
    Print(arr, size);

    return 0;
}
