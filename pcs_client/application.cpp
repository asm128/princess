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

static		::gpk::error_t											setupGameUIPalettes		(::gpk::SGUI & gui, ::gme::SGameUIPalettes & palettes)						{ 
	palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_NORMAL				] = gui.Palettes.push_back({{::gpk::GRAY			, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, {}, ::gpk::WHITE		* .9	,}});
	palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_DISABLED				] = gui.Palettes.push_back({{::gpk::LIGHTGRAY * 1.3	, ::gpk::ORANGE		, ::gpk::YELLOW		, ::gpk::MAGENTA	, ::gpk::CYAN		, {}, ::gpk::LIGHTGRAY	* 1.2	,}});
	palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_HOVER					] = palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_NORMAL	]; // gui.Palettes.push_back({{::gpk::LIGHTGRAY * 1.2	, ::gpk::GRAY		, ::gpk::GRAY		, ::gpk::GRAY		, ::gpk::GRAY		, {}, ::gpk::DARKBLUE	 * .5	,}});
	palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_PRESSED				] = palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_NORMAL	]; // gui.Palettes.push_back({{::gpk::LIGHTGRAY		, ::gpk::LIGHTBLUE	, ::gpk::LIGHTBLUE	, ::gpk::LIGHTBLUE	, ::gpk::LIGHTBLUE	, {}, ::gpk::BLUE				,}});
	palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_SELECTED				] = palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_NORMAL	];
	palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_SELECTED_DISABLED		] = palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_DISABLED	];
	palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_SELECTED_HOVER		] = palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_HOVER		];
	palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_SELECTED_PRESSED		] = palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_PRESSED	];
	palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_EXECUTE				] = palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_PRESSED	];
	palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_OUTDATED				] = palettes.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_NORMAL	];

	palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_NORMAL				] = gui.Palettes.push_back({{::gpk::DARKGRAY		, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, {}, ::gpk::WHITE		* .9	,}});
	palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_DISABLED				] = gui.Palettes.push_back({{::gpk::LIGHTGRAY * 1.3	, ::gpk::ORANGE		, ::gpk::YELLOW		, ::gpk::MAGENTA	, ::gpk::CYAN		, {}, ::gpk::LIGHTGRAY	* 1.2	,}});
	palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_HOVER					] = palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_NORMAL	]; //gui.Palettes.push_back({{::gpk::LIGHTGRAY * 1.2	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, {}, ::gpk::DARKBLUE	 * .5	,}});
	palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_PRESSED				] = palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_NORMAL	]; //gui.Palettes.push_back({{::gpk::LIGHTGRAY		, ::gpk::LIGHTBLUE	, ::gpk::LIGHTBLUE	, ::gpk::LIGHTBLUE	, ::gpk::LIGHTBLUE	, {}, ::gpk::BLUE				,}});
	palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_SELECTED				] = palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_NORMAL	];
	palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_SELECTED_DISABLED		] = palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_DISABLED	];
	palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_SELECTED_HOVER		] = palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_HOVER		];
	palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_SELECTED_PRESSED		] = palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_PRESSED	];
	palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_EXECUTE				] = palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_PRESSED	];
	palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_OUTDATED				] = palettes.PaletteFields[::gpk::GUI_CONTROL_PALETTE_NORMAL	];

	palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_NORMAL				] = gui.Palettes.push_back({{::gpk::LIGHTGRAY		, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, {}, ::gpk::BLACK		* .9	,}});
	palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_DISABLED				] = gui.Palettes.push_back({{::gpk::LIGHTGRAY * 1.3	, ::gpk::ORANGE		, ::gpk::YELLOW		, ::gpk::MAGENTA	, ::gpk::CYAN		, {}, ::gpk::LIGHTGRAY	* 1.2	,}});
	palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_HOVER					] = palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_NORMAL	]; //gui.Palettes.push_back({{::gpk::LIGHTGRAY * 1.2	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, {}, ::gpk::DARKBLUE	 * .5	,}});
	palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_PRESSED				] = palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_NORMAL	]; //gui.Palettes.push_back({{::gpk::LIGHTGRAY		, ::gpk::LIGHTBLUE	, ::gpk::LIGHTBLUE	, ::gpk::LIGHTBLUE	, ::gpk::LIGHTBLUE	, {}, ::gpk::BLUE				,}});
	palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_SELECTED				] = palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_NORMAL	];
	palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_SELECTED_DISABLED		] = palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_DISABLED	];
	palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_SELECTED_HOVER		] = palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_HOVER	];
	palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_SELECTED_PRESSED		] = palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_PRESSED	];
	palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_EXECUTE				] = palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_PRESSED	];
	palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_OUTDATED				] = palettes.PaletteTitles[::gpk::GUI_CONTROL_PALETTE_NORMAL	];
	return 0;
}
static		::gpk::error_t											setupGameUI				(::gme::SApplication & app)						{ 
	::setupGameUIPalettes(*app.Framework.GUI, app.GameUIPalettes);
	for(uint32_t iCharacter = 0; iCharacter < app.CharacterUIFieldNames.size(); ++iCharacter) {
		::gpk::SDialog															& dialogCharacter			= app.DialogCharacter[iCharacter];
		dialogCharacter.GUI													= app.Framework.GUI;
		dialogCharacter.Input												= app.Framework.Input;
		::gme::SCharacterUIControls												& controls					= app.CharacterUIFieldNames[iCharacter];
		::gpk::SGUIControlTable													& controlTable				= dialogCharacter.GUI->Controls;
		gpk_necall(::gme::dialogCreateCharacter(dialogCharacter, controls, app.GameUIPalettes), "%s", "????");
		controlTable.Controls[controls.DialogCharacter].Align				= iCharacter ? ::gpk::ALIGN_RIGHT : ::gpk::ALIGN_LEFT;
		gpk_necall(::gpk::controlSetParent(*dialogCharacter.GUI, controls.DialogCharacter, 0), "%s", "????");
	}
	return 0;
}

			::gpk::error_t											setup						(::gme::SApplication & app)						{ 
	::gpk::SFramework														& framework					= app.Framework;
	::gpk::SDisplay															& mainWindow				= framework.MainDisplay;
	framework.GUI														= app.DialogCharacter[0].GUI;
	::gpk::controlDelete(*framework.GUI, 0);
	error_if(errored(::gpk::mainWindowCreate(mainWindow, framework.RuntimeValues.PlatformDetail, framework.Input)), "%s", "Failed to create main window why?????!?!?!?!?");
	::gpk::SGUI																& gui						= *framework.GUI;
	const int32_t															iShades					= 16;
	gui.ThemeDefault													= app.PaletteColumn * iShades + app.PaletteRow;
	gui.ColorModeDefault												= ::gpk::GUI_COLOR_MODE_3D;
	int32_t																	controlTestRoot			= ::gpk::controlCreate(gui);	// control 0

	::gpk::SControl															& controlRoot			= gui.Controls.Controls[controlTestRoot];
	controlRoot.Area													= {{0, 0}, {320, 240}};
	controlRoot.Border													= {1, 1, 1, 1};
	controlRoot.Margin													= {0, 0, 0, 10};
	controlRoot.Align													= ::gpk::ALIGN_CENTER					;

	gui.Controls.Constraints[controlTestRoot].AttachSizeToControl		= {controlTestRoot, controlTestRoot};
	//gui.Controls.States		[controlTestRoot].Design					= true;

	::setupGameUI(app);

	app.IdExit															= ::gpk::controlCreate(gui);
	::gpk::SControl															& controlExit				= gui.Controls.Controls[app.IdExit];
	controlExit.Area													= {{0, 0}, {64, 20}};
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

	::gpk::SGUI																& gui						= *framework.GUI;
	{
		::gpk::mutex_guard														lock						(app.LockGUI);
		::gpk::guiProcessInput(gui, *app.Framework.Input);
	}
	for(uint32_t iCharacter = 0; iCharacter < app.DialogCharacter.size(); ++iCharacter) 
		app.DialogCharacter[iCharacter].Update();
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
	target->resize(app.Framework.MainDisplay.Size, {0xFF, 0x40, 0x7F, 0xFF}, (uint32_t)-1);
	::gpk::clearTarget(*target);
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