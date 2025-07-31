#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ForgottenAnimInstance.generated.h"

UCLASS()
class FORGOTTEN_API UForgottenAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bIsSitting = false;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bIsLiying = false;

    UPROPERTY(BlueprintReadOnly, Category = "State")
    bool bIsRunning = false;
};