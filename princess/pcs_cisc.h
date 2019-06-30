#include "gpk_typeint.h"

#ifndef PCS_CISC_H_2938409283
#define PCS_CISC_H_2938409283

namespace pcs
{
#pragma pack(push, 1)
	enum  CISC_SYSTEM : uint8_t 
		{ CISC_SYSTEM_NOP								= 0
		, CISC_SYSTEM_GAME
		, CISC_SYSTEM_UI
		, CISC_SYSTEM_SESSION
		, CISC_SYSTEM_COUNT
		};

	enum  CISC_SUBSYSTEM_GAME : uint8_t
		{ CISC_SUBSYSTEM_GAME_CHARACTER					= 0
		, CISC_SUBSYSTEM_GAME_COUNT
		};

	enum  CISC_COMMAND_GAME_CHARACTER : uint8_t
		{ CISC_COMMAND_GAME_CHARACTER_POINTS_Health		= 0
		, CISC_COMMAND_GAME_CHARACTER_POINTS_Power	
		, CISC_COMMAND_GAME_CHARACTER_POINTS_Fitness 
		, CISC_COMMAND_GAME_CHARACTER_POINTS_Attack	
		, CISC_COMMAND_GAME_CHARACTER_PROFILE
		, CISC_COMMAND_GAME_COUNT
		};

	enum CISC_OPCODE_UI : uint8_t
		{ CISC_OPCODE_UI_CHARACTER						= 0
		, CISC_OPCODE_UI_COUNT
		};

	enum CISC_OPCODE_SESSION : uint8_t
		{ CISC_OPCODE_SESSION_LOGIN						= 0
		, CISC_OPCODE_SESSION_COUNT
		};

	struct SCISCOPCode {
							CISC_SYSTEM			System				: 7;
							uint8_t				Response			: 1;
							uint8_t				Subsystem			;
							uint8_t				Command				;
	};

	static constexpr	const size_t		OPCODE_HEADER_SIZE	= sizeof(SCISCOPCode);
#pragma pack(pop)
}

#endif // PCS_CISC_H_2938409283
