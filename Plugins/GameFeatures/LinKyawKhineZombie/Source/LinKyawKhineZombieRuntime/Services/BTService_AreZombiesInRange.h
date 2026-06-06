#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_AreZombiesInRange.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTService_AreZombiesInRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float Range;

public:
	UBTService_AreZombiesInRange();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};