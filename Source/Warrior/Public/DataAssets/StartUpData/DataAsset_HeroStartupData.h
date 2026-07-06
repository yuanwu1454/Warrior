// Martin Yuan All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartupDataBase.h"
#include "WarriorGameplayTags.h"
#include "DataAsset_HeroStartupData.generated.h"

USTRUCT(BlueprintType)
struct FWarriorHeroAbilitySet
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, meta=(Categories="InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, meta=(Categories="InputTag"))
	TSubclassOf<UWarriorGameplayAbility > AbilityToGrant;

	bool IsValid() const;
};
/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_HeroStartupData : public UDataAsset_StartupDataBase
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly,Category="StartUpData", meta=(TitleProperty="InputTag"))
	TArray<FWarriorHeroAbilitySet> HeroStartUpAbilitySets;
};
