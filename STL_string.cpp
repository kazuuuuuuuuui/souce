//-------------------------------------�@
//STL��string�ɂ���

#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>


void main() {

	//std::string str1 = "abc";
	//std::string str2 = "def";

	//printf("size:%d\n", str1.size());//�傫��
	//printf("front:%c\n", str1.front());//�擪�̗v�f
	//printf("back:%c\n", str1.back());//����-1�̗v�f

	//������̕\��
	/*for (int i = 0; i < str1.size();i++) {
		printf("%c", str1[i]);
	}
	printf("\n");*/

	//std::cout << str1 << std::endl;
	//std::cout << str2 << std::endl;

	//������̌���
	//std::string str3 = str1 + str2;
	//std::cout << str3 << std::endl;

	//�����̒ǉ�
	//str1.push_back('A');//push_back() 1���������ǉ��o���Ȃ�
	//std::cout << str1 << std::endl;

	//str1 += 'A'; operator+=(����)
	//std::cout << str1 << std::endl;

	//str1 += "ABC";// operator+=(������) ����������ɒǉ��o����
	//std::cout << str1 << std::endl;

	//�����̍폜
	//str1.pop_back();
	//std::cout << str1 << std::endl;

	/*
	//������̃x�N�^�[
	std::vector<std::string>stringVec = 
	{
	  "acb","edf","ghi","jkl"
	};

	std::cout << stringVec.size() << std::endl;
	std::cout << stringVec.front() << std::endl;
	std::cout << stringVec.back() << std::endl;

	//�����񌟍�
	for (int i = 0; i < stringVec.size();i++) {

		if ("edf"==stringVec[i]) {
			std::cout << "edf�ƌ��������񂪂���܂���" << std::endl;
		}
		else {
			std::cout << stringVec[i] << std::endl;
		}
	}
	*/

	getchar();

}