// Martin Yuan All Rights Reserved.


#include "Characters/WarriorHeroCharacter.h"
#include "Components/Input/WarriorInputComponent.h"
#include "WarriorDebugHelper.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WarriorGameplayTags.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "DataAssets/StartUpData/DataAsset_StartupDataBase.h"


AWarriorHeroCharacter::AWarriorHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f,96.f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 66.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,500.f,0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
	
}

void AWarriorHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// !IsNull() ≠ IsValid()，二者完全不是一回事，绝对不能互相替换。
	// IsValid 主要看是否已经加载
	// IsNull 只看软引用有没有填写资源路径
	if (!CharacterStartUpData.IsNull())
	{
		if(UDataAsset_StartupDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(WarriorAbilitySystemComponent);
		}
	}
}

void AWarriorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWarriorHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext,0);
	UWarriorInputComponent* WarriorInputComponent =  CastChecked<UWarriorInputComponent>(PlayerInputComponent);
	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
}

void AWarriorHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	// 1. 从输入动作中读取二维向量：X=左右(A/D)，Y=前后(W/S)，范围[-1,1]
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	// 2. 获取控制器控制旋转，只保留Yaw（水平左右转向），Pitch/Roll置0，只算水平平面方向
	// Controller->GetControlRotation() = 相机朝向
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	// ========== 前后移动（W/S 对应 Y 轴） ==========
	if (MovementVector.Y != 0.f)
	{
		// 将世界前向向量，按相机水平旋转偏移，得到角色自身前向（面朝相机前方走）
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		// 添加移动输入，Y正数向前、负数向后
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	// ========== 左右侧移（A/D 对应 X 轴） ==========
	if (MovementVector.X != 0.f)
	{
		// 将世界右向向量，按相机水平旋转偏移，得到角色自身右向（相机视角左右横移）
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		// 添加移动输入，X正数向右、负数向左		
		AddMovementInput(RightDirection, MovementVector.X);
	}

}



void AWarriorHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	// 从增强输入中提取二维视角向量
	// X：鼠标左右移动 / 右摇杆左右（控制水平转向 Yaw）
	// Y：鼠标上下移动 / 右摇杆上下（控制俯仰抬头 Pitch）
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	// 水平左右转头（Yaw）
	if (LookAxisVector.X != 0.f)
	{
		// 给控制器叠加水平旋转输入，正数右转、负数左转
		AddControllerYawInput(LookAxisVector.X);	
	}

	// 上下抬头低头（Pitch）
	if (LookAxisVector.Y != 0.f)
	{
		// 给控制器叠加俯仰旋转输入，正数抬头、负数低头
		AddControllerPitchInput(LookAxisVector.Y);	
	}
}
