// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"

AMyGameModeBase::AMyGameModeBase(){
    //DefaultPawnClass = AMyCharacter::StaticClass();
    // AMyPawn에서 AMyCharacter로 상속받을 class 조정
    // 즉 AMyCharacter을 게임시작시, 명령을 받고 움직이는 주인공으로 설정한다는 의미
    
    // 10-10 1-6. 블루프린트 클래스
    static ConstructorHelpers::FClassFinder<ACharacter> BP_Char(TEXT("Blueprint'/Game/BluePrints/BP_MyCharacter.BP_MyCharacter_C'"));
    // BluePrint에서 세팅해놓은 파일을 기본 월드 게임모드 세팅으로 하고 싶을때
    // (!) BluePrint는 ref 경로 마지막에 무조건 _C를 붙여줘야한다고 하네요! - 언리얼 규칙
    
    if(BP_Char.Succeeded()){
        DefaultPawnClass = BP_Char.Class;
        // 클래스의 C는 대문자!
    }
}

