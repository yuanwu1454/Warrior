// Martin Yuan All Rights Reserved.

#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"

#include "Characters/WarriorEnemyCharacter.h"

AWarriorEnemyCharacter* UWarriorEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedWarriorEnemyCharacter.IsValid())
	{
		CachedWarriorEnemyCharacter = Cast<AWarriorEnemyCharacter>(GetAvatarActorFromActorInfo());
	}

	return CachedWarriorEnemyCharacter.IsValid()?CachedWarriorEnemyCharacter.Get():nullptr;
}

UEnemyCombatComponent* UWarriorEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	if (auto Character = GetEnemyCharacterFromActorInfo())
	{
		return Character->GetEnemyCombatComponent();
	}
	return nullptr;
}
