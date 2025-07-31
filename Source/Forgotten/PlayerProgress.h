#pragma once

#include "CoreMinimal.h"
#include "PlayerProgress.generated.h"

USTRUCT(BlueprintType)
struct FORGOTTEN_API FPlayerProgress
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player State")
	FVector PlayerLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player State")
	FRotator PlayerRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player State")
	TMap<FString, bool> ProgressFlags;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player State")
	TArray<FName> ShownSubtitleRows;
};