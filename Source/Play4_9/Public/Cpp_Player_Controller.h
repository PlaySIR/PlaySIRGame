// Temp

#pragma once
#include "BP_Library.h"
#include "Cpp_Unit_Parent.h"
#include "Play4_9_GameMode.h"

#include "GameFramework/PlayerController.h"
#include "Cpp_Player_Controller.generated.h"

/**
 * 
 */
UCLASS()
class PLAY4_9_API ACpp_Player_Controller : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APlay4_9_GameMode * _gameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 _targetIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 _currentTileHover;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 _clickedTile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool _isViewTPS;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool _targetIsPawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool disableInput;



	
	
	
};
