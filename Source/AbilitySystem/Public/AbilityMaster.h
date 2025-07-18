// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityInterface.h"
#include "GameFramework/Actor.h"
#include "AbilityMaster.generated.h"

UCLASS(Abstract)
class ABILITYSYSTEM_API AAbilityMaster : public AActor, public IAbilityInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbilityMaster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Settings
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	FTagsAbility Ability;

	UPROPERTY(BlueprintReadOnly, Category = "Settings")
	bool bIsAvailable = true;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Settings")
	float Cooldown = 0.f;
	// End Settings

	//Interface
	void EndAbility_Implementation();
	bool IsAccessible_Implementation();
	virtual FTagsAbility GetTags() override;


	

private:
	
	FTimerHandle TimerCooldownHandle;
	UFUNCTION(BlueprintCallable,  Category = "Cooldown")
	void StartCooldown();
	void EndCooldown();
};
