#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PlayerProgress.h"
#include "ForgottenSaveGame.generated.h"

UCLASS()
class FORGOTTEN_API UForgottenSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    UPROPERTY(VisibleAnywhere, Category = "Save Data")
    FPlayerProgress PlayerProgress;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
    FString PlayerName;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
    FString CurrentLevel;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State")
    int32 CurrentChapter;
};
