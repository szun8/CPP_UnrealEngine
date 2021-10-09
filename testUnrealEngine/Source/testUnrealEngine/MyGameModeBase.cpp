// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"

AMyGameModeBase::AMyGameModeBase(){
    DefaultPawnClass = AMyCharacter::StaticClass();
    // AMyPawn에서 AMyCharacter로 상속받을 class 조정
    // 즉 AMyCharacter을 게임시작시, 명령을 받고 움직이는 주인공으로 설정한다는 의미
}

