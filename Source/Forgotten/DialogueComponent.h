#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "UObject/NameTypes.h" 
#include "Containers/UnrealString.h"
#include "Internationalization/Text.h"
#include "ForgottenGameInstance.h"
class UInteractionComponent;
#include "DialogueComponent.generated.h"

USTRUCT(BlueprintType)
struct FDialogueData : public FTableRowBase
{
	GENERATED_BODY()

public:
    FDialogueData() : ID(0) {}

    UPROPERTY()
    int32 Chapter;

    UPROPERTY()
    FString Type;

    UPROPERTY()
    int32 ID;

    UPROPERTY()
    FString Character;

    UPROPERTY()
    FString Text;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FORGOTTEN_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDialogueComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    UDataTable* DialogueTable;

    FString ActorType;

    TArray<FString> GetAllDialogues();

	void ShowNextDialogue();
    
    void StartDialogueSequence(float DelayBetweenDialogues, UInteractionComponent* TargetActor);

    void StartDialogueSequenceNoneActor(float DelayBetweenDialogues, float DialogueDelay);

protected:
    virtual void BeginPlay() override;

private:
    FTimerHandle DialogueTimerHandle;

    TArray<FDialogueData*> AllRows;

    TArray<FString> DialogueQueue;

    float DelayTime;

    int32 CurrentChapter;

    int32 CurrentID;

    UPROPERTY()
    UInteractionComponent* CurrentTargetActor;

	UForgottenGameInstance* GameInstance;
};
