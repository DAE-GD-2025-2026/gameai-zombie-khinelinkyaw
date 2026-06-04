#include "BTDecorator_IsItemInInventory.h"

#include <LinKyawKhineZombieRuntime/PluginUtils/ZombiePluginUtils.h>

#include <GameAI_Zombie/Items/BaseItem.h>

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsItemInInventory::UBTDecorator_IsItemInInventory()
{
	NodeName = "Is Item In Inventory";
	ItemKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_IsItemInInventory, ItemKey), ABaseItem::StaticClass());
}

bool UBTDecorator_IsItemInInventory::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return false;
	
	UBlackboardComponent const* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return false;

	UInventoryComponent const* InvComp { AIController->GetPawn()->GetComponentByClass<UInventoryComponent>() };
	
	ABaseItem const* Item = Cast<ABaseItem>(BlackboardComp->GetValueAsObject(ItemKey.SelectedKeyName));
	if (!Item) return false;
	
	if (PluginUtils::GetFirstItemByType(*InvComp, Item->GetItemType()) != -1)
	{
		return true;
	}
	
	return false;
}
