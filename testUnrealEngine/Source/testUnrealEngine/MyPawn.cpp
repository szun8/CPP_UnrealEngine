// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));  // 메쉬 컴포넌트
    Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT")); // 이동 컴포넌트
        
    RootComponent = Mesh;
    
    //static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Users/szun/Documents/Unreal Projects/test/Content/StarterContent/Props/SM_Couch.uasset"));
    // 파일 경로 복사가 아니라 '레퍼런스 복사'를 눌러서 적용해줘야함!!! 헷갈리지 않기

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Couch.SM_Couch'"));
    
    if(SM.Succeeded()){
        Mesh->SetStaticMesh(SM.Object);
    }

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input - Actor랑 다른 점!
// 입력받는 것도 따로 클래스로 처리
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    // Move Code(1) - W(Up),S(Down),A(Left),D(Right) key
    PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyPawn::UpDown);
    PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyPawn::LeftRight);
    // 현재 우리는 축(Axis)설정 => 입력 조정도 따로 세팅에서 설정해줘야 인식
    // [세팅]-[입력]-[축매핑] : 설정한 이름과 동일하게 지정 + Scale : 이동한 만큼의 정도

}

void AMyPawn::UpDown(float Value){
    if(Value == 0.f)
        return;
    //UE_LOG(LogTemp, Warning, TEXT("UpDown %f"), Value);
    
    // Move Code(2-1)
    AddMovementInput(GetActorForwardVector(), Value); // Forward : Up 기준 / 마이너스는 자동적으로 Down
    
}

void AMyPawn::LeftRight(float Value){
    if(Value == 0.f)
        return;
    //UE_LOG(LogTemp, Warning, TEXT("LeftRight %f"), Value);
    
    // Move Code(2-2)
    AddMovementInput(GetActorRightVector(), Value); // Right 기준, 마이너스는 자동적으로 Left
}

