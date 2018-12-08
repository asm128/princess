#include "pcs_points.h"
#include "gpk_array.h"

#ifndef PCS_CHArACTER_H_0237498234
#define PCS_CHArACTER_H_0237498234

namespace pcs 
{
#pragma pack (push, 1)
	struct SCharacterScore {
		GPKMNDF(, uint64_t, 						MoneyEarned			, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMNDF(, uint64_t, 						MoneySpent			, ::gpk::DATA_TYPE_INT64)	= 0;

		GPKMNDF(, uint64_t, 						DamageDealt			, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMNDF(, uint64_t, 						DamageTaken			, ::gpk::DATA_TYPE_INT64)	= 0;

		GPKMNDF(, uint64_t, 						TurnsPlayed			, ::gpk::DATA_TYPE_INT64)	= 0;

		GPKMNDF(, uint64_t, 						BattlesWon			, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMNDF(, uint64_t, 						BattlesLost			, ::gpk::DATA_TYPE_INT64)	= 0;

		GPKMNDF(, uint64_t, 						EscapesSucceeded	, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMNDF(, uint64_t, 						EscapesFailed		, ::gpk::DATA_TYPE_INT64)	= 0;

		GPKMNDF(, uint64_t, 						EnemiesKilled		, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMNDF(, uint64_t, 						AttacksHit			, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMNDF(, uint64_t, 						AttacksMissed		, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMNDF(, uint64_t, 						AttacksReceived		, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMNDF(, uint64_t, 						AttacksAvoided		, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMNDF(, uint64_t, 						ShotsFired			, ::gpk::DATA_TYPE_INT64)	= 0;

		GPKMNDF(, uint64_t, 						UsedPotions			, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMNDF(, uint64_t, 						UsedGrenades		, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMNDF(, uint64_t, 						UsedProjectiless	, ::gpk::DATA_TYPE_INT64)	= 0;

		GPKMNDF(, uint64_t, 						CompletedResearch	, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMNDF(, uint64_t, 						CompletedProduction	, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMNDF(, uint64_t, 						CompletedUpgrade	, ::gpk::DATA_TYPE_INT64)	= 0;

	};

	static constexpr const size_t CHARACTER_SCORE_TABLE_SIZE = sizeof(::pcs::SCharacterScore);

	struct SCharacterProfile {
		int32_t										Height					;
		int32_t										Weight					;
		int64_t										TimeBirth				;
		int64_t										TimeDeath				;
		SCharacterScore								Score					;
		::gpk::array_pod<::gpk::view_const_string>	NamesFirst				;
		::gpk::array_pod<::gpk::view_const_string>	NamesLast				;
		::gpk::array_pod<::gpk::view_const_string>	Nationalities			;
	};

	struct SCharacter {
		::pcs::SPointsLife							Life					;
		::pcs::SPointsPower							Power					;
		::pcs::SPointsFitness						Fitness					;
		::pcs::SPointsAttack						Attack					;
		::pcs::SPointsLife							Life					;
		::pcs::SPointsPower							DirectDamagePower		;
		::pcs::SPointsLife							DirectDamageDrainLife	;
		::pcs::SPointsPower							DrainPower				;
		int32_t										CharacterProfile		;
	};

#pragma pack (pop)
} // namespace

#endif // PCS_CHArACTER_H_0237498234
