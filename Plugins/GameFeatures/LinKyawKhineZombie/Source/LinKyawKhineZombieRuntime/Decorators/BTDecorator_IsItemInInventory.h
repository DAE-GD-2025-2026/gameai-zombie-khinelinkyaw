#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include <GameAI_Zombie/Items/ItemType.h>

#include "BTDecorator_IsItemInInventory.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTDecorator_IsItemInInventory : public UBTDecorator
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	EItemType ItemType;

	
public:
	UBTDecorator_IsItemInInventory();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
