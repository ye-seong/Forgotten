// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class FORGOTTEN_API IInteractableInterface
{
	GENERATED_BODY()

public:
    // �÷��̾ �� ��ü�� ��ȣ�ۿ��� �� ȣ��Ǵ� �Լ�
    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    void OnInteract(AActor* Interactor);

    // �÷��̾ �� ��ü�� �ٶ� �� ȣ��Ǵ� �Լ�
    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    void OnFocus();

    // �÷��̾ �� ��ü���� �ü��� ���� �� ȣ��Ǵ� �Լ�
    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    void OnLoseFocus();

    // ��ȣ�ۿ� �ؽ�Ʈ ��ȯ (��: "����", "�����ϱ�" ��)
    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    FString GetInteractionText();
};
