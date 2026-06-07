#include "BTDecorator_AreItemsInHouse.h"

#include "BehaviorTree/BlackboardComponent.h"

#include <GameAI_Zombie/Village/House/House.h>
#include <GameAI_Zombie/Items/BaseItem.h>

#include "LinKyawKhineZombieRuntime/StudentPerceptorLinKyawKhine.h"
#include <../PluginUtils/ZombiePluginUtils.h>

#include "AIController.h"

UBTDecorator_AreItemsInHouse::UBTDecorator_AreItemsInHouse()
{
	NodeName = "Are Items in House";
	HouseKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_AreItemsInHouse, HouseKey), AHouse::StaticClass());
}

bool UBTDecorator_AreItemsInHouse::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return EBTNodeResult::Failed;
	
	UBlackboardComponent const* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return false;
	
	AHouse const* House = Cast<AHouse>(BlackboardComp->GetValueAsObject(HouseKey.SelectedKeyName));
	//AActor const* Survivor = Cast<AActor>(BlackboardComp->GetValueAsObject(SurvivorKey.SelectedKeyName));
	if (House == nullptr) return false;
	
	UStudentPerceptorLinKyawKhine* PerceptorComp { AIController->GetPawn()->GetComponentByClass<UStudentPerceptorLinKyawKhine>() };
	
	FVector HouseOrigin{}, HouseBoxExtend{};
	House->GetActorBounds(false, HouseOrigin, HouseBoxExtend);
	FBox const HouseBox { FBox::BuildAABB(HouseOrigin, HouseBoxExtend) };
	
	auto const ItemsInHouse { PluginUtils::GetAllItemsInHouse(House, PerceptorComp->GetPerceivedItems()) };
	
	return !ItemsInHouse.IsEmpty();
}
