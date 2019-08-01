// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageExecutionCalculation.h"
#include "BaseAttributeSet.h"
//这项修改编译后需要重启，才会正常生效
struct DamageSatics {
DECLARE_ATTRIBUTE_CAPTUREDEF(AttackDamage)
DECLARE_ATTRIBUTE_CAPTUREDEF(Armor)
DamageSatics() {
	DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, AttackDamage, Source, true)
	DEFINE_ATTRIBUTE_CAPTUREDEF(UBaseAttributeSet, Armor, Target, true)
}
};
static DamageSatics& GetDamageSatics() {
	static DamageSatics DamageSaticVar;
	return DamageSaticVar;
}
UDamageExecutionCalculation::UDamageExecutionCalculation() {
	//使用宏来简化下面的书写
	HealthProperty = FindFieldChecked<UProperty>(UBaseAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UBaseAttributeSet, Health));
	HealthDef = FGameplayEffectAttributeCaptureDefinition(HealthProperty, EGameplayEffectAttributeCaptureSource::Target, true);

	RelevantAttributesToCapture.Add(HealthDef);
	RelevantAttributesToCapture.Add(GetDamageSatics().AttackDamageDef);
	RelevantAttributesToCapture.Add(GetDamageSatics().ArmorDef);
}

void UDamageExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	//ExecutionParams可以用于获取很多有用的信息
	float AttackDamageMagnitude = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageSatics().AttackDamageDef, FAggregatorEvaluateParameters(), AttackDamageMagnitude);
	float ArmorMagnitude = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageSatics().ArmorDef, FAggregatorEvaluateParameters(), ArmorMagnitude);

	float finalDamage = FMath::Clamp(AttackDamageMagnitude - ArmorMagnitude,0.f, AttackDamageMagnitude-ArmorMagnitude);
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HealthProperty, EGameplayModOp::Additive, -finalDamage));
}
