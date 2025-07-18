// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityManager.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "AbilityInterface.h"





// Sets default values for this component's properties
UAbilityManager::UAbilityManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

// Called when the game starts
void UAbilityManager::BeginPlay()
{
	Super::BeginPlay();
}

void UAbilityManager::AddAbility(TSubclassOf<AActor> Ability)
{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
	
		AActor* NewAbility = GetWorld()->SpawnActor<AActor>(Ability, GetOwner()->GetActorTransform(),SpawnParams);
	
		if (NewAbility && NewAbility->GetClass()->ImplementsInterface(UAbilityInterface::StaticClass()))
		{
			IAbilityInterface* AbilityI = Cast<IAbilityInterface>(NewAbility);
			FTagsAbility AbilityTags = AbilityI->GetTags();
		
			Abilities.Add(AbilityTags.AbilityTag, NewAbility);
		}
		else
		{
			NewAbility->Destroy();
		}
}

void UAbilityManager::DeleteTagsInAbilityActive(FGameplayTag AbilityTag)
{
	if (AbilityActive.HasTag(AbilityTag))
	{
		AbilityActive.RemoveTag(AbilityTag);
	}
}

void UAbilityManager::ActivateAbility(FGameplayTag AbilityTag, bool bPressed)
{
	if (Abilities.Contains(AbilityTag))
	{
		AActor* Ability = Abilities[AbilityTag];
		
		if (IsAccessible(Ability))
		{
			CheckAndCancelAbility(Ability);
			
			if (bPressed)
			{
				IAbilityInterface::Execute_ActivateAbility(Ability);
				AbilityActive.AddTag(AbilityTag);
			}
			else
			{
				IAbilityInterface::Execute_EndAbility(Ability);
				DeleteTagsInAbilityActive(AbilityTag);
			}
		}
	}
}

void UAbilityManager::DeleteAbility(FGameplayTag AbilityTag)
{
	if (Abilities.Contains(AbilityTag))
	{
		AActor* Ability = Abilities[AbilityTag];
		DeleteTagsInAbilityActive(AbilityTag);
		Abilities.Remove(AbilityTag);
		Ability->Destroy();
	}
}


bool UAbilityManager::IsAccessible(AActor* Ability)
{
	IAbilityInterface* AbilityI = Cast<IAbilityInterface>(Ability);
	FTagsAbility AbilityTags = AbilityI->GetTags();

	
	bool BlockedTag = AbilityActive.HasAny(AbilityTags.ActivationBlockedTag);
	bool RequiredTag = AbilityActive.HasAll(AbilityTags.ActivationRequiredTag);
	
	
	return IAbilityInterface::Execute_IsAccessible(Ability) && !BlockedTag && RequiredTag;
}

void UAbilityManager::CheckAndCancelAbility(AActor* Ability)
{
	IAbilityInterface* AbilityI = Cast<IAbilityInterface>(Ability);
	FTagsAbility AbilityTags = AbilityI->GetTags();

	for (const FGameplayTag& CancelTag : AbilityTags.CancelAbility)
	{
		if (AbilityActive.HasTag(CancelTag))
		{
			IAbilityInterface::Execute_CancelAbility(Abilities[CancelTag]);
			DeleteTagsInAbilityActive(CancelTag);
		}
	}
}
