// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActorFireBlast.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API AGATargetActorFireBlast : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
public:
	virtual void StartTargeting(UGameplayAbility* Ability)override;
	virtual void ConfirmTargetingAndContinue();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn=true), Category = Radius)
	float Radius;
};
