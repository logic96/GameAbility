// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "BaseAttributeSet.generated.h"

/**
 * 
 */
//创建一个Multicast多播类型的委托，里面传入两个参数
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeDelegate, float, Health, float, MaxHealth);
UCLASS()
class ABILITYSYSTEM_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	//创建一个构造函数
	UBaseAttributeSet();
	//生命值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData MaxHealth;
	//FGameplayAttributeData拥有BaseValue和AttributeValue两个值
	//魔法值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData Mana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData MaxMana;
	//力量值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData Strength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData MaxStrength;
	//攻击力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData AttackDamage;

	//护甲
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttributeSet)
		FGameplayAttributeData Armor;

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)override;
	//这里的delegate名称需要优化
	FOnHealthChangeDelegate OnHealthChange;
	FOnHealthChangeDelegate OnManaChange;
	FOnHealthChangeDelegate OnStrengthChange;
};
