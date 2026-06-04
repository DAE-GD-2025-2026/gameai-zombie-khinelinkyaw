#include "BTDecorator_AreItemsNearbyByType.h"

#include "LinKyawKhineZombieRuntime/StudentPerceptor.h"

#include <GameAI_Zombie/Items/BaseItem.h>

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>

UBTDecorator_AreItemsNearbyByType::UBTDecorator_AreItemsNearbyByType()
{
	NodeName = "Are Items Nearby By Type";
	Range = 100.f;
	ItemType = EItemType::Food;
}

bool UBTDecorator_AreItemsNearbyByType::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
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
		
		if (Distance < Range and Item->GetItemType() == ItemType)
		{
			return true;			
		}
	}
	
	return false;
}
