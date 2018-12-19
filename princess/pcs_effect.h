#include "gpk_enum.h"

#ifndef PCS_EFFECT_H_20934782908374
#define PCS_EFFECT_H_20934782908374
namespace pcs
{
#pragma pack(push, 1)
	GDEFINE_ENUM_TYPE(COMBAT_STATUS, uint32_t);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, None				, 0x00000	);

	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Blind				, 0x00001	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Stun				, 0x00002	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Shock				, 0x00004	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Bleeding			, 0x00008	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Burn				, 0x00010	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Poison			, 0x00020	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Freezing			, 0x00040	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Petrify			, 0x00080	);

	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Frozen			, 0x00100	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Blackout			, 0x00200	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Charmed			, 0x00400	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Drunk				, 0x00800	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Sleep				, 0x01000	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Slow				, 0x02000	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Weakness			, 0x04000	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Panic				, 0x08000	);

	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Berserk			, 0x10000	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Invisible			, 0x20000	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Rage				, 0x40000	);
	GDEFINE_ENUM_VALUE(COMBAT_STATUS, Bullied			, 0x80000	);

	struct SCombatStatusLevel {
		uint8_t							Blind			:2;
		uint8_t							Stun			:2;
		uint8_t							Shock			:2;
		uint8_t							Bleeding		:2;
		uint8_t							Burn			:2;
		uint8_t							Poison			:2;
		uint8_t							Freezing		:2;
		uint8_t							Petrify			:2;

		uint8_t							Frozen			:2;
		uint8_t							Blackout		:2;
		uint8_t							Charmed			:2;
		uint8_t							Drunk			:2;
		uint8_t							Sleep			:2;
		uint8_t							Slow			:2;
		uint8_t							Weakness		:2;
		uint8_t							Panic			:2;

		uint8_t							Berserk			:2;
		uint8_t							Invisible		:2;
		uint8_t							Rage			:2;
		uint8_t							Bullied			:2;
	};

	struct SCharacterStatus {
		COMBAT_STATUS					Immunity		= {};
		SCombatStatusLevel				Attack			= {};
		SCombatStatusLevel				Passive			= {};
		SCombatStatusLevel				Resistance		= {};
	};

	GDEFINE_ENUM_TYPE(ATTACK_EFFECT, uint16_t);
	GDEFINE_ENUM_VALUE(ATTACK_EFFECT, NONE				, 0x00		);
	GDEFINE_ENUM_VALUE(ATTACK_EFFECT, LEECH_HEALTH		, 0x01		);
	GDEFINE_ENUM_VALUE(ATTACK_EFFECT, LEECH_MANA		, 0x02		);
	GDEFINE_ENUM_VALUE(ATTACK_EFFECT, LEECH_SHIELD		, 0x04		);
	GDEFINE_ENUM_VALUE(ATTACK_EFFECT, LEECH_ENERGY		, 0x08		);
	GDEFINE_ENUM_VALUE(ATTACK_EFFECT, LEECH_STAMINA		, 0x10		);
	GDEFINE_ENUM_VALUE(ATTACK_EFFECT, STEAL				, 0x20		);

	GDEFINE_ENUM_TYPE(DEFEND_EFFECT, uint16_t);
	GDEFINE_ENUM_VALUE(DEFEND_EFFECT, NONE				, 0x00		); 
	GDEFINE_ENUM_VALUE(DEFEND_EFFECT, REFLECT			, 0x01		); 	// Reflects damage to the attacker
	GDEFINE_ENUM_VALUE(DEFEND_EFFECT, BLIND				, 0x02		); 	// Blinds the attacker when inflicting 1 to 1 damage.
	GDEFINE_ENUM_VALUE(DEFEND_EFFECT, IMPENETRABLE		, 0x04		); 	// Reflects damage to the attacker
	GDEFINE_ENUM_VALUE(DEFEND_EFFECT, DEFLECT			, 0x08		); 	// Reflects damage to the attacker

	GDEFINE_ENUM_TYPE(PASSIVE_EFFECT, uint16_t);
	GDEFINE_ENUM_VALUE(PASSIVE_EFFECT, NONE				, 0x00		);
	GDEFINE_ENUM_VALUE(PASSIVE_EFFECT, REGEN_HEALTH		, 0x01		);
	GDEFINE_ENUM_VALUE(PASSIVE_EFFECT, REGEN_MANA		, 0x02		);
	GDEFINE_ENUM_VALUE(PASSIVE_EFFECT, REGEN_SHIELD		, 0x04		);
	GDEFINE_ENUM_VALUE(PASSIVE_EFFECT, REGEN_ENERGY		, 0x08		);
	GDEFINE_ENUM_VALUE(PASSIVE_EFFECT, REGEN_STAMINA	, 0x10		);
	GDEFINE_ENUM_VALUE(PASSIVE_EFFECT, SHIELD_REPAIR	, 0x20		);
#pragma pack(pop)
} // namespace

#endif // PCS_EFFECT_H_20934782908374