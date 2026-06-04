#include "BTTask_FindNearbyItem.h"

#include "LinKyawKhineZombieRuntime/StudentPerceptor.h"

#include <GameAI_Zombie/Items/BaseItem.h>

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>

UBTTask_FindNearbyItem::UBTTask_FindNearbyItem()
{
	NodeName = "Find Nearby Item";
	Range = 100.f;
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindNearbyItem, BlackboardKey), ABaseItem::StaticClass());
}

EBTNodeResult::Type UBTTask_FindNearbyItem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return EBTNodeResult::Failed;
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return EBTNodeResult::Failed;
	
	UStudentPerceptor* PerceptorComp { AIController->GetPawn()->GetComponentByClass<UStudentPerceptor>() };
	auto Items { PerceptorComp->GetPerceivedItems() };
	
	FVector const SurvivorLocation { AIController->GetPawn()->GetActorLocation() };
	for (auto const Item : Items)
	{
		FVector const ItemLocation { Item->GetActorLocation() };
		FVector const Distance { SurvivorLocation - ItemLocation };
		
		if (Distance.Size() < Range)
		{
			BlackboardComp->SetValueAsObject(BlackboardKey.SelectedKeyName, Item);
			return EBTNodeResult::Succeeded;			
		}
	}
	
	return EBTNodeResult::Failed;
}
