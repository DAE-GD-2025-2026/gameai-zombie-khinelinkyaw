#include "BTTask_CollectNearbyItem.h"

#include <../PluginUtils/ZombiePluginUtils.h>
#include "LinKyawKhineZombieRuntime/StudentPerceptor.h"

#include <GameAI_Zombie/Items/BaseItem.h>
#include <GameAI_Zombie/Common/InventoryComponent.h>

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>

UBTTask_CollectNearbyItem::UBTTask_CollectNearbyItem()
{
	NodeName = "Collect Nearby Item";
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_CollectNearbyItem, BlackboardKey), ABaseItem::StaticClass());
}

EBTNodeResult::Type UBTTask_CollectNearbyItem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn())
	{
		return EBTNodeResult::Failed;
	}
	
	UBlackboardComponent const* BlackboardComp = OwnerComp.GetBlackboardComponent();
	
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	if (ABaseItem* Item = Cast<ABaseItem>(BlackboardComp->GetValueAsObject(BlackboardKey.SelectedKeyName)))
	{
		UInventoryComponent* InvComp { AIController->GetPawn()->GetComponentByClass<UInventoryComponent>() };

		if (int FreeIndex{ PluginUtils::GetFirstEmptyInventoryIndex(InvComp) }; FreeIndex != -1)
		{
			//BlackboardComp->SetValueAsObject(BlackboardKey.SelectedKeyName, nullptr);
			InvComp->GrabItem(FreeIndex, Item);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
