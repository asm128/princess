#include "pcs_character.h"

#ifndef PCS_PLAYER_H_298342937842389
#define PCS_PLAYER_H_298342937842389

namespace pcs 
{
	struct SPlayerScore {
		GPKMBND(, int32_t									, CharactersKilled	, ::gpk::DATA_TYPE_INT32) = 0;
		GPKMBND(, int32_t									, CharactersBought	, ::gpk::DATA_TYPE_INT32) = 0;
		GPKMBND(, int32_t									, CharactersSold	, ::gpk::DATA_TYPE_INT32) = 0;

		GPKMBND(, int32_t									, MoneySpent		, ::gpk::DATA_TYPE_INT32) = 0;
		GPKMBND(, int32_t									, MoneyEarned		, ::gpk::DATA_TYPE_INT32) = 0;
		GPKMBND(, int32_t									, MoneyLost			, ::gpk::DATA_TYPE_INT32) = 0;
	};

	struct SPlayer {
		::gpk::array_pod<int32_t>							Characters;
	};
}

#endif // PCS_PLAYER_H_298342937842389
