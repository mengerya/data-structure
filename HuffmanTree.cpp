#pragma once
#include<iostream>
#include<vector>
using namespace std;

//存放HuffTree节点信息
template<class T>
struct HuffNode{
public:
	HuffNode(const T weight)
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

	HuffTree(const T arr[],size_t size){
		//创建一个叶子节点的森林，一个节点就是一个树，存放在数组里
		vector<pNode> forest;
		for (size_t i = 0; i < size; i++){
			forest.push_back(new Node(arr[i]));
		}
		while (forest.size()>1){
			//在森林中查找权值最小的两个树
			pNode min_1 = SelectHTWeight(forest);
			pNode min_2 = SelectHTWeight(forest);
			CreateHuffTree()
		}
		
	}



	pNode SelectHTWeight(vector<pNode>& forest){
		pNode min = forest[0]; 
		for (size_t i = 0; i < forest.size(); i++){
			if (min->_weight < forest[i])
				min = i;
		}
		forest.erase(forest.begin() + min);
		return min;
	}

private:
	pNode _root;
};
