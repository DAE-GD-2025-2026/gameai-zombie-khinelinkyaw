// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptor.h"

#include <GameAI_Zombie/Items/BaseItem.h>
#include <GameAI_Zombie/Survivor/SurvivorPawn.h>
#include <GameAI_Zombie/Village/House/House.h>
#include <GameAI_Zombie/Zombies/BaseZombie.h>

#include <AIController.h>
#include <Algo/MinElement.h>
#include <Math/Box.h>

#include <BehaviorTree/BlackboardComponent.h>

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

void UStudentPerceptor::UpdateClosestZombie() const
{
	if (NearbyZombies.IsEmpty()) return;
	
	auto ZombiePtr{ GetClosestItem<ABaseZombie>(NearbyZombies) };
	APawn* OwningPawn { Cast<APawn>(GetOwner())};
	AAIController* AIController  = Cast<AAIController>(OwningPawn->GetController());
	auto BBComp {AIController->GetBlackboardComponent()};

	BBComp->SetValueAsObject(TEXT("NearestZombie"), ZombiePtr);
	BBComp->SetValueAsBool(TEXT("ZombieDetected"), true);
}

UStudentPerceptor::UStudentPerceptor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

TSet<TObjectPtr<ABaseItem>> UStudentPerceptor::GetPerceivedItems()
{
	TSet<TObjectPtr<ABaseItem>> Result{};
	
	for (auto const Item: Items)
	{
		if (Item == nullptr or Item->IsHidden()) continue;
		Result.Add(Item);
	}
	
	return Result;
}

TSet<TObjectPtr<ABaseItem>> UStudentPerceptor::GetPerceivedItemsByType(EItemType ItemType)
{
	TSet<TObjectPtr<ABaseItem>> Result{};
	
	for (auto const Item: Items)
	{
		if (Item == nullptr or Item->IsHidden()) continue;
		
		if (Item->GetItemType() == ItemType)
		{
			Result.Add(Item);
		}
	}
	
	return Result;
}

TArray<TObjectPtr<APurgeZone>> UStudentPerceptor::GetSortedPurgeZones()
{
	TArray<TObjectPtr<APurgeZone>> Result{};
	
	for (auto const PurgeZone : PurgeZones)
	{
		if (PurgeZone != nullptr)
		{
			Result.Add(PurgeZone);
		}
	}
	
	FVector SurvivorLocation { GetOwner()->GetActorLocation() };
	
	Result.Sort([SurvivorLocation](TObjectPtr<APurgeZone> const& PurgeZoneA, TObjectPtr<APurgeZone> const& PurgeZoneB)
	{
		FVector PurgeZoneALocation{ PurgeZoneA->GetActorLocation() };
		FVector PurgeZoneBLocation{ PurgeZoneB->GetActorLocation() };
		return (PurgeZoneALocation - SurvivorLocation).SizeSquared() < (PurgeZoneBLocation - SurvivorLocation).SizeSquared();
	});
	
	return Result;
}

void UStudentPerceptor::MarkHouseAsVisited(TObjectPtr<AHouse> House)
{
	VisitedHouses.Add(House);
	NearbyHouses.Remove(House);
}

void UStudentPerceptor::ClearVisitedHouses()
{
	VisitedHouses.Empty();
}

void UStudentPerceptor::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptor::OnPerceptionUpdated);
	}
}

void UStudentPerceptor::SetPurgeZoneDetectionBlackboard()
{
	APawn const* OwningPawn { Cast<APawn>(GetOwner())};
	AAIController* AIController  = Cast<AAIController>(OwningPawn->GetController());
	auto const BBComp {AIController->GetBlackboardComponent()};
	BBComp->SetValueAsBool(TEXT("PurgeZoneDetected"), true);
}

void UStudentPerceptor::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Something!")));
	
	if (ABaseItem* Item { Cast<ABaseItem>(Actor) })
	{
		RemoveNullPtrsFromSet<ABaseItem>(Items);
		Items.Add(Item);
	}
	
	if (AHouse* House { Cast<AHouse>(Actor) })
	{
		if (!VisitedHouses.Contains(House))
		{
			RemoveNullPtrsFromSet<AHouse>(NearbyHouses);
			RemoveNullPtrsFromSet<AHouse>(VisitedHouses);
			NearbyHouses.Add(House);
			UpdateClosestHouse();
		}
	}
	
	if (ABaseZombie* Zombie { Cast<ABaseZombie>(Actor) })
	{
		RemoveNullPtrsFromSet<ABaseZombie>(NearbyZombies);
		NearbyZombies.Add(Zombie);
		UpdateClosestZombie();
	}
	
	if (APurgeZone* PurgeZone { Cast<APurgeZone>(Actor) })
	{
		RemoveNullPtrsFromSet<APurgeZone>(PurgeZones);
		PurgeZones.Add(PurgeZone);
		SetPurgeZoneDetectionBlackboard();
	}
}
