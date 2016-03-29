#pragma once

#include "stdafx.h"

#include "ArmyItemFactory.h"


namespace ArmyControl
{
	template<typename T>
	class ArmyItemMaker : public IArmyItemMaker
	{
	public:
		virtual ArmyItem* Create(std::wstring _type, std::wstring _name) const
		{
			return new T(_type, _name);
		}
	};
}

