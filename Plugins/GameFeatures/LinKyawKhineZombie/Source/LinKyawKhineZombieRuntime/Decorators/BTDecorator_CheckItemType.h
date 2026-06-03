#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include <GameAI_Zombie/Items/ItemType.h>

#include "BTDecorator_CheckItemType.generated.h"

UCLASS()
class UBTDecorator_CheckItemType : public UBTDecorator
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector ItemKey;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	EItemType ItemType;
	
public:
	UBTDecorator_CheckItemType();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
