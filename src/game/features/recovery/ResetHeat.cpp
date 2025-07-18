#include "core/commands/ListCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/script/globals/GPBD_FM.hpp"
#include "types/script/globals/GPBD_FM_2.hpp"
#include "game/gta/Natives.hpp"
namespace YimMenu::Features
{


	class ResetHeat : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;
			;
			STATS::SET_PACKED_STAT_INT_CODE(24924, 0, -1);
			STATS::SET_PACKED_STAT_INT_CODE(24925, 0, -1);
			STATS::SET_PACKED_STAT_INT_CODE(24926, 0, -1);
		};
	};

	static ResetHeat _ResetHeat{"resetheat", "Reset Heat", "Resets heat level at money front businesses"};
	
}