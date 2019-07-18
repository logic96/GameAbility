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

	//�ú������ڻ�ȡ�����Ability
	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
		void AquireAbility(TSubclassOf<UGameplayAbility>AbilityToAquire);
};
