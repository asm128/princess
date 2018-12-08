#include "application.h"

static constexpr	const uint16_t								heightOfField					= 20;

template<typename _TPoints>
static				::gpk::error_t								guiCreateFieldArray				(::gpk::SGUI & gui, _TPoints & fields, int32_t idParent)	{ 
	gui.Controls.Controls	[idParent].Area.Size.y					= heightOfField + 4;
	::gpk::view_array<int32_t>											fieldValues						= {((int32_t*)&fields), _TPoints::TRegistry::get_member_count()};
	for(uint32_t iMember = 0; iMember < fieldValues.size(); ++iMember) {
		int32_t																idControl						= ::gpk::controlCreateChild(gui, idParent);
		fieldValues[iMember]											= idControl; 
		gui.Controls.Text		[idControl].Align						= ::gpk::ALIGN_CENTER_LEFT; //= {00, 0};
		gui.Controls.Text		[idControl].Text						= _TPoints::TRegistry::get_names()[iMember]; //= {00, 0};
		gui.Controls.Modes		[idControl].ColorMode					= ::gpk::GUI_COLOR_MODE_3D; //= {00, 0};
		//gui.Controls.Modes		[idControl].UseNewPalettes				= true;
		gui.Controls.Constraints[idControl].AttachSizeToControl			= {idControl, -1};
		gui.Controls.Controls	[idControl].Area.Size.y					= heightOfField;
		gui.Controls.Controls	[idParent].Area.Size.y					+= heightOfField;
		if(iMember)
			gui.Controls.Constraints[idControl].DockToControl.Bottom		= idControl - 1;
		else
			gui.Controls.Controls	[idControl].Area.Offset.y				= heightOfField;
	}	
	return 0; 
}

					::gpk::error_t								gme::guiCreateCharacter			(::gpk::SGUI & gui, ::gme::SCharacterUIControls	& character	)	{
	character.DialogCharacter										= ::gpk::controlCreate(gui); 
	{
		::gpk::SControl														& controlCharacter				= gui.Controls.Controls[character.DialogCharacter];
		gui.Controls.States[character.DialogCharacter].Design			= true;
		::gpk::memcpy_s(gui.Controls.Controls[character.DialogCharacter].Palettes, gui.DefaultColors);
		controlCharacter.Border		= controlCharacter.Margin			= {};
	}
	gpk_necall(::guiCreateFieldArray	(gui, character.DialogStatGroups, character.DialogCharacter	), "%s", "????"); 
	gui.Controls.Text[character.DialogStatGroups.DirectDamageLife	].Text	= "Direct Damage (Life)";
	gui.Controls.Text[character.DialogStatGroups.DirectDamagePower	].Text	= "Direct Damage (Power)";
	gui.Controls.Text[character.DialogStatGroups.DrainLife			].Text	= "Drain (Life)";
	gui.Controls.Text[character.DialogStatGroups.DrainPower			].Text	= "Drain (Power)";
	gpk_necall(::guiCreateFieldArray	(gui, character.Life				, character.DialogStatGroups.Life	), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray	(gui, character.Power				, character.DialogStatGroups.Power	), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray	(gui, character.Fitness				, character.DialogStatGroups.Fitness), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray	(gui, character.Attack				, character.DialogStatGroups.Attack	), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray	(gui, character.DirectDamageLife	, character.DialogStatGroups.DirectDamageLife	), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray	(gui, character.DirectDamagePower	, character.DialogStatGroups.DirectDamagePower	), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray	(gui, character.DrainLife			, character.DialogStatGroups.DrainLife			), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray	(gui, character.DrainPower			, character.DialogStatGroups.DrainPower			), "%s", "????"); 
	{
		auto																& constraints					= gui.Controls.Constraints;
		::gpk::SControl														& controlCharacter				= gui.Controls.Controls[character.DialogCharacter];
		const ::gpk::array_pod<int32_t>										& characterChildSections		= gui.Controls.Children[character.DialogCharacter];
		controlCharacter.Area.Size.y									= 0;
		for(uint32_t iChild = 0; iChild < characterChildSections.size(); ++iChild) {
			int32_t																idControlChild					= characterChildSections[iChild];
			controlCharacter.Area.Size.y									+= gui.Controls.Controls[idControlChild].Area.Size.y;
			if(iChild)
				constraints[idControlChild].DockToControl.Bottom				= characterChildSections[iChild - 1];
		}
	}
	typedef	SCharacterPropertyGroups::TRegistry							TGroupMembers;
	::gpk::view_array<int32_t>											fieldValues						= {((int32_t*)&character.DialogStatGroups), TGroupMembers::get_member_count()};
	for(uint32_t iMember = 0; iMember < fieldValues.size(); ++iMember) {
		int32_t																idControl						= fieldValues[iMember];
		::gpk::SControl														& controlSection				= gui.Controls.Controls[idControl];
		gui.Controls.Text[idControl].Align								= ::gpk::ALIGN_TOP_LEFT;
		auto																& constraints					= gui.Controls.Constraints;
		constraints[idControl].AttachSizeToControl						= {-1, -1};
		controlSection.Border	= controlSection.Margin					= {};
		controlSection.Margin.Top										= 4;
		controlSection.Area.Size.x										= 210;
	}
	return 0;
}
