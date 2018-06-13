#pragma once
#include<iostream>

using namespace std;

template<class K,class V>
struct AVLTreeNode{
public:
    AVLTreeNode()
    {}

    AVLTreeNode(const K& key,const V& value)
        :_key(key)
        , _value(value)
        , _bf(0)
        , _pLeft(NULL)
        , _pRight(NULL)
        , _pParent(NULL)
    {}

public:
    AVLTreeNode<K,V>* _pLeft;
    AVLTreeNode<K,V>* _pRight;
    AVLTreeNode<K,V>* _pParent;
    int _bf;
    K _key;
    V _value;
};

template<class K,class V>
class AVLTree{
    typedef AVLTreeNode<K,V> Node;
    typedef Node* pNode;
public:
    AVLTree()
        :_pRoot(NULL)
    {}

    //插入元素
    bool Insert(const K& key, const V& value){
        //如果是空树，插入后即为根节点，插入后直接返回true
        if (NULL == _pRoot){
            _pRoot = new Node(key, value);
            return true;
        }

        //寻找插入位置，若在寻找的过程中找到key，则插入失败直接返回false
        pNode pCur = _pRoot;
        pNode pParent = NULL;
        while (pCur){
            if (key > pCur->_key){
                pParent = pCur;
                pCur = pCur->_pRight;
            }
            else if (key < pCur->_key){
                pParent = pCur;
                pCur = pCur->_pLeft;
            }
            else
                return false;//在寻找的过程中找到key
        }//pCur == NULL

        //插入节点
        pCur = new Node(key, value);
        if (pParent->_key < pCur->_key)
        {
            pParent->_pRight = pCur;
        }
        else
        {
            pParent->_pLeft = pCur;
        }
        pCur->_pParent = pParent;

        //更新平衡因子,调整树

        while (pParent){//最多更新至根节点

            //更新平衡因子,调整树
            if (pCur == pParent->_pLeft){
                pParent->_bf++;
            }
            if (pCur == pParent->_pRight){
                pParent->_bf--;
            }

            //调整树
            if (0 == pParent->_bf){
                //各结点的平衡因子不变，结束平衡化处理
                break;
            }
            else if (1 == pParent->_bf || -1 == pParent->_bf){
                //以parent为根的子树没有失去平衡，但该子树的高度增加，需从parent向根节点方向回溯，继续查看parent的双亲的平衡性
                pCur = pParent;
                pParent = pParent->_pParent;
            }
            else{
                //如果parent平衡因子的绝对值为2,新节点在较高的子树插入，需要做平衡化处理
                if (-2 == pParent->_bf){
                    if (-1 == pCur->_bf){
                        //pParent->-2   pCur->-1   左单旋
                        RotateL(pParent);
                    }
                    if (1 == pCur->_bf){
                        //pParent->-2   pCur->1    先右后左双旋
                        RotateRL(pParent);
                    }
                }
                if (2 == pParent->_bf){
                    if (1 == pCur->_bf){
                        //pParent->2   pCur->1     右单旋
                        RotateR(pParent);
                    }
                    if (-1 == pCur->_bf){
                        //pParent->2   pCur->-1    先左后右双旋
                        RotateLR(pParent);
                    }
                }
                break;
            }
        }
        return true;
    }

    //中序遍历
    void InOder(){
        cout << "中序遍历："<< endl;
        _InOder(_pRoot);
        cout << endl;
    }

    //判断AVL树是否平衡
    bool IsBalance(){
        int depth;
        return _IsBalance(_pRoot, depth);
    }

    //求取树的深度
    int Depth(){
        return _Depth(_pRoot);
    }

protected:

    //中序遍历
    void _InOder(pNode pRoot){
        if (NULL == pRoot)
            return;
        _InOder(pRoot->_pLeft);
        cout << "<" << pRoot->_key << "," << pRoot->_value << ">" << endl;
        _InOder(pRoot->_pRight);
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

        //更新平衡因子
        ptr->_bf = pSubR->_bf = 0;

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

        //更新平衡因子
        ptr->_bf = pSubL->_bf = 0;
    }

    //先左后右双旋（LR）
    void RotateLR(pNode pParent){
        if (NULL == pParent)
            return;
        pNode ptr = pParent;
        pNode pSubL = ptr->_pLeft;
        pNode pSubLR = pSubL->_pRight;
        int bf = pSubLR->_bf;

        //插入节点后，对不平衡节点（ptr）的左子树进行左单旋
        RotateL(ptr->_pLeft);
        //对根为ptr的树进行右单旋
        RotateR(ptr);

        //更新平衡因子
        if (-1 == bf){
            pSubL->_bf = 1;
        }
        else if (1 == bf){
            ptr->_bf = -1;
        }
        else
        {
            ;
        }
    }

    //先右后左双旋（RL）
    void RotateRL(pNode pParent){
        if (NULL == pParent)
            return;
        pNode ptr = pParent;
        pNode pSubR = ptr->_pRight;
        pNode pSubRL = pSubR->_pLeft;
        int bf = pSubRL->_bf;

        //插入节点后，对不平衡节点（ptr）的右子树进行右单旋
        RotateR(ptr->_pRight);
        //对根为ptr的树进行左单旋
        RotateL(ptr);

        //更新平衡因子
        if (-1 == bf){
            ptr->_bf = 1;
        }
        else if (1 == bf){
            pSubR->_bf = -1;
        }
        else
        {
            ;
        }
    }

    //判断AVL树是否平衡
    bool _IsBalance(pNode pRoot, int& depth){
        if (NULL == pRoot){
            depth = 0;
            return true;
        }
        int LeftDepth = 0;
        int RightDepth = 0;

        if (false == _IsBalance(pRoot->_pLeft, LeftDepth))
            return false;
        if (false == _IsBalance(pRoot->_pRight, RightDepth))
            return false;
        if (LeftDepth - RightDepth != pRoot->_bf){
            cout << "<" << pRoot->_key << "," << pRoot->_value << ">   " << "bf异常：" << pRoot->_bf << endl;
            return false;
        }
        depth = LeftDepth > RightDepth ? (LeftDepth + 1) : (RightDepth + 1);
        return true;
    }

    //求取树的深度
    int _Depth(pNode pRoot){
        if (NULL == pRoot)
            return 0;
        int LeftDepth = 0;
        int RightDepth = 0;
        LeftDepth = _Depth(pRoot->_pLeft);
        RightDepth = _Depth(pRoot->_pRight);
        return LeftDepth > RightDepth ? (LeftDepth + 1) : (RightDepth + 1);

    }

private:
    pNode _pRoot;
};
