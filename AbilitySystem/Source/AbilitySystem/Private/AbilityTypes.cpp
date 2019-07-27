// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTypes.h"

FGameplayAbilityInfo::FGameplayAbilityInfo()
:CooldownDuration(0.f),
Cost(0),
CostType(EAbilityCostType::Mana),
UIMat(nullptr),
AbilityClass(nullptr)
{
}

FGameplayAbilityInfo::FGameplayAbilityInfo(float InCooldownDuration, float InCost, EAbilityCostType InCostType, UMaterialInstance* InUIMat, TSubclassOf<class UBaseGameplayAbility> InAbilityClass)
:CooldownDuration(InCooldownDuration),
Cost(InCost),
CostType(InCostType),
UIMat(InUIMat),
AbilityClass(InAbilityClass)
{
}
