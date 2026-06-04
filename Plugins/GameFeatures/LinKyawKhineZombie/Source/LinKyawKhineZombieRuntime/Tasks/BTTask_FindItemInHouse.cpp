#include "BTTask_FindItemInHouse.h"

#include <LinKyawKhineZombieRuntime/PluginUtils/ZombiePluginUtils.h>
#include "LinKyawKhineZombieRuntime/StudentPerceptor.h"

#include <GameAI_Zombie/Common/InventoryComponent.h>
#include <GameAI_Zombie/Items/BaseItem.h>

#include <AIController.h>
#include <BehaviorTree/BlackboardComponent.h>


UBTTask_FindItemInHouse::UBTTask_FindItemInHouse()
{
	NodeName = "Find Item In House";
	HouseKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindItemInHouse, HouseKey), AHouse::StaticClass());
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_FindItemInHouse, BlackboardKey), ABaseItem::StaticClass());
}

EBTNodeResult::Type UBTTask_FindItemInHouse::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
