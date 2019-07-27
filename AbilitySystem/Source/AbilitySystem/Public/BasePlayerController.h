// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AbilityTypes.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "PlayControllerBase")
		void AddAbilityToUI(FGameplayAbilityInfo AbilityInfo);
};
