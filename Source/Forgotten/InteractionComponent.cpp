#include "InteractionComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ForgottenHUD.h"
#include "ForgottenCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "TimerManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "ForgottenGameInstance.h"
#include "DialogueComponent.h"
#include "Engine/Engine.h"
#include "GlobalActorController.h"

UInteractionComponent::UInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    // 기본값 설정
    InteractionType = EInteractionType::OpenClose;
    InteractionText = FString("Interaction");
}

void UInteractionComponent::BeginPlay()
{
    Super::BeginPlay();

    SetMonitorCollision();
}

void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (InteractionType == EInteractionType::OpenClose && MovingComponent)
    {
        if (bRotationMovement)
        {
            if (!FMath::IsNearlyEqual(CurrentRotation, TargetRotation, 0.1f))
            {
                CurrentRotation = FMath::FInterpTo(CurrentRotation, TargetRotation, DeltaTime, MovementSpeed);
                MovingComponent->SetRelativeRotation(FRotator(0.0f, CurrentRotation, 0.0f));
            }
        }
        else
        {
            if (!CurrentOffset.Equals(TargetOffset, 0.1f))
            {
                CurrentOffset = FMath::VInterpTo(CurrentOffset, TargetOffset, DeltaTime, MovementSpeed);
                MovingComponent->SetRelativeLocation(CurrentOffset);
            }
        }
    }
}

void UInteractionComponent::Interact(AActor* Interactor)
{
    UForgottenGameInstance* GameInstance = Cast<UForgottenGameInstance>(GetWorld()->GetGameInstance());

    if (!GameInstance) return;

    switch (InteractionType)
    {
    case EInteractionType::OpenClose:
        HandleOpenClose(Interactor);
        break;
    case EInteractionType::ReadMemo:
        HandleReadMemo(Interactor);
        GameInstance->PlayerProgress.ProgressFlags.Add("ReadMemo", true);
        break;
    case EInteractionType::Inspect:
		HandleInspect(Interactor);
        GameInstance->PlayerProgress.ProgressFlags.Add("Inspect", true);
        break;
	case EInteractionType::Sit:
		HandleSit(Interactor);
        break;
	case EInteractionType::Lie:
        HandleLie(Interactor);
        GameInstance->PlayerProgress.ProgressFlags.Add("BedUsed", true);
		break;
    case EInteractionType::Break:
        HandleBreak(Interactor);
        GameInstance->PlayerProgress.ProgressFlags.Add("MirrorBroken", true);
    default:
        break;
    }

    // 인터랙션 이벤트 발생
    OnInteract.Broadcast(Interactor);
}

void UInteractionComponent::SetFocus(bool bFocused, AActor* Interactor)
{
    bIsFocused = bFocused;

    // 하이라이트 효과 적용
    if (HighlightMesh)
    {
        HighlightMesh->SetRenderCustomDepth(bFocused);
    }

    // 이벤트 발생
    if (bFocused)
    {
        OnFocus.Broadcast(Interactor);
    }
    else
    {
        OnLoseFocus.Broadcast(Interactor);
    }
}

FString UInteractionComponent::GetInteractionText() const
{
    switch (InteractionType)
    {
    case EInteractionType::OpenClose:
        return bIsOpen ? FString("Close") : FString("Open");
    case EInteractionType::ReadMemo:
        return bIsRead ? FString("Quit") : FString("Read");
    case EInteractionType::Inspect:
        return bIsInspect ? FString("Look Away") : FString("Inspect");
    case EInteractionType::Sit:
		return bIsSit ? FString("Stand Up") : FString("Sit");
	case EInteractionType::Lie:
		return bIsLie ? FString("Wake Up") : FString("Lie");
    case EInteractionType::Break:
		return bIsBreak ? FString("See") : FString("Break");
    default:
        return InteractionText;
    }
}

void UInteractionComponent::HandleOpenClose(AActor* Interactor)
{
    if (!MovingComponent)
    {
        return;
    }

    bIsOpen = !bIsOpen;

    if (bRotationMovement)
    {
        float Direction = 1.0f;

        if (bIsOpen)
        {
            TargetRotation = OpenAngle * Direction;
        }
        else
        {
            TargetRotation = 0.0f;
        }
    }
    else
    {
        if (bIsOpen)
        {
            FVector InitialLocation = MovingComponent->GetRelativeLocation();
            CurrentOffset = InitialLocation;
            TargetOffset = InitialLocation + OpenOffset;
        }
        else
        {
            FVector CurrentLocation = MovingComponent->GetRelativeLocation();
            CurrentOffset = CurrentLocation;
            TargetOffset = CurrentLocation - OpenOffset;
        }
    }
}

void UInteractionComponent::HandleReadMemo(AActor* Interactor)
{
    bIsRead = !bIsRead;

    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        if (AForgottenHUD* HUD = Cast<AForgottenHUD>(PC->GetHUD()))
        {
            if (bIsRead)
            {
                DialogueDelay = 0.5f;
                CanShowDialogue = true;
                FText MemoText = FText::FromString(MemoContent);
                HUD->ShowMemoWidget(MemoText);
            }
            else
            {
                CanShowDialogue = false;
                HUD->HideMemoWidget();
            }
        }
    }
    
}

void UInteractionComponent::HandleInspect(AActor* Interactor)
{
	CachedInteractor = Interactor;

    AForgottenCharacter* Player = Cast<AForgottenCharacter>(Interactor);

	if (!Player || !Player->FirstPersonCamera || !CachedInteractor)
	{
		return;
	}

    bIsInspect = !bIsInspect;

    if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
    {
        if (bIsInspect)
        {
            DialogueDelay = 0.8f;
            CanShowDialogue = true;
            GetWorld()->GetTimerManager().SetTimer(ZoomTimerHandle, this, &UInteractionComponent::ZoomIn, 0.01f, true);
            PC->SetIgnoreMoveInput(true);
            PC->SetIgnoreLookInput(true);
        }
        else
        {
            CanShowDialogue = false;
            GetWorld()->GetTimerManager().SetTimer(ZoomTimerHandle, this, &UInteractionComponent::ZoomOut, 0.01f, true);
            PC->SetIgnoreMoveInput(false);
            PC->SetIgnoreLookInput(false);
        }
    }
}

void UInteractionComponent::ZoomIn()
{
	AForgottenCharacter* Player = Cast<AForgottenCharacter>(CachedInteractor);
	if (!Player || !Player->FirstPersonCamera)
	{
		return;
	}
	Player->FirstPersonCamera->SetFieldOfView(ZoomedFOV);
}

void UInteractionComponent::ZoomOut()
{
	AForgottenCharacter* Player = Cast<AForgottenCharacter>(CachedInteractor);
	if (!Player || !Player->FirstPersonCamera)
	{
		return;
	}
	Player->FirstPersonCamera->SetFieldOfView(OriginalFOV);
}

void UInteractionComponent::HandlePickUp(AActor* Interactor)
{
    // 아이템 줍기 처리
    UE_LOG(LogTemp, Display, TEXT("Item picked up"));

    // 인벤토리에 추가하는 로직
    // 오너 액터를 제거하거나 숨김
    AActor* Owner = GetOwner();
    if (Owner)
    {
        Owner->SetActorHiddenInGame(true);
        Owner->SetActorEnableCollision(false);

        // 또는 완전히 제거
        // Owner->Destroy();
    }
}

void UInteractionComponent::HandleSit(AActor* Interactor)
{
    if (!SittingComponent)
    {
		return;
    }

    FVector ChairLocation = SittingComponent->GetComponentLocation();
    FRotator SitRotation = SittingComponent->GetComponentRotation();
    FVector SitLocation = FVector(ChairLocation.X, ChairLocation.Y + 30, Interactor->GetActorLocation().Z);

	bIsSit = !bIsSit;
    SetMonitorCollision();

    if (AForgottenCharacter* Player = Cast<AForgottenCharacter>(Interactor))
    {
        if (bIsSit)
        {
            Player->bSitting = bIsSit;
            Player->bMonitoring = true;
            Player->bUseControllerRotationYaw = false;
            Player->GetCharacterMovement()->bOrientRotationToMovement = false;

            Interactor->SetActorLocation(SitLocation, false, nullptr, ETeleportType::TeleportPhysics);
            Interactor->SetActorRotation(SitRotation);

            if (AController* PC = Player->GetController())
            {
                PC->SetControlRotation(SitRotation);  
            }

            Player->PlaySitAnimation();

        }
        else
        {
            Player->bSitting = bIsSit;
            Player->bMonitoring = false;
            Player->bUseControllerRotationYaw = true;
            Player->GetCharacterMovement()->bOrientRotationToMovement = true;

            Player->EnableInput(Cast<APlayerController>(Player->GetController()));

            Player->PlayStandUpAnimation();

            UForgottenGameInstance* GameInstance = Cast<UForgottenGameInstance>(GetWorld()->GetGameInstance());
            if (GameInstance->CurrentChapter == 1)
            {
                StartChapter2();
            }
            else if (GameInstance->CurrentChapter == 2)
            {
                bool ReadAdminNote = GameInstance->PlayerProgress.ProgressFlags.FindRef("ReadAdminNote");
                bool ReadAudio = GameInstance->PlayerProgress.ProgressFlags.FindRef("ReadAudio");

                if (ReadAdminNote && ReadAudio)
                {
                    GameInstance->SetChapter(3);
                    StartChapter3();
                    GameInstance->SaveGame();
                    GetWorld()->GetTimerManager().SetTimer(
                        QuitTimerHandle,
                        [this]() {
                            UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
                        },
                        8.0f,
                        false
                    );
                }
            }
        }
    }
}

void UInteractionComponent::HandleLie(AActor* Interactor)
{
    if (!LiyingComponent)
    {
        return;
    }

    FVector BedLocation = LiyingComponent->GetComponentLocation();
    FRotator LieRotation = LiyingComponent->GetComponentRotation();
    FVector LieLocation = FVector(BedLocation.X - 20, BedLocation.Y, Interactor->GetActorLocation().Z+10);

    bIsLie = !bIsLie;

    if (AForgottenCharacter* Player = Cast<AForgottenCharacter>(Interactor))
    {
        if (bIsLie)
        {
            DialogueDelay = 1.0f;
            CanShowDialogue = true;
            if (APlayerController* PC = Cast<APlayerController>(Player->GetController()))
            {
                PC->SetIgnoreMoveInput(true);
                PC->SetIgnoreLookInput(true);
                Player->DisableInput(PC);
            }

            Player->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            Player->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            Player->GetCharacterMovement()->GravityScale = 0.0f;

            Player->bLiying = bIsLie;

            Player->FirstPersonCamera->bUsePawnControlRotation = false;
            Player->GetCharacterMovement()->bOrientRotationToMovement = false;

            Interactor->SetActorLocation(LieLocation, false, nullptr, ETeleportType::TeleportPhysics);
            Interactor->SetActorRotation(LieRotation);

            if (AController* PC = Player->GetController())
            {
                PC->SetControlRotation(LieRotation);
            }

            Player->PlayLieAnimation();

        }
        else
        {
            CanShowDialogue = false;
            Player->bLiying = bIsLie;

            Player->bUseControllerRotationYaw = true;
            Player->GetCharacterMovement()->bOrientRotationToMovement = true;

            Player->EnableInput(Cast<APlayerController>(Player->GetController()));

            if (APlayerController* PC = Cast<APlayerController>(Player->GetController()))
            {
                PC->SetIgnoreMoveInput(false);
                PC->SetIgnoreLookInput(false);
            }

            Player->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            Player->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            Player->GetCharacterMovement()->GravityScale = 1.0f;
            Player->PlayWakeUpAnimation();

        }
    }
}

bool UInteractionComponent::IsInteractorInFront(AActor* Interactor)
{
    if (Interactor && GetOwner())
    {
        FVector OwnerForward = GetOwner()->GetActorForwardVector();

        FVector ToInteractor = Interactor->GetActorLocation() - GetOwner()->GetActorLocation();
        ToInteractor.Normalize();

        float DotProduct = FVector::DotProduct(OwnerForward, ToInteractor);

        return DotProduct > 0;
    }

    return true;
}

void UInteractionComponent::SetMonitorCollision()
{
    if (!MonitorComponent) return;

	if (bIsSit)
	{
		if (UBoxComponent* MonitorBox = Cast<UBoxComponent>(MonitorComponent))
		{
			MonitorBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
	}
	else
	{
		if (UBoxComponent* MonitorBox = Cast<UBoxComponent>(MonitorComponent))
		{
			MonitorBox->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		}
	}
}

void UInteractionComponent::HandleBreak(AActor* Interactor)
{
    if (!MirrorMeshComponent || !DefaultMirrorMaterial || !BrokenMirrorMaterial) return;

    DialogueDelay = 0.7f;
    CanShowDialogue = true;
    bIsBreak = true;
	MirrorMeshComponent->SetMaterial(0, BrokenMirrorMaterial);
}

void UInteractionComponent::StartChapter2()
{
    UForgottenGameInstance* GameInstance = Cast<UForgottenGameInstance>(GetWorld()->GetGameInstance());

    if (!GameInstance) return;

    bool ReadInternet = GameInstance->PlayerProgress.ProgressFlags.FindRef("ReadInternet");
    bool ReadMail = GameInstance->PlayerProgress.ProgressFlags.FindRef("ReadMail");
    bool ReadUserNote = GameInstance->PlayerProgress.ProgressFlags.FindRef("ReadUserNote");

    if (ReadInternet && ReadMail && ReadUserNote)
    {
        GameInstance->SetChapter(2);

        float DelayTime = 3.0f; 

        GetWorld()->GetTimerManager().SetTimer(
            LightTimerHandle,          
            this,                     
            &UInteractionComponent::OpeningChapter2, 
            DelayTime,                 
            false                    
        );
    }
}

void UInteractionComponent::OpeningChapter2()
{
	UWorld* World = GetWorld();
    ACharacter* Character = UGameplayStatics::GetPlayerCharacter(World, 0);
    if (!World || !Character) return;

    AForgottenCharacter* PlayerCharacter = Cast<AForgottenCharacter>(Character);
    if (!PlayerCharacter) return;

    UDialogueComponent* DialogueComp = PlayerCharacter->DialogueComponent;
    if (!DialogueComp) return;

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(World, TEXT("GlobalControllerTag"), FoundActors);

    DialogueComp->ActorType = "Story";
    DialogueComp->StartDialogueSequenceNoneActor(3.0f, 1.0f);

    for (AActor* Actor : FoundActors)
    {
        AGlobalActorController* GlobalController = Cast<AGlobalActorController>(Actor);
        if (GlobalController)
        {
            GlobalController->TriggerControllLightEvent();
        }
    }
}

void UInteractionComponent::StartChapter3()
{
    float DelayTime = 2.0f;

    GetWorld()->GetTimerManager().SetTimer(
        LightTimerHandle,
        this,
        &UInteractionComponent::OpeningChapter3,
        DelayTime,
        false
    );
}

void UInteractionComponent::OpeningChapter3()
{
    UWorld* World = GetWorld();
    ACharacter* Character = UGameplayStatics::GetPlayerCharacter(World, 0);
    if (!World || !Character) return;

    AForgottenCharacter* PlayerCharacter = Cast<AForgottenCharacter>(Character);
    if (!PlayerCharacter) return;

    UDialogueComponent* DialogueComp = PlayerCharacter->DialogueComponent;
    if (!DialogueComp) return;

    DialogueComp->ActorType = "2end";
    DialogueComp->StartDialogueSequenceNoneActor(3.0f, 1.0f);
}