#include "DialogueComponent.h"
#include "Engine/World.h" 
#include "Blueprint/UserWidget.h" 
#include "Components/TextBlock.h"
#include "TimerManager.h"       
#include "ForgottenCharacter.h"
#include "InteractionComponent.h"
#include "Engine/Engine.h"
#include "ForgottenGameInstance.h"

UDialogueComponent::UDialogueComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    
}

void UDialogueComponent::BeginPlay()
{
    Super::BeginPlay();

    if (DialogueTable)
    {
        FString ContextString;
        DialogueTable->GetAllRows<FDialogueData>(ContextString, AllRows);
    }
	GameInstance = Cast<UForgottenGameInstance>(GetWorld()->GetGameInstance());

	if (!GameInstance) return;

    CurrentChapter = GameInstance->CurrentChapter;
    CurrentID = 1;
}

TArray<FString> UDialogueComponent::GetAllDialogues()
{
    TArray<FString> Dialogues;

    GameInstance = Cast<UForgottenGameInstance>(GetWorld()->GetGameInstance());
    if (!GameInstance) return Dialogues;
    CurrentChapter = GameInstance->CurrentChapter;

    for (FDialogueData* Row : AllRows)
    {
        if (Row && Row->Chapter == CurrentChapter && Row->Type == ActorType)
        {
            Dialogues.Add(Row->Text);
        }
    }
    return Dialogues;
}

void UDialogueComponent::ShowNextDialogue()
{
    AForgottenCharacter* OwnerChar = Cast<AForgottenCharacter>(GetOwner());
    if (!OwnerChar) return;
    UUserWidget* UIWidget = OwnerChar->UserInterfaceWidget;
    if (!UIWidget) return;
    UTextBlock* TextBlock = Cast<UTextBlock>(UIWidget->GetWidgetFromName(TEXT("DialogueText")));
    if (!TextBlock) return;

    CurrentID++;

    if (CurrentID >= DialogueQueue.Num())
    {
        TextBlock->SetVisibility(ESlateVisibility::Hidden);
        if (CurrentTargetActor)
        {
            CurrentTargetActor->CanShowDialogue = false;
        }
        return;
    }

    TextBlock->SetText(FText::FromString(DialogueQueue[CurrentID]));
    TextBlock->SetVisibility(ESlateVisibility::Visible);

    GetWorld()->GetTimerManager().SetTimer(
        DialogueTimerHandle,
        this,
        &UDialogueComponent::ShowNextDialogue,
        DelayTime,
        false
    );
}

void UDialogueComponent::StartDialogueSequence(float DelayBetweenDialogues, UInteractionComponent* TargetActor)
{
    if (!TargetActor) return;
    CurrentTargetActor = TargetActor;
    GetWorld()->GetTimerManager().ClearTimer(DialogueTimerHandle);
    AForgottenCharacter* OwnerChar = Cast<AForgottenCharacter>(GetOwner());
    if (!OwnerChar) return;
    UUserWidget* UIWidget = OwnerChar->UserInterfaceWidget;
    if (!UIWidget) return;
    UTextBlock* TextBlock = Cast<UTextBlock>(UIWidget->GetWidgetFromName(TEXT("DialogueText")));
    if (!TextBlock) return;

    DialogueQueue = GetAllDialogues();
    CurrentID = -1;
    DelayTime = DelayBetweenDialogues > 0.0f ? DelayBetweenDialogues : 3.0f;

    FTimerHandle WaitHandle;
    GetWorld()->GetTimerManager().SetTimer(
        WaitHandle,
        [this, TargetActor]() {
            if (DialogueQueue.Num() > 0 && TargetActor && TargetActor->CanShowDialogue)
            {
                ShowNextDialogue();
            }
        },
        TargetActor->DialogueDelay,
        false
    );
}

void UDialogueComponent::StartDialogueSequenceNoneActor(float DelayBetweenDialogues, float DialogueDelay)
{
    GetWorld()->GetTimerManager().ClearTimer(DialogueTimerHandle);
    AForgottenCharacter* OwnerChar = Cast<AForgottenCharacter>(GetOwner());
    if (!OwnerChar) return;
    UUserWidget* UIWidget = OwnerChar->UserInterfaceWidget;
    if (!UIWidget) return;
    UTextBlock* TextBlock = Cast<UTextBlock>(UIWidget->GetWidgetFromName(TEXT("DialogueText")));
    if (!TextBlock) return;

    CurrentTargetActor = nullptr;
    DialogueQueue = GetAllDialogues();
    CurrentID = -1;
    DelayTime = DelayBetweenDialogues > 0.0f ? DelayBetweenDialogues : 3.0f;

    FTimerHandle WaitHandle;
    GetWorld()->GetTimerManager().SetTimer(
        WaitHandle,
        [this]() {
            if (DialogueQueue.Num() > 0)
            {
                ShowNextDialogue();
            }
        },
        DialogueDelay,
        false
    );
}