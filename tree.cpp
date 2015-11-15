#include<stdio.h>
#include<stdlib.h>

struct TreeNode{
	int m_value;
	TreeNode *m_leftNode;
	TreeNode *m_rightNode;
};

TreeNode *root;

//数字を受け取ってノードを生成し自身のアドレスを返す
TreeNode* CreateNewNode(int _num){
	TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
	newNode->m_value = _num;
	newNode->m_leftNode = NULL;
	newNode->m_rightNode = NULL;

	return newNode;
}

//木にノードを追加
//*_parentNodeは追加するノードの親を示すポインタ
void InsertNode(TreeNode *_parentNode, int _num){
	//rootの生成
	if (_parentNode == NULL){
		root = CreateNewNode(_num);
		return;
	}

	//親＞子
	if (_parentNode->m_value > _num){
		//左がNULLじゃなかったらNULLになるまで回す
		if (_parentNode->m_leftNode != NULL){
			InsertNode(_parentNode->m_leftNode, _num);
		}
		//左がNULLだったらそこにノードを作ってvalue追加
		else{
			_parentNode->m_leftNode = CreateNewNode(_num);
		}
	}

	//親＜子
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