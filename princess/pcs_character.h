#include "pcs_points.h"
#include "pcs_effect.h"
#include "gpk_array.h"
#include "gpk_noise.h"

#ifndef PCS_CHARACTER_H_0237498234
#define PCS_CHARACTER_H_0237498234

namespace pcs 
{
#pragma pack (push, 1)
	struct SCharacterScore {
		GPKMBND(, uint64_t, MoneyEarned			, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, MoneySpent			, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, DamageDealt			, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, DamageTaken			, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, TurnsPlayed			, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, BattlesWon			, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, BattlesLost			, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, EnemiesKilled		, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, AttacksHit			, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, AttacksMissed		, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, AttacksReceived		, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, AttacksAvoided		, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, ShotsFired			, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, UsedPotions			, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, UsedGrenades		, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, UsedProjectiles		, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, CompletedResearch	, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, CompletedProduction	, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKMBND(, uint64_t, CompletedUpgrade	, ::gpk::DATA_TYPE_INT64)	= 0;
		GPKM_REGISTRY
			(	GPKM_NAME(MoneyEarned			)
			,	GPKM_NAME(MoneySpent			)
			,	GPKM_NAME(DamageDealt			)
			,	GPKM_NAME(DamageTaken			)
			,	GPKM_NAME(TurnsPlayed			)
			,	GPKM_NAME(BattlesWon			)
			,	GPKM_NAME(BattlesLost			)
			,	GPKM_NAME(EnemiesKilled			)
			,	GPKM_NAME(AttacksHit			)
			,	GPKM_NAME(AttacksMissed			)
			,	GPKM_NAME(AttacksReceived		)
			,	GPKM_NAME(AttacksAvoided		)
			,	GPKM_NAME(ShotsFired			)
			,	GPKM_NAME(UsedPotions			)
			,	GPKM_NAME(UsedGrenades			)
			,	GPKM_NAME(UsedProjectiles		)
			,	GPKM_NAME(CompletedResearch		)
			,	GPKM_NAME(CompletedProduction	)
			,	GPKM_NAME(CompletedUpgrade		)
			);
	};

	static constexpr	const size_t			CHARACTER_SCORE_TABLE_SIZE				= sizeof(::pcs::SCharacterScore);

	struct SCharacterProfile {
		int32_t										Height			;
		int32_t										Weight			;
		int64_t										TimeBirth		;
		int64_t										TimeDeath		;
		SCharacterScore								Score			;
		::gpk::array_pod<::gpk::view_const_string>	NamesFirst		;
		::gpk::array_pod<::gpk::view_const_string>	NamesLast		;
		::gpk::array_pod<::gpk::view_const_string>	Nationalities	;
	};

	struct SEntityPropertyPoints {
		::pcs::SPointsLife							Life								= {};
		::pcs::SPointsPower							Power								= {};
		::pcs::SPointsFitness						Fitness								= {};
		::pcs::SPointsAttack						Attack								= {};
		::pcs::SPointsLife							DirectDamageLife					= {};
		::pcs::SPointsPower							DirectDamagePower					= {};
		::pcs::SPointsLife							DrainLife							= {};
		::pcs::SPointsPower							DrainPower							= {};
		::pcs::SPointsLife							RegenLife							= {};
		::pcs::SPointsPower							RegenPower							= {};
		::pcs::SPointsLife							MaxLife								= {};
		::pcs::SPointsPower							MaxPower							= {};
		::pcs::SPointsLife							BonusLife							= {};
		::pcs::SPointsPower							BonusPower							= {};
	};

	struct SEntityPropertyGroups {
		GPKMBND( , int32_t, Life				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMBND( , int32_t, Power				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMBND( , int32_t, Fitness				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMBND( , int32_t, Attack				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMBND( , int32_t, DirectDamageLife	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMBND( , int32_t, DirectDamagePower	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMBND( , int32_t, DrainLife			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMBND( , int32_t, DrainPower			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMBND( , int32_t, RegenLife			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMBND( , int32_t, RegenPower			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMBND( , int32_t, MaxLife				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMBND( , int32_t, MaxPower			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMBND( , int32_t, BonusLife			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMBND( , int32_t, BonusPower			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKM_REGISTRY
			(	GPKM_NAME(Life				)
			,	GPKM_NAME(Power				)
			,	GPKM_NAME(Fitness			)
			,	GPKM_NAME(Attack			)
			,	GPKM_NAME(DirectDamageLife	)
			,	GPKM_NAME(DirectDamagePower	)
			,	GPKM_NAME(DrainLife			)
			,	GPKM_NAME(DrainPower		)
			,	GPKM_NAME(RegenLife			)
			,	GPKM_NAME(RegenPower		)
			,	GPKM_NAME(MaxLife			)
			,	GPKM_NAME(MaxPower			)
			,	GPKM_NAME(BonusLife			)
			,	GPKM_NAME(BonusPower		)
			);
	};

	struct SEntity {
		//::pcs::SEntityPropertyPoints				Points								= {};
		::pcs::SEntityPropertyGroups				PointIndices						= {};
		::pcs::SCombatStatusLevel					ImmunityInflict						= {};
		::pcs::SCombatStatusLevel					ResistanceLevel						= {};
		int32_t										CharacterProfile					= -1;
	};

	struct SEntityState {
		bool										Unused								: 1;
	};

	static constexpr	const size_t			Charsize							= sizeof(SEntity);
	static constexpr	const uint32_t			POINT_SCALE_INT						= 10000;
	static constexpr	const double			POINT_SCALE_DOUBLE					= 10000.0;

// Returns 2 if deflected, 1 if hit and 
	::gpk::error_t								attackCalculateHitChanceResult	
		( ::gpk::SPRNG					& prng
		, const ::pcs::SPointsAttack	& attackerPoints
		, const ::pcs::SPointsFitness	& attackerFitness
		, const ::pcs::SPointsFitness	& attackedFitness
		, const ::pcs::SCharacterStatus	& attackerStatus
		, const ::pcs::SCharacterStatus	& attackedStatus
		, const ::pcs::SDefend			& attackedDefend
		);

	::gpk::error_t								attackCalculateDamage			
		( ::pcs::SPointsLife			& lifeRemaining
		, ::pcs::SPointsLife			& damageDealt
		, ::pcs::SPointsLife			& damageReflected
		, ::pcs::SPointsPower			& powerRemaining
		, ::pcs::SPointsPower			& powerDamageDealt
		, ::pcs::SEntityPropertyPoints	& attacker
		, const ::pcs::SDefend			& attackedDefend
		, int32_t						absorption
		);

	::gpk::error_t								attackApplyDrain
		( ::pcs::SPointsLife			& damageDealt
		, ::pcs::SPointsLife			& lifeDrained
		, ::pcs::SPointsLife			& drainPoints
		, ::pcs::SPointsPower			& powerDamageDealt
		, ::pcs::SPointsPower			& powerDrained
		, ::pcs::SPointsPower			& powerDrainPoints
		);
	::gpk::error_t								attackMelee						
		( ::gpk::SPRNG					& prng
		, ::pcs::SCharacterScore		& scoreAttacker
		, ::pcs::SCharacterScore		& scoreAttacked
		, ::pcs::SEntityPropertyPoints	& attacker
		, ::pcs::SEntityPropertyPoints	& attacked
		, ::pcs::SCharacterStatus		& attackerStatus
		, ::pcs::SCharacterStatus		& attackedStatus
		//, ::pcs::SDefend				& attackerDefend
		, const ::pcs::SDefend			& attackedDefend
		);
#pragma pack (pop)
} // namespace

#endif // PCS_CHArACTER_H_0237498234
