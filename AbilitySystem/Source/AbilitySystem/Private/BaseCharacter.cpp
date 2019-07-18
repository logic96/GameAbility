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
	//���ж�AbilitySytemcomp�Ƿ�Ϊ��
	if (AbilitySystemComp) {
		//HasAuthrity�����жϿͻ����Ƿ��Actor�п���Ȩ
		//���жϴ���ļ����Ƿ�Ϊ��
		if (HasAuthority() && AbilityToAquire) {
			//GiveAbility���ھ����ΪAbilitySystemComp���������������TryActiveAbility
			//FGameplayAbilitySpec��һ�����ڴ洢������Ability��ص�������Ϣ�Ľṹ��
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToAquire, 1, 0));
			//InitAbilityActorInfo����˵����˭���߼��Ͽ���Actor(Pawn��Characrter�ȵ�)��˭�������Ͽ��ƣ������ǽ�����Ҳ���ܺ�OwnedActor��ͬ��
			AbilitySystemComp->InitAbilityActorInfo(this, this);
		}
	}
}
