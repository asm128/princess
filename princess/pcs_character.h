#include "pcs_points.h"
#include "gpk_array.h"

#ifndef PCS_CHArACTER_H_0237498234
#define PCS_CHArACTER_H_0237498234

namespace pcs 
{
#pragma pack (push, 1)
	struct SCharacterScore {
	};

	struct SCharacterProfile {
		int32_t										Height				;
		int32_t										Weight				;
		int64_t										TimeBirth			;
		int64_t										TimeDeath			;
		::gpk::array_pod<::gpk::view_const_string>	NamesFirst			;
		::gpk::array_pod<::gpk::view_const_string>	NamesLast			;
		::gpk::array_pod<::gpk::view_const_string>	Nationalities		;
	};

	struct SCharacter {
		::pcs::SPointsHealth						Health				;
		::pcs::SPointsPower							Power				;
		int32_t										CharacterProfile	;
	};

#pragma pack (pop)
} // namespace

#endif // PCS_CHArACTER_H_0237498234
