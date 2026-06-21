// Martin Yuan All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorBaseCharacter.h"
#include "WarriorHeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorHeroCharacter : public AWarriorBaseCharacter
{
	GENERATED_BODY()
public:
	AWarriorHeroCharacter();
protected:

	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End	APawn Interface

	
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
private:
#pragma region Components
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera",meta=(AllowPrivateAccess="true"))
	USpringArmComponent* CameraBoom;

// 	C++ 中变量 / 函数标记为 private / protected 时，默认蓝图无法读写、调用；
// 加上 AllowPrivateAccess="true" 后：
// C++ 层面依然是私有，C++ 代码外部不能直接访问；
// 蓝图编辑器可以正常读取、修改、调用 这个私有成员。
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Camera",meta=(AllowPrivateAccess="true"))
	UCameraComponent* FollowCamera;
#pragma endregion


#pragma region Input
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="CharacterData",meta=(AllowPrivateAccess="true"))
	UDataAsset_InputConfig* InputConfigDataAsset;
	void Input_Move(const FInputActionValue& InputActionValue);	
	void Input_Look(const FInputActionValue& InputActionValue);	
#pragma endregion 

};
