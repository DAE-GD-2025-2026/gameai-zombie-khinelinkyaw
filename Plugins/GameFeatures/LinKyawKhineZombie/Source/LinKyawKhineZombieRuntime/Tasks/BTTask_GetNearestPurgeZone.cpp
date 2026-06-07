#include "BTTask_GetNearestPurgeZone.h"

#include "LinKyawKhineZombieRuntime/StudentPerceptorLinKyawKhine.h"

#include <GameAI_Zombie/PurgeZones/PurgeZone.h>

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>

UBTTask_GetNearestPurgeZone::UBTTask_GetNearestPurgeZone()
{
	NodeName = "Get Nearest Purge Zone";
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_GetNearestPurgeZone, BlackboardKey), APurgeZone::StaticClass());
}

EBTNodeResult::Type UBTTask_GetNearestPurgeZone::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return EBTNodeResult::Failed;
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return EBTNodeResult::Failed;
	
	UStudentPerceptorLinKyawKhine* PerceptorComp { AIController->GetPawn()->GetComponentByClass<UStudentPerceptorLinKyawKhine>() };
	auto PurgeZones { PerceptorComp->GetSortedPurgeZones() };
	
	if (!PurgeZones.IsEmpty())
	{
		BlackboardComp->SetValueAsObject(BlackboardKey.SelectedKeyName, PurgeZones[0]);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
