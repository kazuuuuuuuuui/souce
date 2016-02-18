//-------------------------------------　
//STLのstringについて

#include<stdio.h>
#include<iostream>
#include<string>


void main() {

	std::string str1 = "abc";

	printf("size:%d\n", str1.size());//大きさ
	printf("top:%c\n", str1.front());//先頭の要素
	printf("bottom:%c\n", str1.back());//末尾-1の要素

	//文字列の表示
	for (int i = 0; i < str1.size();i++) {
		printf("%c", str1[i]);
	}

	printf("\n");

	std::cout << str1 << std::endl;

	getchar();

}