#include "gpk_framework.h"
#include "gpk_udp_client.h"
#include "pcs_game.h"
#include "gpk_dialog_controls.h"

#ifndef APPLICATION_H_2078934982734
#define APPLICATION_H_2078934982734

namespace gme // I'm gonna use a different namespace in order to test a few things about the macros.
{
#pragma pack(push, 1)
	struct SCharacterPropertyGroups {
		GPKMNDF( , int32_t, Life				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t, Power				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t, Fitness				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t, Attack				, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t, DirectDamageLife	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t, DirectDamagePower	, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t, DrainLife			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKMNDF( , int32_t, DrainPower			, ::gpk::DATA_TYPE_INT32)				= -1;
		GPKM_REGISTRY
			(	GPKM_NAME(Life				)
			,	GPKM_NAME(Power				)
			,	GPKM_NAME(Fitness			)
			,	GPKM_NAME(Attack			)
			,	GPKM_NAME(DirectDamageLife	)
			,	GPKM_NAME(DirectDamagePower	)
			,	GPKM_NAME(DrainLife			)
			,	GPKM_NAME(DrainPower		)
			);
	};

	struct SCharacterUIControls {
		int32_t																	DialogCharacter				= -1;
		//int32_t																	ButtonAttack				= -1;

		SCharacterPropertyGroups												DialogStatGroups			= {};

		::pcs::SPointsLife														Life						= {-1, -1,			}; 
		::pcs::SPointsPower														Power						= {-1, -1, -1,		}; 	
		::pcs::SPointsFitness													Fitness						= {-1, -1, -1, -1,	}; 
		::pcs::SPointsAttack													Attack						= {-1, -1, -1, -1,	}; 
		::pcs::SPointsLife														DirectDamageLife			= {-1, -1,			}; 
		::pcs::SPointsLife														DirectDamagePower			= {-1, -1,			}; 
		::pcs::SPointsLife														DrainLife					= {-1, -1,			}; 
		::pcs::SPointsPower														DrainPower					= {-1, -1, -1,		}; 	
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersLife				[::pcs::SPointsLife		::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersPower				[::pcs::SPointsPower	::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersFitness			[::pcs::SPointsFitness	::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersAttack			[::pcs::SPointsAttack	::TRegistry::get_member_count()]	= {};
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersDirectDamageLife	[::pcs::SPointsLife		::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersDirectDamagePower	[::pcs::SPointsPower	::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersDrainLife			[::pcs::SPointsLife		::TRegistry::get_member_count()]	= {}; 
		::gpk::ptr_nco<::gpk::SDialogTuner>										TunersDrainPower		[::pcs::SPointsPower	::TRegistry::get_member_count()]	= {}; 

	};

#pragma pack(pop)
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
		::gpk::array_static<::gme::SCharacterUIControls, 2>						CharacterUIFieldNames;
		::gpk::array_static<::gme::SCharacterUIControls, 2>						CharacterUIFieldValue;

		::gpk::array_static<::gpk::SDialog, 2>									DialogCharacter;

																				SApplication									(::gpk::SRuntimeValues& runtimeValues)	: Framework(runtimeValues)		{}
	};
} // namespace

#endif // APPLICATION_H_2078934982734
