#include "gpk_framework.h"
#include "gpk_udp_client.h"
#include "pcs_game.h"
#include "gpk_dialog_controls.h"
#include "gpk_noise.h"

#ifndef APPLICATION_H_2078934982734
#define APPLICATION_H_2078934982734

namespace gme // I'm gonna use a different namespace in order to test a few things about the macros.
{
#pragma pack(push, 1)
	struct SCombatStatusControls {							
		GPKMNDF( , int32_t,	Blind		, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Stun		, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Shock		, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Bleeding	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Burn		, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Poison		, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Freezing	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Petrify		, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Frozen		, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Blackout	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Charmed		, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Drunk		, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Sleep		, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Slow		, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Weakness	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Panic		, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Berserk		, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Invisible	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Rage		, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Bullied		, ::gpk::DATA_TYPE_INT32)				= -1;
	};

	struct SCombatStatusGroups {					
		GPKMNDF( , int32_t,	Immunity	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Inflict		, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Resistance	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Weakness	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKM_REGISTRY
			(	GPKM_NAME(Immunity			)
			,	GPKM_NAME(Inflict			)
			,	GPKM_NAME(Resistance		)
			,	GPKM_NAME(Weakness			)
			);
	};

	static constexpr const uint32_t											STATUS_TYPE_COUNT				= 4;

	struct SCharacterUIControls {
		int32_t																	ViewportCharacter				= -1;
		int32_t																	DialogCharacter					= -1;
		::pcs::SEntityPropertyGroups											DialogPointsGroups				= {};
		::gme::SCombatStatusGroups												DialogStatusGroups				= {};
		::pcs::SDefend															ViewportDefend					= {};

		::gpk::ptr_nco<::gpk::SDialogCheckBox>									CheckBoxesDefend		[::pcs::SDefend::TRegistry::get_member_count()]				= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersDefend			[::pcs::SDefend::TRegistry::get_member_count()]				= {}; 
		
		::gpk::ptr_nco<::gpk::SDialogCheckBox>									CheckBoxesImmunity		[::pcs::SCombatStatusValue::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersInflict			[::pcs::SCombatStatusValue::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersResistance		[::pcs::SCombatStatusValue::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersWeakness			[::pcs::SCombatStatusValue::TRegistry::get_member_count()]	= {}; 

		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersLife				[::pcs::SPointsLife		::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersPower				[::pcs::SPointsPower	::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersFitness			[::pcs::SPointsFitness	::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersAttack			[::pcs::SPointsAttack	::TRegistry::get_member_count()]	= {};
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersDirectDamageLife	[::pcs::SPointsLife		::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersDirectDamagePower	[::pcs::SPointsPower	::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersDrainLife			[::pcs::SPointsLife		::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersDrainPower		[::pcs::SPointsPower	::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersRegenLife			[::pcs::SPointsLife		::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersRegenPower		[::pcs::SPointsPower	::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersMaxLife			[::pcs::SPointsLife		::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersMaxPower			[::pcs::SPointsPower	::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersBonusLife			[::pcs::SPointsLife		::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersBonusPower		[::pcs::SPointsPower	::TRegistry::get_member_count()]	= {}; 

		//int32_t																	ButtonAttack				= -1;
	};

#pragma pack(pop)
	::gpk::error_t															dialogCreateCharacter			(::gpk::SDialog & dialog, ::gme::SCharacterUIControls & character);
	
	struct SApplication {
		::gpk::SFramework														Framework;
		::gpk::ptr_obj<::gpk::SRenderTarget<::gpk::SColorBGRA, uint32_t>>		Offscreen										= {};
		::gpk::array_static<::gpk::SDialog, 2>									DialogCharacter;

		::gpk::SPRNG															RandomGenerator									= {};
		::pcs::SEntityPropertyPoints											CharacterPoints			[2]						= {};
		::pcs::SCharacterScore													CharacterScore			[2]						= {};
		::pcs::SCharacterStatus													CharacterStatus			[2]						= {};
		::pcs::SDefend															CharacterDefend			[2]						= {};

		int32_t																	Palettes[::gpk::GUI_CONTROL_PALETTE_COUNT]		= {};
		int32_t																	PaletteRow										= 10;
		int32_t																	PaletteColumn									= 16;

		int32_t																	IdExit											= -1;
		int32_t																	IdAttack[2]										= {-1, -1};

		::std::mutex															LockGUI;
		::std::mutex															LockRender;

		::gpk::SUDPClient														Client;
		::gpk::SUDPClient														ClientTest1;

		::pcs::SGame															Game;
		int32_t																	Player											= -1;

		::gpk::array_static<::gme::SCharacterUIControls, 2>						CharacterUI;

																				SApplication									(::gpk::SRuntimeValues& runtimeValues)	: Framework(runtimeValues)		{}
	};
} // namespace

#endif // APPLICATION_H_2078934982734
