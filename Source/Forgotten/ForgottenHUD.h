#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ForgottenGameInstance.h"
#include "ForgottenHUD.generated.h"

UCLASS()
class FORGOTTEN_API AForgottenHUD : public AHUD
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	AForgottenHUD();

	UFUNCTION(BlueprintCallable)
	void ShowMenuWidget();

	UFUNCTION(BlueprintCallable)
	void HideMenuWidget();

	UFUNCTION(BlueprintCallable)
	void ShowMemoWidget(const FText& MemoText);

	UFUNCTION(BlueprintCallable)
	void HideMemoWidget();

	UFUNCTION(BlueprintCallable)
	void ShowUserMonitorWidget();

	UFUNCTION(BlueprintCallable)
	void HideUserMonitorWidget();

	UFUNCTION(BlueprintCallable)
	void ShowAdminMonitorWidget();

	UFUNCTION(BlueprintCallable)
	void HideAdminMonitorWidget();

	UFUNCTION(BlueprintCallable)
	void ShowInternetWindowWidget();

	UFUNCTION(BlueprintCallable)
	void HideInternetWidowWidget();

	UFUNCTION(BlueprintCallable)
	void ShowMailWidget();

	UFUNCTION(BlueprintCallable)
	void HideMailWidget();

	UFUNCTION(BlueprintCallable)
	void ShowUserNoteWidget();

	UFUNCTION(BlueprintCallable)
	void HideUserNoteWidget();

	UFUNCTION(BlueprintCallable)
	void ShowAdminNoteWidget();

	UFUNCTION(BlueprintCallable)
	void HideAdminNoteWidget();

	UFUNCTION(BlueprintCallable)
	void ShowAudioWidget();

	UFUNCTION(BlueprintCallable)
	void HideAudioWidget();

	UFUNCTION(BlueprintCallable)
	void ShowEscMenuWidget();

	UFUNCTION(BlueprintCallable)
	void HideEscMenuWidget();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> MenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> UserMonitorWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> AdminMonitorWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> InternetWindowWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> MailWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> UserNoteWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> AdminNoteWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> AudioWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> EscMenuWidgetClass;

	UPROPERTY()
	class UUserWidget* MenuWidget;

	UPROPERTY()
	class UUserWidget* UserMonitorWidget;

	UPROPERTY()
	class UUserWidget* AdminMonitorWidget;

	UPROPERTY()
	class UUserWidget* InternetWindowWidget;

	UPROPERTY()
	class UUserWidget* MailWidget;

	UPROPERTY()
	class UUserWidget* UserNoteWidget;

	UPROPERTY(BlueprintReadOnly)
	class UUserWidget* AdminNoteWidget;

	UPROPERTY(BlueprintReadOnly)
	class UUserWidget* AudioWidget;

	UPROPERTY()
	class UUserWidget* EscMenuWidget;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> MemoWidgetClass;

private:
	UPROPERTY()
	class UUserWidget* MemoWidget;

	UForgottenGameInstance* GameInstance;

	void ShowDialogueFromWidget(FString WidgetType);
};
