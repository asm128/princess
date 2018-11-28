#include "pcs_player.h"

#ifndef PCS_GAME_H_298342937842389
#define PCS_GAME_H_298342937842389

namespace pcs 
{
	struct SGame {
		::gpk::array_pod<::pcs::SCharacter>					Characters;
		::gpk::array_pod<::pcs::SCharacterProfile>			CharacterProfilesAlive;
		::gpk::array_pod<::pcs::SCharacterProfile>			CharacterProfilesDead;
		::gpk::array_pod<::pcs::SPlayer>					Players;
	};

	uint64_t											damageCalculatePlayer			
		( const ::gpk::view_array<const ::pcs::SCharacterProfile> characterProfilesAlive
		, const ::gpk::view_array<const ::pcs::SCharacterProfile> characterProfilesDead
		);
}

#endif // PCS_GAME_H_298342937842389
