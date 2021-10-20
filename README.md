# CPP_UnrealEngine
- 언리얼 작명 규칙 : https://docs.unrealengine.com/4.27/ko/ProductionPipelines/DevelopmentSetup/CodingStandard/

🕹 29th, Sep

1. 로그 찍어보기   
간단히 BeginPlay에서 시작

    ```c++  
    UE_LOG(LogTemp, Error, TEXT(“Tick %f), DeltaTime);
    // 카테고리(이름), 로깅수준(얼마나 중요한지?), 형식, 인자
    ```
    = 로깅수준의 문법도 도큐먼트에 설명되어있어서 정말 체계적이군,,,   
    = Saved내에 출력된 log를 저장하는 파일 존재

2. 디버그   
유니티는 그냥 브레이크포인트 잡으면 되지만 언리얼은 역시나 쉽지 않다   
일단 프로젝트를 다 닫고 엑스코드 상에서 빌드 -> 언리얼이 엑스코드를 통해 켜진다음에 디버그 진행!

    (<-> 프로젝트키고 엑스코드 건드리기(Hot reload)의 반대)   
    (디버그중에 중단하면 프로젝트 engine도 중단되고 꺼짐)

    < 🔎 여러가지 디버그 옵션 >   
    Debug (최적화가 가장 덜 되어있음)    
    - Game : .exe 파일이 만들어져서 실행됨(이거는 아트 리소스가 없이 디버그되어 에러 발생함)
    - Game Editor :  .dll 파일을 만들어서 실행 (실행파일이 아님)
    Development(최적화 굳굳)
    Shipping (최적화 굳굳굳굳) - 최종 배포시,

📒 Binary 폴더는 우리가 빌드한 결과물들이 저장됨

📄 Document : 프로젝트를 컴파일하려면 언리얼 엔진 Xcode 프로젝트는 Xcode 의
Product - Build For - Profiling 사용시 Development 환경설정을, 
Product - Build 옵션 사용시 Debug 환경설정을 사용하도록 되어 있습니다.    
이 작동방식은 타깃 스키마를 편집하여 바꿀 수 있습니다.   

1. Rotation Code 회전 함수 적용
    ```c++
    <in tick()>
    AddActorLocalRotaion(FRotator(0.f, RotateSpeed * DeltaTime, 0.f));
    // x, y, z축
    // 이동하는 어떤 코드가 있을때는 돌리는 PC의 사양에 따라 보이는 것이 다르기에 시간(델타타임!경과시간!)을 곱해주는 것이 좋다
    // 200프레임이라면 1초에 200번 = 부드러워보임
    // 40프레임이라면 1초에 40번 = 버벅여보임
    // 각 하드웨어의 사양을 고려해주는 코드 지향
    // 거리 = 속도 * 시간
    ```

* Local vs World

🕹 02nd, Oct

- 월드세팅 : 게임모드 오버라이딩

* DefaultPawnClass 지정으로 게임 시작시, 명령에따라 움직이는 주인공 설정

    🔗 MyGameModeBase.cpp
    ```c++
    AMyGameModeBase::AMyGameModeBase(){
        DefaultPawnClass = AMyPawn::StaticClass();
        // APawn을 상속받을 수 있는 클래스
        // 즉 AMyPawn을 게임시작시, 명령을 받고 움직이는 주인공으로 설정한다는 의미
    }
    ```
    🔗 MyPawn.h
    ```c++
        UPROPERTY(VisibleAnywhere)
        class UFloatingPawnMovement* Movement;
        // 간단한 이동을 제공한 컨포넌트
        // CoreMinimal.h에 포함되어 있지 않은 컴포넌트 => class 전방 선언 후, #include "GameFramework/FloatingPawnMovement.h" 선언 필요
        
        // 10-01 Lesson : 월드세팅의 게임모드 오버라이딩 조정 => 플레이시, 주체 이동 조작
    ```

    🔗 MyPawn.cpp
    ```c++
    Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));  // 이동 컴포넌트

    축설정 및 방향키 조정을 통한 위치 조정 코드 및 세팅
    // Move Code(1) - W(Up),S(Down),A(Left),D(Right) key
    PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyPawn::UpDown);
    PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyPawn::LeftRight);
    // 현재 우리는 축(Axis)설정 => 입력 조정도 따로 세팅에서 설정해줘야 인식
    // [세팅]-[입력]-[축매핑] : 설정한 이름과 동일하게 지정 + Scale : 이동한 만큼의 정도

    AddMovementInput(GetActorForwardVector(), Value);
    // Forward : Up 기준 / 마이너스는 자동적으로 Down

    AddMovementInput(GetActorRightVector(), Value); 
    // Right 기준, 마이너스는 자동적으로 Left
    ```

🕹 09th, Oct 1-5. 캐릭터 생성   
1. Mesh - skeletalMeshComponent (in Character)
2. 카메라뷰 - SpringArm/Camera
3. 축조정 - Yaw

🕹 10th, Oct 1-6. 블루프린트 클래스   

🕹 11th, Oct 2-1. 애니메이션 기초

📒 보통 애니메이션 기능은 독립적인 class로 생성 (Tick으로가 아닌?)   

🕹 16th, Oct 2-2. 스테이트 머신

* 🛎 들어가기에 앞서,    
    앞 전시간에 다뤘던 `if-else문`으로 조건을 나누는 것은 조건이 많아지면 굉장히 어지뤄워지고 관리가 힘들어짐 => 이번시간에 다루는 `StateMachine`을 이용하면 보다 쾌적한 조건관리를 할 수 있음

* 🪄 `StateMachine` : 가질 수 있는 경우의 수들을 체크하고 다양한 상태를 빠르고 쉽게 관리 가능한 기능, 여러 상태들을 모아놓은 기계   
📁 ex. Jump - start, fall, end, etc... 한 동작에도 다양한 애니메이션이 필요   
📂 Use in BP - `StateMachine` 더블클릭시, 안으로 들어가면 여러 상태를 나누기 가능   
➡️ 스테이트 추가 및 내부 조건 설정 / 스테이트끼리 연결 / 스테이트들 사이의 연결 조건 = 룰 설정 

    💻 experiment : (1) Ground-(rule)-(2) JumpStart-(rule)-(3) Jumping-(rule)-(4) JumpEnd(rule)-(5) Ground   
* ⌨️ Jump Code 
  ```c++
    PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed, this, &AMyCharacter::Jump);
    // Jump 함수는 언리얼 내부 제공함수로 따로 코드를 만들지 않아도 됨
    // IE_Pressed : 눌렀을때의 상태에서 해당 액션 수행
    // 이외의 상태옵션도 많음!
  ```   


🕹 21th, Oct 2-3(인데 4로 commit 해버리기). 애니메이션 몽타주
* Mesh의 Asset 생성 - 애님 몽타주 : 연속적인 애니메이션 편집 및 연출
* `Attack()` : `Jump`와 같이 `BindAction`으로 액션 매핑 (프로젝트 세팅 - 입력 필요!   
📁 [클릭]-[캐릭터]-[애니메이션]의 경로로 코드 진행 (<-> [애니메이션]-[캐릭터]의 경로)   
 ⌨️ Attack Code 
  ```c++
    //캐릭터.cpp
    PlayerInputComponent->BindAction(TEXT("Attack"),EInputEvent::IE_Pressed, this, &AMyCharacter::Attack);
    ⬇️
    void AMyCharacter::Attack();
    ⬇️ 
    //애니메이션.cpp
    PlayAttackMontage();
    ⬇️ //!(중복플레잉)
    Montage_Play(AttackMontage, 1.f);
    //AttackMontage는 생성자에서 만들어놓은 애님 몽타주 에셋 경로 오브젝트에 연결
}
    
  ```  
