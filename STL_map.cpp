//-------------------------------------
//STL�̋@�\map�̎g����

#include<map>
#include<string>
#include<iostream>

void main() {

	//std::map<std::string, int>mp;//<key,value>

	////key��value�̐ݒ�
	//mp["abc"] = 123;
	//mp["def"] = 456;
	//mp["ghi"] = 789;

	//std::cout << mp.size() << std::endl;//�}�b�v�̑傫��

	//key�̏o��
	//std::cout << mp["abc"] << std::endl;
	//std::cout << mp["def"] << std::endl;

	/*���݂��Ȃ��m�[�h�ɃA�N�Z�X����Ə���Ƀm�[�h������Ă��܂�*/
	//std::cout << mp["ghi"] << std::endl;
	//std::cout << mp.size() << std::endl;

	//�C�e���[�^���g����map�S�̂ɃA�N�Z�X
	//for (auto itr = mp.begin(); itr != mp.end();itr++) { // auto�͌^���_

	//	std::cout << "key:" << itr->first << ' '//key�o��
	//		<< "value:" << itr->second << std::endl;//value�o��

	//}

	//std::cout << std::endl;

	////�폜
	//mp.erase("def");

	//for (auto itr = mp.begin(); itr != mp.end(); itr++) { // auto�͌^���_

	//	std::cout << "key:" << itr->first << ' '//key�o��
	//		<< "value:" << itr->second << std::endl;//value�o��

	//}

	//map��key���o�^����Ă��邩����
	//auto itr = mp.find("abc");
	//if (itr != mp.end()) {
	//	std::cout << itr->first << ' '//�o�^�ς݂�key�̏o��
	//		<< itr->second << std::endl;//�o�^�ς݂�value�̏o��
	//}
	//else {
	//	std::cout << "���o�^�ł�" << std::endl;
	//}


	getchar();
}