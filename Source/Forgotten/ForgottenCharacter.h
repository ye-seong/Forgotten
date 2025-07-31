// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
#include "DialogueComponent.h"
#include "ForgottenCharacter.generated.h"

UCLASS()
class FORGOTTEN_API AForgottenCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AForgottenCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FirstPersonCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UDialogueComponent* DialogueComponent;

    UPROPERTY()
    class UUserWidget* UserInterfaceWidget;

    bool bSitting;
    bool bLiying;
    bool bMonitoring;
    bool bUsingMonitor;

protected:
	virtual void BeginPlay() override;

    // ��ȣ�ۿ� ó�� �Լ�
    void Interact();

    void UseMonitor();
    // ���� Ʈ���̽��� ���� ��ȣ�ۿ� ���� ��ü ����
    void CheckForInteractables();

    // Widget �߰� ��
    void ShowInteractionWidget();

    // ���� ��Ŀ���� ���ͷ�Ƽ�� ��ü
    UPROPERTY()
    UActorComponent* FocusedInteractable;

    // ��ȣ�ۿ� ���� �Ÿ�
    UPROPERTY(EditAnywhere, Category = "Interaction")
    float InteractionDistance = 100.0f;

    // UI�� ǥ�õ� ��ȣ�ۿ� �ؽ�Ʈ
    UPROPERTY(BlueprintReadOnly, Category = "Interaction")
    FString InteractionText;

    // ��ȣ�ۿ� UI ǥ�� ����
    UPROPERTY(BlueprintReadOnly, Category = "Interaction")
    bool bShowInteractionUI;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> UserInterfaceWidgetClass;

    FTimerHandle CollisionEnableTimerHandle;

    UPrimitiveComponent* FocusedComponent;

    // �ִϸ��̼� ��Ÿ�� ����
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* SitMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* StandUpMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* LieMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* WakeUpMontage;



public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void PlaySitAnimation();

    void PlayStandUpAnimation();

    void PlayLieAnimation();

    void PlayWakeUpAnimation();

    void ShowInteractionText();

    void PressEscButton();

    UFUNCTION(BlueprintCallable)
    void PressContinueButton();
};
