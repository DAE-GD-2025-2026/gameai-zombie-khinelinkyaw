#include "BTDecorator_IsInsideHouse.h"

#include <Math/Box.h>
#include "BehaviorTree/BlackboardComponent.h"

#include <AIController.h>
#include "Village/House/House.h"
#include <GameAI_Zombie/Survivor/SurvivorPawn.h>

UBTDecorator_IsInsideHouse::UBTDecorator_IsInsideHouse()
{
	NodeName = "IsInsideHouse";
	HouseKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_IsInsideHouse, HouseKey), AHouse::StaticClass());
	SurvivorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_IsInsideHouse, SurvivorKey), AActor::StaticClass());
}

bool UBTDecorator_IsInsideHouse::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent const* BlackboardComp = OwnerComp.GetBlackboardComponent();
	
	if (!BlackboardComp)
	{
		return false;
	}
	
	AHouse const* House = Cast<AHouse>(BlackboardComp->GetValueAsObject(HouseKey.SelectedKeyName));
	AActor const* Survivor = Cast<AActor>(BlackboardComp->GetValueAsObject(SurvivorKey.SelectedKeyName));
	
	if (House == nullptr or Survivor == nullptr) return false;
		
	FVector HouseOrigin{}, HouseBoxExtend{};
	House->GetActorBounds(false, HouseOrigin, HouseBoxExtend);
	auto ActorLocation {Survivor->GetActorLocation()};

	FBox const HouseBox { FBox::BuildAABB(HouseOrigin, HouseBoxExtend) };

	bool Result {HouseBox.IsInside(ActorLocation)};
	return Result;
}
