#include "application.h"

template<typename _TPoints>
static	::gpk::error_t												guiCreateFieldArray			(::gpk::SGUI & gui, _TPoints & fields, int32_t idParent)	{ 
	auto																	members						= 	_TPoints::get_member_registry();
	for(uint32_t iMember = 0, countMembers = members.get_member_count(); iMember < countMembers; ++iMember) {
		int32_t																idControl					= (-1 == idParent) ? ::gpk::controlCreateChild(gui, idParent) : ::gpk::controlCreate(gui);
		((int32_t*)&fields)[iMember]									= idControl; 
		gui.Controls.Text		[idControl].Text						= members.get_names()[iMember]; //= {00, 0};
		gui.Controls.Modes		[idControl].ColorMode					= ::gpk::GUI_COLOR_MODE_3D; //= {00, 0};
		gui.Controls.Controls	[idControl].Area.Size.y					= 20;
		gui.Controls.Constraints[idControl].AttachSizeToControl			= {idControl, -1};
		if(iMember)
			gui.Controls.Constraints[idControl].DockToControl.Bottom		= idControl - 1;
		else
			gui.Controls.Controls	[idControl].Area.Offset.y				= 20;
	}	
	return 0; 
}

static	::gpk::error_t												guiCreateFieldsAttack				(::gpk::SGUI & gui, ::pcs::SPointsAttackFull	& fields, int32_t idParent)	{ 
	::guiCreateFieldArray(gui, fields.Raw			, idParent); 
	::guiCreateFieldArray(gui, fields.DirectDamage	, idParent); 
	::guiCreateFieldArray(gui, fields.DrainHealth	, idParent); 
	::guiCreateFieldArray(gui, fields.DrainPower	, idParent); 

	auto																	& constraints						= gui.Controls.Constraints;
	constraints[fields.DirectDamage.Health	].DockToControl.Bottom		= fields.Raw.Damage;
	constraints[fields.DrainHealth.Health	].DockToControl.Bottom		= fields.DirectDamage	.Shield;
	constraints[fields.DrainPower.Energy	].DockToControl.Bottom		= fields.DrainHealth	.Shield;

	gui.Controls.Text[fields.DirectDamage.Health		].Text			= "Direct Damage (Health)";
	gui.Controls.Text[fields.DirectDamage.Shield		].Text			= "Direct Damage (Shield)";
	gui.Controls.Text[fields.DrainHealth.Health			].Text			= "Drain (Health) ";
	gui.Controls.Text[fields.DrainHealth.Shield			].Text			= "Drain (Shield) ";
	gui.Controls.Text[fields.DrainPower.Energy			].Text			= "Drain (Energy) ";
	gui.Controls.Text[fields.DrainPower.Mana			].Text			= "Drain (Mana)   ";
	gui.Controls.Text[fields.DrainPower.Stamina			].Text			= "Drain (Stamina)";
	return 0; 
}

		::gpk::error_t												gme::guiCreateCharacter			(::gpk::SGUI & gui, ::gme::SCharacterUIControls	& character	)	{
	character.DialogCharacter											= ::gpk::controlCreate(gui); 
	gui.Controls.Controls	[character.DialogCharacter].Border			= ///{1, 1, 1, 1};
	gui.Controls.Controls	[character.DialogCharacter].Margin			= {};
	gui.Controls.Controls	[character.DialogCharacter].Area.Offset		= {};
	gui.Controls.Modes		[character.DialogCharacter].ColorMode		= ::gpk::GUI_COLOR_MODE_3D;
	::gme::SCharacterDialogs												& characterDialogs				= character.DialogPoints;
	gpk_necall(::guiCreateFieldArray(gui, characterDialogs, character.DialogCharacter), "%s", "????"); 

	gui.Controls.States[character.DialogCharacter].Design				= false;

	gpk_necall(::guiCreateFieldArray	(gui, character.Life	, characterDialogs.Life		), "%s", "????");
	gpk_necall(::guiCreateFieldArray	(gui, character.Power	, characterDialogs.Power	), "%s", "????");
	gpk_necall(::guiCreateFieldArray	(gui, character.Fitness	, characterDialogs.Fitness	), "%s", "????");
	gpk_necall(::guiCreateFieldsAttack	(gui, character.Attack	, characterDialogs.Attack	), "%s", "????"); 

	auto																	& constraints						= gui.Controls.Constraints;
	constraints[characterDialogs.Power		].DockToControl.Bottom		= characterDialogs.Life	;
	constraints[characterDialogs.Fitness	].DockToControl.Bottom		= characterDialogs.Power	;
	constraints[characterDialogs.Attack		].DockToControl.Bottom		= characterDialogs.Fitness;

	gui.Controls.Controls[characterDialogs.Life		].Area.Size.y		= (int16_t)(4 + 20 * (character.Life	.get_member_registry().get_member_count() + 1));
	gui.Controls.Controls[characterDialogs.Power	].Area.Size.y		= (int16_t)(4 + 20 * (character.Power	.get_member_registry().get_member_count() + 1));
	gui.Controls.Controls[characterDialogs.Fitness	].Area.Size.y		= (int16_t)(4 + 20 * (character.Fitness	.get_member_registry().get_member_count() + 1));
	gui.Controls.Controls[characterDialogs.Attack	].Area.Size.y		= (int16_t)
		( 20 * ::pcs::SPointsAttackRaw::get_member_registry().get_member_count()
		+ 20 * character.Life	.get_member_registry().get_member_count()
		+ 20 * character.Life	.get_member_registry().get_member_count()
		+ 20 * character.Power	.get_member_registry().get_member_count()
		+ 20 + 4
		);
	gui.Controls.Controls[character.DialogCharacter].Area.Size.y		= 0;
	for(uint32_t iChild = 0; iChild < gui.Controls.Children[character.DialogCharacter].size(); ++iChild) {
		int32_t																	idControlChild				= gui.Controls.Children[character.DialogCharacter][iChild];
		::gpk::controlSetParent(gui, idControlChild, character.DialogCharacter);
		::gpk::SControl															& control					= gui.Controls.Controls[idControlChild];
		control.Area.Size.x													= 210;
		control.Border														= control.Margin = {};
		control.Area.Offset													= {};
		control.Margin.Top													= 4;
		gui.Controls.Text		[idControlChild].Align						= ::gpk::ALIGN_TOP_LEFT;
		gui.Controls.Constraints[idControlChild].AttachSizeToControl		= {-1, -1};
		gui.Controls.Controls	[character.DialogCharacter].Area.Size.y		+= control.Area.Size.y;
	}
	return 0;
}
