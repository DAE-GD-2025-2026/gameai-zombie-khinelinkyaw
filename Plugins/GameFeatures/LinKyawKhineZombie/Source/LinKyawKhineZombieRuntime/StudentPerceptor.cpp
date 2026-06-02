// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptor.h"

#include <GameAI_Zombie/Items/BaseItem.h>
#include <GameAI_Zombie/Survivor/SurvivorPawn.h>
#include <GameAI_Zombie/Village/House/House.h>

#include "Common/InventoryComponent.h"

#include <AIController.h>
#include <Algo/MinElement.h>
#include <Math/Box.h>

#include <BehaviorTree/BlackboardComponent.h>

bool UStudentPerceptor::IsInHouse(TObjectPtr<AHouse> const& House) const
{
	FVector HouseOrigin{}, HouseBoxExtend{}, SurvivorOrigin{}, SurvivorBoxExtend{};
	House->GetActorBounds(false, HouseOrigin, HouseBoxExtend);
	GetOwner()->GetActorBounds(false, SurvivorOrigin, SurvivorBoxExtend);
	
	FBox const HouseBox { FBox::BuildAABB(HouseOrigin, HouseBoxExtend) };
	FBox const OwnerBox { FBox::BuildAABB(SurvivorOrigin, SurvivorBoxExtend) };
	
	return HouseBox.Intersect(OwnerBox);
}

void UStudentPerceptor::UpdateSurvivorTargetLocation() const
{
	if (!NearbyHouses.IsEmpty())
	{
		auto HousePtr { GetClosestItem<AHouse>(NearbyHouses) };
		APawn* OwningPawn { Cast<APawn>(GetOwner())};
		AAIController* AIController  = Cast<AAIController>(OwningPawn->GetController());
		auto BBComp {AIController->GetBlackboardComponent()};
		
		if (IsInHouse(HousePtr))
		{
			if (Items.IsEmpty()) return;
			
			auto ItemPtr { GetClosestItem<ABaseItem>(Items) };
			BBComp->SetValueAsVector(TEXT("TargetLocation"), ItemPtr->GetActorLocation());
			BBComp->SetValueAsObject(TEXT("ActiveTarget"), ItemPtr);
		}
		else
		{
			BBComp->SetValueAsVector(TEXT("TargetLocation"), HousePtr->GetActorLocation());
			BBComp->SetValueAsObject(TEXT("ActiveTarget"), HousePtr);
		}
	}
}

void UStudentPerceptor::UpdateClosestHouse() const
{
	if (!NearbyHouses.IsEmpty())
	{
		auto HousePtr { GetClosestItem<AHouse>(NearbyHouses) };
		APawn* OwningPawn { Cast<APawn>(GetOwner())};
		AAIController* AIController  = Cast<AAIController>(OwningPawn->GetController());
		auto BBComp {AIController->GetBlackboardComponent()};

		BBComp->SetValueAsObject(TEXT("ClosestHouse"), HousePtr);
	}
}

bool UStudentPerceptor::IsHealthNeeded() const
{
	if (UHealthComponent const* HealthComp = GetOwner()->GetComponentByClass<UHealthComponent>())
	{
		auto CurrentHealth {HealthComp->GetHealth()};
		if (CurrentHealth < 5)
		{
			return true;
		}
	}
	return false;
}

bool UStudentPerceptor::IsFoodNeeded() const
{
	if (UStaminaComponent const* StamComp = GetOwner()->GetComponentByClass<UStaminaComponent>())
	{
		auto CurrentStamina {StamComp->GetCurrentStamina()};
		if (CurrentStamina < 5)
		{
			return true;
		}
	}
	return false;
}

bool UStudentPerceptor::IsAGunEquipped() const
{
	if (UInventoryComponent const* InvComp = GetOwner()->GetComponentByClass<UInventoryComponent>())
	{
		for (auto InvItems { InvComp->GetInventory() }; auto const  InvItem : InvItems)
		{
			if (InvItem->GetItemType() == EItemType::Shotgun or InvItem->GetItemType() == EItemType::Pistol)
			{
				return true;
			}
		}
	}
	return false;
}

UStudentPerceptor::UStudentPerceptor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStudentPerceptor::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptor::OnPerceptionUpdated);
	}
}

void UStudentPerceptor::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Something!")));
	
	//auto blackBoard {GetOwner()->GetComponentByClass<UBlackboardComponent>()};

	if (ABaseItem* Item { Cast<ABaseItem>(Actor) })
	{
		Items.Add(Item);
		
		switch (Item->GetItemType())
		{
		case EItemType::Food:
			{
				FoodItems.Add(Item);
				break;
			}
		case EItemType::Medkit:
			{
				MedkitItems.Add(Item);
				break;
			}
		case EItemType::Shotgun:
			{
				Shotguns.Add(Item);
				break;
			}
		case EItemType::Pistol:
			{
				Pistols.Add(Item);
				break;
			}
		case EItemType::Garbage:
			{
				GarbageItems.Add(Item);
				break;
			}
		}
	}
	
	if (AHouse* House { Cast<AHouse>(Actor) })
	{
		NearbyHouses.Add(House);
		UpdateClosestHouse();
	}
	
	//UpdateSurvivorTargetLocation();
}
