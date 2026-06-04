#include "BTTask_FindNearestItemByType.h"

#include "LinKyawKhineZombieRuntime/StudentPerceptor.h"

#include <GameAI_Zombie/Items/BaseItem.h>

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindNearestItemByType::UBTTask_FindNearestItemByType()
{
	NodeName = "Find Nearest Item By Type";
	Range = 100.f;
	ItemType = EItemType::Food;
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindNearestItemByType, BlackboardKey), ABaseItem::StaticClass());
}

EBTNodeResult::Type UBTTask_FindNearestItemByType::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return EBTNodeResult::Failed;
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return EBTNodeResult::Failed;
	
	UStudentPerceptor* PerceptorComp { AIController->GetPawn()->GetComponentByClass<UStudentPerceptor>() };
	auto Items { PerceptorComp->GetPerceivedItemsByType(ItemType) };
	
	if (Items.IsEmpty()) return EBTNodeResult::Failed;
	
	FVector const SurvivorLocation { AIController->GetPawn()->GetActorLocation() };
	
	auto const ClosestElement { Algo::MinElementBy(Items, [SurvivorLocation](TObjectPtr<ABaseItem> const& Item)
	{
		FVector const ItemLocation{ Item->GetActorLocation() - SurvivorLocation };
		return ItemLocation.Size();
	})};
	
	if (ClosestElement)
	{
		FVector ClosestElementDistance { ClosestElement->Get()->GetActorLocation() - SurvivorLocation };
		
		if (ClosestElementDistance.Size() < Range)
		{
			BlackboardComp->SetValueAsObject(BlackboardKey.SelectedKeyName, ClosestElement->Get());
			return EBTNodeResult::Succeeded;
		}
		
	}
	
	return EBTNodeResult::Failed;
}
