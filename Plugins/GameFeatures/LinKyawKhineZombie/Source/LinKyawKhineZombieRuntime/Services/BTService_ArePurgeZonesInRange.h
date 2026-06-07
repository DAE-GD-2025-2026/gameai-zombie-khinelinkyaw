#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_ArePurgeZonesInRange.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTService_ArePurgeZonesInRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float Range;

public:
	UBTService_ArePurgeZonesInRange();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};