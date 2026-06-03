#include "BTService_ResetVisitedHouses.h"

#include "AIController.h"

#include "LinKyawKhineZombieRuntime/StudentPerceptor.h"

UBTService_ResetVisitedHouses::UBTService_ResetVisitedHouses()
{
	NodeName = "Reset Visited Houses";
}

void UBTService_ResetVisitedHouses::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return;

	if (UStudentPerceptor* PerceptorComp { AIController->GetPawn()->GetComponentByClass<UStudentPerceptor>() })
	{
		PerceptorComp->ClearVisitedHouses();
	}
}
