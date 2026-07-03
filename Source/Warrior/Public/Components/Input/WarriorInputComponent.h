// Martin Yuan All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "WarriorInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConf, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObj, CallbackFunc Func);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConf, UserObject* ContextObj, CallbackFunc PressedFunc, CallbackFunc ReleasedFunc);
	
};

template <class UserObject, typename CallbackFunc>
void UWarriorInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObj, CallbackFunc Func)
{
	checkf(InInputConfig, TEXT("Input Config data asset is null, can not proceed with binding"));

	if(UInputAction* FoundInputAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		BindAction(FoundInputAction, TriggerEvent, ContextObj, Func);
	}
}

template <class UserObject, typename CallbackFunc>
void UWarriorInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObj, CallbackFunc PressedFunc, CallbackFunc ReleasedFunc)
{
	checkf(InInputConfig, TEXT("Input Config data asset is null, can not proceed with binding"));

	for (const FWarriorInputActionConfig& Config : InInputConfig->AbilityInputConfig)
	{
		if (!Config.IsValid()) continue;

		BindAction(Config.InputAction, ETriggerEvent::Started, ContextObj, PressedFunc, Config.InputTag);
		BindAction(Config.InputAction, ETriggerEvent::Completed, ContextObj, ReleasedFunc, Config.InputTag);
	}
	
}
