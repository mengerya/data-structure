#pragma once
#ifndef __BSTREE_H__
#define __BSTREE_H__
#include<iostream>
#include<assert.h>

using namespace std;

template<class T>
struct BSTreeNode
{
public:
    BSTreeNode(const T& data)
        :_data(data)
        , _pLeft(NULL)
        , _pRight(NULL)
    {}

    BSTreeNode()
        :_pLeft(NULL)
        , _pRight(NULL)
    {}

public:
    BSTreeNode<T>* _pLeft;
    BSTreeNode<T>* _pRight;
    T _data;
};

template<class T>
class BSTree
{
public:
    typedef BSTreeNode<T> Node;
    typedef Node* pNode;

    BSTree()
        :_pRoot(NULL)
    {}

    BSTree(pNode node)
        :_pRoot(node)
    {}

    //查找
    bool Find(const T& data){
        if (NULL == _pRoot)
            return false;
        pNode pCur = _pRoot;
        while (pCur){
            if (data == pCur->_data)
                return true;
            else if (data > pCur->_data)
                pCur = pCur->_pRight;
            else
                pCur = pCur->_pLeft;
        }
        return false;
    }

    //插入
    bool Insert(const T& data){
        //要插入的为空树
        if (NULL == _pRoot){
            _pRoot = new Node(data);
            return true;
        }
        //查找要插入的位置
        pNode pCur = _pRoot;
        pNode pParent = NULL;
        while (pCur){
            if (data == pCur->_data)//树中已经存在该值
                return false;
            else if (data < pCur->_data){
                pParent = pCur;
                pCur = pCur->_pLeft;
            }
            else{
                pParent = pCur;
                pCur = pCur->_pRight;
            }
        }
        //进行插入操作
        if (data < pParent->_data)
            pParent->_pLeft = new Node(data);
        else
            pParent->_pRight = new Node(data);
        return true;
    }

    //删除操作
    bool Delete(const T& data){

        //判断树是否存在
        if (NULL == _pRoot)
            return false;

        //查找要删除的节点
        pNode pCur = _pRoot;
        pNode pParent = NULL;
        pNode pDel = NULL;
        while (pCur){
            if (data > pCur->_data){
                pParent = pCur;
                pCur = pCur->_pRight;
            }
            else if (data < pCur->_data){
                pParent = pCur;
                pCur = pCur->_pLeft;
            }
            else{
                //删除节点

                //待删除节点是叶子节点 & 当前节点只有右孩子
                if (NULL == pCur->_pLeft){
                    pDel = pCur;

                    if (NULL == pParent){
                        //待删除节点是根节点
                        _pRoot = pDel->_pRight;
                    }
                    else if (pDel == pParent->_pLeft){
                        //待删除节点是上一节点的左子树
                        pParent->_pLeft = pDel->_pRight;//待删除节点的左子树一定为空
                    }
                    else{
                        //待删除节点是上一节点的右子树
                        pParent->_pRight = pDel->_pRight;
                    }
                }
                else if (NULL == pCur->_pRight){
                    //待删除节点是叶子节点 & 当前节点只有左孩子
                    pDel = pCur;
                    if (NULL == pParent){
                        //待删除节点是根节点
                        _pRoot = pDel->_pLeft;
                    }
                    else if (pDel == pParent->_pLeft){
                        //待删除节点是上一节点的左子树
                        pParent->_pLeft = pDel->_pLeft;
                    }
                    else{
                        //待删除节点是上一节点的右子树
                        pParent->_pRight = pDel->_pLeft;
                    }
                }
                else{
                    //待删除节点左右子树均存在

                    pNode subRight = pCur->_pRight;
                    pParent = pCur;
                    //parent 在这里不能为空，否则在特定场景下判断subRight与上一节点的关系时会崩溃

                    //查找待删除节点的右子树的最小值（左子树）节点
                    while (subRight->_pLeft){
                        pParent = subRight;
                        subRight = subRight->_pLeft;
                    }
                    pDel = subRight;//要删除的节点

                    //交换待删除节点和它的右子树的值，再直接删除它的右子树节点
                    pCur->_data = pDel->_data;

                    //还需判断pDel是pParent的左节点还是右节点
                    //parent 在这里不能为空的原因，↓
                    if (pDel == pParent->_pLeft)
                        pParent->_pLeft = pDel->_pLeft;
                    else
                        pParent->_pRight = pDel->_pRight;
                }
                delete pDel;
                return true;
            }
        }

        return false;

    }

    //中序遍历
    void InOrder(){
        _InOrder(_pRoot);
        cout << endl;
    }

    //析构
    ~BSTree(){
        _Destory(_pRoot);
    }

protected:

    void _InOrder(pNode pRoot){
        if (NULL == pRoot)
            return;
        _InOrder(pRoot->_pLeft);
        cout << pRoot->_data << "  ";
        _InOrder(pRoot->_pRight);
    }

    void _Destory(pNode pRoot){
        if (NULL == pRoot)
            return;
        _Destory(pRoot->_pLeft);
        _Destory(pRoot->_pRight);
        delete pRoot;
    }

private:
    pNode _pRoot;
};

#endif //__BSTREE_H__
