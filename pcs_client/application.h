#include "gpk_framework.h"
#include "gpk_udp_client.h"
#include "pcs_game.h"
#include "gpk_dialog_controls.h"

#ifndef APPLICATION_H_2078934982734
#define APPLICATION_H_2078934982734

namespace gme // I'm gonna use a different namespace in order to test a few things about the macros.
{
#pragma pack(push, 1)
	struct SGameUIPalettes {
		::gpk::array_static<int32_t, ::gpk::GUI_CONTROL_PALETTE_COUNT>			Groups				= {};
		::gpk::array_static<int32_t, ::gpk::GUI_CONTROL_PALETTE_COUNT>			Fields				= {};
		::gpk::array_static<int32_t, ::gpk::GUI_CONTROL_PALETTE_COUNT>			Titles				= {};
	};

	struct SCombatStatusControls {							
		GPKMNDF( , int32_t,	Blind				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Stun				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Shock				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Bleeding			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Burn				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Poison				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Freezing			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Petrify				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Frozen				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Blackout			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Charmed				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Drunk				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Sleep				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Slow				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Weakness			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Panic				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Berserk				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Invisible			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Rage				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Bullied				, ::gpk::DATA_TYPE_INT32)				= -1;
	};			   
struct SCombatStatusGroups {							
		GPKMNDF( , int32_t,	Immunity			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Inflict				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Resistance			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t,	Weakness			, ::gpk::DATA_TYPE_INT32)				= -1;

	};			   



	struct SCharacterUIControls {
		int32_t																	ViewportCharacter			= -1;
		int32_t																	DialogCharacter				= -1;
		::pcs::SEntityPropertyGroups											DialogStatGroupViewports	= {};
		::pcs::SEntityPropertyPoints											DialogStatLabels			= {};
		::pcs::SCombatStatusValue												DalogStatusImmunities   ={};
		::pcs::SCombatStatusValue												DalogStatusInflict      ={};
		::pcs::SCombatStatusValue												DalogStatusWeaknesses   ={};
		::pcs::SCombatStatusValue												DalogStatusResistance   ={};


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

		int32_t																	Palettes[::gpk::GUI_CONTROL_PALETTE_COUNT]		= {};
		int32_t																	PaletteRow										= 10;
		int32_t																	PaletteColumn									= 16;

		SGameUIPalettes															GameUIPalettes									= {};

		int32_t																	IdExit											= -1;

		::std::mutex															LockGUI;
		::std::mutex															LockRender;

		::gpk::SUDPClient														Client;
		::gpk::SUDPClient														ClientTest1;

		::pcs::SGame															Game;
		int32_t																	Player											= -1;

		::gpk::array_static<::gme::SCharacterUIControls, 2>						CharacterUIFieldNames;


																				SApplication									(::gpk::SRuntimeValues& runtimeValues)	: Framework(runtimeValues)		{}
	};
} // namespace

#endif // APPLICATION_H_2078934982734
