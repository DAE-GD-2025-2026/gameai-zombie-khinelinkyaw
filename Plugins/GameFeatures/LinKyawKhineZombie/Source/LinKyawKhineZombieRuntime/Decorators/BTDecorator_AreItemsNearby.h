#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_AreItemsNearby.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTDecorator_AreItemsNearby : public UBTDecorator
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float Range;
	
public:
	UBTDecorator_AreItemsNearby();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
