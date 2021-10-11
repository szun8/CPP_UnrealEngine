// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAnimInstance.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds){
    Super::NativeUpdateAnimation(DeltaSeconds);
    // Super : GENERATED_BODY()에 포함된 기능, 공식문법 X
    // 해당 클래스(UMyAnimInstance)의 부모 클래스(UAnimInstance)를 가리킴
    // C++ 정석 문법 : UAnimInstance::NativeUpdateAnimation(DeltaSeconds);
    
    auto pawn = TryGetPawnOwner();
    // 나를 포함하고 있는 나의 주인님의 정보들을 가져오겠다
    // 근데 항상 Try가 있을 수는 없으니 아래처럼 확인 필요
    if(IsValid(pawn)){  // null이 아니라면,
        speed = pawn->GetVelocity().Size();
        // pawn에 들어가있는 속도의(.) 사이즈를 가져오기
        // 실시간으로 speed가 조정되는 결과를 도출해냄
        // 필요한 정보를 긁어오기
    }
    // 근데 매 프레임 움직이는(try)것이 아닐수있는데 매번 확인(if)하는게 낭비 아닌가?하지만 그게 그거라고 한다
}
