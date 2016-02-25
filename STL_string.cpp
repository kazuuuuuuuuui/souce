//-------------------------------------　
//STLのstringについて

#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>


void main() {

	//std::string str1 = "abc";
	//std::string str2 = "def";

	//printf("size:%d\n", str1.size());//大きさ
	//printf("front:%c\n", str1.front());//先頭の要素
	//printf("back:%c\n", str1.back());//末尾-1の要素

	//文字列の表示
	/*for (int i = 0; i < str1.size();i++) {
		printf("%c", str1[i]);
	}
	printf("\n");*/

	//std::cout << str1 << std::endl;
	//std::cout << str2 << std::endl;

	//文字列の結合
	//std::string str3 = str1 + str2;
	//std::cout << str3 << std::endl;

	//文字の追加
	//str1.push_back('A');//push_back() 1文字しか追加出来ない
	//std::cout << str1 << std::endl;

	//str1 += 'A'; operator+=(文字)
	//std::cout << str1 << std::endl;

	//str1 += "ABC";// operator+=(文字列) 文字列も後ろに追加出来る
	//std::cout << str1 << std::endl;

	//文字の削除
	//str1.pop_back();
	//std::cout << str1 << std::endl;

	/*
	//文字列のベクター
	std::vector<std::string>stringVec = 
	{
	  "acb","edf","ghi","jkl"
	};

	std::cout << stringVec.size() << std::endl;
	std::cout << stringVec.front() << std::endl;
	std::cout << stringVec.back() << std::endl;

	//文字列検索
	for (int i = 0; i < stringVec.size();i++) {

		if ("edf"==stringVec[i]) {
			std::cout << "edfと言う文字列がありました" << std::endl;
		}
		else {
			std::cout << stringVec[i] << std::endl;
		}
	}
	*/

	getchar();

}