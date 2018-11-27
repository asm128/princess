#include "gpk_typeint.h"

#ifndef PCS_POINTS_H_2938409283
#define PCS_POINTS_H_2938409283

namespace pcs 
{
#pragma pack (push, 1)
	struct SPointsHealth {
		uint32_t			Health	;
		uint32_t			Shield	;
	};

	struct SMultipliersHealth {
		double				Health	;
		double				Shield	;
	};		

	struct SPointsPower {
		uint32_t			Mana	;
		uint32_t			Energy	;
	};

	struct SMultipliersPower {
		double				Mana	;
		double				Energy	;
	};
#pragma pack (pop)
} // namespace

#endif // PCS_POINTS_H_2938409283
