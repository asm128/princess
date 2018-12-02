#include "application.h"
	
		::gpk::error_t					gme::guiCreateHealth			(::gpk::SGUI gui, ::gme::SPointsUIHealth	& fields)	{ 
	fields.IdHealth							= ::gpk::controlCreate(gui); 
	fields.IdShield							= ::gpk::controlCreate(gui); 
	return 0; 
}

		::gpk::error_t					gme::guiCreatePower				(::gpk::SGUI gui, ::gme::SPointsUIPower		& fields)	{ 
	fields.IdEnergy							= ::gpk::controlCreate(gui); 
	fields.IdMana							= ::gpk::controlCreate(gui); 
	fields.IdEnergy							= ::gpk::controlCreate(gui); 
	return 0; 
}

		::gpk::error_t					gme::guiCreateFitness			(::gpk::SGUI gui, ::gme::SPointsUIFitness	& fields)	{ 
	fields.IdRange							= ::gpk::controlCreate(gui); 
	fields.IdHit							= ::gpk::controlCreate(gui); 
	fields.IdAbsorption						= ::gpk::controlCreate(gui); 
	fields.IdDamage							= ::gpk::controlCreate(gui); 
	::gme::guiCreateHealth(gui, fields.IdDirectDamage); 
	return 0; 
}

		::gpk::error_t					gme::guiCreateAttack			(::gpk::SGUI gui, ::gme::SPointsUIAttack	& fields)	{ 
	fields.IdAttack							= ::gpk::controlCreate(gui); 
	fields.IdSight							= ::gpk::controlCreate(gui); 
	fields.IdReflexes						= ::gpk::controlCreate(gui); 
	return 0; 
}
