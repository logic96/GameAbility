// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActorGroundSelect.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API AGATargetActorGroundSelect : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
public:
	AGATargetActorGroundSelect();
	/** Initialize and begin targeting logic  */
	virtual void StartTargeting(UGameplayAbility* Ability)override;
	/** Requesting targeting data, but not necessarily stopping/destroying the task. Useful for external target data requests. */
	virtual void ConfirmTargetingAndContinue();

	virtual void Tick(float DeltaSeconds)override;
	UFUNCTION(BlueprintCallable, Category = GroundSelect)
	bool GetPlayerLookingPoint(FVector& OutViewPoint);
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(ExposeOnSpawn), Category = Radius)
	float Radius;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = GroundSelect)
	class	UDecalComponent* Decal;
	class USceneComponent* RootComp;
};
