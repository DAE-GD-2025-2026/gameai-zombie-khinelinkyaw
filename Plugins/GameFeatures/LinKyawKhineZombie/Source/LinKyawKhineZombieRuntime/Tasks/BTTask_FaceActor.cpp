#include "BTTask_FaceActor.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FaceActor::UBTTask_FaceActor()
{
	NodeName = "Face Actor";
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FaceActor, BlackboardKey), AActor::StaticClass());
	RotatorKey.AddRotatorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FaceActor, RotatorKey));
}

EBTNodeResult::Type UBTTask_FaceActor::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return EBTNodeResult::Failed;
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return EBTNodeResult::Failed;
	
	if (AActor* ActorToAvoid = Cast<AActor>(BlackboardComp->GetValueAsObject(BlackboardKey.SelectedKeyName)))
	{
		AIController->SetFocus(ActorToAvoid);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
