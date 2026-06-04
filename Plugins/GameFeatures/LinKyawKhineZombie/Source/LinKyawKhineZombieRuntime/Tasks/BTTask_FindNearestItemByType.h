#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include <GameAI_Zombie/Items/ItemType.h>

#include "BTTask_FindNearestItemByType.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTTask_FindNearestItemByType final : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float Range;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	EItemType ItemType;
	
public:
	UBTTask_FindNearestItemByType();
	 
	// This is the main logic of your task
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
