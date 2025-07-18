// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "AbilityManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ABILITYSYSTEM_API UAbilityManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAbilityManager();

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void AddAbility(TSubclassOf<AActor> Ability );

	
	
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void ActivateAbility(FGameplayTag AbilityTag, bool bPressed);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void DeleteAbility(FGameplayTag AbilityTag);
	

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	
	bool IsAccessible(AActor* Ability);
	void CheckAndCancelAbility(AActor* Ability);

	void DeleteTagsInAbilityActive(FGameplayTag AbilityTag);
	
	TMap<FGameplayTag, AActor*> Abilities;
	FGameplayTagContainer AbilityActive;
};
