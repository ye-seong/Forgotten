#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ForgottenCharacter.h"
#include "IntroManager.generated.h"

class AForgottencharacter;
class AActor;

UCLASS()
class FORGOTTEN_API AIntroManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AIntroManager();

    UPROPERTY(EditAnywhere, Category = "Intro")
    AActor* BedActor;

    void StartIntroSequence();

protected:
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Intro")
    UAnimMontage* GetUpMontage;

    UPROPERTY(EditAnywhere, Category = "Intro")
    float EyeBlinkDuration = 2.0f;

    FTimerHandle EyeBlinkHandle;
    FTimerHandle MontageEndHandle;

    void PlayGetUpAnimation();
    void EndIntroSequence();

public:	
    AForgottenCharacter* SpawnedCharacter;
};
