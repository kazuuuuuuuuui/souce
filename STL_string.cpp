//-------------------------------------�@
//STL��string�ɂ���

#include<stdio.h>
#include<iostream>
#include<string>


void main() {

	std::string str1 = "abc";

	printf("size:%d\n", str1.size());//�傫��
	printf("top:%c\n", str1.front());//�擪�̗v�f
	printf("bottom:%c\n", str1.back());//����-1�̗v�f

	//������̕\��
	for (int i = 0; i < str1.size();i++) {
		printf("%c", str1[i]);
	}

	printf("\n");

	std::cout << str1 << std::endl;

	getchar();

}