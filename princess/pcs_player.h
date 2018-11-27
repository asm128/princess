#include "pcs_character.h"

#ifndef PCS_PLAYER_H_298342937842389
#define PCS_PLAYER_H_298342937842389

namespace pcs 
{
	struct SPlayerScore {
		int32_t												CharactersKilled				= 0;
		int32_t												CharactersBought				= 0;
		int32_t												CharactersSold					= 0;
		int32_t												MoneySpent						= 0;
		int32_t												MoneyEarned						= 0;
		int32_t												MoneyLost						= 0;
	};

	struct SPlayer {
		::gpk::array_pod<int32_t>							Characters;
	};
}

#endif // PCS_PLAYER_H_298342937842389
