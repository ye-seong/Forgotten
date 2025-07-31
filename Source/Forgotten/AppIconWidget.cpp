#include "AppIconWidget.h"
#include "ForgottenHUD.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

#define LOCTEXT_NAMESPACE "AppIcon"

void UAppIconWidget::SetupApp(EAppType InAppType)
{
    if (!AppText) return;

    AppType = InAppType;

    switch (AppType)
    {
    case EAppType::Internet:
        AppText->SetText(LOCTEXT("Internet", "인터넷"));
        break;
    case EAppType::Mail:
        AppText->SetText(LOCTEXT("Mail", "메일함"));
        break;
    case EAppType::UserNote:
        AppText->SetText(LOCTEXT("UserNote", "a.txt"));
        break;
    case EAppType::AdminNote:
        AppText->SetText(LOCTEXT("AdminNote", "log_12.txt"));
        break;
    case EAppType::Audio:
        AppText->SetText(LOCTEXT("Audio", "audio_clip_12.wav"));
        break;
    default:
        break;
    }
}

#undef LOCTEXT_NAMESPACE

void UAppIconWidget::NativeConstruct()
{
    AppText = Cast<UTextBlock>(GetWidgetFromName("AppText"));
}

void UAppIconWidget::OnClickAppIcon()
{
    switch (AppType)
    {
    case EAppType::Internet:
        ClickInternetIcon();
        break;
    case EAppType::Mail:
        ClickMailIcon();
        break;
    case EAppType::UserNote:
        ClickUserNoteIcon();
        break;
    case EAppType::AdminNote:
        ClickAdminNoteIcon();
        break;
    case EAppType::Audio:
        ClickAudioIcon();
        break;
    default:
        break;
    }
}

void UAppIconWidget::ClickInternetIcon()
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        if (AForgottenHUD* HUD = Cast<AForgottenHUD>(PC->GetHUD()))
        {
            HUD->ShowInternetWindowWidget();
        }
    }
}

void UAppIconWidget::ClickMailIcon()
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        if (AForgottenHUD* HUD = Cast<AForgottenHUD>(PC->GetHUD()))
        {
            HUD->ShowMailWidget();
        }
    }
}

void UAppIconWidget::ClickUserNoteIcon()
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        if (AForgottenHUD* HUD = Cast<AForgottenHUD>(PC->GetHUD()))
        {
            HUD->ShowUserNoteWidget();
        }
    }
}

void UAppIconWidget::ClickAdminNoteIcon()
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        if (AForgottenHUD* HUD = Cast<AForgottenHUD>(PC->GetHUD()))
        {
            HUD->ShowAdminNoteWidget();
        }
    }
}

void UAppIconWidget::ClickAudioIcon()
{
    if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
    {
        if (AForgottenHUD* HUD = Cast<AForgottenHUD>(PC->GetHUD()))
        {
            HUD->ShowAudioWidget();
        }
    }
}