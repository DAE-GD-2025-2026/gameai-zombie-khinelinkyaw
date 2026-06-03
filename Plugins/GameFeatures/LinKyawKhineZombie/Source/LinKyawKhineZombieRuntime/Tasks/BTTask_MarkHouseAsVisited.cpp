#include "BTTask_MarkHouseAsVisited.h"

#include <../PluginUtils/ZombiePluginUtils.h>
#include "LinKyawKhineZombieRuntime/StudentPerceptor.h"

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>

UBTTask_MarkHouseAsVisited::UBTTask_MarkHouseAsVisited()
{
	NodeName = "Mark House as Visited";
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_MarkHouseAsVisited, BlackboardKey), AHouse::StaticClass());
}

EBTNodeResult::Type UBTTask_MarkHouseAsVisited::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn())
	{
		return EBTNodeResult::Failed;
	}
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}
	FVector SurvivorLocation = AIController->GetPawn()->GetActorLocation();
	
	AHouse* House = Cast<AHouse>(BlackboardComp->GetValueAsObject(BlackboardKey.SelectedKeyName));
	UStudentPerceptor* PerceptorComp { AIController->GetPawn()->GetComponentByClass<UStudentPerceptor>() };
	
	if (House)
	{
		PerceptorComp->MarkHouseAsVisisted(House);
		BlackboardComp->SetValueAsObject(BlackboardKey.SelectedKeyName, nullptr);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
