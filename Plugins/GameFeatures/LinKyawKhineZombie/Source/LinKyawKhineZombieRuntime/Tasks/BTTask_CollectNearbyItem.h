#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_CollectNearbyItem.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTTask_CollectNearbyItem final : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector HouseKey;
	
public:
	UBTTask_CollectNearbyItem();
	 
	// This is the main logic of your task
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
