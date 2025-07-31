#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AppIconWidget.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "UserMonitorWidget.generated.h"

UCLASS()
class FORGOTTEN_API UUserMonitorWidget : public UUserWidget
{
    GENERATED_BODY()

public:

protected:
    UPROPERTY(BlueprintReadWrite, Category = "App")
    UAppIconWidget* InternetWidget;

    UPROPERTY(BlueprintReadWrite, Category = "App")
    UAppIconWidget* MailWidget;

    UPROPERTY(BlueprintReadWrite, Category = "App")
    UAppIconWidget* NoteWidget;
};
