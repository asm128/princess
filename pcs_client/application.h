#include "gpk_framework.h"
#include "gpk_udp_client.h"
#include "pcs_game.h"

#ifndef APPLICATION_H_2078934982734
#define APPLICATION_H_2078934982734

namespace gme // I'm gonna use a different namespace in order to test a few things about the macros.
{
	struct SPointsUIHealth	{
		int32_t							IdHealth					;
		int32_t							IdShield					;
	};

	struct SPointsUIPower	{
		int32_t							IdMana						;
		int32_t							IdEnergy					;
		int32_t							IdStamina					;
	};

	struct SPointsUIFitness {
		int32_t							IdRange						;
		int32_t							IdHit						;
		int32_t							IdAbsorption				;
		int32_t							IdDamage					;
		SPointsUIHealth					IdDirectDamage				;
	};

	struct SPointsUIAttack	{
		int32_t							IdAttack					;
		int32_t							IdMovement					;
		int32_t							IdReflexes					;
		int32_t							IdSight						;
	};


	::gpk::error_t					guiCreateHealth				(::gpk::SGUI gui, ::gme::SPointsUIHealth	& );
	::gpk::error_t					guiCreatePower				(::gpk::SGUI gui, ::gme::SPointsUIPower		& );
	::gpk::error_t					guiCreateFitness			(::gpk::SGUI gui, ::gme::SPointsUIFitness	& );
	::gpk::error_t					guiCreateAttack				(::gpk::SGUI gui, ::gme::SPointsUIAttack	& );

	struct SCharacterUIControls {
		int32_t							IdButtonAttack;
	};
	
	struct SApplication {
		::gpk::SFramework														Framework;
		::gpk::ptr_obj<::gpk::SRenderTarget<::gpk::SColorBGRA, uint32_t>>		Offscreen							= {};

		int32_t																	IdExit								= -1;

		::std::mutex															LockGUI;
		::std::mutex															LockRender;

		::gpk::SUDPClient														Client;
		::gpk::SUDPClient														ClientTest1;

		::pcs::SGame															Game;
		::gpk::SGUI																BoardUI;

																				SApplication						(::gpk::SRuntimeValues& runtimeValues)	: Framework(runtimeValues)		{}
	};
} // namespace

#endif // APPLICATION_H_2078934982734
