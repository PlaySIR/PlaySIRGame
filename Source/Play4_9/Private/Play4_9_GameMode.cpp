// Temp

#include "Play4_9.h"
#include "Play4_9_GameMode.h"




void APlay4_9_GameMode::ChoiceEffected() {
		if (ArrowHUD != nullptr && ArrowHUD->selectFlech.Num() >=2) {

			ArrowHUD->RemoveFromParent();
			ArrowHUD->selectFlech.Empty();

		UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeGameAndUI());

		}

}

void APlay4_9_GameMode::EffectChoice() {
	if (ArrowHUD != nullptr) {
		ArrowHUD->AddToViewport(1);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(FInputModeUIOnly());
	}
	
}
