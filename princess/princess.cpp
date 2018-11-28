#include "pcs_game.h"

			uint64_t										damageCalculatePlayer			
	( ::gpk::array_pod<::pcs::SCharacterProfile> characterProfilesAlive
	, ::gpk::array_pod<::pcs::SCharacterProfile> characterProfilesDead
	) {
	uint64_t														totalDamage								= 0;
	for(uint32_t iCharacter = 0, countCharacters = characterProfilesAlive	.size(); iCharacter < countCharacters; ++iCharacter) totalDamage += characterProfilesAlive	[iCharacter].Score.DamageDealt;
	for(uint32_t iCharacter = 0, countCharacters = characterProfilesDead	.size(); iCharacter < countCharacters; ++iCharacter) totalDamage += characterProfilesDead	[iCharacter].Score.DamageDealt;
	return totalDamage;
}
