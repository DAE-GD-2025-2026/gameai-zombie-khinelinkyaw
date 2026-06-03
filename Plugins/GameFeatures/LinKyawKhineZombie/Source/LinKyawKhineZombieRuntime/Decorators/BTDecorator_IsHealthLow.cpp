#include "BTDecorator_IsHealthLow.h"

#include <GameAI_Zombie/Common/HealthComponent.h>

#include "AIController.h"

UBTDecorator_IsHealthLow::UBTDecorator_IsHealthLow()
{
	NodeName = "Is Health Low";
	Threshold = 5;
}

bool UBTDecorator_IsHealthLow::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return false;
	
	if (UHealthComponent const* StaminaComp { AIController->GetPawn()->GetComponentByClass<UHealthComponent>() })
	{
		return StaminaComp->GetHealth() < Threshold;
	}
	return false;
}
