// Martin Yuan All Rights Reserved.


#include "AnimInstances/Hero/WarriorHeroAnimInstance.h"

#include "Characters/WarriorHeroCharacter.h"

void UWarriorHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<AWarriorHeroCharacter>(OwningCharacter);
	}
}

void UWarriorHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (bHasAcceleration)
	{
		bShouldEnterRelaxState = false;
		IdleElapsedTime = 0.f;
	}else
	{
		if (bShouldEnterRelaxState == false)
		{
			IdleElapsedTime += DeltaSeconds;
			if (IdleElapsedTime > EnterRelaxStateThreshold)
			{
				bShouldEnterRelaxState = true;
				IdleElapsedTime = 0.f;
			}
		}

		
	}
}
