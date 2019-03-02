#include "pcs_game.h"

		uint64_t														pcs::damageCalculatePlayer			
	( ::gpk::array_pod<::pcs::SCharacterProfile> characterProfilesAlive
	, ::gpk::array_pod<::pcs::SCharacterProfile> characterProfilesDead
	)
{
	uint64_t																	totalDamage								= 0;
	for(uint32_t iCharacter = 0, countCharacters = characterProfilesAlive	.size(); iCharacter < countCharacters; ++iCharacter) totalDamage += characterProfilesAlive	[iCharacter].Score.DamageDealt;
	for(uint32_t iCharacter = 0, countCharacters = characterProfilesDead	.size(); iCharacter < countCharacters; ++iCharacter) totalDamage += characterProfilesDead	[iCharacter].Score.DamageDealt;
	return totalDamage;
}

static	::gpk::error_t													gameEntityCreate					(::gpk::array_pod<::pcs::SEntity> & entityStorage, ::gpk::array_pod<::pcs::SEntityState> & entityStates)		{ 
	for(uint32_t iEntity = 0, countEntities = entityStates.size(); iEntity < countEntities; ++iEntity) { 
		if (entityStates[iEntity].Unused) { 
			entityStates[iEntity].Unused											= false; 
			return iEntity; 
		} 
	} 
	int32_t																		iEntity								= entityStorage.push_back({}); 
	memset(&entityStorage[iEntity], -1, sizeof(::pcs::SEntity)); 
	entityStates.push_back({false}); 
	return iEntity; 
}

		::gpk::error_t													pcs::gameCreateCharacter			(::pcs::SGame & game)																							{ return gameEntityCreate(game.EntityCharacter	, game.StateCharacter	); }
		::gpk::error_t													pcs::gameCreateWeapon				(::pcs::SGame & game)																							{ return gameEntityCreate(game.EntityWeapon		, game.StateWeapon		); }
		::gpk::error_t													pcs::gameCreateArmor				(::pcs::SGame & game)																							{ return gameEntityCreate(game.EntityArmor		, game.StateArmor		); }
		::gpk::error_t													pcs::gameCreateAccessory			(::pcs::SGame & game)																							{ return gameEntityCreate(game.EntityAccessory	, game.StateAccessory	); }
		::gpk::error_t													pcs::gameCreatePlayer				(::pcs::SGame & game)																							{ return gameEntityCreate(game.EntityPlayer		, game.StatePlayer		); }


// Returns 2 if deflected, 1 if hit and 
		::gpk::error_t													pcs::attackCalculateHitChanceResult	
	( ::gpk::SPRNG					& prng
	, const ::pcs::SPointsAttack	& attackerPoints
	, const ::pcs::SPointsFitness	& attackerFitness
	, const ::pcs::SPointsFitness	& attackedFitness
	, const ::pcs::SCharacterStatus	& attackerStatus
	, const ::pcs::SCharacterStatus	& attackedStatus
	, const ::pcs::SDefend			& attackedDefend
	) {
	int32_t																		value							= prng.Next() % POINT_SCALE_INT;	// Increase value in order to decrease hit chance 
	value																	-=  attackerFitness.Movement;	// Some attacker stats incrase hit chance. (decrease value)
	value																	-=  attackerFitness.Reflexes;
	value																	-=  attackerFitness.Sight	/ 2;
	value																	-=  attackerFitness.Moral	;

	value																	+=  attackedFitness.Movement;	// Some target stats decrease hit chance. (increase value)
	value																	+=  attackedFitness.Reflexes;
	value																	+=  attackedFitness.Sight	/ 2;
	value																	+=  attackedFitness.Moral	;

	value																	+=  attackerStatus.Passive.Blind		;	// decreases hit chance (increase value)
	value																	+=  attackerStatus.Passive.Stun			;	// decreases hit chance (increase value)
	value																	+=  attackerStatus.Passive.Shock		;	// decreases hit chance (increase value)
	value																	+=  attackerStatus.Passive.Bleeding		;	// decreases hit chance (increase value)
	value																	+=  attackerStatus.Passive.Burn			;	// decreases hit chance (increase value)
	value																	+=  attackerStatus.Passive.Poison		;	// decreases hit chance (increase value)
	value																	+=  attackerStatus.Passive.Freezing		;	// decreases hit chance (increase value)
	value																	+=  attackerStatus.Passive.Petrify		;	// decreases hit chance (increase value)

	value																	+=  attackerStatus.Passive.Frozen		;	// decreases hit chance (increase value)
	value																	+=  attackerStatus.Passive.Blackout		;	// decreases hit chance (increase value)
	value																	+=  attackerStatus.Passive.Charmed		;	// decreases hit chance (increase value)
	value																	+=  attackerStatus.Passive.Drunk		;	// decreases hit chance (increase value)
	value																	+=  attackerStatus.Passive.Sleep		;	// decreases hit chance (increase value)
	value																	+=  attackerStatus.Passive.Slow			;	// decreases hit chance (increase value)
	value																	+=  attackerStatus.Passive.Weakness		;	// decreases hit chance (increase value)
	value																	+=  attackerStatus.Passive.Panic		;	// decreases hit chance (increase value)

	value																	+=  attackerStatus.Passive.Berserk		;	// decreases hit chance (increase value)
	value																	-=  attackerStatus.Passive.Invisible	;	// increases hit chance (decrease value)
	value																	+=  attackerStatus.Passive.Rage			;	// decreases hit chance (increase value)
	value																	+=  attackerStatus.Passive.Bullied		;	// decreases hit chance (increase value)
	// --------------------
	value																	-=  attackedStatus.Passive.Blind		;	// increases hit chance (decreases value)
	value																	-=  attackedStatus.Passive.Stun			;	// increases hit chance (decreases value)
	value																	-=  attackedStatus.Passive.Shock		;	// increases hit chance (decreases value)
	value																	-=  attackedStatus.Passive.Bleeding		;	// increases hit chance (decreases value)
	value																	-=  attackedStatus.Passive.Burn			;	// increases hit chance (decreases value)
	value																	-=  attackedStatus.Passive.Poison		;	// increases hit chance (decreases value)
	value																	-=  attackedStatus.Passive.Freezing		;	// increases hit chance (decreases value)
	value																	-=  attackedStatus.Passive.Petrify		;	// increases hit chance (decreases value)
	//
	value																	-=  attackedStatus.Passive.Frozen		;	// increases hit chance (decreases value)
	value																	-=  attackedStatus.Passive.Blackout		;	// increases hit chance (decreases value)
	value																	-=  attackedStatus.Passive.Charmed		;	// increases hit chance (decreases value)
	value																	-=  attackedStatus.Passive.Drunk		;	// increases hit chance (decreases value)
	value																	-=  attackedStatus.Passive.Sleep		;	// increases hit chance (decreases value)
	value																	-=  attackedStatus.Passive.Slow			;	// increases hit chance (decreases value)
	value																	-=  attackedStatus.Passive.Weakness		;	// increases hit chance (decreases value)
	value																	-=  attackedStatus.Passive.Panic		;	// increases hit chance (decreases value)
	//
	value																	-=  attackedStatus.Passive.Berserk		;	// increases hit chance (decreases value)
	value																	+=  attackedStatus.Passive.Invisible	;	// decreases hit chance (increases value)
	value																	-=  attackedStatus.Passive.Rage			;	// increases hit chance (decreases value)
	value																	-=  attackedStatus.Passive.Bullied		;	// increases hit chance (decreases value)

	value																	+= attackedDefend.Deflect;	// Deflect decreases hit chance (increase value)

	if(value < attackerPoints.Hit) 
		return 1;
	if((value - attackerPoints.Hit) < attackedDefend.Deflect)
		return -1;
	return 0;
}

			::gpk::error_t												pcs::attackCalculateDamage			
	( ::pcs::SPointsLife				& lifeRemaining
	, ::pcs::SPointsLife				& damageDealt
	, ::pcs::SPointsLife				& damageReflected
	, ::pcs::SPointsPower				& powerRemaining
	, ::pcs::SPointsPower				& powerDamageDealt
	, ::pcs::SEntityPropertyPoints		& attacker
	, const ::pcs::SDefend				& attackedDefend
	, int32_t							absorption
	) {
	if(1 == attacker.Attack.Damage) {
		if(lifeRemaining.Shield) {
			++damageDealt.Shield;
			--lifeRemaining.Shield;
		}
		else {
			++damageDealt.Health;
			--lifeRemaining.Health;
		}
	}
	else  {
		double																		absorptionFactor						= absorption * (1.0 / ::pcs::POINT_SCALE_DOUBLE);
		damageDealt.Health														= (int32_t)(attacker.Attack.Damage * (1.0 - absorptionFactor));
		damageDealt.Shield														= (int32_t)(attacker.Attack.Damage * absorptionFactor + (attacker.Attack.Damage % 2));
		if(attackedDefend.Reflect > 0) {	// If the target reflect	s damage, it only takes a portion of the damage and assign the reflected damage values to the proper structure
			double																		factor									= attackedDefend.Reflect * (1.0 / ::pcs::POINT_SCALE_DOUBLE);
			double																		factorInv								= 1.0 - factor;
			damageReflected.Health													+= (int32_t)(damageDealt.Health * factor);
			damageReflected.Shield													+= (int32_t)(damageDealt.Shield * factor);
			damageDealt.Health														= (int32_t)(damageDealt.Health * factorInv);
			damageDealt.Shield														= (int32_t)(damageDealt.Shield * factorInv);
		}
		if(attackedDefend.Impenetrable) {
			lifeRemaining.Shield													-= (damageDealt.Shield + damageDealt.Health);
			damageDealt.Shield														+= damageDealt.Health;
			damageDealt.Health														= 0;
		}
		else {
			lifeRemaining.Health													-= damageDealt.Health;
			lifeRemaining.Shield													-= damageDealt.Shield;
		}
	}
	// Apply direct damage
	lifeRemaining.Health													-= attacker.DirectDamageLife.Health;
	lifeRemaining.Shield													-= attacker.DirectDamageLife.Shield;
	damageDealt.Health														+= attacker.DirectDamageLife.Health;
	damageDealt.Shield														+= attacker.DirectDamageLife.Shield;

	// Apply direct damage for power
	powerRemaining	.Energy													-= attacker.DirectDamagePower.Energy	;
	powerRemaining	.Mana													-= attacker.DirectDamagePower.Mana		;
	powerRemaining	.Stamina												-= attacker.DirectDamagePower.Stamina	;
	powerDamageDealt.Energy													+= attacker.DirectDamagePower.Energy	;
	powerDamageDealt.Mana													+= attacker.DirectDamagePower.Mana		;
	powerDamageDealt.Stamina												+= attacker.DirectDamagePower.Stamina	;

	if(lifeRemaining.Shield < 0) { // Fix negative shield situat	ion
		lifeRemaining.Health													+= lifeRemaining.Shield;
		lifeRemaining.Shield													-= lifeRemaining.Shield;
		damageDealt.Health														-= lifeRemaining.Shield;
		damageDealt.Shield														+= lifeRemaining.Shield;
	}
	return 0;
}
			::gpk::error_t												pcs::attackApplyDrain
	( ::pcs::SPointsLife			& damageDealt
	, ::pcs::SPointsLife			& lifeDrained
	, ::pcs::SPointsLife			& drainPoints
	, ::pcs::SPointsPower			& powerDamageDealt
	, ::pcs::SPointsPower			& powerDrained
	, ::pcs::SPointsPower			& powerDrainPoints
	) {
	lifeDrained.Health														= (int32_t)(damageDealt.Health * (drainPoints.Health / POINT_SCALE_DOUBLE));
	lifeDrained.Shield														= (int32_t)(damageDealt.Shield * (drainPoints.Shield / POINT_SCALE_DOUBLE));
	powerDrained.Energy														+= (int32_t)(powerDamageDealt.Energy	* (powerDrainPoints.Energy	/ POINT_SCALE_DOUBLE));
	powerDrained.Mana														+= (int32_t)(powerDamageDealt.Mana		* (powerDrainPoints.Mana	/ POINT_SCALE_DOUBLE));
	powerDrained.Stamina													+= (int32_t)(powerDamageDealt.Stamina	* (powerDrainPoints.Stamina / POINT_SCALE_DOUBLE));
	return 0;
}
			::gpk::error_t												pcs::attackMelee						
	( ::gpk::SPRNG					& prng
	, ::pcs::SCharacterScore		& scoreAttacker
	, ::pcs::SCharacterScore		& scoreAttacked
	, ::pcs::SEntityPropertyPoints	& attacker
	, ::pcs::SEntityPropertyPoints	& attacked
	, ::pcs::SCharacterStatus		& attackerStatus
	, ::pcs::SCharacterStatus		& attackedStatus
	//, ::pcs::SDefend				& attackerDefend
	, const ::pcs::SDefend			& attackedDefend
	) {
	if(0 == ::pcs::attackCalculateHitChanceResult(prng, attacker.Attack, attacker.Fitness, attacked.Fitness, attackerStatus, attackedStatus, attackedDefend)) {
		++scoreAttacker.AttacksMissed;
		return 0;
	}
	++scoreAttacker.AttacksHit;
	++scoreAttacked.AttacksReceived;
	::pcs::SPointsLife															damageDealt									= {};
	::pcs::SPointsLife															damageReflected								= {};
	::pcs::SPointsLife															lifeRemaining								= attacked.Life;

	::pcs::SPointsPower															powerDamageDealt							= {};
	::pcs::SPointsPower															powerRemaining								= attacked.Power;
	::pcs::attackCalculateDamage(lifeRemaining, damageDealt, damageReflected, powerRemaining, powerDamageDealt, attacker, attackedDefend, attacked.Attack.Absorption);

	::pcs::SPointsLife															lifeDrained									= {};
	::pcs::SPointsPower															powerDrained								= {};
	::pcs::attackApplyDrain(damageDealt, lifeDrained, attacker.DrainLife, powerDamageDealt, powerDrained, attacker.DrainPower);

	attacker.Life.Health													+= lifeDrained.Health;
	attacker.Life.Shield													+= lifeDrained.Shield;
	attacker.Power.Energy													+= powerDrained.Energy	;
	attacker.Power.Mana														+= powerDrained.Mana	;
	attacker.Power.Stamina													+= powerDrained.Stamina	;
	attacked.Life															= lifeRemaining;
	attacked.Power															= powerRemaining;
	for(uint32_t iMember = 0; iMember < ::pcs::SPointsLife ::TRegistry::get_member_count(); ++iMember)	((int32_t*)&attacked.Life )[iMember] = ::gpk::max(0, ((int32_t*)&attacked.Life )[iMember]);
	for(uint32_t iMember = 0; iMember < ::pcs::SPointsPower::TRegistry::get_member_count(); ++iMember)	((int32_t*)&attacked.Power)[iMember] = ::gpk::max(0, ((int32_t*)&attacked.Power)[iMember]);
	return 0;
}
