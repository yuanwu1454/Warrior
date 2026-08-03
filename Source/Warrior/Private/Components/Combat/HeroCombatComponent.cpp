// Martin Yuan All Rights Reserved.


#include "Components/Combat/HeroCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Items/Weapons/WarriorHeroWeapon.h"
#include "WarriorDebugHelper.h"
#include "WarriorGameplayTags.h"

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	return Cast<AWarriorHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTagToGet));
}

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<AWarriorHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	AWarriorHeroWeapon* WarriorHeroWeapon = GetHeroCurrentEquippedWeapon();
	if (WarriorHeroWeapon)
	{
		return WarriorHeroWeapon->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
	}
	return 0.f;
}


void UHeroCombatComponent::OnWeaponHitTarget(AActor* HitActor)
{
	//Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" hit ") + HitActor->GetActorNameOrLabel(), FColor::Green);

	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}
	OverlappedActors.AddUnique(HitActor);

	APawn* OwningPawn =  GetOwningPawn();
	FGameplayEventData Data;
	Data.Instigator = OwningPawn;
	Data.Target = HitActor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwningPawn, WarriorGameplayTags::Shared_Event_MeleeHit, Data);

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		WarriorGameplayTags::Player_Event_HitPause,
		FGameplayEventData()
	);
}

void UHeroCombatComponent::OnWeaponPulledFromTarget(AActor* InteractedActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		WarriorGameplayTags::Player_Event_HitPause,
		FGameplayEventData()
	);
	// Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT("'s weapon pulled from ") + InteractedActor->GetActorNameOrLabel(), FColor::Red);
}
