#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_ArePurgeZonesInRange.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTDecorator_ArePurgeZonesInRange : public UBTDecorator
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float Range;
	
public:
	UBTDecorator_ArePurgeZonesInRange();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
