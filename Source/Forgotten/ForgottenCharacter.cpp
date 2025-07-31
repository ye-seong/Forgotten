#include "ForgottenCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "InteractableInterface.h"
#include "DrawDebugHelpers.h"
#include "InteractionComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ForgottenHUD.h"
#include "Components/HorizontalBox.h"
#include "Components/BoxComponent.h"
#include "ForgottenGameInstance.h"
#include "Kismet/GameplayStatics.h"

AForgottenCharacter::AForgottenCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    DialogueComponent = CreateDefaultSubobject<UDialogueComponent>(TEXT("DialogueComponent"));

    FocusedInteractable = nullptr;
    bShowInteractionUI = false;
}

void AForgottenCharacter::BeginPlay()
{
	Super::BeginPlay();

    if (FirstPersonCamera && GetMesh())
    {
        FirstPersonCamera->AttachToComponent(
            GetMesh(),
            FAttachmentTransformRules::SnapToTargetNotIncludingScale,
            FName("CameraSocket")
        );
    }

    if (UserInterfaceWidgetClass)
    {
        UserInterfaceWidget = CreateWidget<UUserWidget>(GetWorld(), UserInterfaceWidgetClass);
        if (UserInterfaceWidget)
        {
            UserInterfaceWidget->AddToViewport(10);
            UserInterfaceWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
        }
    }

}

void AForgottenCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    CheckForInteractables();
    ShowInteractionWidget();
}

void AForgottenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("Use", IE_Pressed, this, &AForgottenCharacter::UseMonitor);
    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AForgottenCharacter::Interact);
    PlayerInputComponent->BindAction("Exit", IE_Pressed, this, &AForgottenCharacter::PressEscButton);
}

void AForgottenCharacter::CheckForInteractables()
{
    // 이전 프레임에 포커스된 인터랙션 컴포넌트가 있으면 포커스 해제
    if (FocusedInteractable)
    {
        UInteractionComponent* InteractionComp = Cast<UInteractionComponent>(FocusedInteractable);
        if (InteractionComp)
        {
            InteractionComp->SetFocus(false, this);
        }

        if (!bSitting && !bLiying)
        {
            FocusedInteractable = nullptr;
            bShowInteractionUI = false;
        }
        else
        {
            InteractionText = InteractionComp->GetInteractionText();
        }
    }

    FHitResult HitResult;
    FVector Start = FirstPersonCamera->GetComponentLocation();
    FVector End = Start + FirstPersonCamera->GetForwardVector() * 10000.f;

    // 디버그용 라인 트레이스 시각화 (개발 중에만 사용)
//#if WITH_EDITOR
//    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1.0f, 0, 1.0f);
//#endif

    // 라인 트레이스로 상호작용 가능한 객체 감지
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);

    if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, QueryParams))
    {
        AActor* HitActor = HitResult.GetActor();
        FocusedComponent = HitResult.GetComponent();
        if (!HitActor) return;

        float HitDistance = FVector::Dist(Start, HitResult.ImpactPoint);
        float IntDistance = FVector::Dist(Start, Start + FirstPersonCamera->GetForwardVector() * InteractionDistance);
                
        // 히트된 액터에서 인터랙션 컴포넌트 찾기
        if (UInteractionComponent* InteractionComp = HitActor->FindComponentByClass<UInteractionComponent>())
        {
            if (HitDistance > IntDistance && InteractionComp->InteractionType != EInteractionType::Inspect)
            {
                return;
            }

            FocusedInteractable = InteractionComp;
            InteractionComp->SetFocus(true, this);
            InteractionText = InteractionComp->GetInteractionText();
            bShowInteractionUI = true;
        }
    }
}

void AForgottenCharacter::ShowInteractionText()
{
    if (!UserInterfaceWidget) return;

    UHorizontalBox* PromptBox = Cast<UHorizontalBox>(UserInterfaceWidget->GetWidgetFromName("PromptBox"));
    UHorizontalBox* PromptBox2 = Cast<UHorizontalBox>(UserInterfaceWidget->GetWidgetFromName("PromptBox2"));

    if (bShowInteractionUI)
    {
        PromptBox->SetVisibility(ESlateVisibility::HitTestInvisible);
        PromptBox2->SetVisibility(ESlateVisibility::HitTestInvisible);
    }
    else
    {
        PromptBox->SetVisibility(ESlateVisibility::Hidden);
        PromptBox2->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AForgottenCharacter::ShowInteractionWidget()
{
    if (UserInterfaceWidget)
    {
        ShowInteractionText();
        if (bShowInteractionUI)
        {
            UTextBlock* PromptText = Cast<UTextBlock>(UserInterfaceWidget->GetWidgetFromName("PromptText"));
            UTextBlock* PromptKey = Cast<UTextBlock>(UserInterfaceWidget->GetWidgetFromName("PromptKey"));
            UTextBlock* PromptText2 = Cast<UTextBlock>(UserInterfaceWidget->GetWidgetFromName("PromptText2"));
            UHorizontalBox* PromptBox2 = Cast<UHorizontalBox>(UserInterfaceWidget->GetWidgetFromName("PromptBox2"));

            if (PromptText)
            {
                PromptText->SetText(FText::FromString(InteractionText));
            }
            if (bSitting)
            {
                if (PromptBox2 && PromptText2 && PromptKey)
				{
					if (bUsingMonitor)
					{
                        PromptBox2->SetVisibility(ESlateVisibility::Hidden);
                        PromptText->SetText(FText::FromString("Quit"));
                        PromptKey->SetText(FText::FromString("[E]"));
					}
                    else if (UInteractionComponent* InteractionComp = Cast<UInteractionComponent>(FocusedInteractable))
                    {
                        UBoxComponent* MonitorBox = Cast<UBoxComponent>(InteractionComp->MonitorComponent);

                        if (MonitorBox && FocusedComponent == MonitorBox)
                        {
                            PromptBox2->SetVisibility(ESlateVisibility::HitTestInvisible);
                            PromptText2->SetText(FText::FromString("Use Monitor"));
                            PromptKey->SetText(FText::FromString("[F]"));
                        }
                        else
                        {
                            PromptBox2->SetVisibility(ESlateVisibility::Hidden);
                            PromptKey->SetText(FText::FromString("[F]"));
                        }
                    }
                    else
                    {
                        PromptKey->SetText(FText::FromString("[F]"));
                        PromptBox2->SetVisibility(ESlateVisibility::Hidden);
                    }
				}
            }
            else
            {
                PromptBox2->SetVisibility(ESlateVisibility::Hidden);
            }
        }
    }
}

void AForgottenCharacter::Interact()
{   
    AActor* OwnerActor = GetOwner();
    if (!OwnerActor)
        return;

    UInteractionComponent* InteractionComp = Cast<UInteractionComponent>(FocusedInteractable);
    UDialogueComponent* DialogueComp = FindComponentByClass<UDialogueComponent>();

	if (bUsingMonitor)
	{
		return;
	}
    // 포커스된 인터랙션 컴포넌트가 있을 때만 상호작용
    if (FocusedInteractable || bSitting || bLiying)
    {
        if (InteractionComp)
        {
            InteractionComp->Interact(this);
            if (DialogueComp && InteractionComp->CanShowDialogue)
            {
                FString DialogueType = InteractionComp->DialogueType;
                DialogueComp->ActorType = DialogueType;
                DialogueComp->StartDialogueSequence(3.0f, InteractionComp);
            }
            else
            {
                InteractionComp->CanShowDialogue = false;
            }
        }
    }
}

void AForgottenCharacter::UseMonitor()
{
    if (!bMonitoring) return;

    UForgottenGameInstance* GameInstance = Cast<UForgottenGameInstance>(GetGameInstance());

    if (!GameInstance) return;

    if (FocusedInteractable)
    {
        if (UInteractionComponent* InteractionComp = Cast<UInteractionComponent>(FocusedInteractable))
        {
            UBoxComponent* MonitorBox = Cast<UBoxComponent>(InteractionComp->MonitorComponent);
            if (MonitorBox != FocusedComponent) return;
        }
    }

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (AForgottenHUD* HUD = Cast<AForgottenHUD>(PC->GetHUD()))
        {
            bUsingMonitor = !bUsingMonitor;
            
            if (bUsingMonitor)
            {
                if (GameInstance->CurrentChapter == 1)
                {
                    HUD->ShowUserMonitorWidget();

                    if (HUD->UserMonitorWidget)
                    {
                        FInputModeGameAndUI InputMode;
                        InputMode.SetWidgetToFocus(HUD->UserMonitorWidget->TakeWidget());
                        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                        PC->SetInputMode(InputMode);
                        PC->bShowMouseCursor = true;
                    }
                }
                else if (GameInstance->CurrentChapter == 2)
                {
                    HUD->ShowAdminMonitorWidget();

                    if (HUD->AdminMonitorWidget)
                    {
                        FInputModeGameAndUI InputMode;
                        InputMode.SetWidgetToFocus(HUD->AdminMonitorWidget->TakeWidget());
                        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                        PC->SetInputMode(InputMode);
                        PC->bShowMouseCursor = true;
                    }
                }
            }
            else
            {
                if (GameInstance->CurrentChapter == 1)
                {
                    HUD->HideUserMonitorWidget();
                    FInputModeGameOnly InputMode;

                    PC->SetInputMode(InputMode);
                    PC->bShowMouseCursor = false;
                }
                else if (GameInstance->CurrentChapter == 2)
                {
                    HUD->HideAdminMonitorWidget();
                    FInputModeGameOnly InputMode;

                    PC->SetInputMode(InputMode);
                    PC->bShowMouseCursor = false;
                }
            }
        }
    }
    
}

void AForgottenCharacter::PlaySitAnimation()
{
    if (SitMontage && GetMesh())
    {
        PlayAnimMontage(SitMontage);

        AController* PC = GetController();
        if (PC)
        {
            PC->StopMovement();
        }

        DisableInput(Cast<APlayerController>(PC));
    }
}

void AForgottenCharacter::PlayStandUpAnimation()
{
    if (StandUpMontage && GetMesh())
    {
        PlayAnimMontage(StandUpMontage);

        AController* PC = GetController();
        if (PC)
        {
            PC->StopMovement();
        }

        DisableInput(Cast<APlayerController>(PC));
    }
}

void AForgottenCharacter::PlayLieAnimation()
{
    if (LieMontage && GetMesh())
    {
        PlayAnimMontage(LieMontage);

        AController* PC = GetController();
        if (PC)
        {
            PC->StopMovement();
        }

        DisableInput(Cast<APlayerController>(PC));
    }
}

void AForgottenCharacter::PlayWakeUpAnimation()
{
    if (WakeUpMontage && GetMesh())
    {
        PlayAnimMontage(WakeUpMontage);

        AController* PC = GetController();
        if (PC)
        {
            PC->StopMovement();
        }

        DisableInput(Cast<APlayerController>(PC));
    }
}

void AForgottenCharacter::PressEscButton()
{
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (!PC) return;
    AForgottenHUD* HUD = Cast<AForgottenHUD>(PC->GetHUD());
    if (!HUD) return;

    if (!HUD->EscMenuWidgetClass || HUD->EscMenuWidget) return;

    FInputModeGameAndUI InputMode;

    HUD->ShowEscMenuWidget();
    UGameplayStatics::SetGamePaused(GetWorld(), true);

    if (!HUD->EscMenuWidget) return;

    InputMode.SetWidgetToFocus(HUD->EscMenuWidget->TakeWidget());
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PC->bShowMouseCursor = true;
    PC->SetIgnoreMoveInput(true);
    PC->SetIgnoreLookInput(true);

    PC->SetInputMode(InputMode);
}

void AForgottenCharacter::PressContinueButton()
{
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (!PC) return;
    AForgottenHUD* HUD = Cast<AForgottenHUD>(PC->GetHUD());
    if (!HUD) return;

	if (!HUD->EscMenuWidgetClass || !HUD->EscMenuWidget) return;

	FInputModeGameOnly InputMode;

    HUD->HideEscMenuWidget();
    UGameplayStatics::SetGamePaused(GetWorld(), false);

    PC->bShowMouseCursor = false;
    PC->SetIgnoreMoveInput(false);
    PC->SetIgnoreLookInput(false);

    PC->SetInputMode(InputMode);

	HUD->EscMenuWidget = nullptr;
}