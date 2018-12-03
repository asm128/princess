#include "gpk_framework.h"
#include "gpk_udp_client.h"
#include "pcs_game.h"

#ifndef APPLICATION_H_2078934982734
#define APPLICATION_H_2078934982734

namespace gme // I'm gonna use a different namespace in order to test a few things about the macros.
{
	struct SDialogHealth	{ int32_t Dialog; ::pcs::SPointsHealth	Fields = {-1, -1, };					};
	struct SDialogPower		{ int32_t Dialog; ::pcs::SPointsPower	Fields = {-1, -1, -1, };				};
	struct SDialogFitness	{ int32_t Dialog; ::pcs::SPointsFitness	Fields = {-1, -1, -1, -1, };			};
	struct SDialogAttack	{ int32_t Dialog; ::pcs::SPointsAttack	Fields = {-1, -1, -1, -1, -1, -1, };	};


	struct SCharacterUIControls {
		int32_t							DialogCharacter				= -1;
		SDialogHealth					Health						= {};
		SDialogPower					Power						= {};	
		SDialogFitness					Fitness						= {};
		SDialogAttack					Attack						= {};
		//int32_t							ButtonAttack				= -1;
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
