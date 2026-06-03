#include "BTTask_RemoveItemByType.h"

#include <LinKyawKhineZombieRuntime/PluginUtils/ZombiePluginUtils.h>

#include <GameAI_Zombie/Items/BaseItem.h>

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>

UBTTask_RemoveItemByType::UBTTask_RemoveItemByType()
{
	NodeName = "Remove Item By Type";
}

EBTNodeResult::Type UBTTask_RemoveItemByType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return EBTNodeResult::Failed;

	UInventoryComponent* InvComp { AIController->GetPawn()->GetComponentByClass<UInventoryComponent>() };
	
	if (int FirstIndex {PluginUtils::GetFirstItemByType(*InvComp, ItemType)}; FirstIndex != -1)
	{
		InvComp->RemoveItem(FirstIndex);
	}
	
	return EBTNodeResult::Succeeded;
}
