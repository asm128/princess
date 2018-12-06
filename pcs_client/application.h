#include "gpk_framework.h"
#include "gpk_udp_client.h"
#include "pcs_game.h"
#include "gpk_dialog.h"

#ifndef APPLICATION_H_2078934982734
#define APPLICATION_H_2078934982734

namespace gme // I'm gonna use a different namespace in order to test a few things about the macros.
{
#pragma pack(push, 1)
	struct STunersHealth	{ ::pcs::SPointsLife		Fields = {-1, -1,			}; ::gpk::ptr_nco<::gpk::SDialogTuner> Tuners[::pcs::SPointsLife	::TRegistry::get_member_count()]; };
	struct STunersPower		{ ::pcs::SPointsPower		Fields = {-1, -1, -1,		}; ::gpk::ptr_nco<::gpk::SDialogTuner> Tuners[::pcs::SPointsPower	::TRegistry::get_member_count()]; };
	struct STunersFitness	{ ::pcs::SPointsFitness		Fields = {-1, -1, -1, -1,	}; ::gpk::ptr_nco<::gpk::SDialogTuner> Tuners[::pcs::SPointsFitness	::TRegistry::get_member_count()]; };

	struct SCharacterDialogs {
		GPKMNDF(::pcs, SCharacterDialogs, , int32_t, Life		, ::gpk::DATA_TYPE_INT32) = -1;
		GPKMNDF(::pcs, SCharacterDialogs, , int32_t, Power		, ::gpk::DATA_TYPE_INT32) = -1;
		GPKMNDF(::pcs, SCharacterDialogs, , int32_t, Fitness	, ::gpk::DATA_TYPE_INT32) = -1;
		GPKMNDF(::pcs, SCharacterDialogs, , int32_t, Attack		, ::gpk::DATA_TYPE_INT32) = -1;
		GPKM_REGISTRY
			(	GPKM_NAME(Life		)
			,	GPKM_NAME(Power		)
			,	GPKM_NAME(Fitness	)
			,	GPKM_NAME(Attack	)
			);
	};

	struct SCharacterUIControls {
		int32_t																	DialogCharacter				= -1;
		SCharacterDialogs														DialogPoints				= {};

		::pcs::SPointsLife														Life						= {};
		::pcs::SPointsPower														Power						= {};	
		::pcs::SPointsFitness													Fitness						= {};
		::pcs::SPointsAttackFull													Attack						= {};
		//int32_t																	ButtonAttack				= -1;
	};

#pragma pack(pop)
	::gpk::error_t															guiCreateCharacter			(::gpk::SGUI & gui, ::gme::SCharacterUIControls	& character	);
	
	struct SApplication {
		::gpk::SFramework														Framework;
		::gpk::ptr_obj<::gpk::SRenderTarget<::gpk::SColorBGRA, uint32_t>>		Offscreen										= {};

		int32_t																	Palettes[::gpk::GUI_CONTROL_PALETTE_COUNT]		= {};
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
