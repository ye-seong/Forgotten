#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ForgottenCharacter.h"
#include "EngineUtils.h"
#include "IntroManager.h"
#include "ForgottenSaveGame.h"
#include "ForgottenGameMode.generated.h"

UCLASS()
class FORGOTTEN_API AForgottenGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AForgottenGameMode();

	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere, Category = "Player")
	TSubclassOf<AForgottenCharacter> PlayerCharacterClass;

	UPROPERTY(BlueprintReadOnly, Category = "Player")
	AForgottenCharacter* PlayerCharacter;

	UFUNCTION(BlueprintPure, Category = "Player")
	AForgottenCharacter* GetPlayerCharacter() const
	{
		return PlayerCharacter;
	}

	UFUNCTION(BlueprintCallable, Category = "Player")
	void SpawnCharacter();

	AIntroManager* FindIntroManager() const
	{
		for (TActorIterator<AIntroManager> It(GetWorld()); It; ++It)
		{
			return *It;
		}
		return nullptr;
	}

protected:
	virtual void BeginPlay() override;

	void SetUpMapFromData();

	void FindMirrorAndChangeMaterial();
};
