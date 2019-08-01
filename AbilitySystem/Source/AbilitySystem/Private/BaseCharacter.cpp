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
	//在BeginPlay中动态的绑定委托
	AttributeSetComp->OnHealthChange.AddDynamic(this, &ABaseCharacter::OnHealthChange);
	AttributeSetComp->OnManaChange.AddDynamic(this, &ABaseCharacter::OnManaChange);
	AttributeSetComp->OnStrengthChange.AddDynamic(this, &ABaseCharacter::OnStrengthChange);
	AutoDetermineTeamIDByControllerType();
	//一开始添加Full
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

void ABaseCharacter::AquireAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToAquire)
{
	for (TSubclassOf<UGameplayAbility> AbilityItem:AbilitiesToAquire)
	{
		AquireAbility(AbilityItem);
		//如果是UBaseGameplayAbility的子类，说明可以添加UI
		if (AbilityItem->IsChildOf(UBaseGameplayAbility::StaticClass()))
		{
			//这里加*与不加的区别？
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
		//生命值小于0，调用蓝图事件来播放死亡动画
		bIsDeath = true;
		BP_Die();
		Dead();
	}
	BP_OnHealthChange(Health, MaxHealth);//通知蓝图事件调用
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
	//必须指定要添加的Tag数量
	GetAbilitySystemComponent()->SetTagMapCount(TagToAdd, 1);
}

void ABaseCharacter::RemoveGameplyTag(FGameplayTag TagToRemove)
{
	GetAbilitySystemComponent()->RemoveLooseGameplayTag(TagToRemove);
}

void ABaseCharacter::HitStun(float StunDuration)
{
	DisableInputControl();
	//延时后执行EnableInputControl
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
{   //为了避免错误，先判断角色是否已经死亡
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
			PlayerControllerBase->AddAbilityToUI(AbilityInfo);//最终实现是在蓝图中
		}
	}
}


