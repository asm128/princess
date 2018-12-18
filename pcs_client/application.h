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

	struct SEntityPropertyGroups {
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
		int32_t																	ViewportCharacter			= -1;
		int32_t																	DialogCharacter				= -1;
		//int32_t																	ButtonAttack				= -1;

		//SEntityPropertyGroups													DialogStatGroups			= {};
		//SEntityPropertyGroups													DialogStatGroupFrames		= {};
		SEntityPropertyGroups													DialogStatGroupLabels		= {};
		SEntityPropertyGroups													DialogStatGroupViewports	= {};

		::pcs::SPointsLife														LabelsLife					= {-1, -1,			}; 
		::pcs::SPointsPower														LabelsPower					= {-1, -1, -1,		}; 	
		::pcs::SPointsFitness													LabelsFitness				= {-1, -1, -1, -1,	}; 
		::pcs::SPointsAttack													LabelsAttack				= {-1, -1, -1, -1,	}; 
		::pcs::SPointsLife														LabelsDirectDamageLife		= {-1, -1,			}; 
		::pcs::SPointsPower														LabelsDirectDamagePower		= {-1, -1, -1,		}; 
		::pcs::SPointsLife														LabelsDrainLife				= {-1, -1,			}; 
		::pcs::SPointsPower														LabelsDrainPower			= {-1, -1, -1,		}; 	
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
