#include "ZombiePluginUtils.h"

#include <GameAI_Zombie/Common/InventoryComponent.h>

TArray<TObjectPtr<ABaseItem>> PluginUtils::GetAllItemsInHouse(AHouse const* House,
	TSet<TObjectPtr<ABaseItem>> Items)
{
	TArray<TObjectPtr<ABaseItem>> Result{};
	
	FVector HouseOrigin{}, HouseBoxExtend{};
	House->GetActorBounds(false, HouseOrigin, HouseBoxExtend);
	FBox const HouseBox { FBox::BuildAABB(HouseOrigin, HouseBoxExtend) };
	
	for (auto const Item : Items)
	{
		if (Item->IsHidden()) continue;
		
		auto ItemLocation {Item->GetActorLocation()};
		ItemLocation.Z += 1;
		if (HouseBox.IsInside(ItemLocation))
		{
			Result.Add(Item);
		}
	}
	
	return Result;
}

int PluginUtils::GetFirstEmptyInventoryIndex(UInventoryComponent const* InvComp)
{
	auto Items { InvComp->GetInventory() };
	int InventorySize { InvComp->GetInventoryCapacity() };
	
	for (int Index{0}; Index < InventorySize; ++Index)
	{
		if (Items[Index] == nullptr)
		{
			return Index;
		}
	}
	
	return -1;
}

bool PluginUtils::ConsumeItemByType(UInventoryComponent const& InvComp, EItemType ItemType, ASurvivorPawn& SurvivorPawn)
{
	auto Items { InvComp.GetInventory() };
	int InventorySize { InvComp.GetInventoryCapacity() };
	
	for (int Index{0}; Index < InventorySize; ++Index)
	{
		if (Items[Index] == nullptr) continue;
		
		if (Items[Index]->GetItemType() == ItemType)
		{
			Items[Index]->UseItem(SurvivorPawn);
			return true;
		}
	}
	
	return false;
}

int PluginUtils::GetFirstItemByType(UInventoryComponent const& InvComp, EItemType ItemType)
{
	auto Items { InvComp.GetInventory() };
	int InventorySize { InvComp.GetInventoryCapacity() };
	
	for (int Index{0}; Index < InventorySize; ++Index)
	{
		if (Items[Index] == nullptr) continue;
		
		if (Items[Index]->GetItemType() == ItemType)
		{
			return Index;
		}
	}
	
	return -1;
}
