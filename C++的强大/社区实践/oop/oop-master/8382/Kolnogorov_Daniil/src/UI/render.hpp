#pragma once

#include "../Game/Tiles/tiles.hpp"
#include "../Game/Units/unit_factory.hpp"
#include "../Game/game_facade.hpp"
#include "positioner.hpp"
#include <raylib.h>
#include <vector>

#define TILE_SIZE 32
#define TILE_SIZE_VEC                                                          \
    { TILE_SIZE, TILE_SIZE }

typedef enum scenes {
    SCENE_MENU,
    SCENE_PAUSE,
    SCENE_NEWGAME,
    SCENE_RUNNING,
} scene_type;

class Renderer {
protected:
    GameFacadeInterface* game;
    Positioner* positioner;
    int screen_width;
    int screen_height;

    bool escape_handled; // TODO remove this

    // config
    bool should_close = false;
    scene_type current_scene;
    scene_type previous_scene;
    bool game_initialised;
    bool show_info;
    bool show_help;
    bool mouse_hover_handled;
    bool mouse_click_handled;

    // all units available for creation
    vector<UnitInterface*> available_units;
    unsigned available_units_idx;

    // camera
    Camera2D camera;
    Vector2 camera_min_pos;
    Vector2 camera_max_pos;

    // info about selected tile
    bool selected;
    Coordinates selected_coors;
    TileInterface* selected_tile;
    vector<Coordinates> selected_reachable;

    // some useful boundaries
    Rectangle content_rect;

public:
    Renderer(GameFacadeInterface* game);
    ~Renderer();

    bool running() { return !should_close; }
    void init_new_game(unsigned width, unsigned height, unsigned players);
    void close();

    void render();

    // rendering game field
    void render_field();
    void render_tile(TileInterface* tile, Vector2 pos);
    void render_neutral(Vector2 pos, NeutralInterface* neutral);
    void render_unit(Vector2 pos, UnitInterface* unit, Color color,
                     float scale = 1.0);
    void render_base(Vector2 pos, Base* base);
    void render_reachable();

    void render_unit_creation();

    // rendering scenes
    void render_menu();
    void render_pause();
    void render_newgame();

    // highlighting tile
    void highlight_tile(Coordinates coors);
    void overlay_tile(Coordinates coors);
    void show_reachable(Coordinates coors);

    // handle input
    void handle_key_presses();
    void handle_mouse_presses();
    void set_selected(Coordinates coors);

    // game related stuff
    void draw_help();
    void draw_game_info();
    void draw_tile_info(TileInterface* tile, position box_position);
    void draw_text_rect(string text, Rectangle rect);

    // camera stuff
    Camera2D camera_init();
    void camera_update();
    void camera_fit();
    void camera_zoom(float before, float after);
    void camera_focus_at(Coordinates coors);

    // utils
    bool contains_point(Vector2 pos);

    // converting between coordinates on screen and field
    Vector2 get_real_pos(Vector2 pos);
    Vector2 get_pos_at(Coordinates coors);
    Vector2 get_pos_center_at(Coordinates coors);
    Vector2 get_pos_center_at_pos(Vector2 pos);
    Coordinates coors_at(Vector2 pos);

    Color color_of(unsigned player_id);
};
