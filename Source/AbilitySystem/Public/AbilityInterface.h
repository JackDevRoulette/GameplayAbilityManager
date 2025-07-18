// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "AbilityInterface.generated.h"

USTRUCT(BlueprintType)
struct FTagsAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Tags")
	FGameplayTag AbilityTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Tags")
	FGameplayTagContainer CancelAbility;
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Tags")
	FGameplayTagContainer ActivationRequiredTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Tags")
	FGameplayTagContainer ActivationBlockedTag;
	
};

// This class does not need to be modified.
UINTERFACE()
class UAbilityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ABILITYSYSTEM_API IAbilityInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability")
	void ActivateAbility();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability")
	void EndAbility();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability")
	bool IsAccessible();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability")
	void CancelAbility();
	
	virtual FTagsAbility GetTags() = 0;
};
