// ControlArmy.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <locale>
#include <fstream>
#include <codecvt>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <conio.h>

#include <boost/algorithm/string.hpp>

#include "ArmyMaker.h"
#include "windows.h"

using namespace ArmyControl;

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "rus");
	std::wcout << L"����� ���������... " << std::endl;
	std::wcout << L"������������ �����... " << std::endl;

	std::list<std::wstring> armyFile;

	// ������ ������� ����������
	for (int i = 1; i < argc; ++i)	{
		if (wcscmp(argv[i], L"") != 0)	{
			armyFile.push_back(argv[i]);
		}
	}

	std::wcout << L"���������� ������� ������:  " << argc - 1 << std::endl;

	std::wifstream inputfile;

	ArmyItemFactory factory = ArmyItemFactory::Instance();
	factory.RegisterMaker(L"���������", new ArmyItemMaker<Soldier>());
	factory.RegisterMaker(L"����", new ArmyItemMaker<Tank>());
	factory.RegisterMaker(L"�������", new ArmyItemMaker<Helicopter>());

	std::locale loc("");

	for (std::wstring& file : armyFile)
	{
		std::wcout << L"����:  " << file << std::endl;
		inputfile.open(file);
		inputfile.imbue(loc);

		if (inputfile.fail()) 
			continue;

		std::wstring line, name, typeName;
		while (std::getline(inputfile, line))
		{
			//trim
			boost::algorithm::trim(line);

			std::wstringstream iss(line);
			if (std::getline(iss, name, L' ') &&
				std::getline(iss, typeName, L'\0'))
			{
				boost::algorithm::trim(typeName);
				boost::algorithm::trim(name);
				std::wcout << L"�������:  " << typeName << L' ' << name << std::endl;
				factory.Create(typeName, name);
			}
		}

		inputfile.close();
		inputfile.clear();
	}

	std::wcout << L"\n������� ������ ������������ (���, ���������, ����, �������),\n"
		<< L"����������� ��� ������� ������������ �� ��������� (��������, ������),\n"
		<< L"� ����� ����������� �������� (�����, �����, �����, ������, �����, ����):\n";

	while (true) { 

		std::wstring obj, objType, objName, moveName;
		std::wcout << L"\n>";
		std::wcin.imbue(std::locale("rus_rus.866"));
		std::getline(std::wcin, obj, L'\n');

		//trim
		boost::algorithm::trim(obj);

		std::wstringstream iss(obj);
		if (std::getline(iss, objType, L' '))
		{
			std::wstring attributes[2];
			std::getline(iss, attributes[0], L' ');
			std::getline(iss, attributes[1], L'\0');

			if (attributes[1].empty())
			{
				moveName = attributes[0];
			}
			else if (!attributes[0].empty())
			{
				objName = attributes[0];
				moveName = attributes[1];
			}
			else continue;

			boost::algorithm::trim(objType);
			boost::algorithm::trim(objName);
			boost::algorithm::trim(moveName);

			if (moveName == L"�����"){
				factory.StartMove(objType, objName, ArmyItem::ARM_UP);
			}
			else if (moveName == L"����"){
				factory.StartMove(objType, objName, ArmyItem::ARM_DOWN);
			}
			else if (moveName == L"�����"){
				factory.StartMove(objType, objName, ArmyItem::ARM_LEFT);
			}
			else if (moveName == L"������"){
				factory.StartMove(objType, objName, ArmyItem::ARM_RIGHT);
			}
			else if (moveName == L"�����") {
				factory.StartMove(objType, objName, ArmyItem::ARM_FORWARD);
			}
			else if (moveName == L"�����") {
				factory.StartMove(objType, objName, ArmyItem::ARM_BACKWARD);
			}

			if (GetAsyncKeyState(VK_ESCAPE)) {
				break;
			}
			Sleep(100);
		}
		else return 0;
	}



	system("pause");

	return 0;
}

