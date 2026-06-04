#include "BTDecorator_AreItemsNearby.h"

#include "LinKyawKhineZombieRuntime/StudentPerceptor.h"

#include <GameAI_Zombie/Items/BaseItem.h>

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>

UBTDecorator_AreItemsNearby::UBTDecorator_AreItemsNearby()
{
	NodeName = "Are Items Nearby";
	Range = 100.f;
}

bool UBTDecorator_AreItemsNearby::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return false;
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return false;
	
	UStudentPerceptor* PerceptorComp { AIController->GetPawn()->GetComponentByClass<UStudentPerceptor>() };
	auto Items { PerceptorComp->GetPerceivedItems() };
	
	FVector const SurvivorLocation { AIController->GetPawn()->GetActorLocation() };
	for (auto const Item : Items)
	{
		double const Distance { (Item->GetActorLocation() - SurvivorLocation).Size() };
		
		if (Distance < Range)
		{
			return true;			
		}
	}
	
	return false;
}
