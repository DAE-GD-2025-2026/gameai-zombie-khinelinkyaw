#include "BTTask_FindRandomLocation.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation()
{
	NodeName = "Find Random Location";
	 
	// Limit the Blackboard Key Selector to only show Vectors in the editor
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindRandomLocation, BlackboardKey));
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn())
	{
		return EBTNodeResult::Failed;
	}
	 
	FVector Origin = AIController->GetPawn()->GetActorLocation();
	FNavLocation NextLocation;
	 
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem && NavSystem->GetRandomReachablePointInRadius(Origin, SearchRadius, NextLocation))
	{
		// Write the result to the blackboard key selected in the editor
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, NextLocation.Location);
		return EBTNodeResult::Succeeded;
	}
	 
	return EBTNodeResult::Failed; // Logic failed to find a point; prevents potential elimination of AI flow
}
