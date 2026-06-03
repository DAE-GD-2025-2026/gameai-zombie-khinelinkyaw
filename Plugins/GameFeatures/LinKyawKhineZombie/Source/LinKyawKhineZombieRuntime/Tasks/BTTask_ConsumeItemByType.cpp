#include "BTTask_ConsumeItemByType.h"

#include <LinKyawKhineZombieRuntime/PluginUtils/ZombiePluginUtils.h>

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>

UBTTask_ConsumeItemByType::UBTTask_ConsumeItemByType()
{
	NodeName = "Consume Item By Type";
}

EBTNodeResult::Type UBTTask_ConsumeItemByType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return EBTNodeResult::Failed;

	UInventoryComponent* InvComp { AIController->GetPawn()->GetComponentByClass<UInventoryComponent>() };
	
	if (int FirstIndex {PluginUtils::GetFirstItemByType(*InvComp, ItemType)}; FirstIndex != -1)
	{
		if (InvComp->UseItem(FirstIndex))
		{
			if (InvComp->GetInventory()[FirstIndex]->GetValue() == 0)
			{
				InvComp->RemoveItem(FirstIndex);
			}
			
			return EBTNodeResult::Succeeded;
		}
		else
		{
			return EBTNodeResult::Aborted;
		}
	}
	
	return EBTNodeResult::Failed;
}
