// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilityTypes.generated.h"

//表示当前能力的消耗类型
UENUM(BlueprintType)
enum class EAbilityCostType :uint8 {
	Health,
	Mana,
	Strength
};

USTRUCT(BlueprintType)
struct FGameplayAbilityInfo {
	GENERATED_BODY()

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		float CooldownDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		float Cost;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		EAbilityCostType CostType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		UMaterialInstance* UIMat; //slot图标
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		TSubclassOf<class UBaseGameplayAbility>AbilityClass; //对应的AbilityClass类
	//两个构造函数
	FGameplayAbilityInfo();
	FGameplayAbilityInfo(float InCooldownDuration,float InCost, EAbilityCostType InCostType, UMaterialInstance* InUIMat, TSubclassOf<class UBaseGameplayAbility>InAbilityClass);
};
