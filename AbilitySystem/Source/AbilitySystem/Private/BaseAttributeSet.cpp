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
	//���캯�����ڳ�ʼ��Health
}
//PostGameplayEffectExecute��������ֵ�����޸ĺ��Զ�����
void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UBaseAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UBaseAttributeSet, Health))) {
		//��һ�ε��߼�����PreAttributeChange�������������ֵ�����޸�ǰ���ã�����һЩ
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetCurrentValue()));

		//��ʱ�ȴ�ӡ�޸ĺ������ֵ
	//	UE_LOG(LogTemp, Warning, TEXT("Oh,i got som damagem,now my health is:%f"),Health.GetCurrentValue());
		//������ֵ�����޸ĵ�ʱ��㲥��ȥ
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
		//��һ�ε��߼�����PreAttributeChange�������������ֵ�����޸�ǰ���ã�����һЩ
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.f, MaxMana.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.f, MaxMana.GetCurrentValue()));
		//������ֵ�����޸ĵ�ʱ��㲥��ȥ
		OnManaChange.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	}
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UBaseAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UBaseAttributeSet, Strength))) {
		//��һ�ε��߼�����PreAttributeChange�������������ֵ�����޸�ǰ���ã�����һЩ
		Strength.SetCurrentValue(FMath::Clamp(Strength.GetCurrentValue(), 0.f, MaxStrength.GetCurrentValue()));
		Strength.SetBaseValue(FMath::Clamp(Strength.GetBaseValue(), 0.f, MaxStrength.GetCurrentValue()));
		//������ֵ�����޸ĵ�ʱ��㲥��ȥ
		OnStrengthChange.Broadcast(Strength.GetCurrentValue(), MaxStrength.GetCurrentValue());
	}
}
