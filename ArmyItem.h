#pragma once

#include <istream>
#include <sstream>
#include <string>
#include <iostream>

#include "stdafx.h"



namespace ArmyControl {
	class ArmyItem
	{
	protected:
		std::wstring name;
		
		virtual void moveToLeft() = 0;
		virtual void moveToRight() = 0;
		virtual void moveToForward() = 0;
		virtual void moveToBackward() = 0;
		virtual void moveToUp() = 0;
		virtual void moveToDown() = 0;

	public:
		typedef ArmyItem IArmyItem;

		static enum KeyMove {
			ARM_UP, ARM_DOWN, ARM_LEFT, ARM_RIGHT, ARM_FORWARD, ARM_BACKWARD
		};

		std::wstring TypeName;

		virtual void iter() {};
	
		std::wstring GetName() const
		{
			return name;
		}

		virtual void moveItem(KeyMove state) {
			switch (state)
			{
			case ARM_UP:
					moveToUp();
					break;
			case ARM_DOWN:
					moveToDown();
					break;
			case ARM_LEFT:
					moveToLeft();
					break;
			case ARM_RIGHT:
					moveToRight();
					break;
			case ARM_FORWARD:
					moveToForward();
					break;
			case ARM_BACKWARD:
					moveToBackward();
					break;
			default:
					break;
			}
		}
	};

	class IFullControl : public ArmyItem
	{
	protected:
		const std::wstring typeMove = L" двигается";
		virtual void moveToLeft()
		{
			std::wcout << TypeName << name << typeMove << L" влево" << std::endl;
		}
		virtual void moveToRight()
		{
			std::wcout << TypeName << L' ' << name << typeMove << L" вправо" << std::endl;
		}
		virtual void moveToForward()
		{
			std::wcout << TypeName << L' ' << name << typeMove << L" вперед" << std::endl;
		}
		virtual void moveToBackward()
		{
			std::wcout << TypeName << L' ' << name << typeMove << L" назад" << std::endl;
		}
		virtual void moveToUp()
		{
			std::wcout << TypeName << L' ' << name << typeMove << L" вверх" << std::endl;
		}
		virtual void moveToDown()
		{
			std::wcout << TypeName << L' ' << name << typeMove << L" вниз" << std::endl;
		}
	};

	class IRestricedControl : public ArmyItem
	{
	protected:
		const std::wstring typeMove = L" двигается";
		virtual void moveToLeft()
		{
			std::wcout << TypeName << name << typeMove << L" влево" << std::endl;
		}
		virtual void moveToRight()
		{
			std::wcout << TypeName << L' ' << name << typeMove << L" вправо" << std::endl;
		}
		virtual void moveToForward()
		{
			std::wcout << TypeName << L' ' << name << typeMove << L" вперед" << std::endl;
		}
		virtual void moveToBackward()
		{
			std::wcout << TypeName << L' ' << name << typeMove << L" назад" << std::endl;
		}
		virtual void moveToUp() {};
		virtual void moveToDown() {};
	};

	class Soldier : public IRestricedControl
	{
	public:
		Soldier(std::wstring _type, std::wstring _name) {
			name = _name;
			TypeName = _type;
		}
		virtual IArmyItem* Create(std::wstring _type, std::wstring _name) const { return new Soldier(_type, _name); }
	};

	class Helicopter : public IFullControl
	{
	public:
		Helicopter(std::wstring _type, std::wstring _name) {
			name = _name;
			TypeName = _type;
		}
		virtual IArmyItem* Create(std::wstring _type, std::wstring _name) const { return new Helicopter(_type, _name); }
	};

	class Tank : public IRestricedControl
	{
	public:
		Tank(std::wstring _type, std::wstring _name) {
			name = _name;
			TypeName = _type;
		}
		virtual IArmyItem* Create(std::wstring _type, std::wstring _name) const { return new Tank(_type, _name); }
	};
}

