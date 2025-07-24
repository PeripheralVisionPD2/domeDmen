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
		auto cargoTab = std::make_shared<Category>("Cargo");
		auto cargGroup = std::make_shared<Group>("General");
		//auto casinoWheel = std::make_shared<Group>("Lucky Wheel");
		//auto casinoBlackJack = std::make_shared<Group>("Blackjack");
		//auto casinoRoulette = std::make_shared<Group>("Roulette");
;

		generalGroup->AddItem(std::make_shared<ListCommandItem>("businesssafe"_J));
		generalGroup->AddItem(std::make_shared<CommandItem>("claimsafeearnings"_J));
		generalGroup->AddItem(std::make_shared<CommandItem>("resetheat"_J));
		
		cargGroup->AddItem(std::make_shared<ListCommandItem>("warehousechoice"_J));
		cargGroup->AddItem(std::make_shared<CommandItem>("addwarehousecargo"_J));
		cargGroup->AddItem(std::make_shared<CommandItem>("addairfreight"_J));

		main->AddItem(generalGroup);
		cargoTab->AddItem(cargGroup);

		AddCategory(std::move(main));
		AddCategory(std::move(cargoTab));
		AddCategory(BuildStatEditorMenu());
		AddCategory(BuildDailyActivitiesMenu());
	}
}