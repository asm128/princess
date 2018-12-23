#include "pcs_player.h"

#ifndef PCS_GAME_H_298342937842389
#define PCS_GAME_H_298342937842389

namespace pcs 
{
	struct SGame {
		::gpk::array_pod<::pcs::SCharacterProfile>			CharacterProfilesAlive		= {};
		::gpk::array_pod<::pcs::SCharacterProfile>			CharacterProfilesDead		= {};

		::gpk::array_pod<::pcs::SEntity>					EntityCharacter				= {};
		::gpk::array_pod<::pcs::SEntity>					EntityWeapon				= {};
		::gpk::array_pod<::pcs::SEntity>					EntityArmor					= {};
		::gpk::array_pod<::pcs::SEntity>					EntityAccessory				= {};
		::gpk::array_pod<::pcs::SEntity>					EntityPlayer				= {};

		::gpk::array_pod<::pcs::SEntityState>				StateCharacter				= {};
		::gpk::array_pod<::pcs::SEntityState>				StateWeapon					= {};
		::gpk::array_pod<::pcs::SEntityState>				StateArmor					= {};
		::gpk::array_pod<::pcs::SEntityState>				StateAccessory				= {};
		::gpk::array_pod<::pcs::SEntityState>				StatePlayer					= {};
	};

	uint64_t											damageCalculatePlayer			
		( ::gpk::array_pod<::pcs::SCharacterProfile> characterProfilesAlive
		, ::gpk::array_pod<::pcs::SCharacterProfile> characterProfilesDead
		);
	::gpk::error_t										gameCreateCharacter			(::pcs::SGame & game);
	::gpk::error_t										gameCreateWeapon			(::pcs::SGame & game);
	::gpk::error_t										gameCreateArmor				(::pcs::SGame & game);
	::gpk::error_t										gameCreateAccessory			(::pcs::SGame & game);
	::gpk::error_t										gameCreatePlayer			(::pcs::SGame & game);

	static inline	::gpk::error_t						gameDeleteCharacter			(::pcs::SGame & game, int32_t iEntity) { game.StateCharacter[iEntity].Unused = true; return 0; }
	static inline	::gpk::error_t						gameDeleteWeapon			(::pcs::SGame & game, int32_t iEntity) { game.StateWeapon	[iEntity].Unused = true; return 0; }
	static inline	::gpk::error_t						gameDeleteArmor				(::pcs::SGame & game, int32_t iEntity) { game.StateArmor	[iEntity].Unused = true; return 0; }
	static inline	::gpk::error_t						gameDeleteAccessory			(::pcs::SGame & game, int32_t iEntity) { game.StateAccessory[iEntity].Unused = true; return 0; }
	static inline	::gpk::error_t						gameDeletePlayer			(::pcs::SGame & game, int32_t iEntity) { game.StatePlayer	[iEntity].Unused = true; return 0; }
}

#endif // PCS_GAME_H_298342937842389
