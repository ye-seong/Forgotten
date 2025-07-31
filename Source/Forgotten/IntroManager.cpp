#include "IntroManager.h"
#include "ForgottenCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "Engine.h"
#include "ForgottenGameMode.h"
#include "DialogueComponent.h"
#include "ForgottenGameState.h"
#include "ForgottenGameInstance.h"

AIntroManager::AIntroManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AIntroManager::BeginPlay()
{
    Super::BeginPlay();
}

void AIntroManager::StartIntroSequence()
{
    UForgottenSaveGame* SaveGameData = Cast<UForgottenSaveGame>(UGameplayStatics::LoadGameFromSlot("Save_MainSlot", 0));
    if (AForgottenGameMode* GameMode = Cast<AForgottenGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
    {
        SpawnedCharacter = GameMode->GetPlayerCharacter();
    }
    if (!SpawnedCharacter || !SaveGameData) return;

    SpawnedCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SpawnedCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SpawnedCharacter->GetCharacterMovement()->GravityScale = 0.0f;

    SpawnedCharacter->SetActorLocation(SaveGameData->PlayerProgress.PlayerLocation + FVector(0, 20, 0));

    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PC && SpawnedCharacter)
    {
        PC->SetIgnoreMoveInput(true);
        PC->SetIgnoreLookInput(true);
    }
    
    PlayGetUpAnimation();

    UDialogueComponent* DialogueComp = SpawnedCharacter->DialogueComponent;
    if (!DialogueComp) return;
    DialogueComp->ActorType = "OP";
    DialogueComp->StartDialogueSequenceNoneActor(3.0f, 3.0f);
}

void AIntroManager::PlayGetUpAnimation()
{
    if (SpawnedCharacter && GetUpMontage)
    {
        SpawnedCharacter->FirstPersonCamera->bUsePawnControlRotation = false;
        float MontageDuration = SpawnedCharacter->PlayAnimMontage(GetUpMontage);
        GetWorld()->GetTimerManager().SetTimer(MontageEndHandle, this, &AIntroManager::EndIntroSequence, MontageDuration, false);
    }
    else
    {
        EndIntroSequence(); 
    }
}

void AIntroManager::EndIntroSequence()
{
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PC)
    {
        PC->SetIgnoreMoveInput(false);
        PC->SetIgnoreLookInput(false);
        SpawnedCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        SpawnedCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        SpawnedCharacter->GetCharacterMovement()->GravityScale = 1.0f;
        SpawnedCharacter->FirstPersonCamera->bUsePawnControlRotation = true;
    }
}