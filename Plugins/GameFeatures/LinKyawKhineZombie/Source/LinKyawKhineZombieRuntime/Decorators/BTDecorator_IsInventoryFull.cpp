#include "BTDecorator_IsInventoryFull.h"

#include <LinKyawKhineZombieRuntime/PluginUtils/ZombiePluginUtils.h>

#include <GameAI_Zombie/Items/BaseItem.h>

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInventoryFull::UBTDecorator_IsInventoryFull()
{
	NodeName = "Is Inventory Full";
}

bool UBTDecorator_IsInventoryFull::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                              uint8* NodeMemory) const
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return false;
	
	UBlackboardComponent const* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return false;

	UInventoryComponent const* InvComp { AIController->GetPawn()->GetComponentByClass<UInventoryComponent>() };
	auto InvItems { InvComp->GetInventory() };
	
	for (auto const Item : InvItems)
	{
		if (Item == nullptr) return false;
	}
	
	return true;
}
