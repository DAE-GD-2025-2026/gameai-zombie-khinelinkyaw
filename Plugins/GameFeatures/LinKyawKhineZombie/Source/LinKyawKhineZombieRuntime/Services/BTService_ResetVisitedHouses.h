#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_ResetVisitedHouses.generated.h"

UCLASS()
class LINKYAWKHINEZOMBIERUNTIME_API UBTService_ResetVisitedHouses final : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_ResetVisitedHouses();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
