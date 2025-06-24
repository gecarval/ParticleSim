/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fluidsim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gecarval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:24:07 by gecarval          #+#    #+#             */
/*   Updated: 2024/09/10 20:36:29 by gecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/renderer.h"

void post_processing(int x, int y, t_data *data, int id, int col) {
	if (data->fsim->map[y][x + 1] == id) {
		pixel_to_img(x * 2 + 1, y * 2, data, col);
		pixel_to_img(x * 2 + 1, y * 2 + 1, data, col);
	}
	if (data->fsim->map[y][x - 1] == id) {
		pixel_to_img(x * 2, y * 2, data, col);
		pixel_to_img(x * 2, y * 2 + 1, data, col);
	}
	if (data->fsim->map[y + 1][x] == id) {
		pixel_to_img(x * 2, y * 2 + 1, data, col);
		pixel_to_img(x * 2 + 1, y * 2 + 1, data, col);
	}
	if (data->fsim->map[y - 1][x] == id) {
		pixel_to_img(x * 2, y * 2, data, col);
		pixel_to_img(x * 2 + 1, y * 2, data, col);
	}
}

void process_material(int x, int y, t_data *data, int col) {
	pixel_to_img(x * 2, y * 2, data, col);
	pixel_to_img(x * 2, y * 2 + 1, data, col);
	pixel_to_img(x * 2 + 1, y * 2, data, col);
	pixel_to_img(x * 2 + 1, y * 2 + 1, data, col);
}

static const t_postprocesslookup pplookup[] = {
	[MAT_ID_EMPTY] = {0, 0},
	[MAT_ID_HIDROGEN] = {process_material, MAT_COL_HIDROGEN},
	[MAT_ID_OXYGEN] = {process_material, MAT_COL_OXYGEN},
	[MAT_ID_BUBBLE] = {process_material, MAT_COL_BUBBLE},
	[MAT_ID_STEAM] = {process_material, MAT_COL_STEAM},
	[MAT_ID_PROPANE] = {process_material, MAT_COL_PROPANE},
	[MAT_ID_EMBER] = {process_material, MAT_COL_EMBER},
	[MAT_ID_FIRE] = {process_material, MAT_COL_FIRE},
	[MAT_ID_SMOKE] = {process_material, MAT_COL_SMOKE},
	[MAT_ID_FOG] = {process_material, MAT_COL_FOG},
	[MAT_ID_FLY] = {process_material, MAT_COL_FLY},
	[MAT_ID_SALT] = {process_material, MAT_COL_SALT},
	[MAT_ID_ACID] = {process_material, MAT_COL_ACID},
	[MAT_ID_OIL] = {process_material, MAT_COL_OIL},
	[MAT_ID_OILF] = {process_material, MAT_COL_OILF},
	[MAT_ID_WATER] = {process_material, MAT_COL_WATER},
	[MAT_ID_MOLTENIRON] = {process_material, MAT_COL_MOLTENIRON},
	[MAT_ID_LAVA] = {process_material, MAT_COL_LAVA},
	[MAT_ID_MISSILE] = {process_material, MAT_COL_MISSILE},
	[MAT_ID_GUNPOWDER] = {process_material, MAT_COL_GUNPOWDER},
	[MAT_ID_SOAP] = {process_material, MAT_COL_SOAP},
	[MAT_ID_SAND] = {process_material, MAT_COL_SAND},
	[MAT_ID_WETSAND] = {process_material, MAT_COL_WETSAND},
	[MAT_ID_STONE] = {process_material, MAT_COL_STONE},
	[MAT_ID_RUST] = {process_material, MAT_COL_RUST},
	[MAT_ID_WOOD] = {process_material, MAT_COL_WOOD},
	[MAT_ID_WOODF] = {process_material, MAT_COL_WOODF},
	[MAT_ID_GLASS] = {process_material, MAT_COL_GLASS},
	[MAT_ID_GLASSF] = {process_material, MAT_COL_GLASSF},
	[MAT_ID_IRON] = {process_material, MAT_COL_IRON},
	[MAT_ID_HOTIRON] = {process_material, MAT_COL_HOTIRON},
	[MAT_ID_WIND] = {process_material, MAT_COL_EMPTY},
};

void render_fluidmap(t_data *data) {
	int y;
	int x;
	int c;

	y = -1;
	while (++y < WINY) {
		x = -1;
		while (++x < WINX) {
			c = data->fsim->map[y][x];
			if (c == 'z')
				process_material(x, y, data, 0x555555);
			else if (c == MAT_ID_EMPTY) {
				process_material(x, y, data, MAT_COL_EMPTY);
				post_processing(x, y, data, MAT_ID_FIRE, MAT_COL_FIREG);
				post_processing(x, y, data, MAT_ID_LAVA, MAT_COL_FIREG);
				post_processing(x, y, data, MAT_ID_MOLTENIRON,
								MAT_COL_MOLTENIRONG);
				post_processing(x, y, data, MAT_ID_HOTIRON, MAT_COL_HOTIRONG);
				post_processing(x, y, data, MAT_ID_WATER, MAT_COL_WATER);
				post_processing(x, y, data, MAT_ID_BUBBLE, MAT_COL_BUBBLE);
				post_processing(x, y, data, MAT_ID_HIDROGEN, MAT_COL_HIDROGENG);
				post_processing(x, y, data, MAT_ID_OXYGEN, MAT_COL_OXYGENG);
				post_processing(x, y, data, MAT_ID_FOG, MAT_COL_FOGG);
				post_processing(x, y, data, MAT_ID_GLASS, MAT_COL_GLASSF);
			} else if (c == MAT_ID_GLASS) {
				if ((y + x) % 4)
					process_material(x, y, data, MAT_COL_GLASS);
				else
					process_material(x, y, data, MAT_COL_GLASS + 0x222233);
			} else if (c == MAT_ID_WETSAND) {
				if (((y % 3) + x % 3) > 0)
					process_material(x, y, data, MAT_COL_WETSAND);
				else
					process_material(x, y, data, MAT_COL_WETSAND - 0x111111);
			} else if (c == MAT_ID_SAND) {
				if (((y % 3) + x % 3) > 0)
					process_material(x, y, data, MAT_COL_SAND);
				else
					process_material(x, y, data, MAT_COL_SAND - 0x111111);
			} else if (c == MAT_ID_FIRE) {
				if (rand() % 20)
					process_material(x, y, data, MAT_COL_FIRE);
				else
					process_material(x, y, data, MAT_COL_FIREF);

			} else if (c == MAT_ID_SMOKE) {
				if (rand() % 7)
					process_material(x, y, data, MAT_COL_SMOKE);
				else
					process_material(x, y, data, MAT_COL_SMOKEG);
			} else {
				pplookup[c].f(x, y, data, pplookup[c].param);
			}
		}
	}
}

static const t_matlookup matlookup[] = {
	[MAT_ID_EMPTY] = {0, 0, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_HIDROGEN] = {0, emulate_hidrogen, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_OXYGEN] = {0, emulate_oxygen, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_BUBBLE] = {0, emulate_soap_bubble, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_STEAM] = {0, 0, 0, emulate_steam, {0, 0, 0, 0, 0}},
	[MAT_ID_PROPANE] = {0, emulate_propane, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_EMBER] = {0, 0, 0, 0, {0, 0, 0, 0, 0}}, // EMBER
	[MAT_ID_FIRE] = {0, emulate_fire, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_SMOKE] = {0, emulate_smoke, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_FOG] = {0, emulate_fog, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_FLY] = {0, emulate_fly, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_SALT] = {0, 0, 0, 0, {0, 0, 0, 0, 0}}, // SALT
	[MAT_ID_ACID] = {0, 0, 0, emulate_acid, {0, 0, 0, 0, 0}},
	[MAT_ID_OIL] = {0, 0, 0, emulate_oil, {0, 0, 0, 0, 0}},
	[MAT_ID_OILF] = {0, 0, 0, emulate_oilf, {0, 0, 0, 0, 0}},
	[MAT_ID_WATER] = {0, 0, 0, emulate_water, {0, 0, 0, 0, 0}},
	[MAT_ID_MOLTENIRON] = {0, 0, 0, emulate_molteniron, {0, 0, 0, 0, 0}},
	[MAT_ID_LAVA] = {0, 0, 0, emulate_lava, {0, 0, 0, 0, 0}},
	[MAT_ID_MISSILE] = {emulate_missile, 0, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_GUNPOWDER] = {emulate_gunpowder, 0, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_SOAP] = {emulate_soap, 0, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_SAND] = {0, 0, emulate_solid, 0, {2, 3, 4, 1, 10}},
	[MAT_ID_WETSAND] = {0, 0, emulate_wetsand, 0, {2, 2, 5, 2, 6}},
	[MAT_ID_STONE] = {0, 0, emulate_solid, 0, {1, -1, 8, 10, 1}},
	[MAT_ID_RUST] = {emulate_rust, 0, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_WOOD] = {emulate_wood, 0, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_WOODF] = {emulate_woodf, 0, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_GLASS] = {0, 0, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_GLASSF] = {emulate_glassf, 0, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_IRON] = {emulate_iron, 0, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_HOTIRON] = {emulate_hotiron, 0, 0, 0, {0, 0, 0, 0, 0}},
	[MAT_ID_WIND] = {0, 0, 0, 0, {0, 0, 0, 0, 0}}, // WIND
};

void process_gravity(t_data *data) {
	int y;
	int x;
	int c;

	y = WINY;
	while (--y > 0) {
		x = 0;
		while (++x < WINX) {
			c = data->fsim->map[y][x];
			if (c >= MAT_ID_EMPTY && c <= MAT_ID_WIND) {
				if (matlookup[c].f != NULL)
					matlookup[c].f(x, y, data);
				else if (matlookup[c].fi != NULL)
					matlookup[c].fi(x, y, data);
				else if (matlookup[c].fic != NULL)
					matlookup[c].fic(x, y, data, c);
				else if (matlookup[c].fie != NULL)
					matlookup[c].fie(x, y, data, matlookup[c].param.i,
									 matlookup[c].param.j, matlookup[c].param.k,
									 matlookup[c].param.l,
									 matlookup[c].param.m);
			}
		}
	}
}

void fluidsim_start(t_data *data) {
	static int i = 0;

	if (i <= 2000000000)
		i += 1;
	else
		i = 0;
	process_gravity(data);
	render_fluidmap(data);
}

void render_per_pixel(int x, int y, t_data *data) {
	render_fluidmap_pp(x, y, data);
	if (x + 1 < WINX) render_fluidmap_pp(x + 1, y, data);
	if (x - 1 > 0) render_fluidmap_pp(x - 1, y, data);
	if (y + 1 < WINY) render_fluidmap_pp(x, y + 1, data);
	if (y - 1 > 0) render_fluidmap_pp(x, y - 1, data);
	if (y - 1 > 0 && x - 1 > 0) render_fluidmap_pp(x - 1, y - 1, data);
	if (y - 1 > 0 && x + 1 < WINX) render_fluidmap_pp(x + 1, y - 1, data);
	if (y + 1 < WINY && x - 1 > 0) render_fluidmap_pp(x - 1, y + 1, data);
	if (y + 1 < WINY && x + 1 < WINX) render_fluidmap_pp(x + 1, y + 1, data);
}

void post_processing_pp(int x, int y, t_data *data, char id, int col) {
	if (data->fsim->map[y][x] != id) return;
	if (x + 1 < WINX) {
		if (data->fsim->map[y][x - 1] == MAT_ID_EMPTY) {
			pixel_to_img((x - 1) * 2 + 1, y * 2, data, col);
			pixel_to_img((x - 1) * 2 + 1, y * 2 + 1, data, col);
		}
	}
	if (x - 1 > 0) {
		if (data->fsim->map[y][x + 1] == MAT_ID_EMPTY) {
			pixel_to_img((x + 1) * 2, y * 2, data, col);
			pixel_to_img((x + 1) * 2, y * 2 + 1, data, col);
		}
	}
	if (y + 1 < WINY) {
		if (data->fsim->map[y - 1][x] == MAT_ID_EMPTY) {
			pixel_to_img(x * 2, (y - 1) * 2 + 1, data, col);
			pixel_to_img(x * 2 + 1, (y - 1) * 2 + 1, data, col);
		}
	}
	if (y - 1 > 0) {
		if (data->fsim->map[y + 1][x] == MAT_ID_EMPTY) {
			pixel_to_img(x * 2, (y + 1) * 2, data, col);
			pixel_to_img(x * 2 + 1, (y + 1) * 2, data, col);
		}
	}
}

void render_fluidmap_pp(int x, int y, t_data *data) {
	if (data->fsim->map[y][x] == 'z')
		process_material(x, y, data, 0x555555);
	else if (data->fsim->map[y][x] == MAT_ID_EMPTY)
		process_material(x, y, data, MAT_COL_EMPTY);
	else if (data->fsim->map[y][x] == MAT_ID_GLASSF)
		process_material(x, y, data, MAT_COL_GLASSF);
	else if (data->fsim->map[y][x] == MAT_ID_GLASS) {
		if ((y + x) % 4)
			process_material(x, y, data, MAT_COL_GLASS);
		else
			process_material(x, y, data, MAT_COL_GLASS + 0x222233);
	} else if (data->fsim->map[y][x] == MAT_ID_WOODF)
		process_material(x, y, data, MAT_COL_WOODF);
	else if (data->fsim->map[y][x] == MAT_ID_WOOD)
		process_material(x, y, data, MAT_COL_WOOD);
	else if (data->fsim->map[y][x] == MAT_ID_STONE)
		process_material(x, y, data, MAT_COL_STONE);
	else if (data->fsim->map[y][x] == MAT_ID_WETSAND) {
		if (((y % 3) + x % 3) > 0)
			process_material(x, y, data, MAT_COL_WETSAND);
		else
			process_material(x, y, data, MAT_COL_WETSAND - 0x111111);
	} else if (data->fsim->map[y][x] == MAT_ID_SAND) {
		if (((y % 3) + x % 3) > 0)
			process_material(x, y, data, MAT_COL_SAND);
		else
			process_material(x, y, data, MAT_COL_SAND - 0x111111);
	} else if (data->fsim->map[y][x] == MAT_ID_SOAP)
		process_material(x, y, data, MAT_COL_SOAP);
	else if (data->fsim->map[y][x] == MAT_ID_GUNPOWDER)
		process_material(x, y, data, MAT_COL_GUNPOWDER);
	else if (data->fsim->map[y][x] == MAT_ID_LAVA)
		process_material(x, y, data, MAT_COL_LAVA);
	else if (data->fsim->map[y][x] == MAT_ID_WATER)
		process_material(x, y, data, MAT_COL_WATER);
	else if (data->fsim->map[y][x] == MAT_ID_OIL)
		process_material(x, y, data, MAT_COL_OIL);
	else if (data->fsim->map[y][x] == MAT_ID_OILF)
		process_material(x, y, data, MAT_COL_OILF);
	else if (data->fsim->map[y][x] == MAT_ID_ACID)
		process_material(x, y, data, MAT_COL_ACID);
	else if (data->fsim->map[y][x] == MAT_ID_SALT)
		process_material(x, y, data, MAT_COL_SALT);
	else if (data->fsim->map[y][x] == MAT_ID_FLY)
		process_material(x, y, data, MAT_COL_FLY);
	else if (data->fsim->map[y][x] == MAT_ID_FOG)
		process_material(x, y, data, MAT_COL_FOG);
	else if (data->fsim->map[y][x] == MAT_ID_FIRE) {
		if (rand() % 20)
			process_material(x, y, data, MAT_COL_FIRE);
		else
			process_material(x, y, data, MAT_COL_FIREF);

	} else if (data->fsim->map[y][x] == MAT_ID_EMBER)
		process_material(x, y, data, MAT_COL_EMBER);
	else if (data->fsim->map[y][x] == MAT_ID_SMOKE) {
		if (rand() % 7)
			process_material(x, y, data, MAT_COL_SMOKE);
		else
			process_material(x, y, data, MAT_COL_SMOKEG);
	} else if (data->fsim->map[y][x] == MAT_ID_PROPANE)
		process_material(x, y, data, MAT_COL_PROPANE);
	else if (data->fsim->map[y][x] == MAT_ID_STEAM)
		process_material(x, y, data, MAT_COL_STEAM);
	else if (data->fsim->map[y][x] == MAT_ID_BUBBLE)
		process_material(x, y, data, MAT_COL_EMPTY);
	else if (data->fsim->map[y][x] == MAT_ID_OXYGEN)
		process_material(x, y, data, MAT_COL_OXYGEN);
	else if (data->fsim->map[y][x] == MAT_ID_HIDROGEN)
		process_material(x, y, data, MAT_COL_HIDROGEN);
	post_processing_pp(x, y, data, MAT_ID_FIRE, MAT_COL_FIREG);
	post_processing_pp(x, y, data, MAT_ID_LAVA, MAT_COL_FIREG);
	post_processing_pp(x, y, data, MAT_ID_WATER, MAT_COL_WATER);
	post_processing_pp(x, y, data, MAT_ID_BUBBLE, MAT_COL_BUBBLE);
	post_processing_pp(x, y, data, MAT_ID_HIDROGEN, MAT_COL_HIDROGENG);
	post_processing_pp(x, y, data, MAT_ID_OXYGEN, MAT_COL_OXYGENG);
	post_processing_pp(x, y, data, MAT_ID_FOG, MAT_COL_FOGG);
	post_processing_pp(x, y, data, MAT_ID_GLASS, MAT_COL_GLASSF);
}

void circle_calc(int xc, int yc, int x, int y, t_data *data) {
	if (xc <= 0 || xc >= WINX) return;
	if (yc <= 0 || yc >= WINX) return;
	if ((yc + y > 0 && yc + y < WINY) && (xc + x > 0 && xc + x < WINX)) {
		if (data->fsim->map[yc + y][xc + x] != 'z') {
			if (data->click_fill == MAT_ID_EMPTY)
				data->fsim->map[yc + y][xc + x] = data->click_fill;
			else if (data->fsim->map[yc + y][xc + x] == MAT_ID_EMPTY)
				data->fsim->map[yc + y][xc + x] = data->click_fill;
		}
	}
	if ((yc + y > 0 && yc + y < WINY) && (xc - x > 0 && xc - x < WINX)) {
		if (data->fsim->map[yc + y][xc - x] != 'z') {
			if (data->click_fill == MAT_ID_EMPTY)
				data->fsim->map[yc + y][xc - x] = data->click_fill;
			else if (data->fsim->map[yc + y][xc - x] == MAT_ID_EMPTY)
				data->fsim->map[yc + y][xc - x] = data->click_fill;
		}
	}
	if ((yc - y > 0 && yc - y < WINY) && (xc + x > 0 && xc + x < WINX)) {
		if (data->fsim->map[yc - y][xc + x] != 'z') {
			if (data->click_fill == MAT_ID_EMPTY)
				data->fsim->map[yc - y][xc + x] = data->click_fill;
			else if (data->fsim->map[yc - y][xc + x] == MAT_ID_EMPTY)
				data->fsim->map[yc - y][xc + x] = data->click_fill;
		}
	}
	if ((yc - y > 0 && yc - y < WINY) && (xc - x > 0 && xc - x < WINX)) {
		if (data->fsim->map[yc - y][xc - x] != 'z') {
			if (data->click_fill == MAT_ID_EMPTY)
				data->fsim->map[yc - y][xc - x] = data->click_fill;
			else if (data->fsim->map[yc - y][xc - x] == MAT_ID_EMPTY)
				data->fsim->map[yc - y][xc - x] = data->click_fill;
		}
	}
	if ((yc + x > 0 && yc + x < WINY) && (xc + y > 0 && xc + y < WINX)) {
		if (data->fsim->map[yc + x][xc + y] != 'z') {
			if (data->click_fill == MAT_ID_EMPTY)
				data->fsim->map[yc + x][xc + y] = data->click_fill;
			else if (data->fsim->map[yc + x][xc + y] == MAT_ID_EMPTY)
				data->fsim->map[yc + x][xc + y] = data->click_fill;
		}
	}
	if ((yc + x > 0 && yc + x < WINY) && (xc - y > 0 && xc - y < WINX)) {
		if (data->fsim->map[yc + x][xc - y] != 'z') {
			if (data->click_fill == MAT_ID_EMPTY)
				data->fsim->map[yc + x][xc - y] = data->click_fill;
			else if (data->fsim->map[yc + x][xc - y] == MAT_ID_EMPTY)
				data->fsim->map[yc + x][xc - y] = data->click_fill;
		}
	}
	if ((yc - x > 0 && yc - x < WINY) && (xc + y > 0 && xc + y < WINX)) {
		if (data->fsim->map[yc - x][xc + y] != 'z') {
			if (data->click_fill == MAT_ID_EMPTY)
				data->fsim->map[yc - x][xc + y] = data->click_fill;
			else if (data->fsim->map[yc - x][xc + y] == MAT_ID_EMPTY)
				data->fsim->map[yc - x][xc + y] = data->click_fill;
		}
	}
	if ((yc - x > 0 && yc - x < WINY) && (xc - y > 0 && xc - y < WINX)) {
		if (data->fsim->map[yc - x][xc - y] != 'z') {
			if (data->click_fill == MAT_ID_EMPTY)
				data->fsim->map[yc - x][xc - y] = data->click_fill;
			else if (data->fsim->map[yc - x][xc - y] == MAT_ID_EMPTY)
				data->fsim->map[yc - x][xc - y] = data->click_fill;
		}
	}
}

void circle_putmat(int xc, int yc, int r, t_data *data) {
	int x;
	int y;
	int d;

	if (r < 0) return;
	x = 0;
	y = r;
	d = 3 - 2 * r;
	circle_calc(xc, yc, x, y, data);
	while (y >= x) {
		x++;
		if (d > 0) {
			y--;
			d = d + 4 * (x - y) + 10;
		} else
			d = d + 4 * x + 6;
		circle_calc(xc, yc, x, y, data);
	}
	circle_putmat(xc, yc, r - 1, data);
}

void put_mat(int x, int y, t_data *data) {
	int i;
	int j;

	if (x <= 0 || x >= WINX) return;
	if (y <= 0 || y >= WINY) return;
	i = y - data->brush_size;
	while (i <= y + data->brush_size) {
		j = x - data->brush_size;
		while (j <= x + data->brush_size) {
			if ((i > 0 && i < WINY) && (j > 0 && j < WINX)) {
				if (data->fsim->map[i][j] != 'z') {
					if (data->click_fill == MAT_ID_EMPTY)
						data->fsim->map[i][j] = data->click_fill;
					else if (data->fsim->map[i][j] == MAT_ID_EMPTY)
						data->fsim->map[i][j] = data->click_fill;
				}
			}
			j++;
		}
		i++;
	}
}
