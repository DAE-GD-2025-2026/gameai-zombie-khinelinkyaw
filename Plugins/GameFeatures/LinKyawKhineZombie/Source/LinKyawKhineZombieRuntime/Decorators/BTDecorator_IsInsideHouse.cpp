#include "BTDecorator_IsInsideHouse.h"

#include <Math/Box.h>
#include "BehaviorTree/BlackboardComponent.h"

#include "Village/House/House.h"

UBTDecorator_IsInsideHouse::UBTDecorator_IsInsideHouse()
{
	NodeName = "IsInsideHouse";
}

bool UBTDecorator_IsInsideHouse::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return false;
	}
	 
	// Retrieve the value from the blackboard

	if (AHouse* House = Cast<AHouse>(BlackboardComp->GetValueAsObject(SelectedBlackboardKey.SelectedKeyName)))
	{
		FVector HouseOrigin{}, HouseBoxExtend{}, SurvivorOrigin{}, SurvivorBoxExtend{};
		House->GetActorBounds(false, HouseOrigin, HouseBoxExtend);
		OwnerComp.GetOwner()->GetActorBounds(false, SurvivorOrigin, SurvivorBoxExtend);
	
		FBox const HouseBox { FBox::BuildAABB(HouseOrigin, HouseBoxExtend) };
		FBox const OwnerBox { FBox::BuildAABB(SurvivorOrigin, SurvivorBoxExtend) };
	
		return HouseBox.Intersect(OwnerBox);
	}
	return false;
}
