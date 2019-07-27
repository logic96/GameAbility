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
//IAbilitySystemInterface�����ڻ�ȡAbilitySystemComponent�Ľӿڣ�
//���ڲ���ֻ��һ��GetAbilitySystemComponent()���跽������
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
	//����һ��UAbilitySystemComponent���,һ����ʹ��CreateDefaultSubobject�ķ�ʽ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = BaseCharacter)
	UAbilitySystemComponent* AbilitySystemComp;
	//��д�ӿڰ��е��鷽��
	virtual UAbilitySystemComponent* GetAbilitySystemComponent()const;
	//����һ����UBaseAttributeSet�����һ����ʹ��CreateDefaultSubobject�ķ�ʽ������
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = BaseCharacter)
	class UBaseAttributeSet* AttributeSetComp;
	//�ú������ڻ�ȡ�����Ability
	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
		void AquireAbility(TSubclassOf<UGameplayAbility>AbilityToAquire);
	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	//���ڻ�ȡһ�Ѽ���
		void AquireAbilities(TArray<TSubclassOf<UGameplayAbility>>AbilitiesToAquire);

	UFUNCTION()
		void OnHealthChange(float Health, float MaxHealth);
	UFUNCTION(BlueprintImplementableEvent, Category = BaseCharacter)
		void BP_OnHealthChange(float Health, float MaxHealth);//��ͼ��ʵ��
	UFUNCTION() //������UFUNCTION���ܹ�add Dynamic Delegate
		void OnManaChange(float Mana, float MaxMana);
	UFUNCTION(BlueprintImplementableEvent, Category = BaseCharacter)
		void BP_OnManaChange(float Mana, float MaxMana);//��ͼ��ʵ��
	UFUNCTION()
		void OnStrengthChange(float Strength, float MaxStrength);
	UFUNCTION(BlueprintImplementableEvent, Category = BaseCharacter)
		void BP_OnStrengthChange(float Strength, float MaxStrength);//��ͼ��ʵ��
	UFUNCTION(BlueprintImplementableEvent, Category = BaseCharacter)
		void BP_Die();
	uint8 GetTeamID()const;
	UFUNCTION(BlueprintCallable)
		bool IsOtherHostile(ABaseCharacter* Other);//�����ж�TeamID�Ƿ�ͬ
	
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
	//����Controller����������TeamID
	void AutoDetermineTeamIDByControllerType();
	//��Dead���������
	void Dead();
	//
	void DisableInputControl();
	void EnableInputControl();
	FTimerHandle StunTimerHandle;

	void AddAbilityToUI(TSubclassOf<class UBaseGameplayAbility>AbilityToAdd);
};
