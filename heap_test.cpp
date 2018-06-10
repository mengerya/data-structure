#include"Heap.h"
#include"PriorityQueue.h"
#include<iostream>
#include<stdio.h>
#include<Windows.h>
#define N 10
#define K 4
using namespace std;

//优先级队列
void test2(){
    int arr[] = { 53, 17, 78, 9, 45, 65, 87, 23 };
    PriorityQueue<int> prq;
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i){
        prq.Push(arr[i]);
    }
    cout << prq.Top() << endl;
    cout << prq.Size() << endl;
    prq.Pop();
    cout << prq.Top() << endl;
    cout << prq.Size() << endl;
}

//TopK(海量数据处理问题)
void TopK(){
    int arr[N];
    int max[K];
    for (size_t i = 0; i < N; ++i){
        arr[i] = rand() % N;
    }
    for (size_t j = 0; j < K; ++j){
        max[j] = arr[j];
    }
    //前K个元素建一个小堆
    Heap<int, Less<int>> hp(max, sizeof(max) / sizeof(max[0]));
    //依次读取arr[]之后的数据，与小堆堆头元素比较，若该数据大于堆头元素，则删除堆头元素，将该数据放到堆里，堆会自己排好序
    for (size_t k = K; k < N; ++k){
        if (arr[k] > hp.Top()){
            hp.Pop();
            hp.Push(arr[k]);
        }
    }
    //依次输出最大的K个数据
    hp.Print();
}

int main(){
    //test2();
    TopK();
    system("pause");
    return 0;
}
