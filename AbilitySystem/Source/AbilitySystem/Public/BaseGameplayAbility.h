// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityTypes.h"
#include "BaseGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityBase")
		UMaterialInstance* UIMaterial;
	UFUNCTION(BlueprintCallable)
		FGameplayAbilityInfo GetAbilityInfo();
};
