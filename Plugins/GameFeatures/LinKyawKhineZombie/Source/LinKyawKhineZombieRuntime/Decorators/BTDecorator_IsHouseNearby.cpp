#include "BTDecorator_IsHouseNearby.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Village/House/House.h"

FString UBTDecorator_IsHouseNearby::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: %s >= %.1f"), 
			*Super::GetStaticDescription(), 
			*SelectedBlackboardKey.SelectedKeyName.ToString(), 
			Range);
}

UBTDecorator_IsHouseNearby::UBTDecorator_IsHouseNearby()
{
	NodeName = "IsHouseNearby";
	Range = 100.f;
	
	SelectedBlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_IsHouseNearby, SelectedBlackboardKey), AHouse::StaticClass());
}

bool UBTDecorator_IsHouseNearby::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	const UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return false;
	}
	 
	// Retrieve the value from the blackboard
	auto CurrentValue = BlackboardComp->GetValueAsObject(SelectedBlackboardKey.SelectedKeyName);
	
	if (AHouse* House { Cast<AHouse>(CurrentValue) })
	{
		FVector OwnerLocation { OwnerComp.GetOwner()->GetActorLocation() };
		double HouseDistance{ House->GetActorLocation().Size() - OwnerLocation.Size() };
		return HouseDistance < Range;
	}
	else
	{
		return false;
	}
}
