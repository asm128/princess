#include "gpk_framework.h"
#include "gpk_udp_server.h"
#include "pcs_game.h"

#ifndef APPLICATION_H_2078934982734
#define APPLICATION_H_2078934982734

namespace gme // I'm gonna use a different namespace in order to test a few things about the macros.
{
	struct SApplication {
		::gpk::SFramework														Framework;
		::gpk::ptr_obj<::gpk::SRenderTarget<::gpk::SColorBGRA, uint32_t>>		Offscreen							= {};

		int32_t																	IdExit								= -1;

		::std::mutex															LockGUI;
		::std::mutex															LockRender;

		::gpk::SUDPServer														Server								= {};

		::pcs::SGame															Game;
		::gpk::SGUI																BoardUI;

																				SApplication		(::gpk::SRuntimeValues& runtimeValues)	: Framework(runtimeValues)		{}
	};
} // namespace

#endif // APPLICATION_H_2078934982734
