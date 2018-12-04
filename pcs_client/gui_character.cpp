#include "application.h"

static	::gpk::error_t					guiCreateFieldsHealth		(::gpk::SGUI & gui, ::pcs::SPointsHealth	& fields, int32_t idParent)	{ 
	fields.Health							= ::gpk::controlCreateChild(gui, idParent); 
	fields.Shield							= ::gpk::controlCreateChild(gui, idParent); 
	gui.Controls.Constraints[fields.Shield	].DockToControl.Bottom	= fields.Health;

	gui.Controls.Constraints[fields.Health	].AttachSizeToControl	= {fields.Health	, -1};
	gui.Controls.Constraints[fields.Shield	].AttachSizeToControl	= {fields.Shield	, -1};

	gui.Controls.Text[fields.Health].Text	= "Health"; //= {00, 0};
	gui.Controls.Text[fields.Shield].Text	= "Shield"; //= {20, 0};
	return 0; 
}

static	::gpk::error_t					guiCreateFieldsPower				(::gpk::SGUI & gui, ::pcs::SPointsPower		& fields, int32_t idParent)	{ 
	fields.Energy							= ::gpk::controlCreateChild(gui, idParent); 
	fields.Mana								= ::gpk::controlCreateChild(gui, idParent); 
	fields.Stamina							= ::gpk::controlCreateChild(gui, idParent); 
	gui.Controls.Constraints[fields.Mana	].DockToControl.Bottom	= fields.Energy;
	gui.Controls.Constraints[fields.Stamina	].DockToControl.Bottom	= fields.Mana;

	gui.Controls.Constraints[fields.Energy	].AttachSizeToControl	= {fields.Energy	, -1};
	gui.Controls.Constraints[fields.Mana	].AttachSizeToControl	= {fields.Mana		, -1};
	gui.Controls.Constraints[fields.Stamina	].AttachSizeToControl	= {fields.Stamina	, -1};

	gui.Controls.Text[fields.Energy					].Text	= "Energy"		; //= {20, 0};
	gui.Controls.Text[fields.Mana					].Text	= "Mana"		; //= {40, 0};
	gui.Controls.Text[fields.Stamina				].Text	= "Stamina"		; //= {60, 0};
	return 0; 
}

static	::gpk::error_t					guiCreateFieldsFitness			(::gpk::SGUI & gui, ::pcs::SPointsFitness	& fields, int32_t idParent)	{ 
	fields.Attack							= ::gpk::controlCreateChild(gui, idParent); 
	fields.Movement							= ::gpk::controlCreateChild(gui, idParent); 
	fields.Sight							= ::gpk::controlCreateChild(gui, idParent); 
	fields.Reflexes							= ::gpk::controlCreateChild(gui, idParent); 
	gui.Controls.Constraints[fields.Sight	].DockToControl.Bottom	= fields.Attack;
	gui.Controls.Constraints[fields.Movement].DockToControl.Bottom	= fields.Sight;
	gui.Controls.Constraints[fields.Reflexes].DockToControl.Bottom	= fields.Movement;

	gui.Controls.Constraints[fields.Attack	].AttachSizeToControl	= {fields.Attack	, -1};
	gui.Controls.Constraints[fields.Sight	].AttachSizeToControl	= {fields.Sight		, -1};
	gui.Controls.Constraints[fields.Movement].AttachSizeToControl	= {fields.Movement	, -1};
	gui.Controls.Constraints[fields.Reflexes].AttachSizeToControl	= {fields.Reflexes	, -1};

	gui.Controls.Text[fields.Attack					].Text	= "Attack"; //= {00, 0};
	gui.Controls.Text[fields.Sight					].Text	= "Sight"; //= {20, 0};
	gui.Controls.Text[fields.Movement				].Text	= "Movement"; //= {40, 0};
	gui.Controls.Text[fields.Reflexes				].Text	= "Reflexes"; //= {60, 0};
	return 0; 
}

static	::gpk::error_t					guiCreateFieldsAttack			(::gpk::SGUI & gui, ::pcs::SPointsAttack	& fields, int32_t idParent)	{ 
	fields.Range							= ::gpk::controlCreateChild(gui, idParent); 
	fields.Hit								= ::gpk::controlCreateChild(gui, idParent); 
	fields.Absorption						= ::gpk::controlCreateChild(gui, idParent); 
	fields.Damage							= ::gpk::controlCreateChild(gui, idParent); 
	::guiCreateFieldsHealth	(gui, fields.DirectDamage	, idParent); 
	::guiCreateFieldsHealth	(gui, fields.DrainHealth	, idParent); 
	::guiCreateFieldsPower	(gui, fields.DrainPower		, idParent); 
	for(uint32_t iControl = fields.Range; iControl < (uint32_t)fields.Damage; ++iControl)
		gui.Controls.Constraints[iControl + 1].DockToControl.Bottom	= iControl;

	//gui.Controls.Constraints[fields.Hit					].DockToControl.Bottom	= fields.Range				;
	//gui.Controls.Constraints[fields.Absorption			].DockToControl.Bottom	= fields.Hit				;
	//gui.Controls.Constraints[fields.Damage				].DockToControl.Bottom	= fields.Absorption			;
	gui.Controls.Constraints[fields.DirectDamage.Health	].DockToControl.Bottom	= fields.Damage				;
	gui.Controls.Constraints[fields.DrainHealth.Health	].DockToControl.Bottom	= fields.DirectDamage.Shield;
	gui.Controls.Constraints[fields.DrainPower.Energy	].DockToControl.Bottom	= fields.DrainHealth.Shield	;

	for(uint32_t iControl = fields.Range; iControl <= (uint32_t)fields.Damage; ++iControl)
		gui.Controls.Constraints[iControl].AttachSizeToControl	= {(int32_t)iControl, -1,};
	//gui.Controls.Constraints[fields.Range				].AttachSizeToControl	= {fields.Range			, -1,};
	//gui.Controls.Constraints[fields.Hit					].AttachSizeToControl	= {fields.Hit			, -1,};
	//gui.Controls.Constraints[fields.Absorption			].AttachSizeToControl	= {fields.Absorption	, -1,};
	//gui.Controls.Constraints[fields.Damage				].AttachSizeToControl	= {fields.Damage		, -1,};

	gui.Controls.Text[fields.Range						].Text	= "Range"		; //= {00, 0};
	gui.Controls.Text[fields.Hit						].Text	= "Hit"			; //= {20, 0};
	gui.Controls.Text[fields.Absorption					].Text	= "Absorption"	; //= {40, 0};
	gui.Controls.Text[fields.Damage						].Text	= "Damage"		; //= {60, 0};

	gui.Controls.Text[fields.DirectDamage.Health		].Text	= "Direct Damage (Health)";
	gui.Controls.Text[fields.DirectDamage.Shield		].Text	= "Direct Damage (Shield)";

	gui.Controls.Text[fields.DrainHealth.Health			].Text	= "Drain (Health) ";
	gui.Controls.Text[fields.DrainHealth.Shield			].Text	= "Drain (Shield) ";

	gui.Controls.Text[fields.DrainPower.Energy			].Text	= "Drain (Energy) ";
	gui.Controls.Text[fields.DrainPower.Mana			].Text	= "Drain (Mana)   ";
	gui.Controls.Text[fields.DrainPower.Stamina			].Text	= "Drain (Stamina)";
	return 0; 
}

static	::gpk::error_t					guiCreateHealth					(::gpk::SGUI & gui, ::gme::SDialogHealth		& dialog )		{ dialog.Dialog = ::gpk::controlCreate(gui); gpk_necall(::guiCreateFieldsHealth	(gui, dialog.Fields, dialog.Dialog), "%s", "????"); return 0; }
static	::gpk::error_t					guiCreatePower					(::gpk::SGUI & gui, ::gme::SDialogPower			& dialog )		{ dialog.Dialog = ::gpk::controlCreate(gui); gpk_necall(::guiCreateFieldsPower	(gui, dialog.Fields, dialog.Dialog), "%s", "????"); return 0; }
static	::gpk::error_t					guiCreateFitness				(::gpk::SGUI & gui, ::gme::SDialogFitness		& dialog )		{ dialog.Dialog = ::gpk::controlCreate(gui); gpk_necall(::guiCreateFieldsFitness(gui, dialog.Fields, dialog.Dialog), "%s", "????"); return 0; }
static	::gpk::error_t					guiCreateAttack					(::gpk::SGUI & gui, ::gme::SDialogAttack		& dialog )		{ dialog.Dialog = ::gpk::controlCreate(gui); gpk_necall(::guiCreateFieldsAttack	(gui, dialog.Fields, dialog.Dialog), "%s", "????"); return 0; }
		::gpk::error_t					gme::guiCreateCharacter			(::gpk::SGUI & gui, ::gme::SCharacterUIControls	& character	)	{
	character.DialogCharacter				= ::gpk::controlCreate(gui); 

	gui.Controls.States[character.DialogCharacter].Design	= true;

	gui.Controls.Controls[character.Health	.Dialog].Border = gui.Controls.Controls[character.Health	.Dialog].Margin = {};
	gui.Controls.Controls[character.Power	.Dialog].Border = gui.Controls.Controls[character.Power		.Dialog].Margin = {};
	gui.Controls.Controls[character.Fitness	.Dialog].Border = gui.Controls.Controls[character.Fitness	.Dialog].Margin = {};
	gui.Controls.Controls[character.Attack	.Dialog].Border = gui.Controls.Controls[character.Attack	.Dialog].Margin = {};

	gpk_necall(::guiCreateHealth	(gui, character.Health	), "%s", "????");
	gpk_necall(::guiCreatePower		(gui, character.Power	), "%s", "????");
	gpk_necall(::guiCreateFitness	(gui, character.Fitness	), "%s", "????");
	gpk_necall(::guiCreateAttack	(gui, character.Attack	), "%s", "????");

	::gpk::controlSetParent(gui, character.Health	.Dialog, character.DialogCharacter);
	::gpk::controlSetParent(gui, character.Power	.Dialog, character.DialogCharacter);
	::gpk::controlSetParent(gui, character.Fitness	.Dialog, character.DialogCharacter);
	::gpk::controlSetParent(gui, character.Attack	.Dialog, character.DialogCharacter);

	gui.Controls.Constraints[character.Power	.Dialog].DockToControl.Bottom		= character.Health	.Dialog;
	gui.Controls.Constraints[character.Fitness	.Dialog].DockToControl.Bottom		= character.Power	.Dialog;
	gui.Controls.Constraints[character.Attack	.Dialog].DockToControl.Bottom		= character.Fitness	.Dialog;

	gui.Controls.Controls[character.Health	.Dialog].Area.Size.y		= 40;
	gui.Controls.Controls[character.Power	.Dialog].Area.Size.y		= 60;
	gui.Controls.Controls[character.Fitness	.Dialog].Area.Size.y		= 70;
	gui.Controls.Controls[character.Attack	.Dialog].Area.Size.y		= 180;

	gui.Controls.Controls[character.DialogCharacter].Area.Size.y  = gui.Controls.Controls[character.Health	.Dialog].Area.Size.y;
	gui.Controls.Controls[character.DialogCharacter].Area.Size.y += gui.Controls.Controls[character.Power	.Dialog].Area.Size.y;
	gui.Controls.Controls[character.DialogCharacter].Area.Size.y += gui.Controls.Controls[character.Fitness	.Dialog].Area.Size.y;
	gui.Controls.Controls[character.DialogCharacter].Area.Size.y += gui.Controls.Controls[character.Attack	.Dialog].Area.Size.y;
	for(int32_t iControl = character.DialogCharacter + 1; iControl < (int32_t)gui.Controls.Controls.size(); ++iControl) {
		//if(iControl == character.DialogHealth		) continue;
		//if(iControl == character.DialogPower		) continue;
		//if(iControl == character.DialogFitness		) continue;
		//if(iControl == character.DialogAttack		) continue;
		gui.Controls.Controls[iControl].Area.Size.x		= 210;
		//gui.Controls.Controls[iControl];
		//gui.Controls.Controls[iControl];
		//gui.Controls.Controls[iControl];
	};
	return 0;
}
