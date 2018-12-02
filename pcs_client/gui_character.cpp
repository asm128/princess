#include "application.h"

static	::gpk::error_t					guiCreateHealth			(::gpk::SGUI & gui, ::pcs::SPointsHealth	& fields)	{ 
	fields.Health							= ::gpk::controlCreate(gui); 
	fields.Shield							= ::gpk::controlCreate(gui); 
	gui.Controls.Constraints[fields.Shield].DockToControl.Bottom	= fields.Health;

	gui.Controls.Constraints[fields.Health	].AttachSizeToControl	= {fields.Health	, -1};
	gui.Controls.Constraints[fields.Shield	].AttachSizeToControl	= {fields.Shield	, -1};

	gui.Controls.Text[fields.Health].Text	= "Health"; //= {00, 0};
	gui.Controls.Text[fields.Shield].Text	= "Shield"; //= {20, 0};
	return 0; 
}

static	::gpk::error_t					guiCreatePower				(::gpk::SGUI & gui, ::pcs::SPointsPower		& fields)	{ 
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
	return 0; 
}

static	::gpk::error_t					guiCreateFitness			(::gpk::SGUI & gui, ::pcs::SPointsFitness	& fields)	{ 
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
	return 0; 
}

static	::gpk::error_t					guiCreateAttack			(::gpk::SGUI & gui, ::pcs::SPointsAttack	& fields)	{ 
	fields.Range							= ::gpk::controlCreate(gui); 
	fields.Hit								= ::gpk::controlCreate(gui); 
	fields.Absorption						= ::gpk::controlCreate(gui); 
	fields.Damage							= ::gpk::controlCreate(gui); 
	::guiCreateHealth(gui, fields.DirectDamage); 
	gui.Controls.Constraints[fields.Hit					].DockToControl.Bottom	= fields.Range			;
	gui.Controls.Constraints[fields.Absorption			].DockToControl.Bottom	= fields.Hit			;
	gui.Controls.Constraints[fields.Damage				].DockToControl.Bottom	= fields.Absorption		;
	gui.Controls.Constraints[fields.DirectDamage.Health	].DockToControl.Bottom	= fields.Damage			;

	gui.Controls.Constraints[fields.Range				].AttachSizeToControl	= {fields.Range			, -1,};
	gui.Controls.Constraints[fields.Hit					].AttachSizeToControl	= {fields.Hit			, -1,};
	gui.Controls.Constraints[fields.Absorption			].AttachSizeToControl	= {fields.Absorption	, -1,};
	gui.Controls.Constraints[fields.Damage				].AttachSizeToControl	= {fields.Damage		, -1,};


	gui.Controls.Text[fields.Range						].Text	= "Range"		; //= {00, 0};
	gui.Controls.Text[fields.Hit						].Text	= "Hit"			; //= {20, 0};
	gui.Controls.Text[fields.Absorption					].Text	= "Absorption"	; //= {40, 0};
	gui.Controls.Text[fields.Damage						].Text	= "Damage"		; //= {60, 0};
	return 0; 
}

		::gpk::error_t					gme::guiCreateCharacter			(::gpk::SGUI & gui, ::gme::SCharacterUIControls	& character	) {
	character.DialogCharacter				= ::gpk::controlCreate(gui); 
	character.DialogHealth					= ::gpk::controlCreate(gui); 
	character.DialogPower					= ::gpk::controlCreate(gui); 
	character.DialogFitness					= ::gpk::controlCreate(gui); 
	character.DialogAttack					= ::gpk::controlCreate(gui); 

	gpk_necall(::guiCreateHealth	(gui, character.Health	), "%s", "????");
	gpk_necall(::guiCreatePower		(gui, character.Power	), "%s", "????");
	gpk_necall(::guiCreateFitness	(gui, character.Fitness	), "%s", "????");
	gpk_necall(::guiCreateAttack	(gui, character.Attack	), "%s", "????");

	::gpk::controlSetParent(gui, character.Health.Health, character.DialogHealth);
	::gpk::controlSetParent(gui, character.Health.Shield, character.DialogHealth);

	::gpk::controlSetParent(gui, character.Power.Energy	, character.DialogPower);
	::gpk::controlSetParent(gui, character.Power.Mana	, character.DialogPower);
	::gpk::controlSetParent(gui, character.Power.Stamina, character.DialogPower);

	::gpk::controlSetParent(gui, character.Fitness.Attack	, character.DialogFitness);
	::gpk::controlSetParent(gui, character.Fitness.Movement	, character.DialogFitness);
	::gpk::controlSetParent(gui, character.Fitness.Reflexes	, character.DialogFitness);
	::gpk::controlSetParent(gui, character.Fitness.Sight	, character.DialogFitness);

	gpk::controlSetParent(gui, character.Attack.Range				, character.DialogAttack);
	gpk::controlSetParent(gui, character.Attack.Hit					, character.DialogAttack);
	gpk::controlSetParent(gui, character.Attack.Absorption			, character.DialogAttack);
	gpk::controlSetParent(gui, character.Attack.Damage				, character.DialogAttack);
	gpk::controlSetParent(gui, character.Attack.DirectDamage.Health	, character.DialogAttack);
	gpk::controlSetParent(gui, character.Attack.DirectDamage.Shield	, character.DialogAttack);

	::gpk::controlSetParent(gui, character.DialogHealth	, character.DialogCharacter);
	::gpk::controlSetParent(gui, character.DialogPower	, character.DialogCharacter);
	::gpk::controlSetParent(gui, character.DialogFitness, character.DialogCharacter);
	::gpk::controlSetParent(gui, character.DialogAttack	, character.DialogCharacter);

	gui.Controls.Constraints[character.DialogPower		].DockToControl.Bottom		= character.DialogHealth	;
	gui.Controls.Constraints[character.DialogFitness	].DockToControl.Bottom		= character.DialogPower		;
	gui.Controls.Constraints[character.DialogAttack		].DockToControl.Bottom		= character.DialogFitness	;

	gui.Controls.Controls[character.DialogHealth	].Area.Size.y		= 40;
	gui.Controls.Controls[character.DialogPower		].Area.Size.y		= 60;
	gui.Controls.Controls[character.DialogFitness	].Area.Size.y		= 70;
	gui.Controls.Controls[character.DialogAttack	].Area.Size.y		= 100;

	gui.Controls.Controls[character.DialogCharacter].Area.Size.y  = gui.Controls.Controls[character.DialogHealth	].Area.Size.y;
	gui.Controls.Controls[character.DialogCharacter].Area.Size.y += gui.Controls.Controls[character.DialogPower		].Area.Size.y;
	gui.Controls.Controls[character.DialogCharacter].Area.Size.y += gui.Controls.Controls[character.DialogFitness	].Area.Size.y;
	gui.Controls.Controls[character.DialogCharacter].Area.Size.y += gui.Controls.Controls[character.DialogAttack	].Area.Size.y;
	for(int32_t iControl = character.DialogCharacter + 1; iControl < (int32_t)gui.Controls.Controls.size(); ++iControl) {
		//if(iControl == character.DialogHealth		) continue;
		//if(iControl == character.DialogPower		) continue;
		//if(iControl == character.DialogFitness		) continue;
		//if(iControl == character.DialogAttack		) continue;
		gui.Controls.Controls[iControl].Area.Size.x		= 100;
		//gui.Controls.Controls[iControl];
		//gui.Controls.Controls[iControl];
		//gui.Controls.Controls[iControl];
	};
	return 0;
}
