#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayerProgress.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "ForgottenGameInstance.generated.h"

UCLASS()
class FORGOTTEN_API UForgottenGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Instance")
	FPlayerProgress PlayerProgress;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Instance")
	int32 CurrentChapter;

	UFUNCTION(BlueprintCallable)
	void SetFlag(const FString& FlagName, bool bValue)
	{
		PlayerProgress.ProgressFlags.Add(FlagName, bValue);
	}

	UFUNCTION(BlueprintCallable)
	bool GetFlag(const FString& FlagName)
	{
		if (bool* Found = PlayerProgress.ProgressFlags.Find(FlagName))
			return *Found;
		return false;
	}

	UFUNCTION(BlueprintCallable)
	void SetChapter(int32 NewChapter)
	{
		CurrentChapter = NewChapter;
	}	

	UFUNCTION(BlueprintCallable)
	bool SaveGame(int32 SlotIndex = 0);

	UFUNCTION(BlueprintCallable)
	bool LoadGame(int32 SlotIndex = 0);

	UFUNCTION(BlueprintCallable)
	bool CreateDefaultSaveGame();

	UFUNCTION(BlueprintCallable)
	bool DeleteSaveGame(int32 SlotIndex = 0)
	{
		if (!UGameplayStatics::DoesSaveGameExist("Save_MainSlot", 0)) return false;
		UGameplayStatics::DeleteGameInSlot("Save_MainSlot", 0);
		return true;
	}

	UFUNCTION(BlueprintCallable)
	bool DoesSaveGameExist(int32 SlotIndex = 0)
	{
		return UGameplayStatics::DoesSaveGameExist(GetSaveSlotName(SlotIndex), 0);
	}

	void MarkSubtitleAsShown(FName RowName)
	{
		if (!PlayerProgress.ShownSubtitleRows.Contains(RowName))
		{
			PlayerProgress.ShownSubtitleRows.Add(RowName);
		}
	}

	bool HasShownSubtitle(FName RowName)
	{
		return PlayerProgress.ShownSubtitleRows.Contains(RowName);
	}

private:
	UPROPERTY()
	class UForgottenSaveGame* CurrentSaveGame;
	
	FString GetSaveSlotName(int32 SlotIndex) const
	{
		return "Save_MainSlot";
	}
};
