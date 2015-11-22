// Temp

#pragma once

#include "Blueprint/UserWidget.h"
#include "ArrowGenerator.generated.h"

/**
 * 
 */
UCLASS()
class PLAY4_9_API UArrowGenerator : public UUserWidget
{
	GENERATED_BODY()
public :
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "fleche")
	TArray<int32> selectFlech;
			


	
};
