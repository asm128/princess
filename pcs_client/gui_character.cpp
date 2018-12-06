#include "application.h"

template<typename _TPoints>
static	::gpk::error_t											guiCreateFieldArray				(::gpk::SGUI & gui, _TPoints & fields, int32_t idParent)	{ 
	gui.Controls.Controls	[idParent].Area.Size.y					= 24;
	::gpk::view_array<int32_t>											fieldValues						= {((int32_t*)&fields), _TPoints::TRegistry::get_member_count()};
	for(uint32_t iMember = 0; iMember < fieldValues.size(); ++iMember) {
		int32_t																idControl						= ::gpk::controlCreateChild(gui, idParent);
		fieldValues[iMember]											= idControl; 
		gui.Controls.Text		[idControl].Align						= ::gpk::ALIGN_CENTER_LEFT; //= {00, 0};
		gui.Controls.Text		[idControl].Text						= _TPoints::TRegistry::get_names()[iMember]; //= {00, 0};
		gui.Controls.Modes		[idControl].ColorMode					= ::gpk::GUI_COLOR_MODE_3D; //= {00, 0};
		gui.Controls.Constraints[idControl].AttachSizeToControl			= {idControl, -1};
		gui.Controls.Controls	[idControl].Area.Size.y					= 20;
		gui.Controls.Controls	[idParent].Area.Size.y					+= 20;
		if(iMember)
			gui.Controls.Constraints[idControl].DockToControl.Bottom		= idControl - 1;
		else
			gui.Controls.Controls	[idControl].Area.Offset.y				= 20;
	}	
	return 0; 
}

static	::gpk::error_t											guiCreateFieldsAttack			(::gpk::SGUI & gui, ::pcs::SPointsAttackFull	& fields, int32_t idParent)	{ 
	::guiCreateFieldArray(gui, fields.Raw			, idParent); 
	::guiCreateFieldArray(gui, fields.DirectDamage	, idParent); 
	::guiCreateFieldArray(gui, fields.DrainHealth	, idParent); 
	::guiCreateFieldArray(gui, fields.DrainPower	, idParent); 

	::gpk::array_pod<::gpk::SControlConstraints>						& constraints					= gui.Controls.Constraints;
	constraints[fields.DirectDamage.Health	].DockToControl.Bottom	= fields.Raw.Damage			;
	constraints[fields.DrainHealth.Health	].DockToControl.Bottom	= fields.DirectDamage.Shield;
	constraints[fields.DrainPower.Energy	].DockToControl.Bottom	= fields.DrainHealth.Shield	;

	gui.Controls.Text[fields.DirectDamage.Health		].Text		= "Direct Damage (Health)";
	gui.Controls.Text[fields.DirectDamage.Shield		].Text		= "Direct Damage (Shield)";

	gui.Controls.Text[fields.DrainHealth.Health			].Text		= "Drain (Health) ";
	gui.Controls.Text[fields.DrainHealth.Shield			].Text		= "Drain (Shield) ";

	gui.Controls.Text[fields.DrainPower.Energy			].Text		= "Drain (Energy) ";
	gui.Controls.Text[fields.DrainPower.Mana			].Text		= "Drain (Mana)   ";
	gui.Controls.Text[fields.DrainPower.Stamina			].Text		= "Drain (Stamina)";
	return 0; 
}

		::gpk::error_t											gme::guiCreateCharacter			(::gpk::SGUI & gui, ::gme::SCharacterUIControls	& character	)	{
	character.DialogCharacter										= ::gpk::controlCreate(gui); 
	{
		::gpk::SControl														& controlCharacter				= gui.Controls.Controls[character.DialogCharacter];
		gui.Controls.States[character.DialogCharacter].Design			= true;
		controlCharacter.Border		= controlCharacter.Margin			= {};
	}
	gpk_necall(::guiCreateFieldArray	(gui, character.DialogStatGroups, character.DialogCharacter	), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray	(gui, character.Life	, character.DialogStatGroups.Life	), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray	(gui, character.Power	, character.DialogStatGroups.Power	), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray	(gui, character.Fitness	, character.DialogStatGroups.Fitness), "%s", "????"); 
	gpk_necall(::guiCreateFieldsAttack	(gui, character.Attack	, character.DialogStatGroups.Attack	), "%s", "????"); 
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
	typedef		SCharacterPropertyGroups::TRegistry						TGroupMembers;
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
		::gpk::controlSetParent(gui, idControl, character.DialogCharacter);
	}
	return 0;
}
