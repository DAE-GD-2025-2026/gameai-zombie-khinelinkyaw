#include "BTService_ArePurgeZonesInRange.h"

#include <GameAI_Zombie/PurgeZones/PurgeZone.h>

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LinKyawKhineZombieRuntime/StudentPerceptorLinKyawKhine.h"

UBTService_ArePurgeZonesInRange::UBTService_ArePurgeZonesInRange()
{
	NodeName = "Are Purge Zones in Range";
	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_ArePurgeZonesInRange, BlackboardKey));
	Range = 500.f;
}

void UBTService_ArePurgeZonesInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return;

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return;
	
	UStudentPerceptorLinKyawKhine* PerceptorComp { AIController->GetPawn()->GetComponentByClass<UStudentPerceptorLinKyawKhine>() };
	auto PurgeZones { PerceptorComp->GetSortedPurgeZones() };
	
	if (!PurgeZones.IsEmpty()) 
	{
		double Distance {  FVector::Dist(PurgeZones[0]->GetActorLocation(), AIController->GetPawn()->GetActorLocation()) };
		
		if (Distance < Range)
		{
			BlackboardComp->SetValueAsBool(BlackboardKey.SelectedKeyName, true);
		}
	}
}
