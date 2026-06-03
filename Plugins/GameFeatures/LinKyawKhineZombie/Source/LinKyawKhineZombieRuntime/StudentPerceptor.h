// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Damage.h"
#include "StudentPerceptor.generated.h"

class ABaseZombie;
class AHouse;
class ABaseItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LINKYAWKHINEZOMBIERUNTIME_API UStudentPerceptor : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY() TSet<TObjectPtr<ABaseItem>> Items;
	UPROPERTY() TSet<TObjectPtr<ABaseZombie>> NearbyZombies;
	UPROPERTY() TSet<TObjectPtr<AHouse>> NearbyHouses;
	UPROPERTY() TSet<TObjectPtr<AHouse>> VisitedHouses;
	
	UPROPERTY() TObjectPtr<AHouse> ActiveHouse;
	
	UFUNCTION()
	void UpdateClosestHouse() const;
	
	UFUNCTION()
	void UpdateClosestZombie() const;
	
	template<typename T>
	TObjectPtr<T> GetClosestItem(TSet<TObjectPtr<T>>const& Actors) const;
	
	template <typename T>
	void RemoveNullPtrsFromSet(TSet<TObjectPtr<T>>& Actors);
	
public:
	// Sets default values for this component's properties
	UStudentPerceptor();
	
	TSet<TObjectPtr<ABaseItem>>& GetPerceivedItems() { return Items; }
	
	void MarkHouseAsVisited(TObjectPtr<AHouse> House);
	void ClearVisitedHouses();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};

template <typename T>
void UStudentPerceptor::RemoveNullPtrsFromSet(TSet<TObjectPtr<T>>& Actors)
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
TObjectPtr<T> UStudentPerceptor::GetClosestItem(TSet<TObjectPtr<T>> const& Actors) const
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
