#include "BTService_AreZombiesInRange.h"

#include <GameAI_Zombie/Zombies/BaseZombie.h>

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LinKyawKhineZombieRuntime/StudentPerceptor.h"

UBTService_AreZombiesInRange::UBTService_AreZombiesInRange()
{
	NodeName = "Are Zombies in Range";
	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_AreZombiesInRange, BlackboardKey));
	Range = 500.f;
}

void UBTService_AreZombiesInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return;

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return;
	
	UStudentPerceptor* PerceptorComp { AIController->GetPawn()->GetComponentByClass<UStudentPerceptor>() };
	auto Zombies { PerceptorComp->GetSortedZombies() };
	
	if (!Zombies.IsEmpty()) 
	{
		double Distance {  FVector::Dist(Zombies[0]->GetActorLocation(), AIController->GetPawn()->GetActorLocation()) };
		
		if (Distance < Range)
		{
			BlackboardComp->SetValueAsBool(BlackboardKey.SelectedKeyName, true);
		}
	}
}
