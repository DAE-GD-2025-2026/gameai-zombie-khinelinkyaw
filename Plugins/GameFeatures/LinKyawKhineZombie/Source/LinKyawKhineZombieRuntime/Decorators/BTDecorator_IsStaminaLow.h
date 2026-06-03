#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsStaminaLow.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTDecorator_IsStaminaLow : public UBTDecorator
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	int Threshold;
	
public:
	UBTDecorator_IsStaminaLow();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
