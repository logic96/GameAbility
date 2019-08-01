// Fill out your copyright notice in the Description page of Project Settings.


#include "GATargetActorFireBlast.h"
#include "GameplayAbility.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
void AGATargetActorFireBlast::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	MasterPC= MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void AGATargetActorFireBlast::ConfirmTargetingAndContinue()
{
	APawn* OwningPawn = MasterPC->GetPawn();
	if (!OwningPawn) {
		//���ʧ�ܣ���Ȼ����λ����Ϣ
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
		return;
	}
	FVector ViewLocation=OwningPawn->GetActorLocation();
	//GetPlayerLookingPoint(ViewLocation);

	TArray<FOverlapResult> Overlaps;
	TArray<TWeakObjectPtr<AActor>>OverlapedActors;
	bool TraceComplex = false;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.bTraceComplex = TraceComplex;
	CollisionQueryParams.bReturnPhysicalMaterial = false;
	APawn* MasterPawn = MasterPC->GetPawn();
	if (MasterPawn)
	{
		CollisionQueryParams.AddIgnoredActor(MasterPawn->GetUniqueID());
	}

	bool TryOverlap = GetWorld()->OverlapMultiByObjectType(Overlaps,
		ViewLocation,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECC_Pawn),
		FCollisionShape::MakeSphere(Radius),
		CollisionQueryParams);
	if (TryOverlap)
	{
		for (int32 i = 0; i < Overlaps.Num(); i++) {
			APawn* PawnOverlaped = Cast<APawn>(Overlaps[i].GetActor());
			if (PawnOverlaped && !OverlapedActors.Contains(PawnOverlaped)) {
				OverlapedActors.Add(PawnOverlaped);
			}
		}
	}
	//����λ����Ϣ�����ڲ���������Ч


	if (OverlapedActors.Num() > 0) {
		FGameplayAbilityTargetDataHandle TargetDate = StartLocation.MakeTargetDataHandleFromActors(OverlapedActors);
		TargetDataReadyDelegate.Broadcast(TargetDate);
	}
	else {
		//���û���������ˣ���Ȼ����λ����Ϣ
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
	}
}
