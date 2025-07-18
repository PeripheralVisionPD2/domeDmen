#include "Recovery.hpp"
#include "Recovery/HeistModifier.hpp"
#include "Recovery/StatEditor.hpp"
#include "Recovery/Transactions.hpp"
#include "Recovery/DailyActivities.hpp"
#include "game/frontend/items/Items.hpp"

namespace YimMenu::Submenus
{

	Recovery::Recovery() :
		#define ICON_FA_SACK_DOLLAR "\xef\x93\x80"
	    Submenu::Submenu("Utils", ICON_FA_SACK_DOLLAR)
	{

		auto main = std::make_shared<Category>("Main");
		auto generalGroup = std::make_shared<Group>("General");

		//auto casinoWheel = std::make_shared<Group>("Lucky Wheel");
		//auto casinoBlackJack = std::make_shared<Group>("Blackjack");
		//auto casinoRoulette = std::make_shared<Group>("Roulette");
;

		generalGroup->AddItem(std::make_shared<ListCommandItem>("businesssafe"_J));
		generalGroup->AddItem(std::make_shared<CommandItem>("claimsafeearnings"_J));
		generalGroup->AddItem(std::make_shared<CommandItem>("resetheat"_J));

		auto setVal = 0;
		main->AddItem(generalGroup);
		AddCategory(std::move(main));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildDailyActivitiesMenu());
	}
}