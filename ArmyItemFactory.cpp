#include "stdafx.h"
#include "ArmyItemFactory.h"

#include <vector>
#include <algorithm>

namespace ArmyControl
{
	std::list<ArmyItem*> ArmyItemFactory::army;

	ArmyItemFactory& ArmyItemFactory::Instance()
	{
		static ArmyItemFactory factory;
		return factory;
	}

	void ArmyItemFactory::RegisterMaker(const std::wstring& key, IArmyItemMaker* maker)
	{
		if (_makers.find(key) != _makers.end())
		{
			return;
		}
		_makers[key] = maker;
	}

	void ArmyItemFactory::Create(std::wstring _type, std::wstring _name)
	{
		auto i = _makers.find(_type);
		if (i == _makers.end())
		{
			return;
		}
		IArmyItemMaker* maker = i->second;
		army.push_back(maker->Create(_type, _name));
	}

	void ArmyItemFactory::StartMove(std::wstring typeControl, std::wstring name, ArmyItem::KeyMove key)
	{
		if (typeControl.compare(L"Все") == 0)
		{
			for (auto obj : army)
			{
				obj->moveItem(key);
			}
		}
		else
		{
			std::vector<ArmyControl::ArmyItem*> matches;
			auto i = army.begin(), end = army.end();
			while (i != end)
			{
				i = std::find_if(i, end, [&](ArmyControl::ArmyItem* s) { return name.empty() ? (s->TypeName == typeControl) : (s->TypeName == typeControl) && (s->GetName() == name); });
				if (i != end) {
					matches.push_back((*i));
					i++;
				}
			}
			
			for (auto obj  : matches)
			{
				obj->moveItem(key);
			}
		}
		
	}
}