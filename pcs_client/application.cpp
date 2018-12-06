#include "application.h"
#include "gpk_bitmap_file.h"

//#define GPK_AVOID_LOCAL_APPLICATION_MODULE_MODEL_EXECUTABLE_RUNTIME
#include "gpk_app_impl.h"
#include "gpk_tcpip.h"
#include "gpk_chrono.h"

GPK_DEFINE_APPLICATION_ENTRY_POINT(::gme::SApplication, "Module Explorer");

			::gpk::error_t											cleanup					(::gme::SApplication & app)							{ 
	::gpk::mainWindowDestroy(app.Framework.MainDisplay);
	::gpk::clientDisconnect(app.Client);
	::gpk::tcpipShutdown();
	return 0; 
}

static		::gpk::error_t											setupSimulatorUI			(::gme::SApplication & app)						{ 
	for(uint32_t iCharacter = 0; iCharacter < ::gpk::size(app.CharacterUIFieldValue); ++iCharacter)
		gpk_necall(::gme::guiCreateCharacter(app.DialogCharacter[iCharacter].GUI, app.CharacterUIFieldNames[iCharacter]), "%s", "????");

	app.DialogCharacter[0].GUI.Controls.Controls[app.CharacterUIFieldNames[0].DialogCharacter].Align			= ::gpk::ALIGN_LEFT;
	app.DialogCharacter[1].GUI.Controls.Controls[app.CharacterUIFieldNames[1].DialogCharacter].Align			= ::gpk::ALIGN_RIGHT;
	for(uint32_t iCharacter = 0; iCharacter < ::gpk::size(app.CharacterUIFieldValue); ++iCharacter) {
		app.DialogCharacter[iCharacter].GUI.Controls.Controls[app.CharacterUIFieldNames[iCharacter].DialogCharacter].Area.Size.x		= 320;
		::gpk::controlSetParent(app.DialogCharacter[iCharacter].GUI, app.CharacterUIFieldNames[iCharacter].DialogCharacter, 0);
	}

	for(uint32_t iCharacter = 0; iCharacter < ::gpk::size(app.CharacterUIFieldValue); ++iCharacter) {
		::gpk::SDialog				& dialogCharacter			= app.DialogCharacter[iCharacter];
		::gme::SCharacterUIControls	& controlsCharacterValues	= app.CharacterUIFieldValue[iCharacter];
		gpk_necall(::gme::guiCreateCharacter(dialogCharacter.GUI, controlsCharacterValues), "%s", "????");

		for(uint32_t iChild = 0; iChild < dialogCharacter.GUI.Controls.Children[controlsCharacterValues.DialogCharacter].size(); ++iChild) {
			int32_t									iControl						= dialogCharacter.GUI.Controls.Children[controlsCharacterValues.DialogCharacter][iChild];
			dialogCharacter.GUI.Controls.Text		[iControl].Text					= {}; 
			dialogCharacter.GUI.Controls.Controls	[iControl].Align				= ::gpk::ALIGN_RIGHT;
			dialogCharacter.GUI.Controls.Constraints[iControl].AttachSizeToControl	= {-1, -1};
		}
		int32_t iChild = 0;
		while(dialogCharacter.GUI.Controls.Children[controlsCharacterValues.DialogCharacter].size()) {
			int32_t									iControl				= dialogCharacter.GUI.Controls.Children[controlsCharacterValues.DialogCharacter][iChild];
			::gpk::controlSetParent(dialogCharacter.GUI, iControl, app.CharacterUIFieldNames[iCharacter].DialogCharacter);
		}
		for(uint32_t iControl = controlsCharacterValues.DialogCharacter + 1; iControl < dialogCharacter.GUI.Controls.Controls.size(); ++iControl) {
			dialogCharacter.GUI.Controls.Controls[iControl].Area.Size.x														= 110;
			if(iControl == (uint32_t)controlsCharacterValues.DialogPoints.Life		) continue;
			if(iControl == (uint32_t)controlsCharacterValues.DialogPoints.Power		) continue;
			if(iControl == (uint32_t)controlsCharacterValues.DialogPoints.Fitness	) continue;
			if(iControl == (uint32_t)controlsCharacterValues.DialogPoints.Attack	) continue;
			dialogCharacter.GUI.Controls.Constraints[iControl].AttachSizeToControl.x										= iControl;
			dialogCharacter.GUI.Controls.Text[iControl].Text																= "0";
		}
		::gpk::controlDelete(dialogCharacter.GUI, app.CharacterUIFieldValue[iCharacter].DialogCharacter, true);
	}
	return 0;
}

			::gpk::error_t											setupPalette				(::gpk::view_array<int32_t> out_paletteIndices, ::gpk::array_pod<::gpk::array_static<::gpk::SColorBGRA, ::gpk::GUI_CONTROL_COLOR_COUNT>> & guiPalettes, ::gpk::SColorBGRA& baseColor)						{ 
	out_paletteIndices[::gpk::GUI_CONTROL_PALETTE_NORMAL			]	= guiPalettes.push_back({baseColor, {}, {}, {}, {}, {}, ::gpk::RED, {}, {}, {}, });// gui.DefaultColors.CONTROL_NORMAL				;
	out_paletteIndices[::gpk::GUI_CONTROL_PALETTE_DISABLED			]	= guiPalettes.push_back({baseColor, {}, {}, {}, {}, {}, ::gpk::RED, {}, {}, {}, });// gui.DefaultColors.CONTROL_DISABLED			;
	out_paletteIndices[::gpk::GUI_CONTROL_PALETTE_HOVER				]	= guiPalettes.push_back({baseColor, {}, {}, {}, {}, {}, ::gpk::RED, {}, {}, {}, });// gui.DefaultColors.CONTROL_HOVER				;
	out_paletteIndices[::gpk::GUI_CONTROL_PALETTE_PRESSED			]	= guiPalettes.push_back({baseColor, {}, {}, {}, {}, {}, ::gpk::RED, {}, {}, {}, });// gui.DefaultColors.CONTROL_PRESSED				;
	out_paletteIndices[::gpk::GUI_CONTROL_PALETTE_SELECTED			]	= guiPalettes.push_back({baseColor, {}, {}, {}, {}, {}, ::gpk::RED, {}, {}, {}, });// gui.DefaultColors.CONTROL_SELECTED			;
	out_paletteIndices[::gpk::GUI_CONTROL_PALETTE_SELECTED_DISABLED	]	= guiPalettes.push_back({baseColor, {}, {}, {}, {}, {}, ::gpk::RED, {}, {}, {}, });// gui.DefaultColors.CONTROL_SELECTED_DISABLED	;
	out_paletteIndices[::gpk::GUI_CONTROL_PALETTE_SELECTED_HOVER	]	= guiPalettes.push_back({baseColor, {}, {}, {}, {}, {}, ::gpk::RED, {}, {}, {}, });// gui.DefaultColors.CONTROL_SELECTED_HOVER		;
	out_paletteIndices[::gpk::GUI_CONTROL_PALETTE_SELECTED_PRESSED	]	= guiPalettes.push_back({baseColor, {}, {}, {}, {}, {}, ::gpk::RED, {}, {}, {}, });// gui.DefaultColors.CONTROL_SELECTED_PRESSED	;
	out_paletteIndices[::gpk::GUI_CONTROL_PALETTE_EXECUTE			]	= guiPalettes.push_back({baseColor, {}, {}, {}, {}, {}, ::gpk::RED, {}, {}, {}, });// gui.DefaultColors.CONTROL_EXECUTE				;
	out_paletteIndices[::gpk::GUI_CONTROL_PALETTE_OUTDATED			]	= guiPalettes.push_back({baseColor, {}, {}, {}, {}, {}, ::gpk::RED, {}, {}, {}, });// gui.DefaultColors.CONTROL_OUTDATED			;
	return 0;
}
			::gpk::error_t											setup						(::gme::SApplication & app)						{ 
	::gpk::SFramework														& framework					= app.Framework;
	::gpk::SDisplay															& mainWindow				= framework.MainDisplay;
	framework.Input.create();
	app.DialogCharacter[0].Input										= framework.Input;
	app.DialogCharacter[1].Input										= framework.Input;
	error_if(errored(::gpk::mainWindowCreate(mainWindow, framework.RuntimeValues.PlatformDetail, framework.Input)), "%s", "Failed to create main window why?????!?!?!?!?");
	::gpk::SGUI																& gui						= framework.GUI;
	const int32_t															iShades					= 16;
	gui.ThemeDefault													= app.PaletteColumn * iShades + app.PaletteRow;
	gui.ColorModeDefault												= ::gpk::GUI_COLOR_MODE_3D;
	int32_t																	controlTestRoot			= ::gpk::controlCreate(gui);	// control 0
	::setupPalette(app.Palettes, gui.Palettes, gui.Palette[gui.ThemeDefault]);

	::gpk::SControl															& controlRoot			= gui.Controls.Controls[controlTestRoot];
	controlRoot.Area													= {{0, 0}, {320, 240}};
	controlRoot.Border													= {1, 1, 1, 1};
	controlRoot.Margin													= {20, 20, 20, 10};
	controlRoot.Align													= ::gpk::ALIGN_CENTER					;
	//gui.Controls.Modes[controlTestRoot].UseNewPalettes				= 1;
	memcpy(controlRoot.Palettes, app.Palettes, sizeof(app.Palettes));

	gui.Controls.Constraints[controlTestRoot].AttachSizeToControl		= {controlTestRoot, controlTestRoot};
	//gui.Controls.Modes	[controlTestRoot].Design					= true;
	::gpk::controlSetParent(gui, controlTestRoot, -1);

	::setupSimulatorUI(app);

	app.IdExit															= ::gpk::controlCreate(gui);
	::gpk::SControl															& controlExit				= gui.Controls.Controls[app.IdExit];
	controlExit.Area													= {{0, 0}, {64, 20}};
	controlExit.Border													= {1, 1, 1, 1};
	controlExit.Margin													= {1, 1, 1, 1};
	controlExit.Align													= ::gpk::ALIGN_BOTTOM_RIGHT;
	::gpk::SControlText														& controlText				= gui.Controls.Text[app.IdExit];
	controlText.Text													= "Exit";
	controlText.Align													= ::gpk::ALIGN_CENTER;
	::gpk::SControlConstraints												& controlConstraints		= gui.Controls.Constraints[app.IdExit];
	controlConstraints.AttachSizeToText.y								= false;
	controlConstraints.AttachSizeToText.x								= false;
	::gpk::controlSetParent(gui, app.IdExit, controlTestRoot);


	::gpk::tcpipInitialize();

	app.Client.AddressConnect											= {};
	::gpk::tcpipAddress(9998, 0, ::gpk::TRANSPORT_PROTOCOL_UDP, app.Client.AddressConnect);
	::gpk::clientConnect(app.Client);
	return 0; 
}
			::gpk::error_t											update						(::gme::SApplication & app, bool exitSignal)	{ 
	::gpk::STimer															timer;
	retval_info_if(::gpk::APPLICATION_STATE_EXIT, exitSignal, "Exit requested by runtime.");
	{
		::gpk::mutex_guard														lock						(app.LockRender);
		app.Framework.MainDisplayOffscreen									= app.Offscreen;
	}
	::gpk::SFramework														& framework					= app.Framework;
	retval_info_if(::gpk::APPLICATION_STATE_EXIT, ::gpk::APPLICATION_STATE_EXIT == ::gpk::updateFramework(app.Framework), "Exit requested by framework update.");

	::gpk::SGUI																& gui						= framework.GUI;
	{
		::gpk::mutex_guard														lock						(app.LockGUI);
		::gpk::guiProcessInput(gui, *app.Framework.Input);
	}
	if(app.Framework.Input->MouseCurrent.Deltas.z) {
		gui.Zoom.ZoomLevel													+= app.Framework.Input->MouseCurrent.Deltas.z * (1.0 / (120 * 4));
		::gpk::guiUpdateMetrics(gui, app.Offscreen->Color.metrics(), true);
	}
 
	for(uint32_t iControl = 0, countControls = gui.Controls.Controls.size(); iControl < countControls; ++iControl) {
		const ::gpk::SControlState												& controlState				= gui.Controls.States[iControl];
		if(controlState.Unused || controlState.Disabled)
			continue;
		if(controlState.Execute) {
			info_printf("Executed %u.", iControl);
			if(iControl == (uint32_t)app.IdExit)
				return 1;
		}
	}

	for(uint32_t iCharacter = 0; iCharacter < ::gpk::size(app.DialogCharacter); ++iCharacter) 
		app.DialogCharacter[iCharacter].Update();

	reterr_error_if(app.Client.State != ::gpk::UDP_CONNECTION_STATE_IDLE, "Failed to connect to server.")
	else {
		::gpk::connectionPushData(app.Client, app.Client.Queue, "Message arrived!");
		::gpk::connectionPushData(app.Client, app.Client.Queue, "Message arrived! 2");
		::gpk::connectionPushData(app.Client, app.Client.Queue, "Message arrived! 3");
		::gpk::connectionPushData(app.Client, app.Client.Queue, "Message arrived! 4");
		::gpk::clientUpdate(app.Client);
		//::gpk::sleep(1000);
	}

	::gpk::SUDPClient															& connectTest				= app.ClientTest1;
	connectTest.AddressConnect												= app.Client.AddressConnect;
	::gpk::clientConnect		(connectTest);
	::gpk::connectionPushData	(connectTest, connectTest.Queue, "Connect test!");
	::gpk::clientUpdate			(connectTest);
	::gpk::clientDisconnect		(connectTest);

	//timer.Frame();
	//warning_printf("Update time: %f.", (float)timer.LastTimeSeconds);
	return 0; 
}

			::gpk::error_t												draw					(::gme::SApplication & app)						{ 
	::gpk::STimer																timer;
	app;
	::gpk::ptr_obj<::gpk::SRenderTarget<::gpk::SColorBGRA, uint32_t>>			target;
	target.create();
	target->resize(app.Framework.MainDisplay.Size, {0xFF, 0x40, 0x7F, 0xFF}, (uint32_t)-1);
	//::gpk::clearTarget(*target);
	//{
	//	::gpk::mutex_guard															lock					(app.LockGUI);
	//	::gpk::controlDrawHierarchy(app.Framework.GUI, 0, target->Color.View);
	//}
	
	for(uint32_t iCharacter = 0; iCharacter < ::gpk::size(app.DialogCharacter); ++iCharacter) {
		::gpk::mutex_guard															lock					(app.LockGUI);
		::gpk::controlDrawHierarchy(app.DialogCharacter[iCharacter].GUI, 0, target->Color.View);
	}
	{
		::gpk::mutex_guard															lock					(app.LockRender);
		app.Offscreen															= target;
	}
	//timer.Frame();
	//warning_printf("Draw time: %f.", (float)timer.LastTimeSeconds);
	return 0; 
}