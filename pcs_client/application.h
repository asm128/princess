#include "gpk_framework.h"
#include "gpk_udp_client.h"
#include "pcs_game.h"
#include "gpk_dialog.h"

#ifndef APPLICATION_H_2078934982734
#define APPLICATION_H_2078934982734

namespace gme // I'm gonna use a different namespace in order to test a few things about the macros.
{
	struct STunersLife		{ ::pcs::SPointsLife		Fields = {-1, -1,										}; ::gpk::ptr_nco<::gpk::SDialogTuner> TunerHealth	; ::gpk::ptr_nco<::gpk::SDialogTuner> TunerShield	; };
	struct STunersPower		{ ::pcs::SPointsPower		Fields = {-1, -1, -1,									}; ::gpk::ptr_nco<::gpk::SDialogTuner> TunerEnergy	; ::gpk::ptr_nco<::gpk::SDialogTuner> TunerMana		; ::gpk::ptr_nco<::gpk::SDialogTuner> TunerStamina		; };
	struct STunersFitness	{ ::pcs::SPointsFitness		Fields = {-1, -1, -1, -1,								}; ::gpk::ptr_nco<::gpk::SDialogTuner> TunerAttack	; ::gpk::ptr_nco<::gpk::SDialogTuner> TunerMovement	; ::gpk::ptr_nco<::gpk::SDialogTuner> TunerReflexes		; ::gpk::ptr_nco<::gpk::SDialogTuner> TunerSight	; };
	struct STunersAttack	{ ::pcs::SPointsAttackFull	Fields = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,	}; ::gpk::ptr_nco<::gpk::SDialogTuner> TunerRange	; ::gpk::ptr_nco<::gpk::SDialogTuner> TunerHit		; ::gpk::ptr_nco<::gpk::SDialogTuner> TunerAbsorption	; ::gpk::ptr_nco<::gpk::SDialogTuner> TunerDamage	; };

	struct SDialogLife		{ int32_t Dialog; ::pcs::SPointsLife		Fields = {-1, -1,										}; };
	struct SDialogPower		{ int32_t Dialog; ::pcs::SPointsPower		Fields = {-1, -1, -1,									}; };
	struct SDialogFitness	{ int32_t Dialog; ::pcs::SPointsFitness		Fields = {-1, -1, -1, -1,								}; };
	struct SDialogAttack	{ int32_t Dialog; ::pcs::SPointsAttackFull	Fields = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,	}; };

#pragma pack(push, 1)
	struct SCharacterPropertyGroups {
		GPKMNDF(::pcs, SCharacterPropertyGroups, , int32_t, Life	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF(::pcs, SCharacterPropertyGroups, , int32_t, Power	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF(::pcs, SCharacterPropertyGroups, , int32_t, Fitness	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF(::pcs, SCharacterPropertyGroups, , int32_t, Attack	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKM_REGISTRY
			(	GPKM_NAME(Life		)
			,	GPKM_NAME(Power		)
			,	GPKM_NAME(Fitness	)
			,	GPKM_NAME(Attack	)
			);
	};
#pragma pack(pop)

	struct SCharacterUIControls {
		int32_t																	DialogCharacter				= -1;

		SCharacterPropertyGroups												DialogStatGroups			= {};

		::pcs::SPointsLife														Life						= {-1, -1,										}; 
		::pcs::SPointsPower														Power						= {-1, -1, -1,									}; 	
		::pcs::SPointsFitness													Fitness						= {-1, -1, -1, -1,								}; 
		::pcs::SPointsAttackFull												Attack						= {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,	}; 
		//int32_t																	ButtonAttack				= -1;
	};
	::gpk::error_t															guiCreateCharacter			(::gpk::SGUI & gui, ::gme::SCharacterUIControls	& character	);
	
	struct SApplication {
		::gpk::SFramework														Framework;
		::gpk::ptr_obj<::gpk::SRenderTarget<::gpk::SColorBGRA, uint32_t>>		Offscreen										= {};

		int32_t																	Palettes[::gpk::GUI_CONTROL_PALETTE_COUNT]	= {};
		int32_t																	PaletteRow										= 10;
		int32_t																	PaletteColumn									= 16;
		int32_t																	IdExit											= -1;

		::std::mutex															LockGUI;
		::std::mutex															LockRender;

		::gpk::SUDPClient														Client;
		::gpk::SUDPClient														ClientTest1;

		::pcs::SGame															Game;
		::gme::SCharacterUIControls												CharacterUIFieldNames[2];
		::gme::SCharacterUIControls												CharacterUIFieldValue[2];

		::gpk::SDialog															DialogCharacter[2];

																				SApplication									(::gpk::SRuntimeValues& runtimeValues)	: Framework(runtimeValues)		{}
	};
} // namespace

#endif // APPLICATION_H_2078934982734
