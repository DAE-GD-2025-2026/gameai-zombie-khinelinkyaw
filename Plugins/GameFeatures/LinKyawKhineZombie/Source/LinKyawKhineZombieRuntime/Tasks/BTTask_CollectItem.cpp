#include "BTTask_CollectItem.h"

#include <LinKyawKhineZombieRuntime/PluginUtils/ZombiePluginUtils.h>

#include <GameAI_Zombie/Items/BaseItem.h>
#include <GameAI_Zombie/Common/InventoryComponent.h>

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>


UBTTask_CollectItem::UBTTask_CollectItem()
{
	NodeName = "Collect Item";
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_CollectItem, BlackboardKey), ABaseItem::StaticClass());
}

EBTNodeResult::Type UBTTask_CollectItem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return EBTNodeResult::Failed;
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return EBTNodeResult::Failed;

	if (ABaseItem* Item = Cast<ABaseItem>(BlackboardComp->GetValueAsObject(BlackboardKey.SelectedKeyName)))
	{
		UInventoryComponent* InvComp { AIController->GetPawn()->GetComponentByClass<UInventoryComponent>() };

		if (int FreeIndex{ PluginUtils::GetFirstEmptyInventoryIndex(InvComp) }; FreeIndex != -1)
		{
			BlackboardComp->SetValueAsObject(BlackboardKey.SelectedKeyName, nullptr);
			InvComp->GrabItem(FreeIndex, Item);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
