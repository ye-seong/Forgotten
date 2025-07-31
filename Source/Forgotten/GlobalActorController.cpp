#include "GlobalActorController.h"

AGlobalActorController::AGlobalActorController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGlobalActorController::BeginPlay()
{
	Super::BeginPlay();
}

void AGlobalActorController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGlobalActorController::TriggerControllLightEvent()
{
	K2_OnControllLightEvent();
}
