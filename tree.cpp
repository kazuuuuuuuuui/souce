#include<stdio.h>

class TreeNode{
public:
	int m_value;
	TreeNode *m_leftNode;
	TreeNode *m_rightNode;

	//�������󂯎���ăm�[�h�𐶐������g�̃A�h���X��Ԃ�
	TreeNode CreateNewNode(int _num);
};

TreeNode TreeNode::CreateNewNode(int _num){
	TreeNode *node = new TreeNode();
	node->m_value = _num;
	node->m_leftNode = NULL;
	node->m_rightNode = NULL;

	return /*node��Ԃ�*/;
}

void main(){
	TreeNode *root = NULL;

}