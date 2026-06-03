#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "BTTask_FaceActor.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTTask_FaceActor : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector RotatorKey;
	
public:
	UBTTask_FaceActor();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
