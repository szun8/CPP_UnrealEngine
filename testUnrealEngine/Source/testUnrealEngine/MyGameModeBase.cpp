// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyPawn.h"

AMyGameModeBase::AMyGameModeBase(){
    DefaultPawnClass = AMyPawn::StaticClass();
    // APawn을 상속받을 수 있는 클래스
    // 즉 AMyPawn을 게임시작시, 명령을 받고 움직이는 주인공으로 설정한다는 의미
}

