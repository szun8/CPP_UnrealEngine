// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UMyAnimInstance::UMyAnimInstance(){
    // 생성자 for attack animation
    static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("AnimMontage'/Game/Animations/Greystone_Skeleton_Montage.Greystone_Skeleton_Montage'"));
    
    if(AM.Succeeded()){
        AttackMontage = AM.Object;
    }
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds){
    Super::NativeUpdateAnimation(DeltaSeconds);
    // Super : GENERATED_BODY()에 포함된 기능, 공식문법 X
    // 해당 클래스(UMyAnimInstance)의 부모 클래스(UAnimInstance)를 가리킴
    // C++ 정석 문법 : UAnimInstance::NativeUpdateAnimation(DeltaSeconds);
    
    auto Pawn = TryGetPawnOwner();
    // 나를 포함하고 있는 나의 주인님의 정보들을 가져오겠다
    // 근데 항상 Try가 있을 수는 없으니 아래처럼 확인 필요
    if(IsValid(Pawn)){  // null이 아니라면,
        speed = Pawn->GetVelocity().Size();
        // pawn에 들어가있는 속도의(.) 사이즈를 가져오기
        // 실시간으로 speed가 조정되는 결과를 도출해냄
        // 필요한 정보를 긁어오기
    }
    // 근데 매 프레임 움직이는(try)것이 아닐수있는데 매번 확인(if)하는게 낭비 아닌가?하지만 그게 그거라고 한다
    
    auto Character = Cast<ACharacter>(Pawn);
    if(Character){
        IsFalling = Character->GetMovementComponent()->IsFalling();
    }
}

// 마우스를 클릭하는 순간 애니메이션 실행 => 호출 순서 : 캐릭터.h -> 애니메이션.h
void UMyAnimInstance::PlayAttackMontage(){
    if(!Montage_IsPlaying(AttackMontage)){
        // 플레이중이 아닌 경우에 해당 애미메이션을 실행한다.
        // 중복 플레잉이 되면 안되기에
        Montage_Play(AttackMontage, 1.f);
    }
}
