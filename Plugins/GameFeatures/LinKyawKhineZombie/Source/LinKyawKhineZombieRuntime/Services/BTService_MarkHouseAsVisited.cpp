#include "BTService_MarkHouseAsVisited.h"

#include <GameAI_Zombie/Village/House/House.h>

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LinKyawKhineZombieRuntime/StudentPerceptorLinKyawKhine.h"

UBTService_MarkHouseAsVisited::UBTService_MarkHouseAsVisited()
{
	NodeName = "Mark House as Visited";
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTService_MarkHouseAsVisited, BlackboardKey), AHouse::StaticClass());
}

void UBTService_MarkHouseAsVisited::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	AAIController const* AIController = OwnerComp.GetAIOwner();
	if (!AIController || !AIController->GetPawn()) return;

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return;
	
	AHouse* House = Cast<AHouse>(BlackboardComp->GetValueAsObject(BlackboardKey.SelectedKeyName));
	UStudentPerceptorLinKyawKhine* PerceptorComp { AIController->GetPawn()->GetComponentByClass<UStudentPerceptorLinKyawKhine>() };
	
	if (House)
	{
		PerceptorComp->MarkHouseAsVisited(House);
		BlackboardComp->SetValueAsObject(BlackboardKey.SelectedKeyName, nullptr);
	}
}
