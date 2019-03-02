#include "application.h"

static constexpr	const uint16_t								heightOfField					= 18;
static				::gpk::error_t								dialogCreateField				(::gpk::SDialog & dialog, const ::gpk::view_const_string& text, int32_t idParent)	{ 
	::gpk::SGUI															& gui							= *dialog.GUI;
	int32_t																idControl						= ::gpk::controlCreateChild(gui, idParent);
	::gpk::SControl														& control						= gui.Controls.Controls	[idControl];
	::gpk::SControlText													& controlText					= gui.Controls.Text		[idControl];
	::gpk::SControlMode													& controlMode					= gui.Controls.Modes	[idControl];
	::gpk::memcpy_s(control.Palettes, dialog.ColorsControl.Storage);
	control.Area.Size.y												= heightOfField;
	control.Margin.Left												= 3;
	controlText.Align												= ::gpk::ALIGN_CENTER_LEFT; 
	controlText.Text												= text; 
	controlMode.ColorMode											= ::gpk::GUI_COLOR_MODE_DEFAULT; 
	controlMode.UseNewPalettes										= true;
	controlMode.FrameOut											= true;
	controlMode.NoHoverEffect										= true;
	gui.Controls.Constraints[idControl].AttachSizeToControl			= {idControl, -1};
	gui.Controls.Controls	[idParent].Area.Size.y					+= heightOfField;
	return idControl;
}
template<typename _TPoints>
static				::gpk::error_t								dialogCreateFieldArray			(::gpk::SDialog & dialog, _TPoints & fields, int32_t idParent)	{ 
	::gpk::SGUI															& gui							= *dialog.GUI;
	::gpk::view_array<int32_t>											fieldValues						= {((int32_t*)&fields), _TPoints::TRegistry::get_member_count()};
	for(uint32_t iMember = 0; iMember < fieldValues.size(); ++iMember) {
		int32_t																idControl					= fieldValues[iMember] = ::dialogCreateField(dialog, _TPoints::TRegistry::get_names()[iMember], idParent);
		if(iMember)
			gui.Controls.Constraints[idControl].DockToControl.Bottom		= idControl - 1;
	}	
	return 0; 
}
template<typename _TPoints>
static				::gpk::error_t								dialogCreateViewportArray		(::gpk::SDialog & dialog, _TPoints & fields, int32_t idParent)	{ 
	::gpk::SGUI															& gui							= *dialog.GUI;
	::gpk::view_array<int32_t>											fieldValues						= {((int32_t*)&fields), _TPoints::TRegistry::get_member_count()};
	for(uint32_t iMember = 0; iMember < fieldValues.size(); ++iMember) {
		::gpk::ptr_obj<::gpk::SDialogViewport>								viewport;
		int32_t																idDialogControl					= fieldValues[iMember] = ::gpk::viewportCreate(dialog, viewport);
		gui.Controls.Text[viewport->IdTitle].Text						= _TPoints::TRegistry::get_names()[iMember];
		viewport->Settings.DisplacementLockX							= true;
		viewport->Settings.DisplacementLockY							= true;
		if(iMember)
			gui.Controls.Constraints[viewport->IdGUIControl].DockToControl.Bottom	= dialog.Controls[idDialogControl - 1]->IdGUIControl;
		gpk_necall(::gpk::controlSetParent(gui, viewport->IdGUIControl, idParent), "Invalid group id: %i.", idParent); 
	}	
	return 0; 
}
					::gpk::error_t								dialogCreateTuners					(::gpk::SDialog & dialog, int32_t idGroup, ::gpk::view_array<::gpk::ptr_nco<::gpk::SDialogTuner>> tuners)	{
	::gpk::SGUIControlTable												& controlTable						= dialog.GUI->Controls;
	for(uint32_t iField = 0, countFields = controlTable.Children[idGroup].size(); iField < countFields; ++iField) { 
		int32_t																idLabel								= controlTable.Children[idGroup][iField]; 
		gpk_necall(::gpk::tunerCreate(dialog, tuners[iField]), "%s", "????");
		::gpk::SDialogTuner													& tuner								= *tuners[iField];
		tuner.ValueLimits.Min											= 0; 
		tuner.ValueLimits.Max											= 0xFFFFFFFF; 
		int32_t																idControl							= tuners[iField]->IdGUIControl; 
		::gpk::SControl														& control							= controlTable.Controls[idControl]; 
		control.Align													= ::gpk::ALIGN_TOP_RIGHT; 
		control.Area.Size.x												= 100; 
		control.Area.Size.y												= controlTable.Controls[idLabel].Area.Size.y; 
		if(iField) 
			controlTable.Constraints[idControl].DockToControl.Bottom		= tuners[iField - 1]->IdGUIControl; 
		gpk_necall(::gpk::controlSetParent(*dialog.GUI, idControl, idGroup), "Invalid group id: %i.", idGroup); 
	}
	return 0;
}
					::gpk::error_t								dialogCreateCheckBoxes				(::gpk::SDialog & dialog, int32_t idGroup, ::gpk::view_array<::gpk::ptr_nco<::gpk::SDialogCheckBox>> checkboxes)	{
	::gpk::SGUIControlTable												& controlTable						= dialog.GUI->Controls;
	for(uint32_t iField = 0, countFields = controlTable.Children[idGroup].size(); iField < countFields; ++iField) { 
		gpk_necall(::gpk::checkBoxCreate(dialog, checkboxes[iField]), "%s", "????");
		::gpk::SDialogCheckBox												& tuner								= *checkboxes[iField];
		int32_t																idControl							= tuner.IdGUIControl; 
		::gpk::SControl														& control							= controlTable.Controls[idControl]; 
		control.Align													= ::gpk::ALIGN_TOP_RIGHT; 
		int32_t																idLabel								= controlTable.Children[idGroup][iField]; 
		control.Area.Size.y												= controlTable.Controls[idLabel].Area.Size.y; 
		//control.Area.Size.x												= control.Area.Size.y; 
		if(iField) 
			controlTable.Constraints[idControl].DockToControl.Bottom		= checkboxes[iField - 1]->IdGUIControl; 
		gpk_necall(::gpk::controlSetParent(*dialog.GUI, idControl, idGroup), "Invalid group id: %i.", idGroup); 
	}
	return 0;
}
					::gpk::error_t								dialogCreateCharacterEffect			(::gpk::SDialog & dialog, ::gme::SCharacterUIControls & character)	{
	::gpk::SGUI															& gui								= *dialog.GUI;
	::gpk::ptr_obj<::gpk::SDialogViewport>								viewport;
	int32_t																idDialogControl						= ::gpk::viewportCreate(dialog, viewport);
	gui.Controls.Text[viewport->IdTitle].Text						= "Defend Effect";
	viewport->Settings.DisplacementLockX							= true;
	viewport->Settings.DisplacementLockY							= true;
	gpk_necall(::gpk::controlSetParent(gui, viewport->IdGUIControl, character.DialogCharacter), "Invalid group id: %i.", character.DialogCharacter); 
	::gpk::SGUIControlTable												& controlTable						= gui.Controls;
	gpk_necall(::dialogCreateFieldArray(dialog, character.ViewportDefend, controlTable.Children[dialog.Controls[idDialogControl]->IdGUIControl][0]), "%s", "????");	// Create label control array
	// -- Adjust 
	int32_t																idViewport							= idDialogControl;
	dialog.Controls[idViewport].as(viewport);
	::gpk::SCoord2<int16_t>												sizeViewport						= {};
	sizeViewport.x													= 220;
	controlTable.Controls	[viewport->IdGUIControl	].Area.Size		= sizeViewport;
	controlTable.Controls	[viewport->IdGUIControl	].Align			= ::gpk::ALIGN_TOP_RIGHT;
	controlTable.Text		[viewport->IdTitle		].Align			= ::gpk::ALIGN_TOP_LEFT;
	::gpk::viewportFold(*viewport, true);

	::dialogCreateTuners(dialog, viewport->IdClient, character.TunersDefend);
	return idDialogControl;
}
					::gpk::error_t								dialogCreateCharacterStatus			(::gpk::SDialog & dialog, ::gme::SCharacterUIControls & character)	{
	::gpk::SGUI															& gui								= *dialog.GUI;
	::gpk::ptr_obj<::gpk::SDialogViewport>								viewport							= {};
	gui;
	::gme::SCombatStatusGroups											& viewportIds						= character.DialogStatusGroups;
	gpk_necall(::dialogCreateViewportArray(dialog, viewportIds, character.DialogCharacter), "%s", "????");	// Create group control array

	::gpk::SGUIControlTable												& controlTable						= gui.Controls;
	::pcs::SCombatStatusValue											dialogStatLabels					= {};
	for(uint32_t iMember = 0; iMember < ::gme::SCombatStatusGroups::TRegistry::get_member_count(); ++iMember) {
		int32_t																idViewport							= ((int32_t*)&viewportIds)[iMember];
		gpk_necall(::dialogCreateFieldArray(dialog, dialogStatLabels, controlTable.Children[dialog.Controls[idViewport]->IdGUIControl][0]), "%s", "????");	// Create label control array
	}
	// -- Adjust 
	for(uint32_t iMember = 0; iMember < ::gme::SCombatStatusGroups::TRegistry::get_member_count(); ++iMember) {
		::gpk::SCoord2<int16_t>												sizeViewport						= {};
		int32_t																idViewport							= ((int32_t*)&character.DialogStatusGroups)[iMember];
		dialog.Controls[idViewport].as(viewport);
		sizeViewport.x													= 220;
		controlTable.Controls	[viewport->IdGUIControl	].Area.Size		= sizeViewport;
		controlTable.Controls	[viewport->IdGUIControl	].Align			= ::gpk::ALIGN_TOP_RIGHT;
		controlTable.Text		[viewport->IdTitle		].Align			= ::gpk::ALIGN_TOP_LEFT;
		::gpk::viewportFold(*viewport, true);
	}

	// -- Create tuners.
	dialog.Controls[character.DialogStatusGroups.Immunity	].as(viewport); ::dialogCreateCheckBoxes(dialog, viewport->IdClient, character.CheckBoxesImmunity	);
	//dialog.Controls[character.DialogStatusGroups.Immunity	].as(viewport); ::dialogCreateTuners	(dialog, viewport->IdClient, character.TunersImmunity		);
	dialog.Controls[character.DialogStatusGroups.Inflict	].as(viewport); ::dialogCreateTuners	(dialog, viewport->IdClient, character.TunersInflict		);
	dialog.Controls[character.DialogStatusGroups.Resistance	].as(viewport); ::dialogCreateTuners	(dialog, viewport->IdClient, character.TunersResistance		);
	dialog.Controls[character.DialogStatusGroups.Weakness	].as(viewport); ::dialogCreateTuners	(dialog, viewport->IdClient, character.TunersWeakness		);
	return 0;
}
					::gpk::error_t								dialogCreateCharacterPoints			(::gpk::SDialog & dialog, ::gme::SCharacterUIControls & character)	{
	::pcs::SEntityPropertyGroups										& viewportIds						= character.DialogPointsGroups;
	gpk_necall(::dialogCreateViewportArray(dialog, viewportIds, character.DialogCharacter), "%s", "????");	// Create group control array
	::gpk::SGUI															& gui								= *dialog.GUI;
	::gpk::ptr_obj<::gpk::SDialogViewport>								viewport							= {};

	// -- Fix viewport titles
	dialog.Controls[viewportIds.DirectDamageLife	].as(viewport);		gui.Controls.Text[viewport->IdTitle].Text = "Direct Damage (Life)";
	dialog.Controls[viewportIds.DirectDamagePower	].as(viewport);		gui.Controls.Text[viewport->IdTitle].Text = "Direct Damage (Power)";
	dialog.Controls[viewportIds.DrainLife			].as(viewport);		gui.Controls.Text[viewport->IdTitle].Text = "Drain (Life)";
	dialog.Controls[viewportIds.DrainPower			].as(viewport);		gui.Controls.Text[viewport->IdTitle].Text = "Drain (Power)";
	dialog.Controls[viewportIds.RegenLife			].as(viewport);		gui.Controls.Text[viewport->IdTitle].Text = "Regen (Life)";
	dialog.Controls[viewportIds.RegenPower			].as(viewport);		gui.Controls.Text[viewport->IdTitle].Text = "Regen (Power)";
	dialog.Controls[viewportIds.MaxLife				].as(viewport);		gui.Controls.Text[viewport->IdTitle].Text = "Max Life";
	dialog.Controls[viewportIds.MaxPower			].as(viewport);		gui.Controls.Text[viewport->IdTitle].Text = "Max Power";
	dialog.Controls[viewportIds.BonusLife			].as(viewport);		gui.Controls.Text[viewport->IdTitle].Text = "Bonus Life";
	dialog.Controls[viewportIds.BonusPower			].as(viewport);		gui.Controls.Text[viewport->IdTitle].Text = "Bonus Power";

	::gpk::SGUIControlTable												& controlTable						= gui.Controls;
	::pcs::SEntityPropertyPoints										dialogStatLabels					= {};
	dialog.Controls[viewportIds.Life				].as(viewport);		gpk_necall(::dialogCreateFieldArray(dialog, dialogStatLabels.Life				, viewport->IdClient), "%s", "????");	// Create label control array
	dialog.Controls[viewportIds.Power				].as(viewport);		gpk_necall(::dialogCreateFieldArray(dialog, dialogStatLabels.Power				, viewport->IdClient), "%s", "????"); 	// Create label control array
	dialog.Controls[viewportIds.Fitness				].as(viewport);		gpk_necall(::dialogCreateFieldArray(dialog, dialogStatLabels.Fitness			, viewport->IdClient), "%s", "????"); 	// Create label control array
	dialog.Controls[viewportIds.Attack				].as(viewport);		gpk_necall(::dialogCreateFieldArray(dialog, dialogStatLabels.Attack				, viewport->IdClient), "%s", "????"); 	// Create label control array
	dialog.Controls[viewportIds.DirectDamageLife	].as(viewport);		gpk_necall(::dialogCreateFieldArray(dialog, dialogStatLabels.DirectDamageLife	, viewport->IdClient), "%s", "????"); 	// Create label control array
	dialog.Controls[viewportIds.DirectDamagePower	].as(viewport);		gpk_necall(::dialogCreateFieldArray(dialog, dialogStatLabels.DirectDamagePower	, viewport->IdClient), "%s", "????"); 	// Create label control array
	dialog.Controls[viewportIds.DrainLife			].as(viewport);		gpk_necall(::dialogCreateFieldArray(dialog, dialogStatLabels.DrainLife			, viewport->IdClient), "%s", "????"); 	// Create label control array
	dialog.Controls[viewportIds.DrainPower			].as(viewport);		gpk_necall(::dialogCreateFieldArray(dialog, dialogStatLabels.DrainPower			, viewport->IdClient), "%s", "????"); 	// Create label control array
	dialog.Controls[viewportIds.RegenLife			].as(viewport);		gpk_necall(::dialogCreateFieldArray(dialog, dialogStatLabels.RegenLife			, viewport->IdClient), "%s", "????"); 	// Create label control array
	dialog.Controls[viewportIds.RegenPower			].as(viewport);		gpk_necall(::dialogCreateFieldArray(dialog, dialogStatLabels.RegenPower			, viewport->IdClient), "%s", "????"); 	// Create label control array
	dialog.Controls[viewportIds.MaxLife				].as(viewport);		gpk_necall(::dialogCreateFieldArray(dialog, dialogStatLabels.MaxLife			, viewport->IdClient), "%s", "????"); 	// Create label control array
	dialog.Controls[viewportIds.MaxPower			].as(viewport);		gpk_necall(::dialogCreateFieldArray(dialog, dialogStatLabels.MaxPower			, viewport->IdClient), "%s", "????"); 	// Create label control array
	dialog.Controls[viewportIds.BonusLife			].as(viewport);		gpk_necall(::dialogCreateFieldArray(dialog, dialogStatLabels.BonusLife			, viewport->IdClient), "%s", "????"); 	// Create label control array
	dialog.Controls[viewportIds.BonusPower			].as(viewport);		gpk_necall(::dialogCreateFieldArray(dialog, dialogStatLabels.BonusPower			, viewport->IdClient), "%s", "????"); 	// Create label control array

	// Adjust 
	for(uint32_t iMember = 0; iMember < ::pcs::SEntityPropertyGroups::TRegistry::get_member_count(); ++iMember) {
		::gpk::SCoord2<int16_t>												sizeViewport						= {};
		int32_t																idViewport							= ((int32_t*)&character.DialogPointsGroups)[iMember];
		dialog.Controls[idViewport].as(viewport);
		sizeViewport.x													= 220;
		controlTable.Controls	[viewport->IdGUIControl	].Area.Size		= sizeViewport;
		controlTable.Text		[viewport->IdTitle		].Align			= ::gpk::ALIGN_TOP_LEFT;
		::gpk::viewportFold(*viewport, true);
	}

	// Create tuners.
	dialog.Controls[character.DialogPointsGroups.Life				].as(viewport); ::dialogCreateTuners(dialog, viewport->IdClient, character.TunersLife				);
	dialog.Controls[character.DialogPointsGroups.Power				].as(viewport); ::dialogCreateTuners(dialog, viewport->IdClient, character.TunersPower				);
	dialog.Controls[character.DialogPointsGroups.Fitness			].as(viewport); ::dialogCreateTuners(dialog, viewport->IdClient, character.TunersFitness			);
	dialog.Controls[character.DialogPointsGroups.Attack				].as(viewport); ::dialogCreateTuners(dialog, viewport->IdClient, character.TunersAttack				);
	dialog.Controls[character.DialogPointsGroups.DirectDamageLife	].as(viewport); ::dialogCreateTuners(dialog, viewport->IdClient, character.TunersDirectDamageLife	);
	dialog.Controls[character.DialogPointsGroups.DirectDamagePower	].as(viewport); ::dialogCreateTuners(dialog, viewport->IdClient, character.TunersDirectDamagePower	);
	dialog.Controls[character.DialogPointsGroups.DrainLife			].as(viewport); ::dialogCreateTuners(dialog, viewport->IdClient, character.TunersDrainLife			);
	dialog.Controls[character.DialogPointsGroups.DrainPower			].as(viewport); ::dialogCreateTuners(dialog, viewport->IdClient, character.TunersDrainPower			);
	dialog.Controls[character.DialogPointsGroups.RegenLife			].as(viewport); ::dialogCreateTuners(dialog, viewport->IdClient, character.TunersRegenLife			);
	dialog.Controls[character.DialogPointsGroups.RegenPower			].as(viewport); ::dialogCreateTuners(dialog, viewport->IdClient, character.TunersRegenPower			);
	dialog.Controls[character.DialogPointsGroups.MaxLife			].as(viewport); ::dialogCreateTuners(dialog, viewport->IdClient, character.TunersMaxLife			);
	dialog.Controls[character.DialogPointsGroups.MaxPower			].as(viewport); ::dialogCreateTuners(dialog, viewport->IdClient, character.TunersMaxPower			);
	dialog.Controls[character.DialogPointsGroups.BonusLife			].as(viewport); ::dialogCreateTuners(dialog, viewport->IdClient, character.TunersBonusLife			);
	dialog.Controls[character.DialogPointsGroups.BonusPower			].as(viewport); ::dialogCreateTuners(dialog, viewport->IdClient, character.TunersBonusPower			);
	return 0;
}
					::gpk::error_t								gme::dialogCreateCharacter			(::gpk::SDialog & dialog, ::gme::SCharacterUIControls & character)	{
	::gpk::SGUI															& gui								= *dialog.GUI;
	::gpk::ptr_obj<::gpk::SDialogViewport>								viewport							= {};
	character.ViewportCharacter										= ::gpk::viewportCreate(dialog, viewport);
	character.DialogCharacter										= viewport->IdClient;//::gpk::controlCreate(gui); 
	::gpk::SControl														& controlCharacter					= gui.Controls.Controls[viewport->IdGUIControl];
	controlCharacter.Area.Size.x									= 440;
	controlCharacter.Area.Size.y									= 2;
	gui.Controls.Text[viewport->IdTitle].Text						= "Entity Points";
	::gpk::viewportAdjustSize(controlCharacter.Area.Size, controlCharacter.Area.Size);
	::dialogCreateCharacterPoints(dialog, character);
	::dialogCreateCharacterStatus(dialog, character);

	// -- Dock Defend viewport to last Status viewport
	int32_t																idViewportDefend					= ::dialogCreateCharacterEffect(dialog, character);
	dialog.Controls[idViewportDefend].as(viewport);
	gui.Controls.Constraints[viewport->IdGUIControl].DockToControl.Bottom	= dialog.Controls[character.DialogStatusGroups.Weakness]->IdGUIControl;

	dialog.Controls[character.ViewportCharacter].as(viewport);
	::gpk::viewportFold(*viewport, true);
	return 0;
}
