// Temp

#include "Play4_9.h"


#include "BP_Library.h"


UBP_Library::UBP_Library(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	

}


// TODO revoir le cas de la boucle c-a-d ==6 || -6

bool UBP_Library::isStronger(FElement & structElem, FElement & structElem2) {
	if ((int32)(structElem.enumElement) -
		(int32)(structElem2.enumElement) == 1 || (int32)(structElem.enumElement) -
		(int32)(structElem2.enumElement) == 6 )
	{
		return true;
	}

	return false;
}
bool UBP_Library::isWeaker(FElement & structElem, FElement & structElem2) {
	if ((int32)(structElem.enumElement) -
		(int32)(structElem2.enumElement) == -1 || (int32)(structElem.enumElement) -
		(int32)(structElem2.enumElement) == -6 )
	{
		return true;
	}

	return false;
}