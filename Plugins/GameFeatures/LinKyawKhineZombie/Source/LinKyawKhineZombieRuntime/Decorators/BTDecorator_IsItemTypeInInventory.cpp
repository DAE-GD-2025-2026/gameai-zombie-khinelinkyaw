#include "BTDecorator_IsItemTypeInInventory.h"

#include <LinKyawKhineZombieRuntime/PluginUtils/ZombiePluginUtils.h>

#include "AIController.h"

UBTDecorator_IsItemTypeInInventory::UBTDecorator_IsItemTypeInInventory()
{
	NodeName = "Is Item Type In Inventory";
}

bool UBTDecorator_IsItemTypeInInventory::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                                    uint8* NodeMemory) const
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return false;

	UInventoryComponent const* InvComp { AIController->GetPawn()->GetComponentByClass<UInventoryComponent>() };
	
	if (PluginUtils::GetFirstItemByType(*InvComp, ItemType) != -1)
	{
		return true;
	}
	
	return false;
}
