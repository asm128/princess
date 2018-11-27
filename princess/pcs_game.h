#include "pcs_player.h"

#ifndef PCS_GAME_H_298342937842389
#define PCS_GAME_H_298342937842389

namespace pcs 
{
	struct SGame {
		::gpk::array_pod<::pcs::SCharacter>					Characters;
		::gpk::array_pod<::pcs::SCharacterProfile>			CharacterProfiles;
		::gpk::array_pod<::pcs::SPlayer>					Players;
	};
}

#endif // PCS_GAME_H_298342937842389
