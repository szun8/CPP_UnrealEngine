// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
// USpringArmComponent 포함 헤더
#include "Camera/CameraComponent.h"
// UCameraComponent 포함 헤더
#include "Components/CapsuleComponent.h"
#include "MyAnimInstance.h"

// 오.. 헤더 자동완성 왜되지??? 호와,,,,0_0!

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    // 21-10-09 1-5. 캐릭터 생성 - 카메라 위치 조정 (스프링암)
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
    
    SpringArm->SetupAttachment(GetCapsuleComponent());
    // 루트 컴포넌트를 기준으로 다른애들을 조립, 부모를 누구로 하는지 ?
    Camera->SetupAttachment(SpringArm);
    // 카메라는 스프링암에 붙여주기
    
    GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));    // 위치 조정 = 바라보는 방향과 바닥에 붙이게
    
    SpringArm->TargetArmLength = 500.f; // 셀카봉의 길이
    SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));  // 셀카봉의 각도
    
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
        // SkeletalMesh 로 변경
    
    if(SM.Succeeded()){
        GetMesh()->SetSkeletalMesh(SM.Object);
        // private로 mesh가 막혀있어서 함수사용해서 내부 접근 필요!
    }

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
    
    // MyCharacter.h에서 전방선언 후 mesh 긁어오기
    AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
    
    // delegate : 함수가 종료되면 해당 조건을 실행하라
    AnimInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown);
    PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::LeftRight);
    PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AMyCharacter::Yaw);
    
    PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed, this, &AMyCharacter::Jump);
    // Jump 함수는 이미 만들어져있음!
    PlayerInputComponent->BindAction(TEXT("Attack"),EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);

}
void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted){
    // attack이 종료되면 false로,
    IsAttacking = false;
}

void AMyCharacter::UpDown(float Value){
//    if(Value == 0.f)
//        return;
    //UE_LOG(LogTemp, Warning, TEXT("UpDown %f"), Value);
    
    // Move Code(2-1)
    AddMovementInput(GetActorForwardVector(), Value); // Forward : Up 기준 / 마이너스는 자동적으로 Down
    
    // BlendSpace(Code)
    UpDownValue = Value;
    
}

void AMyCharacter::LeftRight(float Value){
//    if(Value == 0.f)
//        return;
    //UE_LOG(LogTemp, Warning, TEXT("LeftRight %f"), Value);
    
    // Move Code(2-2)
    AddMovementInput(GetActorRightVector(), Value); // Right 기준, 마이너스는 자동적으로 Left
    
    // BlendSpace(Code)
    LeftRightValue = Value;
}

void AMyCharacter::Yaw(float Value){
    // 마우스 카메라 이동
    AddControllerYawInput(Value);
    // player에 적용하는 것이 아니라, controller에 적용시킨다는 것을 생각!
}

void AMyCharacter::Attack(){
    if(IsAttacking)
        // 이미 행동을 하고 있다면, 탈출
        return;
    
    // delegate 사용으로 매 프레임마다 행동확인을 할 필요없이 알아서 행동 종료인식
    AnimInstance->PlayAttackMontage();
    AnimInstance->JumpToSection(AttackIndex);
    // header에서 0으로 초기화하고
    AttackIndex = (AttackIndex+1)%3;
    // Attack이 실행될 때마다 공격모션 갱신 (+1) => 다음 공격모션은 +1이 된 모션으로 진행됨
    IsAttacking = true;
}

