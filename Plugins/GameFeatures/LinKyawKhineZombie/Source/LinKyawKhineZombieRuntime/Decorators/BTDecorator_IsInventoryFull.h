#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"

#include "BTDecorator_IsInventoryFull.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTDecorator_IsInventoryFull : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_IsInventoryFull();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
