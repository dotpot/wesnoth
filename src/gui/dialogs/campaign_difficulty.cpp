/* $Id$ */
/*
   Copyright (C) 2010 by Ignacio Riquelme Morelle <shadowm2006@gmail.com>
   Part of the Battle for Wesnoth Project http://www.wesnoth.org/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/

#define GETTEXT_DOMAIN "wesnoth-lib"

#include "gui/dialogs/campaign_difficulty.hpp"

#include "foreach.hpp"
#include "gui/auxiliary/old_markup.hpp"
#ifdef GUI2_EXPERIMENTAL_LISTBOX
	#include "gui/widgets/list.hpp"
#else
	#include "gui/widgets/listbox.hpp"
#endif
#include "gui/widgets/settings.hpp"
#include "gui/widgets/window.hpp"

namespace gui2 {

REGISTER_WINDOW(campaign_difficulty)

tcampaign_difficulty::tcampaign_difficulty(const std::vector<std::string>& items)
	: index_(-1), items_()
{
	foreach(const std::string& it, items) {
		items_.push_back(it);
	}
}

void tcampaign_difficulty::pre_show(CVideo& /*video*/, twindow& window)
{
	tlistbox& list = find_widget<tlistbox>(&window, "listbox", false);
	window.keyboard_capture(&list);

	std::map<std::string, string_map> data;

	foreach(const legacy_menu_item& item, items_) {
		if(item.is_default()) {
			index_ = list.get_item_count();
		}

		data["icon"]["label"] = item.icon();
		data["label"]["label"] = item.label();
		data["label"]["use_markup"] = "true";
		data["description"]["label"] = item.description();
		data["description"]["use_markup"] = "true";

		list.add_row(data);
	}

	if(index_ != -1) {
		list.select_row(index_);
	}
}

void tcampaign_difficulty::post_show(twindow& window)
{
	if(get_retval() != twindow::OK) {
		index_ = -1;
		return;
	}

	tlistbox& list = find_widget<tlistbox>(&window, "listbox", false);
	index_ = list.get_selected_row();
}

}
