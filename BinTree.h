
#ifndef  __BINTREE_H__

#define __BINTREE_H__
#include<iostream>
#include<stdio.h>
#include<stack>
#include<queue>

using namespace std;

//二叉树节点
template<class T>
struct BinTreeNode
{
	BinTreeNode(const T& data)
		:_data(data)
		, _pLeft(NULL)
		, _pRight(NULL)
	{}
	T _data;
	BinTreeNode<T>* _pLeft;
	BinTreeNode<T>* _pRight;
};

//二叉树
template<class T>
class BinTree
{
	typedef BinTreeNode<T> Node;
	typedef Node* pNode;
public:

	//构造函数
	//空二叉树的构造
	BinTree()
		:_pRoot(NULL)
	{}

	//带参的二叉树构造函数
	BinTree(T* arr,size_t size,T invalid){
		size_t index = 0;
		_pRoot = CreateNewTree(arr, size, index, invalid);
	}

	//拷贝构造函数
	BinTree(const BinTree<T>& bt){
		_pRoot = _CopyBinTree(bt._pRoot);
	}

	//赋值运算符重载
	BinTree<T>& operator=(const BinTree<T>& bt){
		if (this != &bt){
			this->~BinTree();
			_pRoot = _CopyBinTree(bt._pRoot);
		}
		return *this;
	}

	//前序遍历
	void PreOrder(){
		cout << "前序遍历"<<endl;
		_PreOrder(_pRoot);
		cout << endl;
	}

	//前序非递归遍历
	void PreOrderNR(){
		cout << "前序非递归遍历" << endl;
		_PreOrderNR(_pRoot);
		cout << endl;
	}

	//中序遍历
	void InOrder(){
		cout << "中序遍历" << endl;
		_InOrder(_pRoot);
		cout << endl;
	}

	//中序非递归遍历
	void InOrderNR(){
		cout << "中序非递归遍历" << endl;
		_InOrderNR(_pRoot);
		cout << endl;
	}

	//后序遍历
	void PostOrder(){
		cout << "后序遍历" << endl;
		_PostOrder(_pRoot);
		cout << endl;
	}

	//后序非递归遍历
	void PostOrderNR(){
		cout << "后序非递归遍历"<<endl;
		_PostOrderNR(_pRoot);
		cout << endl;
	}

	//层序遍历
	void LevelOrder(){
		cout << "层序遍历" << endl;
		_LevelOrder(_pRoot);
		cout << endl;
	}

	//二叉树的高度
	void Depth(){
		cout << "树的高度为：" << endl;
		cout << _Depth(_pRoot) << endl;
	}

    //二叉树中的节点个数
	void Size(){
		cout << "二叉树的节点个数：" << endl;
		cout << _Size(_pRoot) << endl;
	}

	//求叶子节点的个数
	void LeafSize(){
		cout << "二叉树的叶子节点个数：" << endl;
		cout << _LeafSize(_pRoot) << endl;
	}

	//二叉树中第k层结点的个数
	void GetKLevelSize(size_t k){
		cout << "二叉树中第k层结点的个数:" << endl;
		cout << _GetKLevelSize(_pRoot,k) << endl;
	}

	//查找值为k的节点
	void Find(const T& k){
		cout << "查找值为k的节点" << endl;
		pNode pFin = _Find(_pRoot, k);
		cout <<"找到该节点的值为："<< pFin->_data << endl;
	}

	//判断一个节点是否在二叉树中
	bool IsNodeInBinTree(pNode pNode){
		return _IsNodeInBinTree(_pRoot, pNode);
	}

	//二叉树的镜像
	void Mirror(){
		return _Mirror(_pRoot);
	}

	//二叉树的镜像，非递归
	void Mirror_Nor(){
		if (NULL == _pRoot)
			return;
		queue<T> q;
		q.push(_pRoot);
		while (!q.empty()){
			pNode pCur = q.front();
			swap(pCur->_pLeft, pCur->_pRight);
			if (pCur->_pLeft)
				q.push(pCur->_pLeft);
			if (pCur->_pRight)
				q.push(pCur->_pRight);

			q.pop();
		}
	}

	//判断一颗二叉树是否是完全二叉树
	bool IsCompleteBinTree(){
		//方法一
		//return _IsCompleteBinTree_1(_pRoot);
		//方法二
		return _IsCompleteBinTree_2(_pRoot);
	}

	//根据前序，中序遍历结果重建二叉树
	pNode Construct(T* PreOrder, T* InOrder, T len){
		if (PreOrder == NULL || InOrder == NULL || len < 0)
			return NULL;
		return _ConstructCore(PreOrder, PreOrder + len - 1, InOrder, InOrder + len - 1);
	}

	//析构函数
	~BinTree(){
		_Destroy(_pRoot);
	}
protected:

	//创建二叉树
	Node* CreateNewTree(T* arr, size_t size, size_t& index, const T& invalid){
		pNode pRoot = NULL;
		if (index < size && arr[index] != invalid){
			pRoot = new Node(arr[index]);
			pRoot->_pLeft = CreateNewTree(arr, size, ++index, invalid);
			pRoot->_pRight = CreateNewTree(arr, size, ++index, invalid);
		}
		return pRoot;
	}

	//根据前序，中序遍历结果重建二叉树
	pNode _ConstructCore(T* PreOrderStart, T* PreOrderEnd, T* InOrderStart, T* InOrderEnd){
		//先从前序遍历列表里拿到根节点，并创建根节点
		T rootValue = PreOrderStart[0];
		pNode root = new Node(rootValue);

		if (PreOrderStart == PreOrderEnd){
			if (InOrderStart == InOrderEnd && *PreOrderStart == *InOrderStart)
				return root;
			else
				throw exception("Invalid input.");
		}

		//在中序遍历中找到根节点的值
		int* rootInOrder = InOrderStart;
		while (rootInOrder <= InOrderEnd && *rootInOrder != rootValue)
			++rootInOrder;
		//在整个中序遍历列表里都没有找到前序遍历的根
		if (rootInOrder == InOrderEnd && *rootInOrder != rootValue)
			throw exception("invalid input.");

		int leftlen = rootInOrder - InOrderStart;
		int* leftPreorderEnd = PreOrderStart + leftlen;

		if(leftlen > 0){
			//构建左子树
			root->_pLeft = _ConstructCore(PreOrderStart + 1, leftPreorderEnd, InOrderStart, rootInOrder - 1);
		}
		if (leftlen < PreOrderEnd - PreOrderStart){
			//构建右子树
			root->_pRight = _ConstructCore(leftPreorderEnd + 1, PreOrderEnd, rootInOrder + 1, InOrderEnd);
		}
		return root;
	}


	//销毁二叉树
	void _Destroy(pNode pRoot){
		if(pRoot)
		{
			_Destroy(pRoot->_pLeft);
			_Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = NULL;
		}
	}

	//拷贝二叉树
	pNode _CopyBinTree(pNode pRoot){
		if (NULL == pRoot)
			return NULL;
		pNode newRoot = new Node(pRoot->_data);
		newRoot->_pLeft = _CopyBinTree(pRoot->_pLeft);
		newRoot->_pRight = _CopyBinTree(pRoot->_pRight);
		return newRoot;
	}

	//前序
	void _PreOrder(pNode pRoot){
		if (pRoot){
			cout << pRoot->_data << " ";
			_PreOrder(pRoot->_pLeft);
			_PreOrder(pRoot->_pRight);
		}
	}

	//前序非递归
	void _PreOrderNR(pNode _pRoot){
		pNode pCur = _pRoot;
		stack<pNode> s;
		while (pCur || !s.empty()){
			//将左侧节点依次压栈
			while (pCur){
				cout << pCur->_data << "  ";
				s.push(pCur);
				pCur = pCur->_pLeft;
			}
			//开始依次访问栈顶节点的右子树，通过循环将该右子树的左侧节点依次压栈
			pNode pTop = s.top();
			s.pop();
			pCur = pTop->_pRight;//循环的子问题
		}
	}

	//中序
	void _InOrder(pNode pRoot){
		if (pRoot){
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}

	//中序非递归
	void _InOrderNR(pNode _pRoot){
		pNode pCur = _pRoot;
		stack<pNode> s;
		while (pCur || !s.empty()){
			//将左侧节点依次压栈
			while (pCur){
				s.push(pCur);
				pCur = pCur->_pLeft;
			}
			//栈中节点的左子树已经遍历完
			//栈中节点自身和右子树还没有遍历
			//开始依次访问栈顶节点的右子树，通过循环将该右子树的左侧节点依次压栈
			pNode pTop = s.top();
			cout << pTop->_data << "  ";
			s.pop();
			pCur = pTop->_pRight;//循环的子问题
		}
	}

	//后序
	void _PostOrder(pNode pRoot){
		if (pRoot){
			_PostOrder(pRoot->_pLeft);
			_PostOrder(pRoot->_pRight);
			cout << pRoot->_data << " ";
		}
	}

	//后序非递归
	void _PostOrderNR(pNode _pRoot){
		pNode pCur = _pRoot;
		stack<pNode> s;
		while (pCur || !s.empty()){
			//将左侧节点依次压栈
			while (pCur){
				s.push(pCur);
				pCur = pCur->_pLeft;
			}
			pNode prev = NULL;
			pNode pTop = s.top();
			if (NULL == pTop->_pRight || prev == pTop->_pRight){
				cout << pTop->_data << "  ";
				s.pop();
				prev = pTop;
			}
			else{
				//进入下一层子循环
				pCur = pTop->_pRight;
			}
		}
	}

	//层序
	void _LevelOrder(pNode pRoot){
		queue<pNode> q;
		if (pRoot){
			q.push(pRoot);
		}
		while (!q.empty()){
			pNode front = q.front();
			cout << front->_data << "  ";
			if (front->_pLeft)
				q.push(front->_pLeft);
			if (front->_pRight)
				q.push(front->_pRight);
			q.pop();
		}
	}

	//二叉树的高度
	size_t _Depth(pNode pRoot){
		if (NULL == pRoot)
			return 0;
		if (NULL == pRoot->_pLeft && NULL == pRoot->_pRight)
			return 1;
		size_t LeftDepth = _Depth(pRoot->_pLeft);
		size_t RightDepth = _Depth(pRoot->_pRight);
		return LeftDepth > RightDepth ? LeftDepth + 1 : RightDepth + 1;
	}

	//二叉树的节点个数
	size_t _Size(pNode pRoot){
		if (NULL == pRoot)
			return 0;
		//返回当前节点的左子树和右子树以及当前节点个数
		return _Size(pRoot->_pLeft) + _Size(pRoot->_pRight) + 1;
	}

	//二叉树中叶子节点的个数
	size_t _LeafSize(pNode pRoot){
		if (NULL == pRoot)
			return 0;
		if (NULL == pRoot->_pLeft && NULL == pRoot->_pRight)
			return 1;
		return _LeafSize(pRoot->_pLeft) + _LeafSize(pRoot->_pRight);
	}

	//二叉树中第k层结点的个数
	size_t _GetKLevelSize(pNode pRoot,size_t k){
		if (NULL == pRoot || 0 == k)
			return 0;
		if (1 == k)
			return 1;
		return _GetKLevelSize(pRoot->_pLeft, k - 1) + _GetKLevelSize(pRoot->_pRight, k - 1);
	}
	
	//查找值为k的节点
	pNode _Find(pNode pRoot,const T& k){
		if (NULL == pRoot)
			return NULL;
		if (k == pRoot->_data)
			return pRoot;
		pNode pFin = _Find(pRoot->_pLeft, k);
		if (pFin)
			return pFin;
		return _Find(pRoot->_pRight, k);
	}

	//判断节点是否在二叉树中
	bool _IsNodeInBinTree(pNode pRoot, pNode pNode){
		if (NULL == pRoot || NULL == pNode)
			return false;
		if (pRoot == pNode)
			return true;
		bool IsIn = false;
		if (IsIn = _IsNodeInBinTree(pRoot->_pLeft, pNode))
			return true;
		return _IsNodeInBinTree(_pRoot->_pRight, pNode);
	}

	//二叉树的镜像,递归
	void _Mirror(pNode pRoot){
		if (pRoot){
			swap(pRoot->_pLeft, pRoot->_pRight);
			_Mirror(pRoot->_pLeft);
			_Mirror(pRoot->_pRight);
		}
	}

	//判断一颗二叉树是否是完全二叉树
	//方法一
	bool _IsCompleteBinTree_1(pNode pRoot){
		cout << "_IsCompleteBinTree_1" << endl;
		if (NULL == pRoot)
			return false;
		queue<pNode> q;
		q.push(pRoot);
		pNode pCur = q.front();
		//将所有的结点全部押入队列中，空也压入。每次判断队列的头，如果队列头为空了则跳出循环，如果此后队列中还有元素则不是完全二叉树
		while (pCur){
			q.pop();
			q.push(pCur->_pLeft);
			q.push(pCur->_pRight);
			pCur = q.front();
		}
		while (!q.empty()){
			if (NULL != q.front())
				return false;
			q.pop();
		}
		return true;
	}

	bool _IsCompleteBinTree_2(pNode pRoot){
		cout << "_IsCompleteBinTree_2" << endl;
		if (NULL == pRoot)
			return false;
		queue<pNode> q;
		q.push(pRoot);
		bool flag = false;
		while (!q.empty()){
			pNode pCur = q.front();
			q.pop();
			if (flag){
				//再已经存在非满节点的情况下，还存在非满节点，则一定不是满二叉树
				if (NULL != pCur->_pLeft || NULL != pCur->_pRight)
					return false;
			}
			else{
				//之前不存在非满节点的情况
				if (NULL == pCur->_pLeft && NULL != pCur->_pRight)//一个节点左子树为空，右子树不为空，则一定不是满二叉树
					return false;
				else if (NULL != pCur->_pLeft && NULL != pCur->_pRight)//两个节点都不为空
				{
					q.push(pCur->_pLeft);
					q.push(pCur->_pRight);
				}
				else if (NULL != pCur->_pLeft && NULL == pCur->_pRight){
					//左子树不为空，右子树为空，出现非满节点，改变标记
					q.push(pCur->_pLeft);
					flag = true;
				}
				else{
					//两个节点都为空
					flag = true;
				}
			}
		}
	}

private:
	pNode _pRoot;
};

#endif   //__BINTREE_H__
