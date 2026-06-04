#pragma once

#include "BehaviorTree/BTService.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_MarkHouseAsVisited.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTService_MarkHouseAsVisited final : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_MarkHouseAsVisited();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};