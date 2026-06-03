#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MarkHouseAsVisited.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTTask_MarkHouseAsVisited final : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_MarkHouseAsVisited();
	 
	// This is the main logic of your task
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
