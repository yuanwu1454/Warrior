// Martin Yuan All Rights Reserved.


#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"
#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive,
                                                               int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf<UWarriorEnemyGameplayAbility>& AbilityClass : EnemyCombatAbilities)
		{
			if (!AbilityClass) continue;
			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.Level = ApplyLevel;
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			
			InASCToGive->GiveAbility(AbilitySpec);
		}	
	}
}
