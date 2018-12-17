#include "application.h"

static constexpr	const uint16_t								heightOfField					= 20;

static				::gpk::error_t								guiCreateField					(::gpk::SDialog & dialog, const ::gpk::view_const_string& text, int32_t idParent)	{ 
	::gpk::SGUI															& gui							= *dialog.GUI;
	int32_t																idControl						= ::gpk::controlCreateChild(gui, idParent);
	gui.Controls.Text		[idControl].Align						= ::gpk::ALIGN_CENTER_LEFT; 
	gui.Controls.Text		[idControl].Text						= text; 
	gui.Controls.Modes		[idControl].ColorMode					= ::gpk::GUI_COLOR_MODE_3D; 
	gui.Controls.Modes		[idControl].UseNewPalettes				= true;
	gui.Controls.Constraints[idControl].AttachSizeToControl			= {idControl, -1};
	gui.Controls.Controls	[idControl].Area.Size.y					= heightOfField;
	gui.Controls.Controls	[idControl].Margin						= {3, 2, 0, 0};
	gui.Controls.Controls	[idParent].Area.Size.y					+= heightOfField;
	::gpk::memcpy_s(gui.Controls.Controls[idControl].Palettes, dialog.ColorsControl);
	return idControl;
}

template<typename _TPoints>
static				::gpk::error_t								guiCreateFieldArray				(::gpk::SDialog & dialog, _TPoints & fields, int32_t idParent)	{ 
	::gpk::SGUI															& gui							= *dialog.GUI;
	::gpk::view_array<int32_t>											fieldValues						= {((int32_t*)&fields), _TPoints::TRegistry::get_member_count()};
	for(uint32_t iMember = 0; iMember < fieldValues.size(); ++iMember) {
		int32_t																idControl					= fieldValues[iMember] = guiCreateField(dialog, _TPoints::TRegistry::get_names()[iMember], idParent);
	if(iMember)
		gui.Controls.Constraints[idControl].DockToControl.Bottom		= idControl - 1;
	}	
	return 0; 
}

					::gpk::error_t								dialogCreateTuners					(::gpk::SDialog & dialog, int32_t idGroup, ::gpk::view_array<::gpk::ptr_nco<::gpk::SDialogTuner>> tuners)	{
	::gpk::SGUIControlTable												& controlTable						= dialog.GUI->Controls;
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
		//else 
		//	control.Area.Offset.y											= control.Area.Size.y;
		gpk_necall(::gpk::controlSetParent(*dialog.GUI, idControl, idGroup), "Invalid group id: %i.", idGroup); 
	}
	return 0;
}

					::gpk::error_t								gme::dialogCreateCharacter			(::gpk::SDialog & dialog, ::gme::SCharacterUIControls & character, const ::gme::SGameUIPalettes & palettes)	{
	::gpk::SGUI															& gui								= *dialog.GUI;

	character.DialogCharacter										= ::gpk::controlCreate(gui); 
	{
		::gpk::SControl														& controlCharacter					= gui.Controls.Controls[character.DialogCharacter];
		gui.Controls.States[character.DialogCharacter].Design			= false;
		controlCharacter.Border = controlCharacter.Margin				= {};
		controlCharacter.Area.Size.x									= 220;
	}

	gpk_necall(::guiCreateFieldArray(dialog, character.DialogStatGroups			, character.DialogCharacter						), "%s", "????");	// Create group control array
	// -- Fix group titles
	gui.Controls.Text[character.DialogStatGroups.DirectDamageLife	].Text	= "Direct Damage (Life)";
	gui.Controls.Text[character.DialogStatGroups.DirectDamagePower	].Text	= "Direct Damage (Power)";
	gui.Controls.Text[character.DialogStatGroups.DrainLife			].Text	= "Drain (Life)";
	gui.Controls.Text[character.DialogStatGroups.DrainPower			].Text	= "Drain (Power)";

	for(uint32_t iMember = 0; iMember < ::gme::SEntityPropertyGroups::TRegistry::get_member_count(); ++iMember) {	// For each section
		int32_t																idSection							= ((int32_t*)&character.DialogStatGroups)[iMember];
		{ // Create field group
			int32_t																idControl							= ::guiCreateField(dialog, "", idSection);
			gpk_necall(((int32_t*)&character.DialogStatGroupFrames)[iMember] = idControl, "%s", "????");	// Create group control array
			gui.Controls.Controls	[idControl].Area.Offset					= {0, heightOfField + 2};
			gui.Controls.Controls	[idControl].Area.Size					= {0, 2};
			gui.Controls.Controls	[idControl].Border						= {1, 1, 1, 1};
			gui.Controls.Controls	[idControl].Margin						= {};
			gui.Controls.States		[idControl].Frame						= true;
			gui.Controls.Modes		[idControl].ColorMode					= ::gpk::GUI_COLOR_MODE_3D;
			gui.Controls.Text		[idControl].Text						= gui.Controls.Text[idSection].Text;
			::gpk::memcpy_s(gui.Controls.Controls	[idControl].Palettes, palettes.PaletteFields.Storage);
			::gpk::memcpy_s(gui.Controls.Controls	[idSection].Palettes, palettes.PaletteFields.Storage);
		}
		{ // Create section title
			int32_t																idControl							= ::guiCreateField(dialog, "", idSection);
			gpk_necall(((int32_t*)&character.DialogStatGroupLabels)[iMember] = idControl, "%s", "????");	// Create group control array
			gui.Controls.Controls	[idControl].Area.Offset					= {};
			gui.Controls.Controls	[idControl].Area.Size					= {0, heightOfField};
			gui.Controls.Controls	[idControl].Border						= {1, 1, 1, 1};
			gui.Controls.Controls	[idControl].Margin						= {4, 1, 1, 1};
			gui.Controls.Text		[idControl].Text						= gui.Controls.Text[idSection].Text;
			gui.Controls.States		[idControl].Frame						= true;
			gui.Controls.Modes		[idControl].ColorMode					= ::gpk::GUI_COLOR_MODE_3D;
			::gpk::memcpy_s(gui.Controls.Controls	[idControl].Palettes, palettes.PaletteTitles.Storage);
		}
	}


	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsLife				, character.DialogStatGroupFrames.Life				), "%s", "????");	// Create label control array
	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsPower				, character.DialogStatGroupFrames.Power				), "%s", "????"); 	// Create label control array
	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsFitness			, character.DialogStatGroupFrames.Fitness			), "%s", "????"); 	// Create label control array
	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsAttack				, character.DialogStatGroupFrames.Attack			), "%s", "????"); 	// Create label control array
	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsDirectDamageLife	, character.DialogStatGroupFrames.DirectDamageLife	), "%s", "????"); 	// Create label control array
	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsDirectDamagePower	, character.DialogStatGroupFrames.DirectDamagePower	), "%s", "????"); 	// Create label control array
	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsDrainLife			, character.DialogStatGroupFrames.DrainLife			), "%s", "????"); 	// Create label control array
	gpk_necall(::guiCreateFieldArray(dialog, character.LabelsDrainPower			, character.DialogStatGroupFrames.DrainPower		), "%s", "????"); 	// Create label control array
	for(uint32_t iMember = 0; iMember < ::gme::SEntityPropertyGroups::TRegistry::get_member_count(); ++iMember) {
		int32_t																idSection							= ((int32_t*)&character.DialogStatGroups)[iMember];
		int32_t																idGroup								= gui.Controls.Children[idSection][0];
		int32_t																idLabel								= gui.Controls.Children[idSection][1];
		const ::gpk::SCoord2<int16_t>										groupSize							= gui.Controls.Controls[idGroup].Area.Size + gui.Controls.Controls[idLabel].Area.Size;
		gui.Controls.Controls[idSection].Area.Size						= {groupSize.x, groupSize.y + 6};
		gui.Controls.Controls[idSection].Margin							= {1, 1, 1, 1};
		const ::gpk::array_pod<int32_t>										& characterChildGroups				= gui.Controls.Children[idGroup];
		for(uint32_t iChild = 0; iChild < characterChildGroups.size(); ++iChild)	// Set palette to field labels
			::gpk::memcpy_s(gui.Controls.Controls[gui.Controls.Children[idGroup][iChild]].Palettes, palettes.PaletteFields.Storage);
	}

	// Create tuners.
	::dialogCreateTuners(dialog, character.DialogStatGroupFrames.Life				, character.TunersLife				);
	::dialogCreateTuners(dialog, character.DialogStatGroupFrames.Power				, character.TunersPower				);
	::dialogCreateTuners(dialog, character.DialogStatGroupFrames.Fitness			, character.TunersFitness			);
	::dialogCreateTuners(dialog, character.DialogStatGroupFrames.Attack				, character.TunersAttack			);
	::dialogCreateTuners(dialog, character.DialogStatGroupFrames.DirectDamageLife	, character.TunersDirectDamageLife	);
	::dialogCreateTuners(dialog, character.DialogStatGroupFrames.DirectDamagePower	, character.TunersDirectDamagePower	);
	::dialogCreateTuners(dialog, character.DialogStatGroupFrames.DrainLife			, character.TunersDrainLife			);
	::dialogCreateTuners(dialog, character.DialogStatGroupFrames.DrainPower			, character.TunersDrainPower		);
	return 0;
}
