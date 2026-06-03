#include "BTDecorator_IsItemInInventory.h"

#include <LinKyawKhineZombieRuntime/PluginUtils/ZombiePluginUtils.h>

#include "AIController.h"

UBTDecorator_IsItemInInventory::UBTDecorator_IsItemInInventory()
{
	NodeName = "Is Item In Inventory";
}

bool UBTDecorator_IsItemInInventory::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
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
