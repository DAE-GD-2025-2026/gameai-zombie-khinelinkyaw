#include "BTTask_AvoidActor.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_AvoidActor::UBTTask_AvoidActor()
{
	NodeName = "Avoid Actor";
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_AvoidActor, BlackboardKey), AActor::StaticClass());
	DestinationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_AvoidActor, DestinationKey));
}

EBTNodeResult::Type UBTTask_AvoidActor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return EBTNodeResult::Failed;
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return EBTNodeResult::Failed;
	
	if (AActor const* ActorToAvoid = Cast<AActor>(BlackboardComp->GetValueAsObject(BlackboardKey.SelectedKeyName)))
	{
		FVector const ActorLocation { ActorToAvoid->GetActorLocation() };
		FVector const SurvivorPosition { AIController->GetPawn()->GetActorLocation() };
		FVector AvoidLocation {
			SurvivorPosition.X + ActorLocation.X,
			SurvivorPosition.Y + ActorLocation.Y,
			1
		};
		
		AvoidLocation = AvoidLocation.GetSafeNormal() * 5.f; 
		AvoidLocation.Z = SurvivorPosition.Z;
		
		BlackboardComp->SetValueAsVector(DestinationKey.SelectedKeyName, AvoidLocation);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
