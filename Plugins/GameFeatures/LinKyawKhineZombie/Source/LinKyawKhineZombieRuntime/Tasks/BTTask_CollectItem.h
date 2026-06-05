#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_CollectItem.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTTask_CollectItem final : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_CollectItem();
	 
	// This is the main logic of your task
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
