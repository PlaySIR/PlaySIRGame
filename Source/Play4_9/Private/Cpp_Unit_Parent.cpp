// Temp
#include "Play4_9.h"
#include "BP_Library.h"
#include "Play4_9_GameMode.h"

#include "Cpp_Unit_Parent.h"


// Sets default values
ACpp_Unit_Parent::ACpp_Unit_Parent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACpp_Unit_Parent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACpp_Unit_Parent::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ACpp_Unit_Parent::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}


/**
def == for element

//une attaque a plusieur effet on choisi de laisser l'effet 0 pour l'instant
**/

//TODO ajouter un random
void ACpp_Unit_Parent::ApplyEnchantement(FAttaque & structAttaque, ACpp_Unit_Parent * Victime){

	if(Victime->isEnchanted)
		return;
	
		 
		if(structAttaque.effets[0].structEnchantement.elementCritique[0].enumElement == Victime->myElement.enumElement
			|| structAttaque.effets[0].structEnchantement.elementBonus[0].enumElement == Victime->myElement.enumElement ){
			this->initLatencyEnchantement(structAttaque.effets[0]);
			Victime->ApplyDamageEnchantement();
			Victime->FlipFlopEnchanted();
	}
	
}

//Ajouter l'animation d'application des dégats d'enchantements
 void ACpp_Unit_Parent::ApplyDamageEnchantement(){
 	if(this->latencyRemaining.Num() == 0)
 		return;
 	for (auto It = this->latencyRemaining.CreateIterator(); It; ++It){
        if(It.Value() >0){
			this->mCurrentHealth -= It.Key()->effets;
           	--(It.Value()); 
        }
        if(It.Value() <= 0){
			this->latencyRemaining.Remove(It.Key());
        	FlipFlopEnchanted();
        }
	}	
 }

//Appliquer l'animation de fin/début d'enchantement
 void ACpp_Unit_Parent::FlipFlopEnchanted(){
 	this->isEnchanted = !isEnchanted;
 }

 void ACpp_Unit_Parent::initLatencyEnchantement(FEffet & effet)
 {
	 latencyRemaining[&effet] = effet.latence;
	 

 }

 // ne pas oublié la défense du joueur !!!!!!!!!!!!!
 
int ACpp_Unit_Parent::CalculAttack_Elem(FAttaque & structAttaque, ACpp_Unit_Parent * Victime){
/*	if(isStronger(structAttaque.element,Victime->myElement))
		return ((int32)(structAttaque.damage * FMath::Sqrt(2));
	if(isWeaker(structAttaque.element,Victime->myElement))
		return ((int32)(structAttaque.damage * FMath::Sqrt(1/2));
*/
	return structAttaque.damage;
}


// def = 1 => Protection ; def = 3 => tentative d'esquive 
// attack = 1 => Précision ; attack => Bourrinage
//

	float ACpp_Unit_Parent::CalculAttack_Fleche(int32 fl1_attack, int32 fl2_attack, int32 fl1_def, int32 fl2_def){
		
		if(flechCritique(fl1_attack,fl2_attack,fl1_def,fl2_def)){
			if(abs(fl1_attack - fl2_attack)==1){
				if(abs(fl1_def- fl2_def)==1)
					return 0.9;
				if(abs(fl1_def - fl2_def)==3)
					return 1.1;
				return 1.0;
			}
			if(abs(fl1_attack - fl2_attack)==3){
				if(abs(fl1_def- fl2_def)==1)
					return 1.1;
				if(abs(fl1_def - fl2_def)==3)
					return 1.3;
				return 1.2;
			}
		}
		float random = (float)(FMath::RandRange(0, 100))/100.0;
		if(flechLoose(fl1_attack,fl2_attack,fl1_def,fl2_def)){
			float alpha = random/ abs(fl1_attack - fl2_attack);
			float beta = random/ abs(fl1_def - fl2_def);

			if(alpha < beta){
				return 0.0;
			}
			if(abs(fl1_attack - fl2_attack)==1){
				if(abs(fl1_def - fl2_def)==1)
					return 0.3;
				if(abs(fl1_def - fl2_def)==3)
					return 0.5;
				return 0.4;
			}
			if(abs(fl1_attack - fl2_attack)==3){
				if(abs(fl1_def - fl2_def)==1)
					return 0.5;
				if(abs(fl1_def - fl2_def)==3)
					return 0.7;
				return 0.6;
			}
		}	
		return 1.0;
	}


	bool ACpp_Unit_Parent::flechCritique(int32 fl1_attack, int32 fl2_attack, int32 fl1_def , int32 fl2_def){

		bool result = (fl1_attack == fl1_def && fl2_attack == fl2_def) || (fl1_attack == fl2_def && fl2_attack == fl1_def);

		return result;

	}

	bool ACpp_Unit_Parent::flechLoose(int32 fl1_attack, int32 fl2_attack, int32 fl1_def , int32 fl2_def){

		bool result = (fl1_attack != fl1_def && fl2_attack != fl2_def) || (fl1_attack != fl2_def && fl2_attack != fl1_def);

		return result;

	}


	int32 ACpp_Unit_Parent::DamageFinal(FAttaque & structAttaque, ACpp_Unit_Parent * Victime,bool playerTurn){
		float coef = 0.0;
		int result = CalculAttack_Elem(structAttaque,Victime);
		TArray<int32> IA_arrowGenerator = IAflecheGenerator();

		if (playerTurn) {
			TArray<int32> attackFlech = flechGenerator();
			coef = CalculAttack_Fleche(attackFlech[0], attackFlech[1], IA_arrowGenerator[0], IA_arrowGenerator[1]);

		}
		else {
			TArray<int32> defFlech = flechGenerator();
			 coef = CalculAttack_Fleche(IA_arrowGenerator[0], IA_arrowGenerator[1], defFlech[0], defFlech[1]);

		}

		result = (int32)((float)result * coef);

		return result;
	}

TArray<int32> ACpp_Unit_Parent::flechGenerator(){
	
	return	((APlay4_9_GameMode*)GetWorld()->GetAuthGameMode())->ArrowHUD->selectFlech;

		}
	

TArray<int32> ACpp_Unit_Parent::IAflecheGenerator() {

	int32 first = (FMath::RandRange(0, 100)) / 25	;
	int32 second = (FMath::RandRange(0, 100)) / 25;
	TArray<int32> result;

	while(first == second)
		second = (FMath::RandRange(0, 100)) / 100;
	
	result.Add(first);
	result.Add(second);

	return result;

}
