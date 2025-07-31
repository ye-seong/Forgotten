#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GlobalActorController.generated.h"

UCLASS()
class FORGOTTEN_API AGlobalActorController : public AActor
{
	GENERATED_BODY()
	
public:	
	AGlobalActorController();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Global Actor Controller")
	void K2_OnControllLightEvent();

	void TriggerControllLightEvent();
};
