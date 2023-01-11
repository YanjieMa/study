#include <iostream>

using namespace std;

enum RBTColor {RED, BLACK};

template <class T>
class RBTNode{
	public:
		RBTColor color; // 颜色
		T key;          // 键值
		RBTNode *left;  // 左孩子
		RBTNode *right; // 右孩子
		RBTNode *parent;// 父节点
		RBTNode (T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r) :
			key(value),color(c),parent(p),left(l),right(r) {}
};

template <class T>
class RBTree{
	private:
		RBTNode<T> *mRoot;		//根节点
	public:
		RBTree();
		~RBTree();
	
	//前序遍历
	void preOrder();
	//中序遍历
	void inOrder();
	//后序遍历
	void postOrder();
	

};


int main()
{

	return 0;
}
