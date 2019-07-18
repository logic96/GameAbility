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

	//该函数用于获取具体的Ability
	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
		void AquireAbility(TSubclassOf<UGameplayAbility>AbilityToAquire);
};
