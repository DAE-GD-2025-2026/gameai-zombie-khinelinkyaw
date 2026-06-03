#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include <GameAI_Zombie/Items/ItemType.h>

#include "BTTask_ConsumeItemByType.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTTask_ConsumeItemByType final : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Item")
	EItemType ItemType;
	
public:
	UBTTask_ConsumeItemByType();
	 
	// This is the main logic of your task
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
