// Fill out your copyright notice in the Description page of Project Settings.


#include "public/BaseCharacter.h"
#include "BaseAttributeSet.h"
#include "BasePlayerController.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "TimerManager.h"
#include "BaseGameplayAbility.h"
#include "AbilityTypes.h"
// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	AttributeSetComp = CreateDefaultSubobject<UBaseAttributeSet>("AttributeSetComp");
	bIsDeath = false;
	TeamID = 255;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	//��BeginPlay�ж�̬�İ�ί��
	AttributeSetComp->OnHealthChange.AddDynamic(this, &ABaseCharacter::OnHealthChange);
	AttributeSetComp->OnManaChange.AddDynamic(this, &ABaseCharacter::OnManaChange);
	AttributeSetComp->OnStrengthChange.AddDynamic(this, &ABaseCharacter::OnStrengthChange);
	AutoDetermineTeamIDByControllerType();
	//һ��ʼ���Full
	AddGameplyTag(FullHealthTag);
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

void ABaseCharacter::AquireAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToAquire)
{
	for (TSubclassOf<UGameplayAbility> AbilityItem:AbilitiesToAquire)
	{
		AquireAbility(AbilityItem);
		//�����UBaseGameplayAbility�����࣬˵���������UI
		if (AbilityItem->IsChildOf(UBaseGameplayAbility::StaticClass()))
		{
			//�����*�벻�ӵ�����
			TSubclassOf<UBaseGameplayAbility>AbilityBaseClass = *AbilityItem;
			if (AbilityBaseClass != nullptr)
			{
				AddAbilityToUI(AbilityBaseClass);
			}
		}
	}
}

void ABaseCharacter::OnHealthChange(float Health, float MaxHealth)
{
	if (Health <= 0.f&& !bIsDeath) {
		//����ֵС��0��������ͼ�¼���������������
		bIsDeath = true;
		BP_Die();
		Dead();
	}
	BP_OnHealthChange(Health, MaxHealth);//֪ͨ��ͼ�¼�����
}

void ABaseCharacter::OnManaChange(float Mana, float MaxMana)
{
	BP_OnManaChange(Mana, MaxMana);
}

void ABaseCharacter::OnStrengthChange(float Strength, float MaxStrength)
{
	BP_OnStrengthChange(Strength, MaxStrength);
}

uint8 ABaseCharacter::GetTeamID()const
{
	return TeamID;
}

bool ABaseCharacter::IsOtherHostile(ABaseCharacter* Other)
{
	return TeamID!=Other->GetTeamID();
}

void ABaseCharacter::AddGameplyTag(FGameplayTag TagToAdd)
{
	GetAbilitySystemComponent()->AddLooseGameplayTag(TagToAdd);
	//����ָ��Ҫ��ӵ�Tag����
	GetAbilitySystemComponent()->SetTagMapCount(TagToAdd, 1);
}

void ABaseCharacter::RemoveGameplyTag(FGameplayTag TagToRemove)
{
	GetAbilitySystemComponent()->RemoveLooseGameplayTag(TagToRemove);
}

void ABaseCharacter::HitStun(float StunDuration)
{
	DisableInputControl();
	//��ʱ��ִ��EnableInputControl
	GetWorldTimerManager().SetTimer(StunTimerHandle, this, &ABaseCharacter::EnableInputControl, StunDuration,false);
}

void ABaseCharacter::ApplyGESpecHandleToTargetDataSpecHandle(const FGameplayEffectSpecHandle& GESpecHandle, const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	for (TSharedPtr<FGameplayAbilityTargetData>Data : TargetDataHandle.Data)
	{
		Data->ApplyGameplayEffectSpec(*GESpecHandle.Data.Get());
	}
}

void ABaseCharacter::AutoDetermineTeamIDByControllerType()
{
	if (GetController() && GetController()->IsPlayerController()) {
		TeamID = 0;
	}

}

void ABaseCharacter::Dead()
{
	DisableInputControl();
	
}

void ABaseCharacter::DisableInputControl()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->DisableInput(PC);
	}
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBrainComponent()->StopLogic("Dead");
	}
}

void ABaseCharacter::EnableInputControl()
{   //Ϊ�˱���������жϽ�ɫ�Ƿ��Ѿ�����
	if (!bIsDeath) {
		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC)
		{
			PC->EnableInput(PC);
		}
		AAIController* AIC = Cast<AAIController>(GetController());
		if (AIC)
		{
			AIC->GetBrainComponent()->RestartLogic();
		}
	}	
}

void ABaseCharacter::AddAbilityToUI(TSubclassOf<class UBaseGameplayAbility> AbilityToAdd)
{
	ABasePlayerController* PlayerControllerBase = Cast<ABasePlayerController>(GetController());
	if (PlayerControllerBase)
	{
		UBaseGameplayAbility* AbilityInstance = AbilityToAdd.Get()->GetDefaultObject<UBaseGameplayAbility>();
		if (AbilityInstance)
		{
			FGameplayAbilityInfo AbilityInfo = AbilityInstance->GetAbilityInfo();
			PlayerControllerBase->AddAbilityToUI(AbilityInfo);//����ʵ��������ͼ��
		}
	}
}


