#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "BTTask_AvoidActor.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTTask_AvoidActor final : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector DestinationKey;
	
public:
	UBTTask_AvoidActor();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
