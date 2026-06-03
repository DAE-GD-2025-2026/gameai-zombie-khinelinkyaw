#include "BTDecorator_IsActorInRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsActorInRange::UBTDecorator_IsActorInRange()
{
	NodeName = "Is Zombie In Range";
	ActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_IsActorInRange, ActorKey), AActor::StaticClass());
}

bool UBTDecorator_IsActorInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return false;
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return false;
	
	if (AActor const* ActorToAvoid = Cast<AActor>(BlackboardComp->GetValueAsObject(ActorKey.SelectedKeyName)))
	{
		FVector const ActorLocation { ActorToAvoid->GetActorLocation() };
		FVector const SurvivorPosition { AIController->GetPawn()->GetActorLocation() };
		
		return (SurvivorPosition - ActorLocation).Size() < Range;
	}
	
	return false;
}
