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

    // 상호작용 처리 함수
    void Interact();

    void UseMonitor();
    // 라인 트레이스를 통한 상호작용 가능 객체 감지
    void CheckForInteractables();

    // Widget 뜨게 함
    void ShowInteractionWidget();

    // 현재 포커스된 인터랙티브 객체
    UPROPERTY()
    UActorComponent* FocusedInteractable;

    // 상호작용 가능 거리
    UPROPERTY(EditAnywhere, Category = "Interaction")
    float InteractionDistance = 100.0f;

    // UI에 표시될 상호작용 텍스트
    UPROPERTY(BlueprintReadOnly, Category = "Interaction")
    FString InteractionText;

    // 상호작용 UI 표시 여부
    UPROPERTY(BlueprintReadOnly, Category = "Interaction")
    bool bShowInteractionUI;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> UserInterfaceWidgetClass;

    FTimerHandle CollisionEnableTimerHandle;

    UPrimitiveComponent* FocusedComponent;

    // 애니메이션 몽타주 변수
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
