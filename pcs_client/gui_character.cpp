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
		gui.Controls.Controls	[idControl].Margin						= {2, 2, 2, 2};
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
		::gpk::tunerCreate(dialog, tuners[iField]); 
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
		::gpk::controlSetParent(dialog.GUI, idControl, idGroup); 
	}
	return 0;
}

					::gpk::error_t								gme::dialogCreateCharacter			(::gpk::SDialog & dialog, ::gme::SCharacterUIControls	& character	)	{
	::gpk::SGUI															& gui								= dialog.GUI;
	character.DialogCharacter										= ::gpk::controlCreate(gui); 
	{
		::gpk::SControl														& controlCharacter					= gui.Controls.Controls[character.DialogCharacter];
		gui.Controls.States[character.DialogCharacter].Design			= false;
		::gpk::memcpy_s(gui.Controls.Controls[character.DialogCharacter].Palettes, gui.DefaultColors);
		controlCharacter.Border = controlCharacter.Margin				= {};
		controlCharacter.Area.Size.x									= 320;
	}
	gpk_necall(::guiCreateFieldArray(dialog, character.DialogStatGroups		, character.DialogCharacter	), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray(dialog, character.Life					, character.DialogStatGroups.Life				), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray(dialog, character.Power				, character.DialogStatGroups.Power				), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray(dialog, character.Fitness				, character.DialogStatGroups.Fitness			), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray(dialog, character.Attack				, character.DialogStatGroups.Attack				), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray(dialog, character.DirectDamageLife		, character.DialogStatGroups.DirectDamageLife	), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray(dialog, character.DirectDamagePower	, character.DialogStatGroups.DirectDamagePower	), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray(dialog, character.DrainLife			, character.DialogStatGroups.DrainLife			), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray(dialog, character.DrainPower			, character.DialogStatGroups.DrainPower			), "%s", "????"); 

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
			constraints[idControl].AttachSizeToControl						= {-1, -1};
			controlGroup.Area.Size.x										= 320; //210;
			controlGroup.Area.Offset										= {};
			controlGroup.Border	/*= controlGroup.Margin*/					= {};
			controlGroup.Margin.Top											= 4;
			if(iChild)
				constraints[idControl].DockToControl.Bottom						= characterChildGroups[iChild - 1];
			const ::gpk::array_pod<int32_t>										& childFields					= gui.Controls.Children[idControl];
			for(uint32_t iChildField = 0; iChildField < childFields.size(); ++iChildField) {
				int32_t																idField							= childFields[iChildField];
				constraints[idField].AttachSizeToControl						= {-1, -1};
				gui.Controls.Controls[idField].Area.Size.x						= 210;
			}
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
