#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsActorInRange.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTDecorator_IsActorInRange : public UBTDecorator
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector ActorKey;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float Range;
	
public:
	UBTDecorator_IsActorInRange();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
