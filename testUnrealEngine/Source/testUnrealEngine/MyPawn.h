// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MyPawn.generated.h"

UCLASS()
class TESTUNREALENGINE_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

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
    
private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* Mesh;
    
    UPROPERTY(VisibleAnywhere)
    class UFloatingPawnMovement* Movement;
    // 간단한 이동을 제공한 컨포넌트
    // CoreMinimal.h에 포함되어 있지 않은 컴포넌트 => class 전방 선언 후, #include "GameFramework/FloatingPawnMovement.h" 선언 필요
    
    // 10-01 Lesson : 월드세팅의 게임모드 오버라이딩 조정 => 플레이시, 주체 이동 조작

};
