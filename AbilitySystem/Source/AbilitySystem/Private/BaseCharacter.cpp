// Fill out your copyright notice in the Description page of Project Settings.


#include "public/BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent()const {
	return AbilitySystemComp;
}
void ABaseCharacter::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire)
{
	//先判断AbilitySytemcomp是否为空
	if (AbilitySystemComp) {
		//HasAuthrity用于判断客户端是否对Actor有控制权
		//再判断传入的技能是否为空
		if (HasAuthority() && AbilityToAquire) {
			//GiveAbility用于具体的为AbilitySystemComp赋予能力，会调用TryActiveAbility
			//FGameplayAbilitySpec是一个用于存储被赋予Ability相关的数据信息的结构体
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToAquire, 1, 0));
			//InitAbilityActorInfo用于说明是谁在逻辑上控制Actor(Pawn、Characrter等等)、谁在物理上控制（可以是建筑，也可能和OwnedActor相同）
			AbilitySystemComp->InitAbilityActorInfo(this, this);
		}
	}
}
