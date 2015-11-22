// Temp

#pragma once

#include "GameFramework/GameMode.h"
#include "Cpp_Unit_Parent.h"
#include "BP_Library.h"
#include "Runtime/UMG/Public/UMG.h"
#include "SlateBasics.h"
#include "ArrowGenerator.h"
#include "Blueprint/UserWidget.h"
#include "Play4_9_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLAY4_9_API APlay4_9_GameMode : public AGameMode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataMode")
		bool _playerTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataMode")
		int32 _TurnCounter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataMode")
		bool _DisableInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DataMode")
		ACpp_Unit_Parent * _currentPawn;



	//Ajouter le HUD generator voir tuto PickupBattery(ue4)
	//recupérer la data fourni par le Hud 
	//essayer un while(hud != nullptr || attackflech.size !=2){} -> attack
	// remove le hud et clear attackflech
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "fleche")
		TSubclassOf<class UUserWidget>  HUDWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "fleche")
		class  UArrowGenerator * ArrowHUD;


	UFUNCTION(BlueprintCallable, Category = "fleche")
		void ChoiceEffected();

	UFUNCTION(BlueprintCallable, Category = "fleche")
		void EffectChoice();
};

