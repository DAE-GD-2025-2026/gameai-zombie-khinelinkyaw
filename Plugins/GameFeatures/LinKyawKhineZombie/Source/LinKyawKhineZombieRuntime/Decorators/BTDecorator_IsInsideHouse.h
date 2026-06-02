#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsInsideHouse.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTDecorator_IsInsideHouse : public UBTDecorator
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector HouseKey;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector SurvivorKey;
	
public:
	UBTDecorator_IsInsideHouse();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
