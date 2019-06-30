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

	struct SCombatStatusValue {
		GPKMBND( , int32_t,				Blind			, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Stun			, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Shock			, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Bleeding		, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Burn			, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Poison			, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Freezing		, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Petrify			, ::gpk::DATA_TYPE_INT32)	= 0;
	//	GPKMBND( , int32_t,								, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Frozen			, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Blackout		, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Charmed			, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Drunk			, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Sleep			, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Slow			, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Weakness		, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Panic			, ::gpk::DATA_TYPE_INT32)	= 0;
	//	GPKMBND( , int32_t,								, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Berserk			, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Invisible		, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Rage			, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,				Bullied			, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Blind		)
			,	GPKM_NAME(Stun		)
			,	GPKM_NAME(Shock		)
			,	GPKM_NAME(Bleeding	)
			,	GPKM_NAME(Burn		)
			,	GPKM_NAME(Poison	)
			,	GPKM_NAME(Freezing	)
			,	GPKM_NAME(Petrify	)
//			,	GPKM_NAME(			)
			,	GPKM_NAME(Frozen	)
			,	GPKM_NAME(Blackout	)
			,	GPKM_NAME(Charmed	)
			,	GPKM_NAME(Drunk		)
			,	GPKM_NAME(Sleep		)
			,	GPKM_NAME(Slow		)
			,	GPKM_NAME(Weakness	)
			,	GPKM_NAME(Panic		)
//			,	GPKM_NAME(			)
			,	GPKM_NAME(Berserk	)
			,	GPKM_NAME(Invisible	)
			,	GPKM_NAME(Rage		)
			,	GPKM_NAME(Bullied	)
			);
	};

	struct SCharacterStatus {
		COMBAT_STATUS					Immunity		= {};
		SCombatStatusLevel				Attack			= {};
		SCombatStatusLevel				Passive			= {};
		SCombatStatusLevel				Resistance		= {};
	};

	GDEFINE_ENUM_TYPE(ATTACK_EFFECT, uint16_t);
	GDEFINE_ENUM_VALUE(ATTACK_EFFECT, None				, 0x00		);
	GDEFINE_ENUM_VALUE(ATTACK_EFFECT, Leech_Health		, 0x01		);
	GDEFINE_ENUM_VALUE(ATTACK_EFFECT, Leech_Mana		, 0x02		);
	GDEFINE_ENUM_VALUE(ATTACK_EFFECT, Leech_Shield		, 0x04		);
	GDEFINE_ENUM_VALUE(ATTACK_EFFECT, Leech_Energy		, 0x08		);
	GDEFINE_ENUM_VALUE(ATTACK_EFFECT, Leech_Stamina		, 0x10		);
	GDEFINE_ENUM_VALUE(ATTACK_EFFECT, Steal				, 0x20		);

	GDEFINE_ENUM_TYPE(DEFEND_EFFECT, uint16_t);
	GDEFINE_ENUM_VALUE(DEFEND_EFFECT, None				, 0x00		); 
	GDEFINE_ENUM_VALUE(DEFEND_EFFECT, Reflect			, 0x01		); 	// Reflects damage to the attacker
	GDEFINE_ENUM_VALUE(DEFEND_EFFECT, Blind				, 0x02		); 	// Blinds the attacker when inflicting 1 to 1 damage.
	GDEFINE_ENUM_VALUE(DEFEND_EFFECT, Impenetrable		, 0x04		); 	// Forces 100% damage absorption
	GDEFINE_ENUM_VALUE(DEFEND_EFFECT, Deflect			, 0x08		); 	// Reflects damage to the attacker

	struct SDefend {
		GPKMBND( , int32_t,					 Reflect		, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,					 Blind			, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,					 Impenetrable	, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMBND( , int32_t,					 Deflect		, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKM_REGISTRY
		(	GPKM_NAME(Reflect			)
		,	GPKM_NAME(Blind				)
		,	GPKM_NAME(Impenetrable		)
		,	GPKM_NAME(Deflect			)
		);	   
	};
	GDEFINE_ENUM_TYPE(PASSIVE_EFFECT, uint16_t);
	GDEFINE_ENUM_VALUE(PASSIVE_EFFECT, None				, 0x00		);
	GDEFINE_ENUM_VALUE(PASSIVE_EFFECT, Regen_Health		, 0x01		);
	GDEFINE_ENUM_VALUE(PASSIVE_EFFECT, Regen_Shield		, 0x02		);
	GDEFINE_ENUM_VALUE(PASSIVE_EFFECT, Regen_Energy		, 0x04		);
	GDEFINE_ENUM_VALUE(PASSIVE_EFFECT, Regen_Mana		, 0x08		);
	GDEFINE_ENUM_VALUE(PASSIVE_EFFECT, Regen_Stamina	, 0x10		);
	GDEFINE_ENUM_VALUE(PASSIVE_EFFECT, Repair_Shield	, 0x20		);
#pragma pack(pop)
} // namespace

#endif // PCS_EFFECT_H_20934782908374