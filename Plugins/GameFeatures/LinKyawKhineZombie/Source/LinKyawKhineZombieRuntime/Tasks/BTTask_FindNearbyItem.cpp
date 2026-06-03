#include "BTTask_FindNearbyItem.h"

#include <../PluginUtils/ZombiePluginUtils.h>
#include "LinKyawKhineZombieRuntime/StudentPerceptor.h"

#include <GameAI_Zombie/Village/House/House.h>
#include <GameAI_Zombie/Items/BaseItem.h>

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>

UBTTask_FindNearbyItem::UBTTask_FindNearbyItem()
{
	NodeName = "Find Nearby Item";
	HouseKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindNearbyItem, HouseKey), AHouse::StaticClass());
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindNearbyItem, BlackboardKey), ABaseItem::StaticClass());
}

EBTNodeResult::Type UBTTask_FindNearbyItem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return EBTNodeResult::Failed;
	
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return EBTNodeResult::Failed;
	
	AHouse const* House = Cast<AHouse>(BlackboardComp->GetValueAsObject(HouseKey.SelectedKeyName));
	
	if (!House) return EBTNodeResult::Failed;
	
	UStudentPerceptor* PerceptorComp { AIController->GetPawn()->GetComponentByClass<UStudentPerceptor>() };
	
	auto ItemsInHouse { PluginUtils::GetAllItemsInHouse(House, PerceptorComp->GetPerceivedItems()) };
	
	if (ItemsInHouse.IsEmpty())
	{
		return EBTNodeResult::Failed;
	}
	else
	{
		BlackboardComp->SetValueAsObject(BlackboardKey.SelectedKeyName, ItemsInHouse[0]);
		return EBTNodeResult::Succeeded;
	}
}
