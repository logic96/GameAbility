// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "BaseCharacter.h"
UBaseAttributeSet::UBaseAttributeSet() :Health(200.f),MaxHealth(200.f)
,Mana(150.f),MaxMana(150.f),Strength(250.f),MaxStrength(250.f),AttackDamage(20.f),Armor(5.f)
{
	//构造函数用于初始化Health
}
//PostGameplayEffectExecute是在属性值发生修改后自动调用
void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UBaseAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UBaseAttributeSet, Health))) {
		//这一段的逻辑放在PreAttributeChange（这个是在属性值发生修改前调用）更好一些
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetCurrentValue()));

		//暂时先打印修改后的属性值
	//	UE_LOG(LogTemp, Warning, TEXT("Oh,i got som damagem,now my health is:%f"),Health.GetCurrentValue());
		//当属性值发生修改的时候广播出去
		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
		ABaseCharacter* CharacterOwner = Cast<ABaseCharacter>(GetOwningActor());
		if (Health.GetCurrentValue() == MaxHealth.GetCurrentValue())
		{
			if (CharacterOwner) {
				CharacterOwner->AddGameplyTag(CharacterOwner->FullHealthTag);
			}
		}
		else {
			if (CharacterOwner) {
				CharacterOwner->RemoveGameplyTag(CharacterOwner->FullHealthTag);
			}
		}
	}
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UBaseAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UBaseAttributeSet, Mana))) {
		//这一段的逻辑放在PreAttributeChange（这个是在属性值发生修改前调用）更好一些
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.f, MaxMana.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.f, MaxMana.GetCurrentValue()));
		//当属性值发生修改的时候广播出去
		OnManaChange.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	}
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UBaseAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UBaseAttributeSet, Strength))) {
		//这一段的逻辑放在PreAttributeChange（这个是在属性值发生修改前调用）更好一些
		Strength.SetCurrentValue(FMath::Clamp(Strength.GetCurrentValue(), 0.f, MaxStrength.GetCurrentValue()));
		Strength.SetBaseValue(FMath::Clamp(Strength.GetBaseValue(), 0.f, MaxStrength.GetCurrentValue()));
		//当属性值发生修改的时候广播出去
		OnStrengthChange.Broadcast(Strength.GetCurrentValue(), MaxStrength.GetCurrentValue());
	}
}
