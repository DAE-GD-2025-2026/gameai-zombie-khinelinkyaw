#include "BTDecorator_ArePurgeZonesInRange.h"

#include "LinKyawKhineZombieRuntime/StudentPerceptorLinKyawKhine.h"

#include <GameAI_Zombie/PurgeZones/PurgeZone.h>

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>

UBTDecorator_ArePurgeZonesInRange::UBTDecorator_ArePurgeZonesInRange()
{
	NodeName = "Are Purge Zones in Range";
	Range = 300.f;
}

bool UBTDecorator_ArePurgeZonesInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return false;
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return false;
	
	UStudentPerceptorLinKyawKhine* PerceptorComp { AIController->GetPawn()->GetComponentByClass<UStudentPerceptorLinKyawKhine>() };
	auto PurgeZones { PerceptorComp->GetSortedPurgeZones() };
	
	FVector const SurvivorLocation { AIController->GetPawn()->GetActorLocation() };
	for (auto const PurgeZone : PurgeZones)
	{
		double const Distance { (PurgeZone->GetActorLocation() - SurvivorLocation).Size() };
		
		if (Distance < Range)
		{
			return true;			
		}
	}
	
	return false;
}
