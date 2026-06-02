#include "BTDecorator_AreItemsInHouse.h"

#include "BehaviorTree/BlackboardComponent.h"

#include <GameAI_Zombie/Village/House/House.h>
#include <GameAI_Zombie/Items/BaseItem.h>

#include "LinKyawKhineZombieRuntime/StudentPerceptor.h"

UBTDecorator_AreItemsInHouse::UBTDecorator_AreItemsInHouse()
{
	NodeName = "AreItemsInHouse";
	HouseKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_AreItemsInHouse, HouseKey), AHouse::StaticClass());
	SurvivorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_AreItemsInHouse, SurvivorKey), AActor::StaticClass());
}

bool UBTDecorator_AreItemsInHouse::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	UBlackboardComponent const* BlackboardComp = OwnerComp.GetBlackboardComponent();
	
	if (!BlackboardComp)
	{
		return false;
	}
	
	AHouse const* House = Cast<AHouse>(BlackboardComp->GetValueAsObject(HouseKey.SelectedKeyName));
	AActor const* Survivor = Cast<AActor>(BlackboardComp->GetValueAsObject(SurvivorKey.SelectedKeyName));
	
	if (House == nullptr or Survivor == nullptr) return false;
	
	UStudentPerceptor* PerceptorComp { Survivor->GetComponentByClass<UStudentPerceptor>() };
	
	FVector HouseOrigin{}, HouseBoxExtend{};
	House->GetActorBounds(false, HouseOrigin, HouseBoxExtend);
	FBox const HouseBox { FBox::BuildAABB(HouseOrigin, HouseBoxExtend) };
	
	auto const PerceivedItems{ PerceptorComp->GetPerceivedItems() };
	
	for (auto const Item : PerceivedItems)
	{
		auto ItemLocation {Item->GetActorLocation()};
		ItemLocation.Z += 1;
		if (HouseBox.IsInside(ItemLocation))
		{
			return true;
		}
	}
	
	return false;
}
