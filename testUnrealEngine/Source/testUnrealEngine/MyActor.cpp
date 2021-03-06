// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
        
        RootComponent = Mesh;
        
        //static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Users/szun/Documents/Unreal Projects/test/Content/StarterContent/Props/SM_Couch.uasset"));
        
        static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Couch.SM_Couch'"));
        
        
        if(SM.Succeeded()){
            Mesh->SetStaticMesh(SM.Object);
        }

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Begin Play %d"),3 );
    // Log 찍기 : 카테고리, 로깅수준(얼마나 중요한지?), 형식, 인자
    // 로깅수준 분류 문법은 언리얼 도큐먼트 링크 참조 (첨부 예정)
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Error, TEXT("Tick %f"), DeltaTime );
    
    AddActorLocalRotation(FRotator(0.f, RotateSpeed * DeltaTime, 0.f));

}

