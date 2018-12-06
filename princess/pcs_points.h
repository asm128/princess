#include "gpk_member_registry.h"

#ifndef PCS_POINTS_H_2938409283
#define PCS_POINTS_H_2938409283

namespace pcs 
{
#pragma pack (push, 1)

	struct SPointsLife {
		GPKMNDF(, int32_t, Health, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMNDF(, int32_t, Shield, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Health)
			,	GPKM_NAME(Shield)
			);
	};

	struct SMultipliersLife {
		GPKMNDF(::gpk, float64_t, Health, ::gpk::DATA_TYPE_FLOAT64)	= 0;
		GPKMNDF(::gpk, float64_t, Shield, ::gpk::DATA_TYPE_FLOAT64)	= 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Health)
			,	GPKM_NAME(Shield)
			);
	};		

	struct SPointsPower {
		GPKMNDF( , int32_t, Energy	, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMNDF( , int32_t, Mana	, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKMNDF( , int32_t, Stamina	, ::gpk::DATA_TYPE_INT32)	= 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Energy	)
			,	GPKM_NAME(Mana		)
			,	GPKM_NAME(Stamina	)
			);
	};

	struct SMultipliersPower {
		GPKMNDF(::gpk, float64_t, Energy	, ::gpk::DATA_TYPE_FLOAT64)	= 0;
		GPKMNDF(::gpk, float64_t, Mana		, ::gpk::DATA_TYPE_FLOAT64)	= 0;
		GPKMNDF(::gpk, float64_t, Stamina	, ::gpk::DATA_TYPE_FLOAT64)	= 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Energy	)
			,	GPKM_NAME(Mana		)
			,	GPKM_NAME(Stamina	)
			);
	};

	struct SPointsFitness {
		GPKMNDF(, int32_t, Attack	, ::gpk::DATA_TYPE_INT32) = 0;
		GPKMNDF(, int32_t, Movement	, ::gpk::DATA_TYPE_INT32) = 0;
		GPKMNDF(, int32_t, Reflexes	, ::gpk::DATA_TYPE_INT32) = 0;
		GPKMNDF(, int32_t, Sight	, ::gpk::DATA_TYPE_INT32) = 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Attack	)
			,	GPKM_NAME(Movement	)
			,	GPKM_NAME(Reflexes	)
			,	GPKM_NAME(Sight		)
			);
	};

	struct SMultipliersFitness {
		GPKMNDF(::gpk, float64_t, Attack	, ::gpk::DATA_TYPE_FLOAT64) = 0;
		GPKMNDF(::gpk, float64_t, Movement	, ::gpk::DATA_TYPE_FLOAT64) = 0;
		GPKMNDF(::gpk, float64_t, Reflexes	, ::gpk::DATA_TYPE_FLOAT64) = 0;
		GPKMNDF(::gpk, float64_t, Sight		, ::gpk::DATA_TYPE_FLOAT64) = 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Attack	)
			,	GPKM_NAME(Movement	)
			,	GPKM_NAME(Reflexes	)
			,	GPKM_NAME(Sight		)
			);
	};

	struct SPointsAttackRaw {
		GPKMNDF( , int32_t, Range		, ::gpk::DATA_TYPE_INT32) = 0;
		GPKMNDF( , int32_t, Hit			, ::gpk::DATA_TYPE_INT32) = 0;
		GPKMNDF( , int32_t, Absorption	, ::gpk::DATA_TYPE_INT32) = 0;
		GPKMNDF( , int32_t, Damage		, ::gpk::DATA_TYPE_INT32) = 0;
		GPKM_REGISTRY
			(	GPKM_NAME(Range			)
			,	GPKM_NAME(Hit			)
			,	GPKM_NAME(Absorption	)
			,	GPKM_NAME(Damage		)
			);
	};

	struct SMultipliersAttackRaw {
		GPKMNDF(::gpk, float64_t, Range			, ::gpk::DATA_TYPE_FLOAT64) = 0;
		GPKMNDF(::gpk, float64_t, Hit			, ::gpk::DATA_TYPE_FLOAT64) = 0;
		GPKMNDF(::gpk, float64_t, Absorption	, ::gpk::DATA_TYPE_FLOAT64) = 0;
		GPKMNDF(::gpk, float64_t, Damage		, ::gpk::DATA_TYPE_FLOAT64) = 0;
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
