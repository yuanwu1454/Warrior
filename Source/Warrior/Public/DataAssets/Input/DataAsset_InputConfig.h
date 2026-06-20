// Martin Yuan All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "EnhancedInput/Public/InputAction.h"
#include "EnhancedInput/Public/InputMappingContext.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;
USTRUCT(BlueprintType)
struct FWarriorInputActionConfig
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, meta=(Categories="InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputAction* InputAction;
	
};

/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext;


	// TitleProperty 仅作用于 TArray <自定义 USTRUCT> 结构体数组，用来自定义编辑器细节面板中数组折叠条目右侧的标题文字。
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="InputTag"))
	TArray<FWarriorInputActionConfig> NativeInputConfig;

	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InInputTag);
};
