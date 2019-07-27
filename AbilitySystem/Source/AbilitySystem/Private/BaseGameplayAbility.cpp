// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameplayAbility.h"

FGameplayAbilityInfo UBaseGameplayAbility::GetAbilityInfo()
{
	UGameplayEffect* CoolDownEffect = GetCooldownGameplayEffect();
	UGameplayEffect* CostEffect = GetCostGameplayEffect();
	if (CoolDownEffect && CostEffect) {	
		float CoolDownDuration = 0;
		float Cost = 0;
		EAbilityCostType CostType;
		CoolDownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CoolDownDuration);		
		if (CostEffect->Modifiers.Num() > 0)
		{
			FGameplayModifierInfo EffectInfo = CostEffect->Modifiers[0];
			EffectInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);
			FGameplayAttribute CostAttr = EffectInfo.Attribute;
				FString AttributeName = CostAttr.AttributeName;
				if (AttributeName == "Health")
				{
					CostType = EAbilityCostType::Health;
				}
				else if (AttributeName == "Mana")
				{
					CostType = EAbilityCostType::Mana;
				}
				else if (AttributeName == "Strength")
				{
					CostType = EAbilityCostType::Strength;
				}
				//确保获取了所有的信息
				return FGameplayAbilityInfo(CoolDownDuration, Cost, CostType, UIMaterial, GetClass());
		}
	}
	return  FGameplayAbilityInfo();
}
