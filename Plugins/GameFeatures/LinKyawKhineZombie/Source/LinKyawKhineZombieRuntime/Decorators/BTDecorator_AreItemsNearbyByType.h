#pragma once

#include "BehaviorTree/BTDecorator.h"

#include <GameAI_Zombie/Items/ItemType.h>

#include "BTDecorator_AreItemsNearbyByType.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTDecorator_AreItemsNearbyByType : public UBTDecorator
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float Range;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	EItemType ItemType;
	
public:
	UBTDecorator_AreItemsNearbyByType();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
