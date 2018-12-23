#include "pcs_game.h"

		uint64_t											pcs::damageCalculatePlayer			
	( ::gpk::array_pod<::pcs::SCharacterProfile> characterProfilesAlive
	, ::gpk::array_pod<::pcs::SCharacterProfile> characterProfilesDead
	)
{
	uint64_t														totalDamage								= 0;
	for(uint32_t iCharacter = 0, countCharacters = characterProfilesAlive	.size(); iCharacter < countCharacters; ++iCharacter) totalDamage += characterProfilesAlive	[iCharacter].Score.DamageDealt;
	for(uint32_t iCharacter = 0, countCharacters = characterProfilesDead	.size(); iCharacter < countCharacters; ++iCharacter) totalDamage += characterProfilesDead	[iCharacter].Score.DamageDealt;
	return totalDamage;
}

static	::gpk::error_t										gameEntityCreate					(::gpk::array_pod<::pcs::SEntity> & entityStorage, ::gpk::array_pod<::pcs::SEntityState> & entityStates)		{ 
	for(uint32_t iEntity = 0, countEntities = entityStates.size(); iEntity < countEntities; ++iEntity) { 
		if (entityStates[iEntity].Unused) { 
			entityStates[iEntity].Unused								= false; 
			return iEntity; 
		} 
	} 
	int32_t															iEntity								= entityStorage.push_back({}); 
	memset(&entityStorage[iEntity], -1, sizeof(::pcs::SEntity)); 
	entityStates.push_back({false}); 
	return iEntity; 
}

		::gpk::error_t										pcs::gameCreateCharacter			(::pcs::SGame & game)																							{ return gameEntityCreate(game.EntityCharacter	, game.StateCharacter	); }
		::gpk::error_t										pcs::gameCreateWeapon				(::pcs::SGame & game)																							{ return gameEntityCreate(game.EntityWeapon		, game.StateWeapon		); }
		::gpk::error_t										pcs::gameCreateArmor				(::pcs::SGame & game)																							{ return gameEntityCreate(game.EntityArmor		, game.StateArmor		); }
		::gpk::error_t										pcs::gameCreateAccessory			(::pcs::SGame & game)																							{ return gameEntityCreate(game.EntityAccessory	, game.StateAccessory	); }
		::gpk::error_t										pcs::gameCreatePlayer				(::pcs::SGame & game)																							{ return gameEntityCreate(game.EntityPlayer		, game.StatePlayer		); }
