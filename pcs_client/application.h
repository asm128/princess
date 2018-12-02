#include "gpk_framework.h"
#include "gpk_udp_client.h"
#include "pcs_game.h"

#ifndef APPLICATION_H_2078934982734
#define APPLICATION_H_2078934982734

namespace gme // I'm gonna use a different namespace in order to test a few things about the macros.
{

	struct SCharacterUIControls {
		int32_t							DialogCharacter				= -1;
		int32_t							DialogHealth				= -1;
		int32_t							DialogPower					= -1;
		int32_t							DialogFitness				= -1;
		int32_t							DialogAttack				= -1;
		int32_t							ButtonAttack				= -1;
		::pcs::SPointsHealth			Health						= {-1, -1, };
		::pcs::SPointsPower				Power						= {-1, -1, -1, }; 
		::pcs::SPointsFitness			Fitness						= {-1, -1, -1, -1, };
		::pcs::SPointsAttack			Attack						= {-1, -1, -1, -1, -1, -1, };
	};
	::gpk::error_t					guiCreateCharacter			(::gpk::SGUI & gui, ::gme::SCharacterUIControls	& character	);
	
	struct SApplication {
		::gpk::SFramework														Framework;
		::gpk::ptr_obj<::gpk::SRenderTarget<::gpk::SColorBGRA, uint32_t>>		Offscreen										= {};

		int32_t																	Palettes[::gpk::GUI_CONTROL_STATE_COLORS_COUNT]	= {};
		int32_t																	PaletteRow										= 10;
		int32_t																	PaletteColumn									= 16;
		int32_t																	IdExit											= -1;

		::std::mutex															LockGUI;
		::std::mutex															LockRender;

		::gpk::SUDPClient														Client;
		::gpk::SUDPClient														ClientTest1;

		::pcs::SGame															Game;
		::gpk::SGUI																BoardUI;
		::gme::SCharacterUIControls												CharacterUIFieldNames[2];
		::gme::SCharacterUIControls												CharacterUIFieldValue[2];

																				SApplication									(::gpk::SRuntimeValues& runtimeValues)	: Framework(runtimeValues)		{}
	};
} // namespace

#endif // APPLICATION_H_2078934982734
