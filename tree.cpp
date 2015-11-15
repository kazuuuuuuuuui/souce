#include<stdio.h>
#include<stdlib.h>

struct TreeNode{
	int m_value;
	TreeNode *m_leftNode;
	TreeNode *m_rightNode;
};

TreeNode *root;

//�������󂯎���ăm�[�h�𐶐������g�̃A�h���X��Ԃ�
TreeNode* CreateNewNode(int _num){
	TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->m_value = _num;
	newNode->m_leftNode = NULL;
	newNode->m_rightNode = NULL;

	return newNode;
}

//�؂Ƀm�[�h��ǉ�
//*_parentNode�͒ǉ�����m�[�h�̐e�������|�C���^
void InsertNode(TreeNode *_parentNode, int _num){
	//root�̐���
	if (_parentNode == NULL){
		root = CreateNewNode(_num);
		return;
	}

	//�e���q
	if (_parentNode->m_value > _num){
		//����NULL����Ȃ�������NULL�ɂȂ�܂ŉ�
		if (_parentNode->m_leftNode != NULL){
			InsertNode(_parentNode->m_leftNode, _num);
		}
		//����NULL�������炻���Ƀm�[�h�������value�ǉ�
		else{
			_parentNode->m_leftNode = CreateNewNode(_num);
		}
	}

	//�e���q
	else{
		if (_parentNode->m_rightNode != NULL){
			InsertNode(_parentNode->m_rightNode, _num);
		}
		else{
			_parentNode->m_rightNode = CreateNewNode(_num);
		}
	}
}

void main(){
	root = NULL;

	InsertNode(root, 10);
	InsertNode(root, 5);
	InsertNode(root, 2);

	printf("%d\n", root->m_value);
	printf("%d\n", root->m_leftNode->m_value);
	printf("%d\n", root->m_leftNode->m_leftNode->m_value);
	getchar();


}