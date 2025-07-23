#include "core/commands/ListCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/ScriptGlobal.hpp"
#include "game/pointers/Pointers.hpp"
#include "types/script/globals/GPBD_FM.hpp"
#include "types/script/globals/GPBD_FM_2.hpp"
#include "game/gta/Natives.hpp"
#include "types/stats/CStatsMgr.hpp"
#include <types/stats/sStatData.hpp>
namespace YimMenu::Features
{

	struct StatInfo
	{
		std::string m_Name;
		std::uint32_t m_NameHash;
		bool m_Normalized = false;
		sStatData* m_Data = nullptr;

		bool IsValid()
		{
			return m_Data != nullptr;
		}
	};

	struct PackedStatInfo
	{
		int m_Index;
		bool m_IsBoolStat;
		bool m_IsValid;

		bool IsValid()
		{
			return m_IsValid;
		}
	};

	union StatValue {
		float m_AsFloat;
		int m_AsInt;
		bool m_AsBool;
		std::uint64_t m_AsU64;
		char m_AsString[12];
	};
	static StatInfo GetStatInfo(std::string_view name_str)
	{
		StatInfo name{};
		auto len = name_str.length();

		// not sure why people do this
		if (len > 1 && name_str[0] == '$')
		{
			auto it = name_str.begin();
			std::advance(it, 1);
			name_str = std::string_view{it, name_str.end()};
			len--;
			name.m_Normalized = true;
		}

		name.m_Name = name_str;

		if (len > 3 && tolower(name_str[0]) == 'm' && tolower(name_str[1]) == 'p' && tolower(name_str[2]) == 'x')
		{
			if (auto last_char = Pointers.StatsMgr->GetStat("MPPLY_LAST_MP_CHAR"_J))
			{
				name.m_Name[2] = '0' + last_char->GetInt();
				name.m_Normalized = true;
			}
		}

		name.m_NameHash = Joaat(name.m_Name);
		name.m_Data = Pointers.StatsMgr->GetStat(name.m_NameHash);

		if (name.m_Data == nullptr && len > 3 && (tolower(name_str[0]) != 'm' || tolower(name_str[1]) != 'p' || !(tolower(name_str[2]) == '0' || tolower(name_str[2]) == '1')))
		{
			// stat names without a character prefix
			auto last_char = Pointers.StatsMgr->GetStat("MPPLY_LAST_MP_CHAR"_J);
			auto char_index = last_char ? last_char->GetInt() : 0;
			auto char_prefix = char_index == 0 ? "MP0_" : "MP1_";
			auto new_hash = Joaat(char_prefix + name.m_Name);
			auto new_stat = Pointers.StatsMgr->GetStat(new_hash);

			if (new_stat)
			{
				name.m_Name = char_prefix + name.m_Name;
				name.m_NameHash = new_hash;
				name.m_Data = new_stat;
				name.m_Normalized = true;
			}
		}

		return name;
	}
	class ResetPopularity : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;
			StatInfo PopularityInfo = GetStatInfo("$MPx_CLUB_POPULARITY");
			STATS::STAT_SET_INT(PopularityInfo.m_NameHash, 1000, true);
		};
	};

	static ResetPopularity _ResetPopularity{"resetpopularity", "Reset Popularity", "Resets popularity level at nightclub to full"};

}