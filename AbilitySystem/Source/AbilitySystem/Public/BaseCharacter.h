// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class ABILITYSYSTEM_API ABaseCharacter : public ACharacter,public IAbilitySystemInterface
{
//IAbilitySystemInterface是用于获取AbilitySystemComponent的接口，
//其内部就只有一个GetAbilitySystemComponent()纯需方法方法
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//声明一个UAbilitySystemComponent组件,一样的使用CreateDefaultSubobject的方式来定义
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = BaseCharacter)
	UAbilitySystemComponent* AbilitySystemComp;
	//重写接口板中的虚方法
	virtual UAbilitySystemComponent* GetAbilitySystemComponent()const;
	//声明一个和UBaseAttributeSet组件，一样的使用CreateDefaultSubobject的方式来定义
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = BaseCharacter)
	class UBaseAttributeSet* AttributeSetComp;
	//该函数用于获取具体的Ability
	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
		void AquireAbility(TSubclassOf<UGameplayAbility>AbilityToAquire);
	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	//用于获取一堆技能
		void AquireAbilities(TArray<TSubclassOf<UGameplayAbility>>AbilitiesToAquire);

	UFUNCTION()
		void OnHealthChange(float Health, float MaxHealth);
	UFUNCTION(BlueprintImplementableEvent, Category = BaseCharacter)
		void BP_OnHealthChange(float Health, float MaxHealth);//蓝图中实现
	UFUNCTION() //必须是UFUNCTION才能够add Dynamic Delegate
		void OnManaChange(float Mana, float MaxMana);
	UFUNCTION(BlueprintImplementableEvent, Category = BaseCharacter)
		void BP_OnManaChange(float Mana, float MaxMana);//蓝图中实现
	UFUNCTION()
		void OnStrengthChange(float Strength, float MaxStrength);
	UFUNCTION(BlueprintImplementableEvent, Category = BaseCharacter)
		void BP_OnStrengthChange(float Strength, float MaxStrength);//蓝图中实现
	UFUNCTION(BlueprintImplementableEvent, Category = BaseCharacter)
		void BP_Die();
	uint8 GetTeamID()const;
	UFUNCTION(BlueprintCallable)
		bool IsOtherHostile(ABaseCharacter* Other);//用于判断TeamID是否不同
	
	UFUNCTION(BlueprintCallable, Category = BaseChracter)
		void AddGameplyTag(FGameplayTag TagToAdd);
	UFUNCTION(BlueprintCallable, Category = BaseChracter)
		void RemoveGameplyTag(FGameplayTag TagToRemove);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BaseCharacter)
		FGameplayTag FullHealthTag;
	UFUNCTION(BlueprintCallable)
		void HitStun(float StunDuration);
protected:
	bool bIsDeath;

	uint8 TeamID;
	//根据Controller的类型设置TeamID
	void AutoDetermineTeamIDByControllerType();
	//在Dead里禁用输入
	void Dead();
	//
	void DisableInputControl();
	void EnableInputControl();
	FTimerHandle StunTimerHandle;

	void AddAbilityToUI(TSubclassOf<class UBaseGameplayAbility>AbilityToAdd);
};
