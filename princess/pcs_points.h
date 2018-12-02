#include "gpk_typeint.h"

#ifndef PCS_POINTS_H_2938409283
#define PCS_POINTS_H_2938409283

namespace pcs 
{
#pragma pack (push, 1)
	struct SPointsHealth {
		int32_t						Health	;
		int32_t						Shield	;
	};

	struct SMultipliersHealth {
		double						Health	;
		double						Shield	;
	};		

	struct SPointsPower {
		int32_t						Mana	;
		int32_t						Energy	;
		int32_t						Stamina	;
	};

	struct SMultipliersPower {
		double						Mana	;
		double						Energy	;
		double						Stamina	;
	};

	struct SPointsFitness {
		int32_t						Attack		;
		int32_t						Movement	;
		int32_t						Reflexes	;
		int32_t						Sight		;
	};

	struct SMultipliersFitness {
		double						Attack		;
		double						Movement	;
		double						Reflexes	;
		double						Sight		;
	};

	struct SPointsAttack {
		int32_t						Range					;
		int32_t						Hit						;
		int32_t						Absorption				;
		int32_t						Damage					;
		SPointsHealth				DirectDamage			;
	};

#pragma pack (pop)
} // namespace

#endif // PCS_POINTS_H_2938409283
