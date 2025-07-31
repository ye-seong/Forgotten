#include "ForgottenGameMode.h"
#include "IntroManager.h"
#include "ForgottenSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "ForgottenGameInstance.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "InteractionComponent.h"

AForgottenGameMode::AForgottenGameMode()
{
}

void AForgottenGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void AForgottenGameMode::StartPlay()
{
	Super::StartPlay();

	SetUpMapFromData();
}

void AForgottenGameMode::SpawnCharacter()
{
    if (!PlayerCharacterClass) return;

	UForgottenSaveGame* SaveGameData = Cast<UForgottenSaveGame>(UGameplayStatics::LoadGameFromSlot("Save_MainSlot", 0));
	if (!SaveGameData) return;

	UForgottenGameInstance* GameInstance = Cast<UForgottenGameInstance>(GetGameInstance());
	if (!GameInstance) return;

	GameInstance->LoadGame();

	FVector SpawnLocation = SaveGameData->PlayerProgress.PlayerLocation;
	FRotator SpawnRotation = SaveGameData->PlayerProgress.PlayerRotation;

    PlayerCharacter = GetWorld()->SpawnActor<AForgottenCharacter>(PlayerCharacterClass, SpawnLocation, SpawnRotation);
    if (!PlayerCharacter) return;

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->Possess(PlayerCharacter);
		PC->SetIgnoreMoveInput(false);
		PC->SetIgnoreLookInput(false);
		PlayerCharacter->FirstPersonCamera->bUsePawnControlRotation = true;
	}

	if (GameInstance->HasShownSubtitle(FName("LOG_1")) && GameInstance->HasShownSubtitle(FName("LOG_2")))
	{
		return;
	}

	if (FindIntroManager())
	{
		FindIntroManager()->StartIntroSequence();
		GameInstance->MarkSubtitleAsShown(FName("LOG_1"));
		GameInstance->MarkSubtitleAsShown(FName("LOG_2"));
	}
}

void AForgottenGameMode::SetUpMapFromData()
{
	UForgottenSaveGame* SaveGameData = Cast<UForgottenSaveGame>(UGameplayStatics::LoadGameFromSlot("Save_MainSlot", 0));
	if (!SaveGameData) return;
	
	FindMirrorAndChangeMaterial();
}

void AForgottenGameMode::FindMirrorAndChangeMaterial()
{
	UForgottenSaveGame* SaveGameData = Cast<UForgottenSaveGame>(UGameplayStatics::LoadGameFromSlot("Save_MainSlot", 0));
	bool MirrorBroken = SaveGameData->PlayerProgress.ProgressFlags.FindRef("MirrorBroken");
	if (!MirrorBroken) return;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Mirror", FoundActors);

	for (AActor* Actor : FoundActors)
	{
		if (!Actor) break;
		UInteractionComponent* InteractionComp = Actor->FindComponentByClass<UInteractionComponent>();
		if (InteractionComp)
		{
			InteractionComp->HandleBreak(Actor);
		}
	}
}