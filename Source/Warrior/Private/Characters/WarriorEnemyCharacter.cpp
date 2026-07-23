// Martin Yuan All Rights Reserved.


#include "Characters/WarriorEnemyCharacter.h"

#include "WarriorDebugHelper.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartupDataBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/AssetManager.h"
// Sets default values
AWarriorEnemyCharacter::AWarriorEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");
}

void AWarriorEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
}

void AWarriorEnemyCharacter::InitEnemyStartUpData()
{
	if (CharacterStartUpData.IsNull())
	{
		return;		
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this]()
		{
			if(UDataAsset_StartupDataBase* LoadedData = CharacterStartUpData.Get())
			{
				LoadedData->GiveToAbilitySystemComponent(WarriorAbilitySystemComponent);
				Debug::Print(TEXT("Enemy Start Up Data Loaded"), FColor::Green);
			}
		}));
}


