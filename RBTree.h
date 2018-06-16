#pragma once
#include<stdio.h>
#include<iostream>

using namespace std;
enum Color
{
    RED,
    BLACK
};

template<class K,class V>
struct RBTreeNode{
public:
    RBTreeNode(const K& key,const V& value,Color color = RED)
        :_pLeft(NULL)
        , _pRight(NULL)
        , _pParent(NULL)
        , _value(key,value)
        , _color(color)
    {}

public:
    RBTreeNode<K,V>* _pLeft;
    RBTreeNode<K, V>* _pRight;
    RBTreeNode<K, V>* _pParent;
    Color _color;
    pair<K,V> _value;
};

template<class K,class V>
class RBTree{
    typedef RBTreeNode<K, V> Node;
    typedef Node* pNode;
public:
    RBTree()
        :_pRoot(NULL)
    {}

    //插入
    bool InsertUnique(const pair<K,V>& value){
        return _InsertUnique(_pRoot,value);
    }

    //中序遍历
    void InOder(){
        cout << "中序遍历：" << endl;
        _InOder(_pRoot);
    }

    //判断是否是RBTree
    bool IsRBTree(){
        if (NULL == _pRoot)
            return true;
        size_t blackCount = 0;
        size_t count = 0;
        pNode pCur = _pRoot;
        //统计单支路黑色节点个数
        while (pCur){
            if (BLACK == pCur->_color)
                blackCount++;
            pCur = pCur->_pLeft;
        }
        return _IsRBTree(_pRoot, count, blackCount);
    }

protected:

    //判断是否是RBTree
    bool _IsRBTree(pNode pRoot, size_t count, const size_t blackCount){
        if (NULL == pRoot)
            return true;
        if (BLACK == pRoot->_color)
            count++;

        pNode pParent = pRoot->_pParent;
        if (pParent && pParent->_color == RED && pRoot->_color == RED){
            cout << "违反了性质3：不能有两个连续的红色节点" << endl;
            return false;
        }

        if (NULL == pRoot->_pLeft && NULL == pRoot->_pRight){
            if (count != blackCount){
                cout << "违反了性质4：每条路径上黑色节点的数量相等" << endl;
                return false;
            }
        }
        return _IsRBTree(pRoot->_pLeft, count, blackCount) && _IsRBTree(pRoot->_pRight, count, blackCount);
    }

    //中序遍历
    void _InOder(pNode pRoot){
        if (NULL == pRoot){
            return;
        }
        _InOder(pRoot->_pLeft);
        cout << "<" << pRoot->_value.first << "," << pRoot->_value.second << ">" << endl;
        _InOder(pRoot->_pRight);
    }

    //插入操作
    bool _InsertUnique(pNode& pRoot, const pair<K,V>& value){
        if (NULL == pRoot){
            //为空树,情况一
            pRoot = new Node(value.first,value.second);
            pRoot->_color = BLACK;
            return true;
        }
        //查找当前节点的插入位置
        pNode pCur = pRoot;
        pNode pParent = NULL; //标记
        while (pCur){
            if (value.second < pCur->_value.second){
                pParent = pCur;
                pCur = pCur->_pLeft;
            }
            else if (value.second > pCur->_value.second){
                pParent = pCur;
                pCur = pCur->_pRight;
            }
            else{
                //该树数据是不可重复的
                return false;
            }
        }//pCur指向NULL

        //插入新节点
        pCur = new Node(value.first,value.second);
        if (pCur->_value.second > pParent->_value.second){
            pParent->_pRight = pCur;
            pCur->_pParent = pParent;
        }
        else{
            pParent->_pLeft = pCur;
            pCur->_pParent = pParent;
        }

        //更新节点颜色及调整树的结构
        //情况二
        if (BLACK == pParent->_color)
            return true;

        //注意循环条件（因为三种情况下的变色都不会改变cur的颜色，而parent永远都是cur的parent）
        //所以只要parent的颜色为黑即可结束
        while (pParent && RED == pParent->_color){

            //pParent节点的颜色为红，则pParent的父母节点一定存在
            pNode grand = pParent->_pParent;

            if (pParent == grand->_pLeft){

                pNode uncle = grand->_pRight;
                if (uncle && RED == uncle->_color){
                    //情况三
                    pParent->_color = BLACK;
                    uncle->_color = BLACK;
                    grand->_color = RED;
                    if (grand->_pParent && RED == grand->_pParent->_color){
                        //继续朝上更新
                        pCur = grand;
                        pParent = pCur->_pParent;
                    }
                    else{
                        break;
                    }
                }

                if (NULL == uncle || (uncle && BLACK == uncle->_color)){
                    //树需要旋转
                    if (pCur == pParent->_pRight){
                        //情况五
                        RotateL(pParent);
                        swap(pCur, pParent);
                        //继续进行情况四
                    }
                    //情况四
                    RotateR(grand);
                    pParent->_color = BLACK;
                    grand->_color = RED;
                    return true;
                }
            }
            else{
                //pParent为grand的右孩子
                pNode uncle = grand->_pLeft;
                if (uncle && RED == uncle->_color){
                    //情况三的镜像
                    pParent->_color = BLACK;
                    uncle->_color = BLACK;
                    grand->_color = RED;
                    if (grand->_pParent && RED == grand->_pParent->_color){
                        //继续朝上更新
                        pCur = grand;
                        pParent = pCur->_pParent;
                    }
                    else{
                        break;
                    }
                }
                if (NULL == uncle || (uncle && BLACK == uncle->_color)){
                    //需要旋转
                    if (pCur == pParent->_pLeft){
                        //情况五，镜像
                        RotateR(pParent);
                        swap(pCur, pParent);
                    }
                    //情况四
                    RotateL(grand);
                    pParent->_color = BLACK;
                    grand->_color = RED;
                }
            }
        }
        //统一更新根节点颜色
        pRoot->_color = BLACK;
    }

    //左单旋
    void RotateL(pNode pParent){
        if (NULL == pParent)
            return;

        pNode ptr = pParent;
        pNode pSubR = ptr->_pRight;
        pNode pSubRL = pSubR->_pLeft;


        //标记ptr的父母节点
        pNode pPParent = ptr->_pParent;
        //令ptr成为pSubR的左子树
        pSubR->_pLeft = ptr;
        ptr->_pParent = pSubR;

        //pSubRL的值是小于pSubR的值，大于ptr的值，所以可以令pSubRL作为ptr的右子树
        ptr->_pRight = pSubRL;
        if (pSubRL)
            pSubRL->_pParent = ptr;

        pSubR->_pParent = pPParent;

        //判断ptr上一节点的三种情况
        if (NULL == pPParent){
            //ptr为根节点
            _pRoot = pSubR;
        }
        else{
            if (ptr == pPParent->_pLeft)
                pPParent->_pLeft = pSubR;
            else
                pPParent->_pRight = pSubR;
        }

    }

    //右单旋
    void RotateR(pNode pParent){
        if (NULL == pParent)
            return;
        pNode ptr = pParent;
        pNode pSubL = ptr->_pLeft;
        pNode pSubLR = pSubL->_pRight;

        //标记ptr的父母节点
        pNode pPParent = ptr->_pParent;
        //令ptr成为pSubL的左子树
        pSubL->_pRight = ptr;
        ptr->_pParent = pSubL;

        //pSubLR的值是大于pSubL的值，小于ptr的值，所以可以令pSubLR作为ptr的左子树
        ptr->_pLeft = pSubLR;
        if (pSubLR)
            pSubLR->_pParent = ptr;
        
        pSubL->_pParent = pPParent;

        //判断ptr上一节点的三种情况
        if (NULL == pPParent){
            //ptr为根节点
            _pRoot = pSubL;
        }
        else{
            if (ptr == pPParent->_pLeft)
                pPParent->_pLeft = pSubL;
            else
                pPParent->_pRight = pSubL;
        }

    }

private:
    pNode _pRoot;
};
