#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "UBTTask_FindRandomLocation.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTTask_FindRandomLocation final : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	 
public:
	UBTTask_FindRandomLocation();
	 
	// This is the main logic of your task
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	 
	UPROPERTY(EditAnywhere, Category = "AI")
	float SearchRadius = 500.0f;
};