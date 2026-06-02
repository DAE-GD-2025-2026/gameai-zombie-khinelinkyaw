#pragma once

#include "Items/BaseItem.h"
#include "Village/House/House.h"

namespace PluginUtils
{
	TArray<TObjectPtr<ABaseItem>> GetAllItemsInHouse(AHouse const* House, TSet<TObjectPtr<ABaseItem>> Items);
}