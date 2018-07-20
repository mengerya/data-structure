#pragma once
#include<iostream>
#include<vector>
#include"Heap.h"
using namespace std;

//存放HuffTree节点信息
template<class T>
struct HuffNode{
public:
	HuffNode(const T& t = T())//????
		:_weight(weight)
		, _pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
	{}

	//当_pParent=NULL --> 该树还是森林中的一颗子树，还没有归并到别的树里面去
	//否则_pParent!=NULL -->该树已经是某棵树的子树了
	T _weight;//权值
	HuffNode<T>* _pLeft;
	HuffNode<T>* _pRight;
	HuffNode<T>* _pParent;
};

template<class T>
class HuffTree{
	typedef HuffNode<T> Node;
	typedef Node* pNode;

public:
	HuffTree()
		:_root(NULL)
	{}

	HuffTree(const T arr[], size_t size, const T& invalid){

		_CreateHuffManTree(arr, size, invalid);

	}

	~HuffTree(){
		_DestroyTree(_root);
	}


private:
	void _CreateHuffManTree(T* arr, size_t size, const T& invalid){
		//invalid ->  无效值
		struct Compare{
			bool operator()(pNode pLeft, pNode pRight){
				if (pLeft->_weight < pRight->_weight)
					return true;
				return false;
			}
		};
		Heap<pNode, Compare> hp;
		//1.创建二叉树森林

		for (size_t i = 0; i < size; i++){
			if (arr[i] != invalid)
				hp.Push(new Node(arr[i]));
		}

		if (hp.Empty()){
			_root = NULL:
			return;
		}

		//2.
		while (hp.Size() > 1){
			pNode pLeft = hp.Top();
			hp.Pop();

			pNode pRight = hp.Top();
			hp.Pop;

			pNode parent = new Node(pLeft->_weight + pRight->_weight);
			parent->_pLeft = pLeft;
			pLeft->_pParent = parent;
			parent->_pRight = pRight;
			pRight->_pParent = parent;

			hp.Push(parent);
		}
		_root = hp.Top();
	}

	void _DestoryTree(pNode& pRoot){
		if (pRoot){
			_DestoryTree(pRoot->_pLeft);
			_DestoryTree(pRoot->_pRight);
			delete pRoot;
			pRoot = NULL;
		}
	}

private:
	pNode _root;
};
