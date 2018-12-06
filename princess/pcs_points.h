#include "gpk_member_registry.h"

#ifndef PCS_POINTS_H_2938409283
#define PCS_POINTS_H_2938409283

namespace pcs 
{
#pragma pack (push, 1)

	struct SPointsLife {
		GPKM(::pcs, SPointsLife, , int32_t, Health, ::gpk::DATA_TYPE_INT32	, "Health", "Health Points")	= 0;
		GPKM(::pcs, SPointsLife, , int32_t, Shield, ::gpk::DATA_TYPE_INT32	, "Shield", "Shield Points")	= 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Health)
			,	GPKM_NAME(Shield)
			);
	};

	struct SMultipliersLife {
		GPKM(::pcs, SMultipliersLife, ::gpk, float64_t, Health, ::gpk::DATA_TYPE_FLOAT64, "Health", "Health Multipliers")	= 0;
		GPKM(::pcs, SMultipliersLife, ::gpk, float64_t, Shield, ::gpk::DATA_TYPE_FLOAT64, "Shield", "Shield Multipliers")	= 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Health)
			,	GPKM_NAME(Shield)
			);
	};		

	struct SPointsPower {
		GPKM(::pcs, SPointsPower, , int32_t, Energy	, ::gpk::DATA_TYPE_INT32, "Energy"	, "Energy Points"	)	= 0;
		GPKM(::pcs, SPointsPower, , int32_t, Mana	, ::gpk::DATA_TYPE_INT32, "Mana"	, "Mana Points"		)	= 0;
		GPKM(::pcs, SPointsPower, , int32_t, Stamina, ::gpk::DATA_TYPE_INT32, "Stamina"	, "Stamina Points"	)	= 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Energy	)
			,	GPKM_NAME(Mana		)
			,	GPKM_NAME(Stamina	)
			);
	};

	struct SMultipliersPower {
		GPKM(::pcs, SMultipliersPower, ::gpk, float64_t, Energy	, ::gpk::DATA_TYPE_FLOAT64, "Energy"	, "Energy Multipliers"				)	= 0;
		GPKM(::pcs, SMultipliersPower, ::gpk, float64_t, Mana	, ::gpk::DATA_TYPE_FLOAT64, "Mana"		, "Mana Multipliers"				)	= 0;
		GPKM(::pcs, SMultipliersPower, ::gpk, float64_t, Stamina, ::gpk::DATA_TYPE_FLOAT64, "Stamina"	, "Stamina Multipliers"				)	= 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Energy	)
			,	GPKM_NAME(Mana		)
			,	GPKM_NAME(Stamina	)
			);
	};

	struct SPointsFitness {
		GPKM(::pcs, SPointsFitness, , int32_t, Attack	, ::gpk::DATA_TYPE_INT32, "Attack"		, "Attack Points"							) = 0;
		GPKM(::pcs, SPointsFitness, , int32_t, Movement	, ::gpk::DATA_TYPE_INT32, "Movement"	, "Movement Points"							) = 0;
		GPKM(::pcs, SPointsFitness, , int32_t, Reflexes	, ::gpk::DATA_TYPE_INT32, "Reflexes"	, "Reflexes Points"							) = 0;
		GPKM(::pcs, SPointsFitness, , int32_t, Sight	, ::gpk::DATA_TYPE_INT32, "Sight"		, "Sight Points"							) = 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Attack	)
			,	GPKM_NAME(Movement	)
			,	GPKM_NAME(Reflexes	)
			,	GPKM_NAME(Sight		)
			);
	};

	struct SMultipliersFitness {
		GPKM(::pcs, SMultipliersFitness, ::gpk, float64_t, Attack	, ::gpk::DATA_TYPE_FLOAT64, "Attack"	, "Attack Multipliers"				) = 0;
		GPKM(::pcs, SMultipliersFitness, ::gpk, float64_t, Movement	, ::gpk::DATA_TYPE_FLOAT64, "Movement"	, "Movement Multipliers"			) = 0;
		GPKM(::pcs, SMultipliersFitness, ::gpk, float64_t, Reflexes	, ::gpk::DATA_TYPE_FLOAT64, "Reflexes"	, "Reflexes Multipliers"			) = 0;
		GPKM(::pcs, SMultipliersFitness, ::gpk, float64_t, Sight	, ::gpk::DATA_TYPE_FLOAT64, "Sight"		, "Sight Multipliers"				) = 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Attack	)
			,	GPKM_NAME(Movement	)
			,	GPKM_NAME(Reflexes	)
			,	GPKM_NAME(Sight		)
			);
	};

	struct SPointsAttackRaw {
		GPKM(::pcs, SPointsAttackRaw, , int32_t, Range		, ::gpk::DATA_TYPE_INT32, "Range"		, "Range Points"							) = 0;
		GPKM(::pcs, SPointsAttackRaw, , int32_t, Hit		, ::gpk::DATA_TYPE_INT32, "Hit"			, "Hit Points"								) = 0;
		GPKM(::pcs, SPointsAttackRaw, , int32_t, Absorption	, ::gpk::DATA_TYPE_INT32, "Absorption"	, "Absorption Points"						) = 0;
		GPKM(::pcs, SPointsAttackRaw, , int32_t, Damage		, ::gpk::DATA_TYPE_INT32, "Damage"		, "Damage Points"							) = 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Range			)
			,	GPKM_NAME(Hit			)
			,	GPKM_NAME(Absorption	)
			,	GPKM_NAME(Damage		)
			);
	};

	struct SMultipliersAttackRaw {
		GPKM(::pcs, SMultipliersAttackRaw, ::gpk, float64_t, Range		, ::gpk::DATA_TYPE_FLOAT64, "Range"			, "Range Multipliers"		) = 0;
		GPKM(::pcs, SMultipliersAttackRaw, ::gpk, float64_t, Hit		, ::gpk::DATA_TYPE_FLOAT64, "Hit"			, "Hit Multipliers"			) = 0;
		GPKM(::pcs, SMultipliersAttackRaw, ::gpk, float64_t, Absorption	, ::gpk::DATA_TYPE_FLOAT64, "Absorption"	, "Absorption Multipliers"	) = 0;
		GPKM(::pcs, SMultipliersAttackRaw, ::gpk, float64_t, Damage		, ::gpk::DATA_TYPE_FLOAT64, "Damage"		, "Damage Multipliers"		) = 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Range			)
			,	GPKM_NAME(Hit			)
			,	GPKM_NAME(Absorption	)
			,	GPKM_NAME(Damage		)
			);
	};

	struct SPointsAttackFull {
		SPointsAttackRaw			Raw				= {};
		SPointsLife					DirectDamage	= {};
		SPointsLife					DrainHealth		= {};
		SPointsPower				DrainPower		= {};
	};

#pragma pack (pop)
} // namespace

#endif // PCS_POINTS_H_2938409283
