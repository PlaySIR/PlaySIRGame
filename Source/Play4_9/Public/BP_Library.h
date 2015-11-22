// Temp

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "BP_Library.generated.h"

/***********************************
Faction du personnage, Rajouté un type 
pour les objets construits par un batisseur
*****************************************/
//TODO
UENUM(BlueprintType)	
enum class Enum_Faction : uint8
{
	VE_Empty	UMETA(DisplayName = "Empty"),
	VE_Player 	UMETA(DisplayName = "Player"),
	VE_Enemy 	UMETA(DisplayName = "Enemy")
};

/***********************************
Enumérateur des Races des Unit
*****************************************/

UENUM(BlueprintType)	
enum class Enum_Race : uint8
{
	VE_Humain	UMETA(DisplayName = "Humain"),
	VE_Enerien	UMETA(DisplayName = "Enerien"),
	VE_Cyborg	UMETA(DisplayName = "Cyborg"),
	VE_A	UMETA(DisplayName = "A"),
	VE_B	UMETA(DisplayName = "B"),
	VE_C	UMETA(DisplayName = "C")
};


/******************************************************
Les éléments des Attaques :
Si élément1 - élément2 == 1 élément1> élément2

******************************************************/


UENUM(BlueprintType)
enum class Enum_Elements : uint8
{
	VE_TERRE 	UMETA(DisplayName = "Terre"),
	VE_FEU	UMETA(DisplayName = "Feu"),
	VE_EAU UMETA(DisplayName = "Eau"),
	VE_ELECTRIC UMETA(DisplayName = "Electric"),
	VE_AIR  UMETA(DisplayName = "Air"),
	VE_NATURE  UMETA(DisplayName = "Nature"),
	VE_MAGIE  UMETA(DisplayName = "Magie")

};

/******************************************************
Enchantement modifie les attributs du personnage
Un Personnage a donc un état Neutre pour un état normal
exemple : Si un personnage est de race compatible avec le Feu 
un état de Brulé lui augmentera son attaque et/ou
sa défense. Sinon un type terre sera doublement affecté et 
un autre type sera simplement affecté.
********************************************************/


UENUM(BlueprintType)
enum class Enum_Enchantement : uint8
{
	VE_Neutre  UMETA(DisplayName = "Neutre"),
	VE_Poison 	 UMETA(DisplayName = "Empoisonné"),
	VE_Brule	 UMETA(DisplayName = "Brulé"),
	VE_Asphixie  UMETA(DisplayName = "Asphixié"),
	VE_Paralysie  UMETA(DisplayName = "Paralysé"),
	VE_Apnee  UMETA(DisplayName = "Noyé"),
	VE_Vertige  UMETA(DisplayName = "Vertige"),
	VE_Folie UMETA(DisplayName = "Folie"),
	VE_Peur   UMETA(DisplayName = "Peur"),
	VE_Courage  UMETA(DisplayName = "Courage"),
	VE_Adrenaline  UMETA(DisplayName = "Adrenaline"),
	VE_Mutisme  UMETA(DisplayName = "Mutisme"),
	VE_Cecite UMETA(DisplayName = "Aveugle"),

	VE_Kamikaze  UMETA(DisplayName = "Kamikaze")
};
/****************************************************************
Structure des Elements : Contient uniquement l'énumérateur associé
******************************************************************/
USTRUCT(BlueprintType)
struct FElement : public FTableRowBase {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Element")
		Enum_Elements enumElement;
};


/****************************************************************
Structure des enchantement :
		Un enchantement contient  : 
			- son énumérateur
			- la liste des Elem qui seront critique à l'ennemi
			- la lsite des Elem qui seront Bonus pour l'ennemi
******************************************************************/
USTRUCT(BlueprintType)
struct FEnchantement : public FTableRowBase {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Enchantement")
		Enum_Enchantement enumEnchantement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Enchantement")
		TArray<FElement> elementCritique;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Enchantement")
		TArray<FElement> elementBonus;
};

/****************************************************************

Structure des Effets : Un effet a un dégat associé à un enchantement
le dégat sera multiplié par la constante en fonction des comparaison
des types.
******************************************************************/

USTRUCT(BlueprintType)
struct FEffet : public FTableRowBase {
	GENERATED_USTRUCT_BODY()
	FEnchantement structEnchantement;
	int32 effets;
	int32 latence;

	FEffet() {
	
		effets = 0;
		latence = 0;
	}
	FEffet(FEnchantement _structEnchantement,int32 _effet, int32 _latence) {
		structEnchantement = _structEnchantement;
		effets = _effet;
		latence = _latence;
	}
};


/*
*  do we add experience for the attack ? or a counter of usage? this in order to
*  increase the power of the attack if the attach has been used ten or 20 times
*  by the unit?
*/
USTRUCT(BlueprintType)
struct FAttaque : public FTableRowBase {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Attaque")
		FString nameAttaque;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Data Attaque")
		FString description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Data Attaque")
		int32 damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Data Attaque")
		int32 range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Data Attaque")
		TArray<FEffet> effets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Data Attaque")
		UAnimSequence * animBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Data Attaque")
		FElement element; // or TArray depends on the vote
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = " Data Attaque")
		float experience;
};


/******
* @param : initiative : More the initiative is high more the unit will have the chance to be the first to attack.
* @param : AIMaxSearchRange : la portée de recherche d'ennemi de l'IA.
* @param : experience : chaque Unit a une expérience laquelle servira a calculer
* @param : builder : permet de determiner si l'unit peut construire des objets 
*/

USTRUCT(BlueprintType)
struct FUnit : public FTableRowBase {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Unit")
		FString	name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Unit")
		int32 maxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Unit")
		int32 maxMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Unit")
		int32 force;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Unit")
		int32 defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Unit")
		int32 initiative;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Unit")
		int32 AIMaxSearchRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Unit")
		TArray<FAttaque> myAttaque;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Unit")
		int32 experience;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Unit")
		bool builder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Unit")
		bool mDiagonalMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Unit")
		bool mCrossCorners;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Unit")
		bool mCanSplitUpMove;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Unit")
		bool healer ;
};




/**
*
*/
UCLASS(Blueprintable)
class PLAY4_9_API UBP_Library : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
public:
	//static const int ENCHANTEMENT_BONUS = -2;
	//static const int ENCHANTEMENT_CRITIQUE = 2;
	
	//TArray<Cpp_Unit_Parent *> allUnit;


//	UFUNCTION(BlueprintCallable, Category = "Data Animation")
	//	static FAttaque addIdAnimation(UPARAM(ref) FAttaque & structAttaque, int32 idAnim);

//	UFUNCTION(BlueprintCallable, Category = "Data Animation")
//		static FAttaque addAnimToAttack(UPARAM(ref) FAttaque & structAttaque, UAnimSequence * animBP);

	/************************************************************************/
	/*If ElementX-ElmeentY == 1 alors X>Y                                   */
	/************************************************************************/
		static bool isStronger(FElement & structElem, FElement & structElem2);
		static bool isWeaker(FElement & structElem, FElement & structElem2);

};











/*****************************************************
Fonction pour charger les fichiers existants du projet.
Un exemple est donné en dessous pour chargé un Blueprint 
de type UAnimSequence.
************************************************/

template <typename ObjClass>
static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	//~

	return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString()));
}

// Load Static Mesh From Path 
static FORCEINLINE UAnimSequence* LoadBlueprintFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	//~

	return LoadObjFromPath<UAnimSequence>(Path);
}


