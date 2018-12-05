#include "pcs_points.h"
#include "gpk_array.h"

#ifndef PCS_CHArACTER_H_0237498234
#define PCS_CHArACTER_H_0237498234

namespace pcs 
{
#pragma pack (push, 1)
	struct SCharacterScore {
		uint64_t									MoneyEarned				= 0;
		uint64_t									MoneySpent				= 0;

		uint64_t									DamageDealt				= 0;
		uint64_t									DamageTaken				= 0;

		uint64_t									TurnsPlayed				= 0;

		uint64_t									BattlesWon				= 0;
		uint64_t									BattlesLost				= 0;

		uint64_t									EscapesSucceeded		= 0;
		uint64_t									EscapesFailed			= 0;

		uint64_t									EnemiesKilled			= 0;
		uint64_t									AttacksHit				= 0;
		uint64_t									AttacksMissed			= 0;
		uint64_t									AttacksReceived			= 0;
		uint64_t									AttacksAvoided			= 0;
		uint64_t									ShotsFired				= 0;

		uint64_t									UsedPotions				= 0;
		uint64_t									UsedGrenades			= 0;
		uint64_t									UsedProjectiless		= 0;

		uint64_t									CompletedResearch		= 0;
		uint64_t									CompletedProduction		= 0;
		uint64_t									CompletedUpgrade		= 0;

	};

	static constexpr const size_t CHARACTER_SCORE_TABLE_SIZE = sizeof(::pcs::SCharacterScore);

	struct SCharacterProfile {
		int32_t										Height				;
		int32_t										Weight				;
		int64_t										TimeBirth			;
		int64_t										TimeDeath			;
		SCharacterScore								Score				;
		::gpk::array_pod<::gpk::view_const_string>	NamesFirst			;
		::gpk::array_pod<::gpk::view_const_string>	NamesLast			;
		::gpk::array_pod<::gpk::view_const_string>	Nationalities		;
	};

	struct SCharacter {
		::pcs::SPointsLife							Health				;
		::pcs::SPointsPower							Power				;
		::pcs::SPointsFitness						Fitness				;
		int32_t										CharacterProfile	;
	};

#pragma pack (pop)
} // namespace

#endif // PCS_CHArACTER_H_0237498234
