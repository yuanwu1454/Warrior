// Martin Yuan All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorBaseCharacter.h"
#include "WarriorHeroCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
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
	virtual void BeginPlay() override;
private:
#pragma region Components
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	USpringArmComponent* CameraBoom;

// 	C++ 中变量 / 函数标记为 private / protected 时，默认蓝图无法读写、调用；
// 加上 AllowPrivateAccess="true" 后：
// C++ 层面依然是私有，C++ 代码外部不能直接访问；
// 蓝图编辑器可以正常读取、修改、调用 这个私有成员。
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	UCameraComponent* FollowCamera;
	#pragma endregion 
};
