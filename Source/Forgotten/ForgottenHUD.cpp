#include "ForgottenHUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ForgottenCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "ForgottenGameMode.h"
#include "ForgottenGameInstance.h"

AForgottenHUD::AForgottenHUD()
{
}

void AForgottenHUD::BeginPlay()
{
	Super::BeginPlay();
    GameInstance = Cast<UForgottenGameInstance>(GetGameInstance());
}

void AForgottenHUD::ShowMenuWidget()
{
    if (MenuWidgetClass)
    {
        MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
        MenuWidget->AddToViewport();
    }

    if (MenuWidget)
    {
        APlayerController* PC = GetOwningPlayerController();
        if (PC)
        {
            PC->SetIgnoreMoveInput(true);
            PC->SetIgnoreLookInput(true);
        }
    }
}

void AForgottenHUD::HideMenuWidget()
{
    if (MenuWidgetClass && MenuWidget)
    {
        APlayerController* PC = GetOwningPlayerController();
        if (PC)
        {
            PC->SetIgnoreMoveInput(false);
            PC->SetIgnoreLookInput(false);
        }

        MenuWidget->RemoveFromViewport();
        MenuWidget = nullptr;
    }
}

void AForgottenHUD::ShowMemoWidget(const FText& MemoText)
{
    if (MemoWidgetClass && !MemoWidget)
    {
        MemoWidget = CreateWidget<UUserWidget>(GetWorld(), MemoWidgetClass);
        MemoWidget->AddToViewport();
    }

    if (MemoWidget)
    {
        if (MemoWidget)
        {
            UTextBlock* TextBlock = Cast<UTextBlock>(MemoWidget->GetWidgetFromName("MemoText"));
            if (TextBlock)
            {
                TextBlock->SetText(MemoText);
            }
            APlayerController* PC = GetOwningPlayerController();
            if (PC)
            {
                PC->SetIgnoreMoveInput(true);
                PC->SetIgnoreLookInput(true);
            }
        }
    }
}

void AForgottenHUD::HideMemoWidget()
{
    if (MemoWidgetClass && MemoWidget)
    {
        APlayerController* PC = GetOwningPlayerController();
        if (PC)
        {
            PC->SetIgnoreMoveInput(false);
            PC->SetIgnoreLookInput(false);
        }

        MemoWidget->RemoveFromViewport();
        MemoWidget = nullptr;
    }
}

void AForgottenHUD::ShowUserMonitorWidget()
{
    if (UserMonitorWidgetClass && !UserMonitorWidget)
    {
        UserMonitorWidget = CreateWidget<UUserWidget>(GetWorld(), UserMonitorWidgetClass);
        UserMonitorWidget->AddToViewport();
        UserMonitorWidget->SetVisibility(ESlateVisibility::Visible);
    }

    if (APlayerController* PC = GetOwningPlayerController())
    {
        PC->SetIgnoreMoveInput(true);
        PC->SetIgnoreLookInput(true);
    }
}

void AForgottenHUD::HideUserMonitorWidget()
{
    if (UserMonitorWidgetClass && UserMonitorWidget)
    {
        APlayerController* PC = GetOwningPlayerController();
        if (PC)
        {
            PC->SetIgnoreMoveInput(false);
            PC->SetIgnoreLookInput(false);
        }

        UserMonitorWidget->RemoveFromViewport();
        UserMonitorWidget = nullptr;
    }
}

void AForgottenHUD::ShowAdminMonitorWidget()
{
    if (!GameInstance) return;
    if (AdminMonitorWidgetClass)
    {
        if (!AdminMonitorWidget)
        {
            AdminMonitorWidget = CreateWidget<UUserWidget>(GetWorld(), AdminMonitorWidgetClass);
            AdminMonitorWidget->AddToViewport();
            if (!GameInstance->HasShownSubtitle("LOG_17"))
            {
                ShowDialogueFromWidget("Monitor");
                GameInstance->MarkSubtitleAsShown("LOG_17");
            }
        }
        AdminMonitorWidget->SetVisibility(ESlateVisibility::Visible);
    }

    if (APlayerController* PC = GetOwningPlayerController())
    {
        PC->SetIgnoreMoveInput(true);
        PC->SetIgnoreLookInput(true);
    }
}

void AForgottenHUD::HideAdminMonitorWidget()
{
    if (AdminMonitorWidgetClass && AdminMonitorWidget)
    {
        APlayerController* PC = GetOwningPlayerController();
        if (PC)
        {
            PC->SetIgnoreMoveInput(false);
            PC->SetIgnoreLookInput(false);
        }

        AdminMonitorWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void AForgottenHUD::ShowInternetWindowWidget()
{
    if (InternetWindowWidgetClass && !InternetWindowWidget)
    {
        InternetWindowWidget = CreateWidget<UUserWidget>(GetWorld(), InternetWindowWidgetClass);
        InternetWindowWidget->AddToViewport();
        ShowDialogueFromWidget("Internet");

        if (!GameInstance) return;
        GameInstance->PlayerProgress.ProgressFlags.Add("ReadInternet", true);
    }
}

void AForgottenHUD::HideInternetWidowWidget()
{
	if (InternetWindowWidgetClass && InternetWindowWidget)
	{
        InternetWindowWidget->RemoveFromViewport();
        InternetWindowWidget = nullptr;
	}
}

void AForgottenHUD::ShowMailWidget()
{
    if (MailWidgetClass && !MailWidget)
    {
        MailWidget = CreateWidget<UUserWidget>(GetWorld(), MailWidgetClass);
        MailWidget->AddToViewport();
        ShowDialogueFromWidget("Mail");

        if (!GameInstance) return;
        GameInstance->PlayerProgress.ProgressFlags.Add("ReadMail", true);
    }
}

void AForgottenHUD::HideMailWidget()
{
    if (MailWidgetClass && MailWidget)
    {
        MailWidget->RemoveFromViewport();
        MailWidget = nullptr;
    }
}

void AForgottenHUD::ShowUserNoteWidget()
{
    if (UserNoteWidgetClass && !UserNoteWidget)
    {
        UserNoteWidget = CreateWidget<UUserWidget>(GetWorld(), UserNoteWidgetClass);
        UserNoteWidget->AddToViewport();

        if (!GameInstance) return;
        GameInstance->PlayerProgress.ProgressFlags.Add("ReadUserNote", true);
    }
}

void AForgottenHUD::HideUserNoteWidget()
{
    if (UserNoteWidgetClass && UserNoteWidget)
    {
        UserNoteWidget->RemoveFromViewport();
        UserNoteWidget = nullptr;
    }
}

void AForgottenHUD::ShowAdminNoteWidget()
{
    if (AdminNoteWidgetClass && !AdminNoteWidget)
    {
        AdminNoteWidget = CreateWidget<UUserWidget>(GetWorld(), AdminNoteWidgetClass);
        AdminNoteWidget->AddToViewport();

        if (!GameInstance) return;
        GameInstance->PlayerProgress.ProgressFlags.Add("ReadAdminNote", true);
    }
}

void AForgottenHUD::HideAdminNoteWidget()
{
    if (AdminNoteWidgetClass && AdminNoteWidget)
    {
        AdminNoteWidget->RemoveFromViewport();
        AdminNoteWidget = nullptr;
    }
}

void AForgottenHUD::ShowAudioWidget()
{
    if (AudioWidgetClass && !AudioWidget)
    {
        AudioWidget = CreateWidget<UUserWidget>(GetWorld(), AudioWidgetClass);
        AudioWidget->AddToViewport();
        ShowDialogueFromWidget("Audio");

        if (!GameInstance) return;
        GameInstance->PlayerProgress.ProgressFlags.Add("ReadAudio", true);
    }
}

void AForgottenHUD::HideAudioWidget()
{
    if (AudioWidgetClass && AudioWidget)
    {
        AudioWidget->RemoveFromViewport();
        AudioWidget = nullptr;
    }
}

void AForgottenHUD::ShowEscMenuWidget()
{
	if (EscMenuWidgetClass && !EscMenuWidget)
	{
		EscMenuWidget = CreateWidget<UUserWidget>(GetWorld(), EscMenuWidgetClass);
		EscMenuWidget->AddToViewport();
	}
}

void AForgottenHUD::HideEscMenuWidget()
{
    if (EscMenuWidgetClass && EscMenuWidget)
    {
        EscMenuWidget->RemoveFromViewport();
        EscMenuWidget = nullptr;
    }
}

void AForgottenHUD::ShowDialogueFromWidget(FString WidgetType)
{
    AForgottenGameMode* GameMode = Cast<AForgottenGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (!GameMode) return;
    if (AForgottenCharacter* OwnerChar = GameMode->PlayerCharacter)
    {
        if (UDialogueComponent* DialogueComp = OwnerChar->FindComponentByClass<UDialogueComponent>())
        {
            DialogueComp->ActorType = WidgetType;
            DialogueComp->StartDialogueSequenceNoneActor(3.0f, 1.0f);
        }
    }
}

