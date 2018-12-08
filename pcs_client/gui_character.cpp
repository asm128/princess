#include "application.h"

static constexpr	const uint16_t								heightOfField					= 20;

template<typename _TPoints>
static				::gpk::error_t								guiCreateFieldArray				(::gpk::SDialog & dialog, _TPoints & fields, int32_t idParent)	{ 
	::gpk::SGUI															& gui							= dialog.GUI;
	gui.Controls.Controls	[idParent].Area.Size.y					= heightOfField + 4;
	::gpk::view_array<int32_t>											fieldValues						= {((int32_t*)&fields), _TPoints::TRegistry::get_member_count()};
	for(uint32_t iMember = 0; iMember < fieldValues.size(); ++iMember) {
		int32_t																idControl						= ::gpk::controlCreateChild(gui, idParent);
		fieldValues[iMember]											= idControl; 
		gui.Controls.Text		[idControl].Align						= ::gpk::ALIGN_CENTER_LEFT; //= {00, 0};
		gui.Controls.Text		[idControl].Text						= _TPoints::TRegistry::get_names()[iMember]; //= {00, 0};
		gui.Controls.Modes		[idControl].ColorMode					= ::gpk::GUI_COLOR_MODE_3D; //= {00, 0};
		gui.Controls.Modes		[idControl].UseNewPalettes				= true;
		gui.Controls.Constraints[idControl].AttachSizeToControl			= {idControl, -1};
		gui.Controls.Controls	[idControl].Area.Size.y					= heightOfField;
		gui.Controls.Controls	[idControl].Margin						= {3, 2, 0, 0};
		gui.Controls.Controls	[idParent].Area.Size.y					+= heightOfField;
		if(iMember)
			gui.Controls.Constraints[idControl].DockToControl.Bottom		= idControl - 1;
		else
			gui.Controls.Controls	[idControl].Area.Offset.y				= heightOfField;
		::gpk::memcpy_s(gui.Controls.Controls[idControl].Palettes, dialog.ColorsControl);
	}	
	return 0; 
}

					::gpk::error_t								dialogCreateTuners					(::gpk::SDialog & dialog, int32_t idGroup, ::gpk::view_array<::gpk::ptr_nco<::gpk::SDialogTuner>> tuners)	{
	::gpk::SGUIControlTable												& controlTable						= dialog.GUI.Controls;
	for(uint32_t iField = 0, countFields = controlTable.Children[idGroup].size(); iField < countFields; ++iField) { 
		int32_t																idLabel								= controlTable.Children[idGroup][iField]; 
		gpk_necall(::gpk::tunerCreate(dialog, tuners[iField]), "%s", "????"); 
		tuners[iField]->ValueLimits.Min									= 0; 
		tuners[iField]->ValueLimits.Max									= 0xFFFFFFFF; 
		int32_t																idControl							= tuners[iField]->IdGUIControl; 
		::gpk::SControl														& control							= controlTable.Controls[idControl]; 
		control.Align													= ::gpk::ALIGN_TOP_RIGHT; 
		control.Area.Size.x												= 110; 
		control.Area.Size.y												= controlTable.Controls[idLabel].Area.Size.y; 
		if(iField) 
			controlTable.Constraints[idControl].DockToControl.Bottom		= tuners[iField - 1]->IdGUIControl; 
		else 
			control.Area.Offset.y											= control.Area.Size.y;
		gpk_necall(::gpk::controlSetParent(dialog.GUI, idControl, idGroup), "Invalid group id: %i.", idGroup); 
	}
	return 0;
}

					::gpk::error_t								gme::dialogCreateCharacter			(::gpk::SDialog & dialog, ::gme::SCharacterUIControls	& character	)	{
	::gpk::SGUI															& gui								= dialog.GUI;
	character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_NORMAL				] = gui.Palettes.push_back({{::gpk::GRAY			, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, {}, ::gpk::WHITE		* .9	,}});
	character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_DISABLED				] = gui.Palettes.push_back({{::gpk::LIGHTGRAY * 1.3	, ::gpk::ORANGE		, ::gpk::YELLOW		, ::gpk::MAGENTA	, ::gpk::CYAN		, {}, ::gpk::LIGHTGRAY	* 1.2	,}});
	character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_HOVER				] = character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_NORMAL	]; // gui.Palettes.push_back({{::gpk::LIGHTGRAY * 1.2	, ::gpk::GRAY		, ::gpk::GRAY		, ::gpk::GRAY		, ::gpk::GRAY		, {}, ::gpk::DARKBLUE	 * .5	,}});
	character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_PRESSED				] = character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_NORMAL	]; // gui.Palettes.push_back({{::gpk::LIGHTGRAY		, ::gpk::LIGHTBLUE	, ::gpk::LIGHTBLUE	, ::gpk::LIGHTBLUE	, ::gpk::LIGHTBLUE	, {}, ::gpk::BLUE				,}});
	character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_SELECTED				] = character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_NORMAL	];
	character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_SELECTED_DISABLED	] = character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_DISABLED	];
	character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_SELECTED_HOVER		] = character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_HOVER	];
	character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_SELECTED_PRESSED		] = character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_PRESSED	];
	character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_EXECUTE				] = character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_PRESSED	];
	character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_OUTDATED				] = character.PaletteGroups[::gpk::GUI_CONTROL_PALETTE_NORMAL	];

	character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_NORMAL				] = gui.Palettes.push_back({{::gpk::DARKGRAY		, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, {}, ::gpk::WHITE		* .9	,}});
	character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_DISABLED				] = gui.Palettes.push_back({{::gpk::LIGHTGRAY * 1.3	, ::gpk::ORANGE		, ::gpk::YELLOW		, ::gpk::MAGENTA	, ::gpk::CYAN		, {}, ::gpk::LIGHTGRAY	* 1.2	,}});
	character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_HOVER				] = character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_NORMAL	]; //gui.Palettes.push_back({{::gpk::LIGHTGRAY * 1.2	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, ::gpk::LIGHTGRAY	, {}, ::gpk::DARKBLUE	 * .5	,}});
	character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_PRESSED				] = character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_NORMAL	]; //gui.Palettes.push_back({{::gpk::LIGHTGRAY		, ::gpk::LIGHTBLUE	, ::gpk::LIGHTBLUE	, ::gpk::LIGHTBLUE	, ::gpk::LIGHTBLUE	, {}, ::gpk::BLUE				,}});
	character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_SELECTED				] = character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_NORMAL	];
	character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_SELECTED_DISABLED	] = character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_DISABLED	];
	character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_SELECTED_HOVER		] = character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_HOVER	];
	character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_SELECTED_PRESSED		] = character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_PRESSED	];
	character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_EXECUTE				] = character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_PRESSED	];
	character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_OUTDATED				] = character.PaletteFields[::gpk::GUI_CONTROL_PALETTE_NORMAL	];

	character.DialogCharacter										= ::gpk::controlCreate(gui); 
	{
		::gpk::SControl														& controlCharacter					= gui.Controls.Controls[character.DialogCharacter];
		gui.Controls.States[character.DialogCharacter].Design			= false;
		controlCharacter.Border = controlCharacter.Margin				= {};
		controlCharacter.Area.Size.x									= 220;
	}

	gpk_necall(::guiCreateFieldArray(dialog, character.DialogStatGroups			, character.DialogCharacter						), "%s", "????");	// Create group control array
	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsLife				, character.DialogStatGroups.Life				), "%s", "????");	// Create label control array
	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsPower				, character.DialogStatGroups.Power				), "%s", "????"); 	// Create label control array
	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsFitness			, character.DialogStatGroups.Fitness			), "%s", "????"); 	// Create label control array
	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsAttack				, character.DialogStatGroups.Attack				), "%s", "????"); 	// Create label control array
	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsDirectDamageLife	, character.DialogStatGroups.DirectDamageLife	), "%s", "????"); 	// Create label control array
	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsDirectDamagePower	, character.DialogStatGroups.DirectDamagePower	), "%s", "????"); 	// Create label control array
	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsDrainLife			, character.DialogStatGroups.DrainLife			), "%s", "????"); 	// Create label control array
	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsDrainPower			, character.DialogStatGroups.DrainPower			), "%s", "????"); 	// Create label control array

	// -- Fix group titles
	gui.Controls.Text[character.DialogStatGroups.DirectDamageLife	].Text	= "Direct Damage (Life)";
	gui.Controls.Text[character.DialogStatGroups.DirectDamagePower	].Text	= "Direct Damage (Power)";
	gui.Controls.Text[character.DialogStatGroups.DrainLife			].Text	= "Drain (Life)";
	gui.Controls.Text[character.DialogStatGroups.DrainPower			].Text	= "Drain (Power)";

	// -- Fix group properties
	auto																& constraints					= gui.Controls.Constraints;
	{
		::gpk::SControl														& controlCharacter				= gui.Controls.Controls[character.DialogCharacter];
		const ::gpk::array_pod<int32_t>										& characterChildGroups			= gui.Controls.Children[character.DialogCharacter];
		controlCharacter.Area.Size.y									= 0;
		for(uint32_t iChild = 0; iChild < characterChildGroups.size(); ++iChild) {
			int32_t																idControl						= characterChildGroups[iChild];
			::gpk::SControl														& controlGroup					= gui.Controls.Controls[idControl];
			controlCharacter.Area.Size.y									+= controlGroup.Area.Size.y;
			gui.Controls.Text[idControl].Align								= ::gpk::ALIGN_TOP_LEFT;
			//gui.Controls.Modes[idControl].ColorMode							= ::gpk::GUI_COLOR_MODE_FLAT;
			constraints[idControl].AttachSizeToControl						= {-1, -1};
			controlGroup.Area.Size.x										= 220; 
			controlGroup.Area.Offset										= {};
			//controlGroup.Border	/*= controlGroup.Margin*/					= {};
			//controlGroup.Margin.Top											= 4;
			if(iChild)
				constraints[idControl].DockToControl.Bottom						= characterChildGroups[iChild - 1];
			const ::gpk::array_pod<int32_t>										& childFields					= gui.Controls.Children[idControl];
			for(uint32_t iChildField = 0; iChildField < childFields.size(); ++iChildField) {
				int32_t																idField							= childFields[iChildField];
				constraints[idField].AttachSizeToControl						= {-1, -1};
				gui.Controls.Controls[idField].Area.Size.x						= 110;
				::gpk::memcpy_s(gui.Controls.Controls[idField].Palettes, character.PaletteFields.Storage);//gui.DefaultColors);
			}
			::gpk::memcpy_s(controlGroup.Palettes, character.PaletteGroups.Storage);//gui.DefaultColors);
		}
	}

	// Create tuners.
	::dialogCreateTuners(dialog, character.DialogStatGroups.Life				, character.TunersLife				);
	::dialogCreateTuners(dialog, character.DialogStatGroups.Power				, character.TunersPower				);
	::dialogCreateTuners(dialog, character.DialogStatGroups.Fitness				, character.TunersFitness			);
	::dialogCreateTuners(dialog, character.DialogStatGroups.Attack				, character.TunersAttack			);
	::dialogCreateTuners(dialog, character.DialogStatGroups.DirectDamageLife	, character.TunersDirectDamageLife	);
	::dialogCreateTuners(dialog, character.DialogStatGroups.DirectDamagePower	, character.TunersDirectDamagePower	);
	::dialogCreateTuners(dialog, character.DialogStatGroups.DrainLife			, character.TunersDrainLife			);
	::dialogCreateTuners(dialog, character.DialogStatGroups.DrainPower			, character.TunersDrainPower		);
	return 0;
}
