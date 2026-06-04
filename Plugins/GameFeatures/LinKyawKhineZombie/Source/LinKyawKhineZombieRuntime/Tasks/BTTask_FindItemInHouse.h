#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindItemInHouse.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTTask_FindItemInHouse final : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector HouseKey;
	
public:
	UBTTask_FindItemInHouse();
	 
	// This is the main logic of your task
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
