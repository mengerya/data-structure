#pragma once
#ifndef __HEAP_H__
#define __HEAP_H__
#include<iostream>
#include<vector>


using namespace std;

template<class T>
class Less
{
public:
    bool operator()(T& left, T& right){
        return left < right;
    }
};

template<class T>
class Greater
{
public:
    bool operator()(T& left, T& right){
        return left>right;
    }
};

template<class T,class Compare = Greater<T>>
class Heap
{
public:
    //无参构造
    Heap()
    {}
    //带参构造
    Heap(T* arr, const T size){
        _v.reserve(size);
        for (int i = 0; i < size; ++i){
            _v.push_back(arr[i]);
        }
        //建堆
        for (int j = (_v.size() - 2) >> 1; j >= 0; --j){
            //向下调整
            _AdjustDown(j);
        }
    }

    void Push(const T& data){
        _v.push_back(data);
        _AdjustUp(_v.size() - 1);
    }

    void Pop(){
        //交换堆顶元素与堆底元素
        size_t size = _v.size();
        swap(_v[0], _v[size - 1]);
        //删除堆底元素
        _v.pop_back();
        //向下调整
        _AdjustDown(0);
    }

    size_t Size(){
        return _v.size();
    }

    bool Empty(){
        return _v.empty();
    }

    //打印堆
    void Print(){
        for (size_t i = 0; i < _v.size(); ++i){
            cout << _v[i] << "  ";
        }
        cout << endl;
    }

    T Top()const
    {
        return _v.front();
    }

    T Back()const
    {
        return _v.back();
    }

    //析构
    ~Heap(){
        _v.~vector();
    }

protected:
    //向下调整
    void _AdjustDown(size_t root){
        size_t parent = root;
        size_t min_child = parent * 2 + 1;
        while (min_child < _v.size()){
            if ((min_child + 1 < _v.size()) && (Compare()(_v[min_child + 1],_v[min_child])))
                min_child += 1;
            if (Compare()(_v[min_child],_v[parent])){
                swap(_v[parent], _v[min_child]);
                parent = min_child;
                min_child = parent * 2 + 1;
            }
            else{
                break;
            }
        }
    }

    //向上调整
    void _AdjustUp(size_t index){
        size_t child = index;
        size_t parent = (child - 1) >> 1;
        while (child){
            if (Compare()(_v[parent],_v[child])){
                break;
            }
            else{
                swap(_v[parent], _v[child]);
                child = parent;
                parent = (child - 1) >> 1;
            }
        }
    }

private:
    vector<T> _v;
};


#endif //__HEAP_H__
