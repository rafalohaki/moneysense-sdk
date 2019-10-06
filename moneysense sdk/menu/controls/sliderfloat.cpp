#include "..\cmenu.hpp"
#define gg 9
C_SliderFloat::C_SliderFloat(std::string n_label, float * n_value, float n_min, float n_max, std::string n_follower, std::vector< C_ControlFlag * > n_flags) {
	parent = g_cfg.menu.last_group;
	label = n_label;
	value = n_value;
	min = n_min;
	max = n_max;
	follower = n_follower;
	flags = n_flags;
	area.h = 13;
	if (n_label != "") {
		height_offset = 13;
		area.h += 13;
	}
	parent->add_control(this);
}

void C_SliderFloat::draw() {
	if (menu::get().activate_menu)
	{
		rect_t n_area = area;
		render::get().text(fonts[TAHOMA12], area.x, area.y, Color::Purple, HFONT_CENTERED_NONE, label.c_str());
		n_area.y += height_offset;
		n_area.h -= height_offset;
		POINT mouse; GetCursorPos(&mouse);
		rect_t item_region = rect_t(n_area.x, n_area.y, n_area.w, gg);
		if (item_region.contains_point(mouse)) {
			render::get().rect_filled(n_area.x, n_area.y, area.w, gg, Color{ 72, 72, 72, 255 });
		}
		else render::get().rect_filled(n_area.x, n_area.y, area.w, gg, Color{ 62, 62, 62, 255 });
		float ratio = (*value - min) / (max - min);
		float location = ratio * area.w;
		render::get().rect_filled(n_area.x, n_area.y, location, gg, g_cfg.menu.menu_theme[0]);
		render::get().rect(n_area.x, n_area.y, area.w, gg, Color::Black);
		render::get().text(fonts[CTAB_MIN], n_area.x - 7, n_area.y - 2, Color(60, 60, 60), HFONT_CENTERED_NONE, ("-"));
		render::get().text(fonts[CTAB_MIN], n_area.x + 3 + area.w, n_area.y - 2, Color(60, 60, 60), HFONT_CENTERED_NONE, ("+"));
		char value_transformed[128];
		sprintf_s(value_transformed, "%0.1f", *value);
		std::stringstream ss;
		ss << value_transformed << follower.c_str();
		render::get().text(fonts[TAHOMA12], n_area.x + location, n_area.y + 6, Color::Purple, HFONT_CENTERED_X, ss.str().c_str());
	}
}
void C_SliderFloat::update() {
	if (dragging) {
		if (GetAsyncKeyState(VK_LBUTTON)) {
			POINT mouse;  GetCursorPos(&mouse);
			float
				new_x,
				ratio;
			new_x = mouse.x - area.x;
			if (new_x < 0) { new_x = 0; }
			if (new_x > area.w) { new_x = area.w; }
			ratio = new_x / float(area.w);
			*value = min + (max - min) * ratio;
		}
		else {
			dragging = false;
		}
	}
}
void C_SliderFloat::click() {
	dragging = true;
}