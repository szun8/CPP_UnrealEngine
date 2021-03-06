 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHit);

UCLASS()
class TESTUNREALENGINE_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
    
public:
    UMyAnimInstance();
    
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
    void PlayAttackMontage();
    
    FName GetAttackMontageName(int32 SectionIndex);
    void JumpToSection(int32 SectionIndex);
    
    
private:
    UFUNCTION()
    void AnimNotify_AttackHit();
	
private:
    UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
    // private임에도 접근을 허용한다는 의미
    float speed;
    
    UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
    bool IsFalling;
    
    UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
    UAnimMontage* AttackMontage;
    
    UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
    float Horizontal;
    
    UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
    float Vertical;
    
public:
    FOnAttackHit OnAttackHit;
};
