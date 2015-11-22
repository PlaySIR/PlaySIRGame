
// Temp

#pragma once
#include "BP_Library.h"

#include "GameFramework/Pawn.h"
#include "Cpp_Unit_Parent.generated.h"


UCLASS()
class PLAY4_9_API ACpp_Unit_Parent : public APawn
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent * _CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent * _CustomGridAnchor;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
		AActor* CameraOne;


protected:



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caracteristique")
		Enum_Faction Faction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caracteristique")
		Enum_Race Race;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caracteristique")
		FElement  myElement;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Caracteristique")
		FName myName;	 

	/************************************************************************/
	/*  GridPlacement : Index, IgnoreSnapToCustomGrid,PlaceActoratAnchor    */
	/************************************************************************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GridPlacement")
		int32 mIndex;
	UPROPERTY(BlueprintReadWrite, Category = "GridPlacement")
		bool mIgnoreSnapToCustomGrid;
	UPROPERTY(BlueprintReadWrite, Category = "GridPlacement")
		bool mPlaceActoratAnchor;
	UPROPERTY(BlueprintReadWrite, Category = "GridPlacement")
		int32 mStopXtilesFromTarget;
	UPROPERTY(BlueprintReadWrite, Category = "GridPlacement")
		int32 StopXTilesBeforeEnd;
	/************************************************************************/
	/* Attributes : - MaxMove, CurrentMove, Range 'Portée), MaxHealth, CurrentHealth, Damage (force),
	-Faction, AIMaxSearchRange, CanCureMyTeam, CanIbuildObstacle
	*/
	/************************************************************************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int32 level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		float experience;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		TArray<FAttaque> attackForFight;




	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int32 mMaxMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int32 mDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int32 mDefense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int32 mInitiative;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int32 mCurrentMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int32 mRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int32 mMaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int32 mCurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int32 mAIMaxSearchRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool mCanCureMyTeam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool mCanIbuildObstacle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool isEnchanted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		bool healer ;	// guérriseur

	UPROPERTY(BlueprintReadWrite, Category = "Attributes")
		float CurrentSpeed;
	UPROPERTY(BlueprintReadWrite, Category = "Attributes")
		float CurrentSplineDistance;
	UPROPERTY(BlueprintReadWrite, Category = "Attributes")
		bool HasActedThisTurn;

	/**************************************************************************/
	/* Movement Options : Diagonal Movement, Cross Corners, Can Split Up Move**/
	/**************************************************************************/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Options")
		bool mDiagonalMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Options")
		bool mCrossCorners;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Options")
		bool mCanSplitUpMove;


	/***************************************************************************/
	/* Animation : Max Speed, Anim Damage Delay, Death Anim Delay, Acceleration*/
	/***************************************************************************/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float mMaxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float mAnimDamageDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float mDeathDamageDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
		float mAcceleration;
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
		bool mIdle;
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
		bool mAttackOnEnd;



		//Non Blueprintable. calculate the latency remaining of the specific effect 
		TMap<FEffet*, int32> latencyRemaining;	
		

public:
	// Sets default values for this pawn's properties
	ACpp_Unit_Parent();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	static FORCEINLINE UBlueprint* LoadFromPath(const FName& Path);



	/**
	* Apply the enchantement of the effect that the Victim receives.
	*	
	*/
		void ApplyEnchantement( FAttaque & structAttaque, ACpp_Unit_Parent * Victime);

		/**
		* Apply the Damage of the current enchantement 
		* we check the Map latencyRemaining if the Map is empty we not
		* apply any damage else we apply the damage of the specific effect
		* and reduce the latency remaining 
		*/
		void ApplyDamageEnchantement();

		/**
		* Flip Flop the parameter isEnchanted
		*	if isEnchanted is true it will be false and vice versa
		*/
		void FlipFlopEnchanted();


	/**
	*	Applique les dégats de l'attaque sélectionner, met à jour la vie de l'ennemi
	*	applique également l'effet lié à l'attaque
	*/
		int CalculAttack_Elem(FAttaque & structAttaque, ACpp_Unit_Parent * Victime);

		float CalculAttack_Fleche(int32 fl1_attack, int32 fl2_attack, int32 fl1_def, int32 fl2_def);
		bool flechCritique(int32 fl1_attack, int32 fl2_attack, int32 fl1_def , int32 fl2_def);
		bool flechLoose(int32 fl1_attack, int32 fl2_attack, int32 fl1_def , int32 fl2_def);

		UFUNCTION(BlueprintCallable, Category = "Calcul of Damage")
		int32 DamageFinal(FAttaque & structAttaque, ACpp_Unit_Parent * Victime, bool playerTurn);

		TArray<int32> flechGenerator();
		TArray<int32> IAflecheGenerator();

	/***
	*	Initialize the Map which link the latency with the Enchantement 
	**/
		 void initLatencyEnchantement(FEffet &effet);

};