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
    // 플레이어가 이 객체와 상호작용할 때 호출되는 함수
    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    void OnInteract(AActor* Interactor);

    // 플레이어가 이 객체를 바라볼 때 호출되는 함수
    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    void OnFocus();

    // 플레이어가 이 객체에서 시선을 돌릴 때 호출되는 함수
    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    void OnLoseFocus();

    // 상호작용 텍스트 반환 (예: "열기", "조사하기" 등)
    UFUNCTION(BlueprintNativeEvent, Category = "Interaction")
    FString GetInteractionText();
};
