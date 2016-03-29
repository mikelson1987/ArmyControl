#pragma once

#include <map>
#include <memory>
#include <functional>
#include <list>

#include "ArmyItem.h"

namespace ArmyControl 
{
	class IArmyItemMaker
	{
	public:
		virtual ArmyControl::ArmyItem* Create(std::wstring _type, std::wstring _name) const = 0;
		virtual ~IArmyItemMaker() {};
	};

	class ArmyItemFactory
	{
	private:
		std::map<std::wstring, IArmyItemMaker*> _makers;
		static std::list<ArmyItem*> army;
	public:

		static ArmyItemFactory& Instance();
		void RegisterMaker(const std::wstring& key, IArmyItemMaker* maker);
		void Create(std::wstring _type, std::wstring _name);
		void StartMove(std::wstring typeControl, std::wstring name, ArmyItem::KeyMove key);
	};
};



