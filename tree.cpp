#include<stdio.h>

class TreeNode{
public:
	int m_value;
	TreeNode *m_leftNode;
	TreeNode *m_rightNode;

	//数字を受け取ってノードを生成し自身のアドレスを返す
	TreeNode CreateNewNode(int _num);
};

TreeNode TreeNode::CreateNewNode(int _num){
	TreeNode *node = new TreeNode();
	node->m_value = _num;
	node->m_leftNode = NULL;
	node->m_rightNode = NULL;

	return /*nodeを返す*/;
}

void main(){
	TreeNode *root = NULL;

}