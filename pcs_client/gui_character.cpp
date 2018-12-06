#include "application.h"

template<typename _TPoints>
static	::gpk::error_t											guiCreateFieldArray				(::gpk::SGUI & gui, _TPoints & fields, int32_t idParent)	{ 
	auto																members							= _TPoints::get_member_registry();
	gui.Controls.Controls	[idParent].Area.Size.y					= 24;
	for(uint32_t iMember = 0, countMembers = members.get_member_count(); iMember < countMembers; ++iMember) {
		int32_t																idControl						= ::gpk::controlCreateChild(gui, idParent);
		((int32_t*)&fields)[iMember]									= idControl; 
		gui.Controls.Text		[idControl].Text						= members.get_names()[iMember]; //= {00, 0};
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

	auto																& constraints					= gui.Controls.Constraints;
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
	gui.Controls.States		[character.DialogCharacter].Design		= true;
	gui.Controls.Controls	[character.DialogCharacter].Border		= gui.Controls.Controls[character.DialogCharacter].Margin = {};

	gpk_necall(::guiCreateFieldArray	(gui, character.DialogStatGroups, character.DialogCharacter	), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray	(gui, character.Life	, character.DialogStatGroups.Life	), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray	(gui, character.Power	, character.DialogStatGroups.Power	), "%s", "????"); 
	gpk_necall(::guiCreateFieldArray	(gui, character.Fitness	, character.DialogStatGroups.Fitness), "%s", "????"); 
	gpk_necall(::guiCreateFieldsAttack	(gui, character.Attack	, character.DialogStatGroups.Attack	), "%s", "????"); 

	gui.Controls.Controls[character.DialogCharacter].Area.Size.y	= 0;
	for(uint32_t iChild = 0; iChild < gui.Controls.Children[character.DialogCharacter].size(); ++iChild)
		gui.Controls.Controls[character.DialogCharacter].Area.Size.y	+= gui.Controls.Controls[gui.Controls.Children[character.DialogCharacter][iChild]].Area.Size.y;

	typedef		SCharacterPropertyGroups::TRegistry						TGroupMembers;
	for(uint32_t iMember = 0; iMember < TGroupMembers::get_member_count(); ++iMember) {
		int32_t																idControl						= ((int32_t*)&character.DialogStatGroups)[iMember];
		gui.Controls.Text[idControl].Align								= ::gpk::ALIGN_TOP_LEFT;
		gui.Controls.Constraints[idControl].AttachSizeToControl			= {-1, -1};
		gui.Controls.Controls[idControl].Border							= gui.Controls.Controls[idControl].Margin = {};
		gui.Controls.Controls[idControl].Margin.Top						= 4;
		gui.Controls.Controls[idControl].Area.Size.x					= 210;
		::gpk::controlSetParent(gui, idControl, character.DialogCharacter);
	}
	gui.Controls.Constraints[character.DialogStatGroups.Power	].DockToControl.Bottom		= character.DialogStatGroups.Life	;
	gui.Controls.Constraints[character.DialogStatGroups.Fitness	].DockToControl.Bottom		= character.DialogStatGroups.Power	;
	gui.Controls.Constraints[character.DialogStatGroups.Attack	].DockToControl.Bottom		= character.DialogStatGroups.Fitness	;
	return 0;
}
