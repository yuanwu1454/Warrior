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
}

void UHeroCombatComponent::OnWeaponPulledFromTarget(AActor* InteractedActor)
{
	// Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT("'s weapon pulled from ") + InteractedActor->GetActorNameOrLabel(), FColor::Red);
}
