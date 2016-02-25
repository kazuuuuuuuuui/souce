//-------------------------------------
//STLの機能mapの使い方

#include<map>
#include<string>
#include<iostream>

void main() {

	//std::map<std::string, int>mp;//<key,value>

	////keyとvalueの設定
	//mp["abc"] = 123;
	//mp["def"] = 456;
	//mp["ghi"] = 789;

	//std::cout << mp.size() << std::endl;//マップの大きさ

	//keyの出力
	//std::cout << mp["abc"] << std::endl;
	//std::cout << mp["def"] << std::endl;

	/*存在しないノードにアクセスすると勝手にノードが作られてしまう*/
	//std::cout << mp["ghi"] << std::endl;
	//std::cout << mp.size() << std::endl;

	//イテレータを使ってmap全体にアクセス
	//for (auto itr = mp.begin(); itr != mp.end();itr++) { // autoは型推論

	//	std::cout << "key:" << itr->first << ' '//key出力
	//		<< "value:" << itr->second << std::endl;//value出力

	//}

	//std::cout << std::endl;

	////削除
	//mp.erase("def");

	//for (auto itr = mp.begin(); itr != mp.end(); itr++) { // autoは型推論

	//	std::cout << "key:" << itr->first << ' '//key出力
	//		<< "value:" << itr->second << std::endl;//value出力

	//}

	//mapにkeyが登録されているか検索
	//auto itr = mp.find("abc");
	//if (itr != mp.end()) {
	//	std::cout << itr->first << ' '//登録済みのkeyの出力
	//		<< itr->second << std::endl;//登録済みのvalueの出力
	//}
	//else {
	//	std::cout << "未登録です" << std::endl;
	//}


	getchar();
}