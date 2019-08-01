// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"

/**
 * 
 */
//����һ��Multicast�ಥ���͵�ί�У����洫����������
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeDelegate, float, Health, float, MaxHealth);
UCLASS()
class ABILITYSYSTEM_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	//����һ�����캯��
	UBaseAttributeSet();
	//����ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData MaxHealth;
	//FGameplayAttributeDataӵ��BaseValue��AttributeValue����ֵ
	//ħ��ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData Mana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData MaxMana;
	//����ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData Strength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData MaxStrength;
	//������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData AttackDamage;

	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData Armor;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)override;
	//�����delegate������Ҫ�Ż�
	FOnHealthChangeDelegate OnHealthChange;
	FOnHealthChangeDelegate OnManaChange;
	FOnHealthChangeDelegate OnStrengthChange;
};
