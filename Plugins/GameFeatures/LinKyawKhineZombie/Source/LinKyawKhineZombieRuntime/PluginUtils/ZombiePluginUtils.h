#pragma once

#include "Items/BaseItem.h"
#include "Common/InventoryComponent.h"
#include "Village/House/House.h"

namespace PluginUtils
{
	TArray<TObjectPtr<ABaseItem>> GetAllItemsInHouse(AHouse const* House, TSet<TObjectPtr<ABaseItem>> Items);
	int GetFirstEmptyInventoryIndex(UInventoryComponent const* InvComp);
	
	bool ConsumeItemByType(UInventoryComponent const& InvComp, EItemType ItemType, ASurvivorPawn& SurvivorPawn);
	
	int GetFirstItemByType(UInventoryComponent const& InvComp, EItemType ItemType);
}
