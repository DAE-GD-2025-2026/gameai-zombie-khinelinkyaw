#include "BTDecorator_IsStaminaLow.h"

#include <GameAI_Zombie/Common/StaminaComponent.h>

#include "AIController.h"

UBTDecorator_IsStaminaLow::UBTDecorator_IsStaminaLow()
{
	NodeName = "Is Stamina Low";
	Threshold = 5;
}

bool UBTDecorator_IsStaminaLow::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return false;
	
	if (UStaminaComponent const* StaminaComp { AIController->GetPawn()->GetComponentByClass<UStaminaComponent>() })
	{
		return StaminaComp->GetCurrentStamina() < Threshold;
	}
	return false;
}
