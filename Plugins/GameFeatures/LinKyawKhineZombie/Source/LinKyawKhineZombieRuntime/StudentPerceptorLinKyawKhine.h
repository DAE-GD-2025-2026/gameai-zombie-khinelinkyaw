// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Damage.h"

#include <GameAI_Zombie/Items/ItemType.h>
#include <GameAI_Zombie/PurgeZones/PurgeZone.h>

#include "StudentPerceptorLinKyawKhine.generated.h"

class ABaseZombie;
class AHouse;
class ABaseItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LINKYAWKHINEZOMBIERUNTIME_API UStudentPerceptorLinKyawKhine : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY() TSet<TObjectPtr<ABaseItem>> Items;
	UPROPERTY() TSet<TObjectPtr<ABaseZombie>> NearbyZombies;
	UPROPERTY() TSet<TObjectPtr<AHouse>> NearbyHouses;
	UPROPERTY() TSet<TObjectPtr<AHouse>> VisitedHouses;
	UPROPERTY() TSet<TObjectPtr<APurgeZone>> PurgeZones;
	
	UPROPERTY() TObjectPtr<AHouse> ActiveHouse;
	
	UFUNCTION()
	void UpdateClosestHouse() const;
	
	UFUNCTION()
	void UpdateClosestZombie() const;
	
	template<typename T>
	TObjectPtr<T> GetClosestItem(TSet<TObjectPtr<T>>const& Actors) const;
	
	template <typename T>
	void RemoveNullPtrsFromSet(TSet<TObjectPtr<T>>& Actors);
	
	template<typename T>
	TArray<TObjectPtr<T>> GetSortedObjects(TSet<TObjectPtr<T>> const& Actors) const;
	
public:
	// Sets default values for this component's properties
	UStudentPerceptorLinKyawKhine();
	
	TSet<TObjectPtr<ABaseItem>> GetPerceivedItems();
	TSet<TObjectPtr<ABaseItem>> GetPerceivedItemsByType(EItemType ItemType);
	
	TArray<TObjectPtr<APurgeZone>> GetSortedPurgeZones() const;
	TArray<TObjectPtr<ABaseZombie>> GetSortedZombies() const;
	
	void MarkHouseAsVisited(TObjectPtr<AHouse> House);
	void ClearVisitedHouses();
	
	virtual void BeginPlay() override;
	void SetPurgeZoneDetectionBlackboard();

	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};

template <typename T>
void UStudentPerceptorLinKyawKhine::RemoveNullPtrsFromSet(TSet<TObjectPtr<T>>& Actors)
{
	for (auto Iter { Actors.CreateIterator() }; Iter; ++Iter)
	{
		if (*Iter == nullptr)
		{
			Iter.RemoveCurrent();
		}
	}
}

template <typename T>
TArray<TObjectPtr<T>> UStudentPerceptorLinKyawKhine::GetSortedObjects(TSet<TObjectPtr<T>> const& Actors) const
{
	TArray<TObjectPtr<T>> Result{};
	
	for (auto const Actor : Actors)
	{
		if (Actor != nullptr)
		{
			Result.Add(Actor);
		}
	}
	
	FVector SurvivorLocation { GetOwner()->GetActorLocation() };
	
	Result.Sort([SurvivorLocation](TObjectPtr<T> const& ActorA, TObjectPtr<T> const& ActorB)
	{
		FVector ActorALocation{ ActorA->GetActorLocation() };
		FVector ActorBLocation{ ActorB->GetActorLocation() };
		return (ActorALocation - SurvivorLocation).SizeSquared() < (ActorBLocation - SurvivorLocation).SizeSquared();
	});
	
	return Result;
}

template <typename T>
TObjectPtr<T> UStudentPerceptorLinKyawKhine::GetClosestItem(TSet<TObjectPtr<T>> const& Actors) const
{
	FVector SurvivorLocation { GetOwner()->GetActorLocation() };
	
	auto const MinElementPtr { Algo::MinElementBy(Actors, [SurvivorLocation](TObjectPtr<T> const& Actor)
	{
		FVector const ActorLocation{ Actor->GetActorLocation() - SurvivorLocation };
		
		return ActorLocation.Size();
	})};
	
	if (MinElementPtr)
	{
		return MinElementPtr->Get();
	}
	
	return nullptr;
}
