#pragma once
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include <GameAI_Zombie/Items/ItemType.h>

#include "BTTask_RemoveItemByType.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTTask_RemoveItemByType final : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Item")
	EItemType ItemType;
	
public:
	UBTTask_RemoveItemByType();
	 
	// This is the main logic of your task
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};