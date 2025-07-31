#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ForgottenGameInstance.h"
#include "DialogueComponent.h"
#include "ForgottenCharacter.h"
#include "InteractionComponent.generated.h"


UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	None		UMETA(DisplayName = "None"),
	OpenClose	UMETA(DisplayName = "Open Close"),
	ReadMemo	UMETA(DisplayName = "Read Memo"),
	Inspect		UMETA(DisplayName = "Inspect"),
	Sit         UMETA(DisplayName = "Sit"),
	Lie 	    UMETA(DisplayName = "Lie"),
    Break       UMETA(DisplayName = "break")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionEvent, class AActor*, Interactor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FORGOTTEN_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

public:	
    // 인터랙션 타입
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    EInteractionType InteractionType;

    // 인터랙션 텍스트 (기본값: "상호작용")
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    FString InteractionText;

    // 인터랙션 거리
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    float InteractionDistance = 200.0f;

    // 하이라이트 효과를 적용할 메시 컴포넌트
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    class UPrimitiveComponent* HighlightMesh;

    // 문/서랍 인터랙션 설정
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|OpenClose", meta = (EditCondition = "InteractionType == EInteractionType::OpenClose"))
    class USceneComponent* MovingComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|OpenClose", meta = (EditCondition = "InteractionType == EInteractionType::OpenClose"))
    bool bRotationMovement = true;  // true: 회전 (문), false: 이동 (서랍)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|OpenClose", meta = (EditCondition = "InteractionType == EInteractionType::OpenClose && bRotationMovement"))
    float OpenAngle = 90.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|OpenClose", meta = (EditCondition = "InteractionType == EInteractionType::OpenClose && !bRotationMovement"))
    FVector OpenOffset = FVector(20.0f, 0.0f, 0.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|OpenClose", meta = (EditCondition = "InteractionType == EInteractionType::OpenClose"))
    float MovementSpeed = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|ReadMemo", meta = (EditCondition = "InteractionType == EInteractionType::ReadMemo"))
    FString MemoContent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Inspect", meta = (EditCondition = "InteractionType == EInteractionType::Inspect"))
    float OriginalFOV = 90.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Inspect", meta = (EditCondition = "InteractionType == EInteractionType::Inspect"))
    float ZoomedFOV = 30.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Lie", meta = (EditCondition = "InteractionType == EInteractionType::Lie"))
    class USceneComponent* LiyingComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Sit", meta = (EditCondition = "InteractionType == EInteractionType::Sit"))
    class USceneComponent* SittingComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Sit", meta = (EditCondition = "InteractionType == EInteractionType::Sit"))
    class USceneComponent* MonitorComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Break", meta = (EditCondition = "InteractionType == EInteractionType::Break"))
	UStaticMeshComponent* MirrorMeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Break", meta = (EditCondition = "InteractionType == EInteractionType::Break"))
    UMaterialInterface* DefaultMirrorMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Break", meta = (EditCondition = "InteractionType == EInteractionType::Break"))
    UMaterialInterface* BrokenMirrorMaterial;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
    FString DialogueType;

    UPROPERTY()
    AActor* CachedInteractor;

    // 상태 관련 변수
    UPROPERTY(BlueprintReadOnly, Category = "Interaction|State")
    bool bIsOpen = false;

    UPROPERTY(BlueprintReadOnly, Category = "Interaction|State")
    bool bIsRead = false;

    UPROPERTY(BlueprintReadOnly, Category = "Interaction|State")
	bool bIsInspect = false;

    UPROPERTY(BlueprintReadOnly, Category = "Interaction|State")
    bool bIsSit = false;

    UPROPERTY(BlueprintReadOnly, Category = "Interaction|State")
    bool bIsUseMoniter = false;

    UPROPERTY(BlueprintReadOnly, Category = "Interaction|State")
    bool bIsLie = false;

    UPROPERTY(BlueprintReadOnly, Category = "Interaction|State")
    bool bIsFocused = false;

    UPROPERTY(BlueprintReadOnly, Category = "Interaction|State")
    bool bIsBreak = false;

    // 델리게이트 (블루프린트에서 이벤트 핸들링용)
    UPROPERTY(BlueprintAssignable, Category = "Interaction|Events")
    FOnInteractionEvent OnInteract;

    UPROPERTY(BlueprintAssignable, Category = "Interaction|Events")
    FOnInteractionEvent OnFocus;

    UPROPERTY(BlueprintAssignable, Category = "Interaction|Events")
    FOnInteractionEvent OnLoseFocus;

    // 인터랙션 함수
    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void Interact(AActor* Interactor);

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    void SetFocus(bool bFocused, AActor* Interactor = nullptr);

    UFUNCTION(BlueprintCallable, Category = "Interaction")
    FString GetInteractionText() const;

    void HandleBreak(AActor* Interactor);

    bool CanShowDialogue = false;

    float DialogueDelay = 1.0f;

    UFUNCTION()
    void StartChapter2();

    UFUNCTION()
    void OpeningChapter2();

    UFUNCTION()
    void StartChapter3();

    UFUNCTION()
    void OpeningChapter3();

private:
    // 현재 움직임 값
    float CurrentRotation = 0.0f;
    FVector CurrentOffset = FVector::ZeroVector;

    // 목표 움직임 값
    float TargetRotation = 0.0f;
    FVector TargetOffset = FVector::ZeroVector;

    FTimerHandle ZoomTimerHandle;
    FTimerHandle LightTimerHandle;
    FTimerHandle QuitTimerHandle;

    void HandleOpenClose(AActor* Interactor);

    void HandleReadMemo(AActor* Interactor);

	void HandleInspect(AActor* Interactor);
    void ZoomIn();
	void ZoomOut();

    void HandlePickUp(AActor* Interactor);

	void HandleSit(AActor* Interactor);

    void HandleLie(AActor* Interactor);

    void SetMonitorCollision();
    // 상호작용자 위치 확인 (문 열리는 방향 결정용)
    bool IsInteractorInFront(AActor* Interactor);

};
