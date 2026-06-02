#include "BTTask_CollectNearbyItem.h"

#include <../PluginUtils/ZombiePluginUtils.h>
#include "LinKyawKhineZombieRuntime/StudentPerceptor.h"

#include <GameAI_Zombie/Village/House/House.h>
#include <GameAI_Zombie/Items/BaseItem.h>

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>



UBTTask_CollectNearbyItem::UBTTask_CollectNearbyItem()
{
	NodeName = "Collect Nearby Item";
	HouseKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_CollectNearbyItem, HouseKey), AHouse::StaticClass());
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_CollectNearbyItem, BlackboardKey), ABaseItem::StaticClass());
}

EBTNodeResult::Type UBTTask_CollectNearbyItem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn())
	{
		return EBTNodeResult::Failed;
	}
	
	UBlackboardComponent const* BlackboardComp = OwnerComp.GetBlackboardComponent();
	
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}
	
	AHouse const* House = Cast<AHouse>(BlackboardComp->GetValueAsObject(HouseKey.SelectedKeyName));
	FVector SurvivorLocation = AIController->GetPawn()->GetActorLocation();
	
	UStudentPerceptor* PerceptorComp { AIController->GetPawn()->GetComponentByClass<UStudentPerceptor>() };
	
	auto ItemsInHouse { PluginUtils::GetAllItemsInHouse(House, PerceptorComp->GetPerceivedItems()) };
	
	if (ItemsInHouse.IsEmpty())
	{
		return EBTNodeResult::Failed;
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, ItemsInHouse[0]);
		return EBTNodeResult::Succeeded;
	}
}
