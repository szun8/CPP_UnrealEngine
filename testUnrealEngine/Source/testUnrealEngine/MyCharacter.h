// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class TESTUNREALENGINE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    void UpDown(float Value);  // 반드시 인자로 float를 받아줘야함
    void LeftRight(float Value);
    void Yaw(float Value);  // 마우스 입력 도리도리
    
    void Attack();
private:
    UPROPERTY(VisibleAnywhere)
    class USpringArmComponent* SpringArm;
    
    UPROPERTY(VisibleAnywhere)
    class UCameraComponent* Camera;

};
