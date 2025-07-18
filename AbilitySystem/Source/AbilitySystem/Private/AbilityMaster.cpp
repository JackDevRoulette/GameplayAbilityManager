// Fill out your copyright notice in the Description page of Project Settings.



#include "AbilityMaster.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManager.h"




// Sets default values
AAbilityMaster::AAbilityMaster()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AAbilityMaster::BeginPlay()
{
	Super::BeginPlay();
	
}
//Interface
void AAbilityMaster::EndAbility_Implementation()
{
	StartCooldown();
}

bool AAbilityMaster::IsAccessible_Implementation()
{
	return bIsAvailable;
}

FTagsAbility AAbilityMaster::GetTags()
{
	return Ability;
}
//End Interface
void AAbilityMaster::StartCooldown()
{
	if (Cooldown > 0)
	{
		bIsAvailable = false;
		GetWorldTimerManager().SetTimer(TimerCooldownHandle, this, &AAbilityMaster::EndCooldown, Cooldown, false);
	}
}

void AAbilityMaster::EndCooldown()
{
	TimerCooldownHandle.Invalidate();
	bIsAvailable = true;
}
