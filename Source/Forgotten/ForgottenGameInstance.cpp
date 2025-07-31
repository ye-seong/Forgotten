#include "ForgottenGameInstance.h"
#include "ForgottenSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "ForgottenGameMode.h"

void UForgottenGameInstance::Init()
{
	Super::Init();
}

bool UForgottenGameInstance::SaveGame(int32 SlotIndex)
{
	UForgottenSaveGame* SaveInstance = Cast<UForgottenSaveGame>(UGameplayStatics::LoadGameFromSlot("Save_MainSlot", 0));
	if (!SaveInstance) return false;

	SaveInstance->CurrentLevel = UGameplayStatics::GetCurrentLevelName(GetWorld());
	SaveInstance->CurrentChapter = CurrentChapter;
	SaveInstance->PlayerProgress.ProgressFlags = PlayerProgress.ProgressFlags;
	SaveInstance->PlayerProgress.PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	SaveInstance->PlayerProgress.PlayerRotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();
	
	for (FName SubtitleRow : PlayerProgress.ShownSubtitleRows)
	{
		if (!SaveInstance->PlayerProgress.ShownSubtitleRows.Contains(SubtitleRow))
		{
			SaveInstance->PlayerProgress.ShownSubtitleRows.Add(SubtitleRow);
		}
	}

	UGameplayStatics::DeleteGameInSlot("Save_MainSlot", 0);
	UGameplayStatics::SaveGameToSlot(SaveInstance, "Save_MainSlot", 0);

	return true;
}

bool UForgottenGameInstance::LoadGame(int32 SlotIndex)
{
	UForgottenSaveGame* LoadInstance = Cast<UForgottenSaveGame>(UGameplayStatics::LoadGameFromSlot("Save_MainSlot", 0));
	if (!LoadInstance) return false;

	PlayerProgress = LoadInstance->PlayerProgress;
	CurrentChapter = LoadInstance->CurrentChapter;

	return true;
}

bool UForgottenGameInstance::CreateDefaultSaveGame()
{
	AForgottenGameMode* GameMode = Cast<AForgottenGameMode>(GetWorld()->GetAuthGameMode());
	UForgottenSaveGame* DefaultSave = Cast<UForgottenSaveGame>(UGameplayStatics::CreateSaveGameObject(UForgottenSaveGame::StaticClass()));

	if (!GameMode || !DefaultSave) return false;

	AIntroManager* IntroManager = GameMode ? GameMode->FindIntroManager() : nullptr;

	if (!IntroManager) return false;

	DefaultSave->PlayerName = "";
	DefaultSave->CurrentLevel = "LV_SingleRoom";
	DefaultSave->CurrentChapter = 1;

	if (!IntroManager->BedActor || !GameMode->PlayerCharacterClass) return false;

	DefaultSave->PlayerProgress.PlayerLocation = IntroManager->BedActor->GetActorLocation() + FVector(0, 0, 90);
	DefaultSave->PlayerProgress.PlayerRotation = IntroManager->BedActor->GetActorRotation() + FRotator(0, -180, 0);

	DefaultSave->PlayerProgress.ProgressFlags.Add("BedUsed", false);
	DefaultSave->PlayerProgress.ProgressFlags.Add("Inspect", false);
	DefaultSave->PlayerProgress.ProgressFlags.Add("ReadMemo", false);
	DefaultSave->PlayerProgress.ProgressFlags.Add("MirrorBroken", false);

	UGameplayStatics::SaveGameToSlot(DefaultSave, "Save_MainSlot", 0);

	return true;
}