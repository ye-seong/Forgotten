#include "ForgottenAnimInstance.h"
#include "ForgottenCharacter.h"

void UForgottenAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (APawn* Pawn = TryGetPawnOwner())
    {
        AForgottenCharacter* Char = Cast<AForgottenCharacter>(Pawn);
        if (Char)
        {
            bIsSitting = Char->bSitting;
            bIsLiying = Char->bLiying;
        }
    }
}

