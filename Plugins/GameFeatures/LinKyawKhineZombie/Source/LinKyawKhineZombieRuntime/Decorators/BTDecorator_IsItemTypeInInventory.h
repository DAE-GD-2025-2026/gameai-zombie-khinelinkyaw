#pragma once

#include <GameAI_Zombie/Items/ItemType.h>

#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"

#include "BTDecorator_IsItemTypeInInventory.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTDecorator_IsItemTypeInInventory : public UBTDecorator
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	EItemType ItemType;

public:
	UBTDecorator_IsItemTypeInInventory();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
