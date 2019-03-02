#include "application.h"
#include "gpk_bitmap_file.h"

//#define GPK_AVOID_LOCAL_APPLICATION_MODULE_MODEL_EXECUTABLE_RUNTIME
#include "gpk_app_impl.h"
#include "gpk_tcpip.h"
#include "gpk_chrono.h"

GPK_DEFINE_APPLICATION_ENTRY_POINT(::gme::SApplication, "Module Explorer");

template <typename _tStruct>
static		::gpk::error_t											syncCharacterPoints			(_tStruct & data, ::gpk::ptr_nco<::gpk::SDialogTuner>* tuners)						{ 
	for(uint32_t iMember = 0; iMember < _tStruct::TRegistry::get_member_count(); ++iMember) 
		((int32_t*)&data)[iMember]											= (int32_t)tuners[iMember]->ValueCurrent; 
	return 0;
}

template <typename _tStruct>
static		::gpk::error_t											syncTunersPoints			(_tStruct & data, ::gpk::ptr_nco<::gpk::SDialogTuner>* tuners)						{ 
	for(uint32_t iMember = 0; iMember < _tStruct::TRegistry::get_member_count(); ++iMember) 
		::gpk::tunerSetValue(*tuners[iMember], ((int32_t*)&data)[iMember]); 
	return 0;
}

			::gpk::error_t											cleanup						(::gme::SApplication & app)							{ 
	::gpk::mainWindowDestroy(app.Framework.MainDisplay);
	::gpk::clientDisconnect(app.Client);
	::gpk::tcpipShutdown();
	return 0; 
}

static		::gpk::error_t											setupGameUI					(::gme::SApplication & app)						{ 
	for(uint32_t iCharacter = 0; iCharacter < app.CharacterUI.size(); ++iCharacter) {
		::gpk::SDialog															& dialogCharacter			= app.DialogCharacter[iCharacter];
		dialogCharacter.GUI													= app.Framework.GUI;
		dialogCharacter.Input												= app.Framework.Input;
		::gme::SCharacterUIControls												& controls					= app.CharacterUI[iCharacter];
		::gpk::SGUIControlTable													& controlTable				= dialogCharacter.GUI->Controls;
		gpk_necall(::gme::dialogCreateCharacter(dialogCharacter, controls), "%s", "????");
		controlTable.Controls[dialogCharacter.Controls[controls.ViewportCharacter]->IdGUIControl].Align				= iCharacter ? ::gpk::ALIGN_RIGHT : ::gpk::ALIGN_LEFT;
		gpk_necall(::gpk::controlSetParent(*dialogCharacter.GUI, dialogCharacter.Controls[controls.ViewportCharacter]->IdGUIControl, 0), "%s", "????");
	}
	return 0;
}


			::gpk::error_t											setup						(::gme::SApplication & app)						{ 
	::gpk::SFramework														& framework					= app.Framework;
	::gpk::SDisplay															& mainWindow				= framework.MainDisplay;
	framework.GUI														= app.DialogCharacter[0].GUI;
	//::gpk::controlDelete(*framework.GUI, 0);
	error_if(errored(::gpk::mainWindowCreate(mainWindow, framework.RuntimeValues.PlatformDetail, framework.Input)), "%s", "Failed to create main window why?????!?!?!?!?");
	::gpk::SGUI																& gui						= *framework.GUI;
	const int32_t															iShades					= 16;
	gui.ThemeDefault													= app.PaletteColumn * iShades + app.PaletteRow;
	gui.ColorModeDefault												= ::gpk::GUI_COLOR_MODE_3D;
	int32_t																	controlTestRoot			= 0; //::gpk::controlCreate(gui);	// control 0

	::gpk::SControl															& controlRoot			= gui.Controls.Controls[controlTestRoot];
	controlRoot.Area													= {{0, 0}, {320, 240}};
	controlRoot.Border													= {};// {1, 1, 1, 1};
	controlRoot.Margin													= {};// {0, 0, 0, 10};
	controlRoot.Align													= ::gpk::ALIGN_CENTER					;

	gui.Controls.Constraints[controlTestRoot].AttachSizeToControl		= {controlTestRoot, controlTestRoot};
	//gui.Controls.Modes		[controlTestRoot].Design					= true;

	::setupGameUI(app);

	{
		app.IdExit															= ::gpk::controlCreate(gui);
		::gpk::SControl															& controlExit				= gui.Controls.Controls[app.IdExit];
		controlExit.Area													= {{0, 0}, {64, 18}};
		controlExit.Border													= {1, 1, 1, 1};
		controlExit.Margin													= {1, 1, 1, 1};
		controlExit.Align													= ::gpk::ALIGN_CENTER_BOTTOM;
		::gpk::SControlText														& controlText				= gui.Controls.Text[app.IdExit];
		controlText.Text													= "Exit";
		controlText.Align													= ::gpk::ALIGN_CENTER;
		::gpk::SControlConstraints												& controlConstraints		= gui.Controls.Constraints[app.IdExit];
		controlConstraints.AttachSizeToText.y								= false;
		controlConstraints.AttachSizeToText.x								= false;
		::gpk::controlSetParent(gui, app.IdExit, controlTestRoot);
	}
	for(uint32_t iButton = 0; iButton < 2; ++iButton) {
		app.IdAttack[iButton]												= ::gpk::controlCreate(gui);
		::gpk::SControl															& controlExit				= gui.Controls.Controls[app.IdAttack[iButton]];
		controlExit.Area													= {{0, 0}, {96, 18}};
		controlExit.Border													= {1, 1, 1, 1};
		controlExit.Margin													= {1, 1, 1, 1};
		controlExit.Align													= iButton ? ::gpk::ALIGN_BOTTOM_RIGHT : ::gpk::ALIGN_BOTTOM_LEFT;
		::gpk::SControlText														& controlText				= gui.Controls.Text[app.IdAttack[iButton]];
		controlText.Text													= iButton ? "Attack (1)" : "Attack (0)";
		controlText.Align													= ::gpk::ALIGN_CENTER;
		::gpk::SControlConstraints												& controlConstraints		= gui.Controls.Constraints[app.IdAttack[iButton]];
		controlConstraints.AttachSizeToText.y								= false;
		controlConstraints.AttachSizeToText.x								= false;
		::gpk::controlSetParent(gui, app.IdAttack[iButton], controlTestRoot);
	}
	// Set up initial characters
	for(uint32_t i = 0; i < 2; ++i) {
		::pcs::SEntityPropertyPoints											& characterPoints			= app.CharacterPoints[i];
		characterPoints.Attack.Hit											= 5000;
		characterPoints.Attack.Damage										= 5;
		characterPoints.Attack.Absorption									= 2500 + (i * 2500);
		characterPoints.Attack.Range										= 0;
		characterPoints.MaxLife.Health										= 20;
		characterPoints.MaxLife.Shield										= 20;
		//characterPoints.DrainLife.Health									= 5000;
		//characterPoints.DrainLife.Shield									= 100;
		//characterPoints.DirectDamageLife.Health								= 2;
		//characterPoints.DirectDamageLife.Shield								= 1;
		characterPoints.Life												= characterPoints.MaxLife;
		::gme::SCharacterUIControls												& characterUI				= app.CharacterUI[i];
		::syncTunersPoints(characterPoints.Life					, characterUI.TunersLife				);
		::syncTunersPoints(characterPoints.Power				, characterUI.TunersPower				);
		::syncTunersPoints(characterPoints.Fitness				, characterUI.TunersFitness				);
		::syncTunersPoints(characterPoints.Attack				, characterUI.TunersAttack				);
		::syncTunersPoints(characterPoints.DirectDamageLife		, characterUI.TunersDirectDamageLife	);
		::syncTunersPoints(characterPoints.DirectDamagePower	, characterUI.TunersDirectDamagePower	);
		::syncTunersPoints(characterPoints.DrainLife			, characterUI.TunersDrainLife			);
		::syncTunersPoints(characterPoints.DrainPower			, characterUI.TunersDrainPower			);
		::syncTunersPoints(characterPoints.RegenLife			, characterUI.TunersRegenLife			);
		::syncTunersPoints(characterPoints.RegenPower			, characterUI.TunersRegenPower			);
		::syncTunersPoints(characterPoints.MaxLife				, characterUI.TunersMaxLife				);
		::syncTunersPoints(characterPoints.MaxPower				, characterUI.TunersMaxPower			);
		::syncTunersPoints(characterPoints.BonusLife			, characterUI.TunersBonusLife			);
		::syncTunersPoints(characterPoints.BonusPower			, characterUI.TunersBonusPower			);
	}

	::gpk::tcpipInitialize();

	app.Client.AddressConnect											= {};
	::gpk::tcpipAddress(9998, 0, ::gpk::TRANSPORT_PROTOCOL_UDP, app.Client.AddressConnect);
	::gpk::clientConnect(app.Client);
	return 0; 
}

static		::gpk::error_t											attackMelee					(::gme::SApplication & app, int32_t attacker) {
	const int32_t indexAttacker = attacker % 2;
	const int32_t indexAttacked = (attacker + 1) % 2;
	return ::pcs::attackMelee(app.RandomGenerator
		, app.CharacterScore	[indexAttacker]
		, app.CharacterScore	[indexAttacked]
		, app.CharacterPoints	[indexAttacker]
		, app.CharacterPoints	[indexAttacked]
		, app.CharacterStatus	[indexAttacker]
		, app.CharacterStatus	[indexAttacked]
		, app.CharacterDefend	[indexAttacked]
	);
}

			::gpk::error_t											update						(::gme::SApplication & app, bool exitSignal)											{ 
	::gpk::STimer															timer;
	retval_info_if(::gpk::APPLICATION_STATE_EXIT, exitSignal, "Exit requested by runtime.");
	{
		::gpk::mutex_guard														lock						(app.LockRender);
		app.Framework.MainDisplayOffscreen									= app.Offscreen;
	}
	::gpk::SFramework														& framework					= app.Framework;
	retval_info_if(::gpk::APPLICATION_STATE_EXIT, ::gpk::APPLICATION_STATE_EXIT == ::gpk::updateFramework(app.Framework), "Exit requested by framework update.");

	for(uint32_t iCharacter = 0; iCharacter < app.DialogCharacter.size(); ++iCharacter) 
		app.DialogCharacter[iCharacter].Update();
 
	::gpk::SGUI																& gui						= *framework.GUI;
	::gpk::array_pod<uint32_t>												controlsToProcess			= {};
	::gpk::guiGetProcessableControls(gui, controlsToProcess);
	for(uint32_t iControl = 0, countControls = controlsToProcess.size(); iControl < countControls; ++iControl) {
		uint32_t																idControl					= controlsToProcess[iControl];
		const ::gpk::SControlState												& controlState				= gui.Controls.States[idControl];
		if(controlState.Execute) {
			info_printf("Executed %u.", idControl);
			if(idControl == (uint32_t)app.IdExit)
				return 1;
			if(idControl == (uint32_t)app.IdAttack[1] || idControl == (uint32_t)app.IdAttack[0]) {
				if(idControl == (uint32_t)app.IdAttack[0]) {::attackMelee(app, 0); }
				if(idControl == (uint32_t)app.IdAttack[1]) {::attackMelee(app, 1); }
				for(uint32_t i = 0; i < 2; ++i) {
					::pcs::SEntityPropertyPoints											& characterPoints			= app.CharacterPoints	[i];
					//::pcs::SCharacterStatus													& characterStatus			= app.CharacterStatus	[i];
					//::pcs::SCharacterScore													& characterScore			= app.CharacterScore	[i];
					::pcs::SDefend															& characterDefend			= app.CharacterDefend	[i];
					::gme::SCharacterUIControls												& characterUI				= app.CharacterUI		[i];
					::syncTunersPoints(characterPoints.Life					, characterUI.TunersLife				);
					::syncTunersPoints(characterPoints.Power				, characterUI.TunersPower				);
					::syncTunersPoints(characterPoints.Fitness				, characterUI.TunersFitness				);
					::syncTunersPoints(characterPoints.Attack				, characterUI.TunersAttack				);
					::syncTunersPoints(characterPoints.DirectDamageLife		, characterUI.TunersDirectDamageLife	);
					::syncTunersPoints(characterPoints.DirectDamagePower	, characterUI.TunersDirectDamagePower	);
					::syncTunersPoints(characterPoints.DrainLife			, characterUI.TunersDrainLife			);
					::syncTunersPoints(characterPoints.DrainPower			, characterUI.TunersDrainPower			);
					::syncTunersPoints(characterPoints.RegenLife			, characterUI.TunersRegenLife			);
					::syncTunersPoints(characterPoints.RegenPower			, characterUI.TunersRegenPower			);
					::syncTunersPoints(characterPoints.MaxLife				, characterUI.TunersMaxLife				);
					::syncTunersPoints(characterPoints.MaxPower				, characterUI.TunersMaxPower			);
					::syncTunersPoints(characterPoints.BonusLife			, characterUI.TunersBonusLife			);
					::syncTunersPoints(characterPoints.BonusPower			, characterUI.TunersBonusPower			);
					//
					::syncTunersPoints(characterDefend						, characterUI.TunersDefend				);
				}
			}
		}
	}
	for(uint32_t i = 0; i < 2; ++i) {
		::pcs::SEntityPropertyPoints											& characterPoints			= app.CharacterPoints	[i];
		::pcs::SDefend															& characterDefend			= app.CharacterDefend	[i];
		::gme::SCharacterUIControls												& characterUI				= app.CharacterUI		[i];
		::syncCharacterPoints(characterPoints.Life				, characterUI.TunersLife				);
		::syncCharacterPoints(characterPoints.Power				, characterUI.TunersPower				);
		::syncCharacterPoints(characterPoints.Fitness			, characterUI.TunersFitness				);
		::syncCharacterPoints(characterPoints.Attack			, characterUI.TunersAttack				);
		::syncCharacterPoints(characterPoints.DirectDamageLife	, characterUI.TunersDirectDamageLife	);
		::syncCharacterPoints(characterPoints.DirectDamagePower	, characterUI.TunersDirectDamagePower	);
		::syncCharacterPoints(characterPoints.DrainLife			, characterUI.TunersDrainLife			);
		::syncCharacterPoints(characterPoints.DrainPower		, characterUI.TunersDrainPower			);
		::syncCharacterPoints(characterPoints.RegenLife			, characterUI.TunersRegenLife			);
		::syncCharacterPoints(characterPoints.RegenPower		, characterUI.TunersRegenPower			);
		::syncCharacterPoints(characterPoints.MaxLife			, characterUI.TunersMaxLife				);
		::syncCharacterPoints(characterPoints.MaxPower			, characterUI.TunersMaxPower			);
		::syncCharacterPoints(characterPoints.BonusLife			, characterUI.TunersBonusLife			);
		::syncCharacterPoints(characterPoints.BonusPower		, characterUI.TunersBonusPower			);
		//
		::syncTunersPoints(characterDefend						, characterUI.TunersDefend				);
	}																											 

	reterr_error_if(app.Client.State != ::gpk::UDP_CONNECTION_STATE_IDLE, "Failed to connect to server.")
	else {
		::gpk::connectionPushData(app.Client, app.Client.Queue, "Message arrived!");
		::gpk::connectionPushData(app.Client, app.Client.Queue, "Message arrived! 2");
		::gpk::connectionPushData(app.Client, app.Client.Queue, "Message arrived! 3");
		::gpk::connectionPushData(app.Client, app.Client.Queue, "Message arrived! 4");
		::gpk::clientUpdate(app.Client);
		//::gpk::sleep(1000);
	}

	//timer.Frame();
	//warning_printf("Update time: %f.", (float)timer.LastTimeSeconds);
	return 0; 
}

			::gpk::error_t												draw					(::gme::SApplication & app)						{ 
	::gpk::STimer																timer;
	app;
	::gpk::ptr_obj<::gpk::SRenderTarget<::gpk::SColorBGRA, uint32_t>>			target;
	target.create();
	//target->resize(app.Framework.MainDisplay.Size, {0xFF, 0x40, 0x7F, 0xFF}, (uint32_t)-1);
	target->resize(app.Framework.MainDisplay.Size, {}, (uint32_t)-1);
	{
		::gpk::mutex_guard															lock					(app.LockGUI);
		::gpk::guiDraw(*app.Framework.GUI, target->Color.View);
	}
	
	//for(uint32_t iCharacter = 0; iCharacter < app.DialogCharacter.size(); ++iCharacter) {
	//	::gpk::mutex_guard															lock					(app.LockGUI);
	//	::gpk::controlDrawHierarchy(*app.DialogCharacter[iCharacter].GUI, 0, target->Color.View);
	//}
	{
		::gpk::mutex_guard															lock					(app.LockRender);
		app.Offscreen															= target;
	}
	//timer.Frame();
	//warning_printf("Draw time: %f.", (float)timer.LastTimeSeconds);
	return 0; 
}