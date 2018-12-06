#include "application.h"

template<typename _TPoints>
static	::gpk::error_t					guiCreateFieldArray				(::gpk::SGUI & gui, _TPoints & fields, int32_t idParent)	{ 
	auto										members							= _TPoints::get_member_registry();
	for(uint32_t iMember = 0, countMembers = members.get_member_count(); iMember < countMembers; ++iMember) {
		int32_t										idControl						= ::gpk::controlCreateChild(gui, idParent);
		((int32_t*)&fields)[iMember]								= idControl; 
		gui.Controls.Text		[idControl].Text					= members.get_names()[iMember]; //= {00, 0};
		gui.Controls.Modes		[idControl].ColorMode				= ::gpk::GUI_COLOR_MODE_3D; //= {00, 0};
		gui.Controls.Controls	[idControl].Area.Size.y				= 20;
		gui.Controls.Constraints[idControl].AttachSizeToControl		= {idControl, -1};
		if(iMember)
			gui.Controls.Constraints[idControl].DockToControl.Bottom	= idControl - 1;
		else
			gui.Controls.Controls	[idControl].Area.Offset.y		= 20;
	}	
	return 0; 
}

static	::gpk::error_t					guiCreateFieldsAttack			(::gpk::SGUI & gui, ::pcs::SPointsAttackFull	& fields, int32_t idParent)	{ 
	::guiCreateFieldArray(gui, fields.Raw			, idParent); 
	::guiCreateFieldArray(gui, fields.DirectDamage	, idParent); 
	::guiCreateFieldArray(gui, fields.DrainHealth	, idParent); 
	::guiCreateFieldArray(gui, fields.DrainPower	, idParent); 

	gui.Controls.Constraints[fields.DirectDamage.Health	].DockToControl.Bottom	= fields.Raw.Damage			;
	gui.Controls.Constraints[fields.DrainHealth.Health	].DockToControl.Bottom	= fields.DirectDamage.Shield;
	gui.Controls.Constraints[fields.DrainPower.Energy	].DockToControl.Bottom	= fields.DrainHealth.Shield	;

	gui.Controls.Text[fields.DirectDamage.Health		].Text	= "Direct Damage (Health)";
	gui.Controls.Text[fields.DirectDamage.Shield		].Text	= "Direct Damage (Shield)";

	gui.Controls.Text[fields.DrainHealth.Health			].Text	= "Drain (Health) ";
	gui.Controls.Text[fields.DrainHealth.Shield			].Text	= "Drain (Shield) ";

	gui.Controls.Text[fields.DrainPower.Energy			].Text	= "Drain (Energy) ";
	gui.Controls.Text[fields.DrainPower.Mana			].Text	= "Drain (Mana)   ";
	gui.Controls.Text[fields.DrainPower.Stamina			].Text	= "Drain (Stamina)";
	return 0; 
}

static	::gpk::error_t					guiCreateHealth					(::gpk::SGUI & gui, ::gme::SDialogLife			& dialog )		{ dialog.Dialog = ::gpk::controlCreate(gui); gpk_necall(::guiCreateFieldArray	(gui, dialog.Fields, dialog.Dialog), "%s", "????"); return 0; }
static	::gpk::error_t					guiCreatePower					(::gpk::SGUI & gui, ::gme::SDialogPower			& dialog )		{ dialog.Dialog = ::gpk::controlCreate(gui); gpk_necall(::guiCreateFieldArray	(gui, dialog.Fields, dialog.Dialog), "%s", "????"); return 0; }
static	::gpk::error_t					guiCreateFitness				(::gpk::SGUI & gui, ::gme::SDialogFitness		& dialog )		{ dialog.Dialog = ::gpk::controlCreate(gui); gpk_necall(::guiCreateFieldArray	(gui, dialog.Fields, dialog.Dialog), "%s", "????"); return 0; }
static	::gpk::error_t					guiCreateAttack					(::gpk::SGUI & gui, ::gme::SDialogAttack		& dialog )		{ dialog.Dialog = ::gpk::controlCreate(gui); gpk_necall(::guiCreateFieldsAttack	(gui, dialog.Fields, dialog.Dialog), "%s", "????"); return 0; }
		::gpk::error_t					gme::guiCreateCharacter			(::gpk::SGUI & gui, ::gme::SCharacterUIControls	& character	)	{
	character.DialogCharacter				= ::gpk::controlCreate(gui); 
	gui.Controls.Controls[character.DialogCharacter].Border = gui.Controls.Controls[character.DialogCharacter].Margin = {};

	gui.Controls.States[character.DialogCharacter].Design	= true;

	gpk_necall(::guiCreateHealth	(gui, character.Life	), "%s", "????");
	gpk_necall(::guiCreatePower		(gui, character.Power	), "%s", "????");
	gpk_necall(::guiCreateFitness	(gui, character.Fitness	), "%s", "????");
	gpk_necall(::guiCreateAttack	(gui, character.Attack	), "%s", "????");

	gui.Controls.Text[character.Life	.Dialog].Text	= " Health";
	gui.Controls.Text[character.Power	.Dialog].Text	= " Power";
	gui.Controls.Text[character.Fitness	.Dialog].Text	= " Fitness";
	gui.Controls.Text[character.Attack	.Dialog].Text	= " Attack";
	gui.Controls.Text[character.Life	.Dialog].Align	= ::gpk::ALIGN_TOP_LEFT;
	gui.Controls.Text[character.Power	.Dialog].Align	= ::gpk::ALIGN_TOP_LEFT;
	gui.Controls.Text[character.Fitness	.Dialog].Align	= ::gpk::ALIGN_TOP_LEFT;
	gui.Controls.Text[character.Attack	.Dialog].Align	= ::gpk::ALIGN_TOP_LEFT;

	gui.Controls.Controls[character.Life	.Dialog].Border = gui.Controls.Controls[character.Life		.Dialog].Margin = {};
	gui.Controls.Controls[character.Power	.Dialog].Border = gui.Controls.Controls[character.Power		.Dialog].Margin = {};
	gui.Controls.Controls[character.Fitness	.Dialog].Border = gui.Controls.Controls[character.Fitness	.Dialog].Margin = {};
	gui.Controls.Controls[character.Attack	.Dialog].Border = gui.Controls.Controls[character.Attack	.Dialog].Margin = {};
	gui.Controls.Controls[character.Life	.Dialog].Margin.Top = 4;
	gui.Controls.Controls[character.Power	.Dialog].Margin.Top = 4;
	gui.Controls.Controls[character.Fitness	.Dialog].Margin.Top = 4;
	gui.Controls.Controls[character.Attack	.Dialog].Margin.Top = 4;


	::gpk::controlSetParent(gui, character.Life		.Dialog, character.DialogCharacter);
	::gpk::controlSetParent(gui, character.Power	.Dialog, character.DialogCharacter);
	::gpk::controlSetParent(gui, character.Fitness	.Dialog, character.DialogCharacter);
	::gpk::controlSetParent(gui, character.Attack	.Dialog, character.DialogCharacter);

	gui.Controls.Constraints[character.Power	.Dialog].DockToControl.Bottom		= character.Life	.Dialog;
	gui.Controls.Constraints[character.Fitness	.Dialog].DockToControl.Bottom		= character.Power	.Dialog;
	gui.Controls.Constraints[character.Attack	.Dialog].DockToControl.Bottom		= character.Fitness	.Dialog;

	gui.Controls.Controls[character.Life	.Dialog].Area.Size.y		= (int16_t)(4 + 20 * (character.Life	.Fields.get_member_registry().get_member_count() + 1));
	gui.Controls.Controls[character.Power	.Dialog].Area.Size.y		= (int16_t)(4 + 20 * (character.Power	.Fields.get_member_registry().get_member_count() + 1));
	gui.Controls.Controls[character.Fitness	.Dialog].Area.Size.y		= (int16_t)(4 + 20 * (character.Fitness	.Fields.get_member_registry().get_member_count() + 1));
	gui.Controls.Controls[character.Attack	.Dialog].Area.Size.y		= (int16_t)
		( 20 * ::pcs::SPointsAttackRaw::get_member_registry().get_member_count()
		+ 20 * character.Life	.Fields.get_member_registry().get_member_count()
		+ 20 * character.Life	.Fields.get_member_registry().get_member_count()
		+ 20 * character.Power	.Fields.get_member_registry().get_member_count()
		+ 20 + 4
		);
	gui.Controls.Controls[character.DialogCharacter].Area.Size.y  = 0;
	for(uint32_t iChild = 0; iChild < gui.Controls.Children[character.DialogCharacter].size(); ++iChild)
		gui.Controls.Controls[character.DialogCharacter].Area.Size.y	+= gui.Controls.Controls[gui.Controls.Children[character.DialogCharacter][iChild]].Area.Size.y;

	for(int32_t iControl = character.DialogCharacter + 1; iControl < (int32_t)gui.Controls.Controls.size(); ++iControl) 
		gui.Controls.Controls[iControl].Area.Size.x						= 210;
	return 0;
}
