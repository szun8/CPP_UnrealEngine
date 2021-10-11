 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

UCLASS()
class TESTUNREALENGINE_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
    
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
private:
    UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
    // private임에도 접근을 허용한다는 의미
    float speed;
};
