#include "ZombiePluginUtils.h"

TArray<TObjectPtr<ABaseItem>> PluginUtils::GetAllItemsInHouse(AHouse const* House,
	TSet<TObjectPtr<ABaseItem>> Items)
{
	TArray<TObjectPtr<ABaseItem>> Result{};
	
	FVector HouseOrigin{}, HouseBoxExtend{};
	House->GetActorBounds(false, HouseOrigin, HouseBoxExtend);
	FBox const HouseBox { FBox::BuildAABB(HouseOrigin, HouseBoxExtend) };
	
	for (auto const Item : Items)
	{
		auto ItemLocation {Item->GetActorLocation()};
		ItemLocation.Z += 1;
		if (HouseBox.IsInside(ItemLocation))
		{
			Result.Add(Item);
		}
	}
	
	return Result;
}
