#include "application.h"

static	::gpk::error_t					guiCreateHealth			(::gpk::SGUI & gui, ::pcs::SPointsHealth	& fields, int32_t idParent)	{ 
	fields.Health							= ::gpk::controlCreate(gui); 
	fields.Shield							= ::gpk::controlCreate(gui); 
	gui.Controls.Constraints[fields.Shield].DockToControl.Bottom	= fields.Health;

	gui.Controls.Constraints[fields.Health	].AttachSizeToControl	= {fields.Health	, -1};
	gui.Controls.Constraints[fields.Shield	].AttachSizeToControl	= {fields.Shield	, -1};

	gui.Controls.Text[fields.Health].Text	= "Health"; //= {00, 0};
	gui.Controls.Text[fields.Shield].Text	= "Shield"; //= {20, 0};

	::gpk::controlSetParent(gui, fields.Health, idParent);
	::gpk::controlSetParent(gui, fields.Shield, idParent);
	return 0; 
}

static	::gpk::error_t					guiCreatePower				(::gpk::SGUI & gui, ::pcs::SPointsPower		& fields, int32_t idParent)	{ 
	fields.Energy							= ::gpk::controlCreate(gui); 
	fields.Mana								= ::gpk::controlCreate(gui); 
	fields.Stamina							= ::gpk::controlCreate(gui); 
	gui.Controls.Constraints[fields.Mana	].DockToControl.Bottom	= fields.Energy;
	gui.Controls.Constraints[fields.Stamina	].DockToControl.Bottom	= fields.Mana;

	gui.Controls.Constraints[fields.Energy	].AttachSizeToControl	= {fields.Energy	, -1};
	gui.Controls.Constraints[fields.Mana	].AttachSizeToControl	= {fields.Mana		, -1};
	gui.Controls.Constraints[fields.Stamina	].AttachSizeToControl	= {fields.Stamina	, -1};

	gui.Controls.Text[fields.Energy					].Text	= "Energy"		; //= {20, 0};
	gui.Controls.Text[fields.Mana					].Text	= "Mana"		; //= {40, 0};
	gui.Controls.Text[fields.Stamina				].Text	= "Stamina"		; //= {60, 0};

	::gpk::controlSetParent(gui, fields.Energy	, idParent);
	::gpk::controlSetParent(gui, fields.Mana	, idParent);
	::gpk::controlSetParent(gui, fields.Stamina	, idParent);
	return 0; 
}

static	::gpk::error_t					guiCreateFitness			(::gpk::SGUI & gui, ::pcs::SPointsFitness	& fields, int32_t idParent)	{ 
	fields.Attack							= ::gpk::controlCreate(gui); 
	fields.Movement							= ::gpk::controlCreate(gui); 
	fields.Sight							= ::gpk::controlCreate(gui); 
	fields.Reflexes							= ::gpk::controlCreate(gui); 
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

	::gpk::controlSetParent(gui, fields.Attack		, idParent);
	::gpk::controlSetParent(gui, fields.Sight		, idParent);
	::gpk::controlSetParent(gui, fields.Movement	, idParent);
	::gpk::controlSetParent(gui, fields.Reflexes	, idParent);
	return 0; 
}

static	::gpk::error_t					guiCreateAttack			(::gpk::SGUI & gui, ::pcs::SPointsAttack	& fields, int32_t idParent)	{ 
	fields.Range							= ::gpk::controlCreate(gui); 
	fields.Hit								= ::gpk::controlCreate(gui); 
	fields.Absorption						= ::gpk::controlCreate(gui); 
	fields.Damage							= ::gpk::controlCreate(gui); 
	::guiCreateHealth	(gui, fields.DirectDamage	, idParent); 
	::guiCreateHealth	(gui, fields.DrainHealth	, idParent); 
	::guiCreatePower	(gui, fields.DrainPower		, idParent); 
	gui.Controls.Constraints[fields.Hit					].DockToControl.Bottom	= fields.Range				;
	gui.Controls.Constraints[fields.Absorption			].DockToControl.Bottom	= fields.Hit				;
	gui.Controls.Constraints[fields.Damage				].DockToControl.Bottom	= fields.Absorption			;
	gui.Controls.Constraints[fields.DirectDamage.Health	].DockToControl.Bottom	= fields.Damage				;
	gui.Controls.Constraints[fields.DrainHealth.Health	].DockToControl.Bottom	= fields.DirectDamage.Shield;
	gui.Controls.Constraints[fields.DrainPower.Energy	].DockToControl.Bottom	= fields.DrainHealth.Shield	;

	gui.Controls.Constraints[fields.Range				].AttachSizeToControl	= {fields.Range			, -1,};
	gui.Controls.Constraints[fields.Hit					].AttachSizeToControl	= {fields.Hit			, -1,};
	gui.Controls.Constraints[fields.Absorption			].AttachSizeToControl	= {fields.Absorption	, -1,};
	gui.Controls.Constraints[fields.Damage				].AttachSizeToControl	= {fields.Damage		, -1,};

	gui.Controls.Text[fields.Range						].Text	= "Range"		; //= {00, 0};
	gui.Controls.Text[fields.Hit						].Text	= "Hit"			; //= {20, 0};
	gui.Controls.Text[fields.Absorption					].Text	= "Absorption"	; //= {40, 0};
	gui.Controls.Text[fields.Damage						].Text	= "Damage"		; //= {60, 0};

	::gpk::controlSetParent(gui, fields.Range		, idParent);
	::gpk::controlSetParent(gui, fields.Hit			, idParent);
	::gpk::controlSetParent(gui, fields.Absorption	, idParent);
	::gpk::controlSetParent(gui, fields.Damage		, idParent);
	return 0; 
}
//static	::gpk::error_t					guiCreateHealth					(::gpk::SGUI & gui, int32_t idParent, ::pcs::SPointsHealth		& fields	) { gpk_necall(::guiCreateHealth	(gui, fields), "%s", "????"); return 0; }
//static	::gpk::error_t					guiCreatePower					(::gpk::SGUI & gui, int32_t idParent, ::pcs::SPointsPower		& fields	) { gpk_necall(::guiCreatePower		(gui, fields), "%s", "????"); return 0; }
//static	::gpk::error_t					guiCreateFitness				(::gpk::SGUI & gui, int32_t idParent, ::pcs::SPointsFitness		& fields	) { gpk_necall(::guiCreateFitness	(gui, fields), "%s", "????"); return 0; }
//static	::gpk::error_t					guiCreateAttack					(::gpk::SGUI & gui, int32_t idParent, ::pcs::SPointsAttack		& fields	) { gpk_necall(::guiCreateAttack	(gui, fields), "%s", "????"); return 0; }
		::gpk::error_t					gme::guiCreateCharacter			(::gpk::SGUI & gui, ::gme::SCharacterUIControls	& character	) {
	character.DialogCharacter				= ::gpk::controlCreate(gui); 

	gui.Controls.States[character.DialogCharacter].Design	= true;

	character.DialogHealth					= ::gpk::controlCreate(gui); 
	character.DialogPower					= ::gpk::controlCreate(gui); 
	character.DialogFitness					= ::gpk::controlCreate(gui); 
	character.DialogAttack					= ::gpk::controlCreate(gui); 


	gui.Controls.Controls[character.DialogHealth	].Border = {};
	gui.Controls.Controls[character.DialogPower		].Border = {};
	gui.Controls.Controls[character.DialogFitness	].Border = {};
	gui.Controls.Controls[character.DialogAttack	].Border = {};


	gpk_necall(::guiCreateHealth	(gui, character.Health	, character.DialogHealth	), "%s", "????");
	gpk_necall(::guiCreatePower		(gui, character.Power	, character.DialogPower		), "%s", "????");
	gpk_necall(::guiCreateFitness	(gui, character.Fitness	, character.DialogFitness	), "%s", "????");
	gpk_necall(::guiCreateAttack	(gui, character.Attack	, character.DialogAttack	), "%s", "????");

	::gpk::controlSetParent(gui, character.DialogHealth	, character.DialogCharacter);
	::gpk::controlSetParent(gui, character.DialogPower	, character.DialogCharacter);
	::gpk::controlSetParent(gui, character.DialogFitness, character.DialogCharacter);
	::gpk::controlSetParent(gui, character.DialogAttack	, character.DialogCharacter);

	gui.Controls.Text[character.Attack.DirectDamage.Health	].Text	= "Direct Damage (Health)";
	gui.Controls.Text[character.Attack.DirectDamage.Shield	].Text	= "Direct Damage (Shield)";

	gui.Controls.Text[character.Attack.DrainHealth.Health	].Text	= "Drain (Health) ";
	gui.Controls.Text[character.Attack.DrainHealth.Shield	].Text	= "Drain (Shield) ";

	gui.Controls.Text[character.Attack.DrainPower.Energy	].Text	= "Drain (Energy) ";
	gui.Controls.Text[character.Attack.DrainPower.Mana		].Text	= "Drain (Mana)   ";
	gui.Controls.Text[character.Attack.DrainPower.Stamina	].Text	= "Drain (Stamina)";

	gui.Controls.Constraints[character.DialogPower		].DockToControl.Bottom		= character.DialogHealth	;
	gui.Controls.Constraints[character.DialogFitness	].DockToControl.Bottom		= character.DialogPower		;
	gui.Controls.Constraints[character.DialogAttack		].DockToControl.Bottom		= character.DialogFitness	;

	gui.Controls.Controls[character.DialogHealth	].Area.Size.y		= 40;
	gui.Controls.Controls[character.DialogPower		].Area.Size.y		= 60;
	gui.Controls.Controls[character.DialogFitness	].Area.Size.y		= 70;
	gui.Controls.Controls[character.DialogAttack	].Area.Size.y		= 180;

	gui.Controls.Controls[character.DialogCharacter].Area.Size.y  = gui.Controls.Controls[character.DialogHealth	].Area.Size.y;
	gui.Controls.Controls[character.DialogCharacter].Area.Size.y += gui.Controls.Controls[character.DialogPower		].Area.Size.y;
	gui.Controls.Controls[character.DialogCharacter].Area.Size.y += gui.Controls.Controls[character.DialogFitness	].Area.Size.y;
	gui.Controls.Controls[character.DialogCharacter].Area.Size.y += gui.Controls.Controls[character.DialogAttack	].Area.Size.y;
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
