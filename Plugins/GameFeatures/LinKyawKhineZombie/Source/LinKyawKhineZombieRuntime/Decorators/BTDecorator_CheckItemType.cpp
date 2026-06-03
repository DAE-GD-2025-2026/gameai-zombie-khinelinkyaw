#include "BTDecorator_CheckItemType.h"

#include <GameAI_Zombie/Items/BaseItem.h>

#include <BehaviorTree/BlackboardComponent.h>

UBTDecorator_CheckItemType::UBTDecorator_CheckItemType()
{
	NodeName = "Check Item Type";
	ItemKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_CheckItemType, ItemKey), ABaseItem::StaticClass());
}

bool UBTDecorator_CheckItemType::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent const* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp) return false;
	
	ABaseItem const* Item = Cast<ABaseItem>(BlackboardComp->GetValueAsObject(ItemKey.SelectedKeyName));
	
	if (!Item) return false;
	
	return Item->GetItemType() == ItemType;
}
