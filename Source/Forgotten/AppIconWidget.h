#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "AppIconWidget.generated.h"

UENUM(BlueprintType)
enum class EAppType : uint8
{
    Internet,
    Mail,
    UserNote,
	AdminNote,
	Audio
};

UCLASS()
class FORGOTTEN_API UAppIconWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetupApp(EAppType InAppType);

	UFUNCTION(BlueprintCallable)
	void OnClickAppIcon();

	UPROPERTY(BlueprintReadOnly)
	EAppType AppType;

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AppText;

	UPROPERTY(EditDefaultsOnly)
	UUserWidget* InternatWidget;

private:

	void ClickInternetIcon();
	void ClickMailIcon();
	void ClickUserNoteIcon();
	void ClickAdminNoteIcon();
	void ClickAudioIcon();
};
