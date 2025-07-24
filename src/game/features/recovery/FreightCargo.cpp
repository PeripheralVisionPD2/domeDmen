#include "core/commands/ListCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/script/globals/GPBD_FM.hpp"
#include "types/script/globals/GPBD_FM_2.hpp"
#include "game/gta/Natives.hpp"
namespace YimMenu::Features
{
	/*
	*/
		enum class eCargoWarehouse
	{
		WAREHOUSE1,
		WAREHOUSE2,
		WAREHOUSE3,
		WAREHOUSE4,
		WAREHOUSE5
	};

	static std::vector<std::pair<int, const char*>> warehouseNames = {
	    {static_cast<int>(eCargoWarehouse::WAREHOUSE1), "Warehouse 1"},
	    {static_cast<int>(eCargoWarehouse::WAREHOUSE2), "Warehouse 2"},
	    {static_cast<int>(eCargoWarehouse::WAREHOUSE3), "Warehouse 3"},
	    {static_cast<int>(eCargoWarehouse::WAREHOUSE4), "Warehouse 4"},
	    {static_cast<int>(eCargoWarehouse::WAREHOUSE5), "Warehouse 5"}};
	static ListCommand _SelectedWarehouse{"warehousechoice", "Warehouse", "Warehouse to add cargo to", warehouseNames, 0};

	class AddAirFreight : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;
			;
			STATS::SET_PACKED_STAT_BOOL_CODE(36828, 1, -1);
		};
	};
	class AddCrates : public Command
	{
		using Command::Command;
		virtual void OnCall() override
		{

			if (!*Pointers.IsSessionStarted)
				return;
			switch (static_cast<eCargoWarehouse>(_SelectedWarehouse.GetState()))
			{
			case eCargoWarehouse::WAREHOUSE1:
			{
				STATS::SET_PACKED_STAT_BOOL_CODE(32359, 1, -1);
				break;
			}
			case eCargoWarehouse::WAREHOUSE2:
			{
				STATS::SET_PACKED_STAT_BOOL_CODE(32360, 1, -1);
				break;
			}
			case eCargoWarehouse::WAREHOUSE3:
			{
				STATS::SET_PACKED_STAT_BOOL_CODE(32361, 1, -1);
				break;
			}
			case eCargoWarehouse::WAREHOUSE4:
			{
				STATS::SET_PACKED_STAT_BOOL_CODE(32362, 1, -1);
				break;
			}
			case eCargoWarehouse::WAREHOUSE5:
			{
				STATS::SET_PACKED_STAT_BOOL_CODE(32363, 1, -1);
				break;
			}
			default:
				break;
			}
			

		}
	};
	static AddAirFreight _AddAirFreight{"addairfreight", "Add Air Cargo", "Has rooster source random air cargo."};
	static AddCrates _AddCrates{"addwarehousecargo", "Add Cargo", "Has staff source cargo for selected warehouse."};

}