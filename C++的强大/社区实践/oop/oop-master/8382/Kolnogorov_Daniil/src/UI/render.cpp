#include "render.hpp"

#include "../Game/Commands/command_create_unit.hpp"
#include "../Game/Commands/command_end_game.hpp"
#include "../Game/Commands/command_load_game.hpp"
#include "../Game/Commands/command_new_game.hpp"
#include "../Game/Commands/command_next_player.hpp"
#include "../Game/Commands/command_save_game.hpp"
#include "../Game/Commands/command_unit_action.hpp"
#include "../Game/Commands/command_use_neutral.hpp"
#include "../Game/Commands/commands.hpp"
#include "../Game/Field/coordinates.hpp"
#include "../Game/Neutral/powerup.hpp"
#include "positioner.hpp"
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

Color player_colors[] = {RED, MAGENTA, YELLOW, ORANGE};
Color color_overlay = {255, 255, 255, 122};
Color color_overlay_enemy = {255, 255, 255, 122};

Renderer::Renderer(GameFacadeInterface* game) {
    this->game = game;
    screen_width = 1280;
    screen_height = 720;

    positioner = new Positioner(screen_width, screen_height);

    current_scene = SCENE_MENU;
    show_info = true;
    show_help = true;
    game_initialised = false;

    available_units = {
        new UnitWarrior, new UnitKnight,    new UnitArcher,
        new UnitArbalet, new UnitMageFrost, new UnitMageFire,
    };
    available_units_idx = 0;

    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screen_width, screen_height, "");
    SetWindowMinSize(800, 600);
    SetTargetFPS(60);
    SetExitKey(KEY_F10);

    camera = camera_init();

    Font font_default = GetFontDefault();
    font_default.baseSize = 20;
    GuiSetFont(font_default);
}

Renderer::~Renderer() {
    for (auto unit : available_units)
        delete unit;
    CloseWindow();
    delete positioner;
}

void Renderer::init_new_game(unsigned width, unsigned height,
                             unsigned players) {
    this->content_rect = {0.0f, 0.0f, (float)width * TILE_SIZE,
                          (float)height * TILE_SIZE};

    selected = false;
    selected_coors = {-1, -1};
    selected_tile = nullptr;
    game_initialised = true;

    camera = camera_init();
}

void Renderer::close() {
}

void Renderer::render() {
    if (WindowShouldClose()) {
        // game->execute(new CommandEndGame());
        should_close = true;
        return;
    }

    if (IsWindowResized()) {
        screen_width = GetScreenWidth();
        screen_height = GetScreenHeight();
        positioner->resize(screen_width, screen_height);
    }

    positioner->reset();

    escape_handled = false; // TODO temporary fix to a strange bug

    camera_update();

    Vector2 mouse_pos_real = get_real_pos(GetMousePosition());
    Coordinates mouse_coors = coors_at(mouse_pos_real);
    mouse_hover_handled = false;
    mouse_click_handled = false;

    BeginDrawing();
    if (game_initialised) {

        ClearBackground(BLACK);

        BeginMode2D(camera);

        render_field();

        // highlight selected tile and possible movements
        if (selected) {
            render_reachable();
            highlight_tile(selected_coors);
        }

        // overlay hovered tile
        if (contains_point(mouse_pos_real)) {
            overlay_tile(mouse_coors);
        }

        EndMode2D();

        // show info about hovered tile
        if (show_info && contains_point(mouse_pos_real)) {
            if (mouse_coors != selected_coors) {
                draw_tile_info(game->tile_at(mouse_coors), BOTTOM_RIGHT);
            }
        }

        // show info about selected tile
        if (selected) {
            draw_tile_info(selected_tile, TOP_RIGHT);
            if (selected_tile->get_type() == TILE_BASE &&
                ((Base*)selected_tile)->owner_id ==
                    game->get_current_player_id()) {
                render_unit_creation();
            }
        }

        // show help if F1 is pressed
        if (show_help) {
            draw_help();
        }

        draw_game_info();
    }

    switch (current_scene) {
    case SCENE_MENU:
        render_menu();
        break;
    case SCENE_PAUSE:
        render_pause();
        break;
    case SCENE_NEWGAME:
        render_newgame();
        break;
    default:
        break;
    }

    if (current_scene != SCENE_RUNNING) {
        EndDrawing();
        return;
    }

    // doing this at the end because each scene
    // can have it's own controls
    handle_key_presses();
    handle_mouse_presses();

    EndDrawing();
}

void Renderer::render_field() {
    // load only visible chunk of field
    Coordinates top_left = coors_at(get_real_pos({0, 0}));
    Coordinates bot_right =
        coors_at(get_real_pos({(float)screen_width, (float)screen_height}));
    for (int x = top_left.x; x < bot_right.x + 1; x++) {
        for (int y = top_left.y; y < bot_right.y + 1; y++) {
            TileInterface* tile = game->tile_at({x, y});
            if (tile) {
                Vector2 pos = get_pos_at({x, y});
                render_tile(tile, pos);
            }
        }
    }
}

void Renderer::render_tile(TileInterface* tile, Vector2 pos) {
    Rectangle rect = {pos.x, pos.y, TILE_SIZE, TILE_SIZE};

    switch (tile->get_type()) {
    case TILE_WALL:
        DrawRectangleV(pos, TILE_SIZE_VEC, BLACK);
        break;
    case TILE_WATER:
        DrawRectangleV(pos, TILE_SIZE_VEC, BLUE);
        break;
    case TILE_GRASS:
        DrawRectangleV(pos, TILE_SIZE_VEC, DARKGREEN);
        break;
    case TILE_BASE:
        render_base(pos, (Base*)tile);
        break;
    }

    // draw border
    DrawRectangleLinesEx(rect, 1, BLACK);

    // render neutral
    NeutralInterface* neutral = tile->get_neutral();
    if (neutral) {
        render_neutral(pos, neutral);
    }

    // render unit
    UnitInterface* unit = tile->get_unit();
    if (unit != nullptr) {
        Vector2 center = get_pos_center_at_pos(pos);
        render_unit(center, unit, color_of(unit->get_owner_id()));
    }
}

void Renderer::render_neutral(Vector2 pos, NeutralInterface* neutral) {
    if (!neutral) {
        return;
    }
    Vector2 pos_center = get_pos_center_at_pos(pos);
    unsigned radius = TILE_SIZE * 0.4 / 2;
    DrawCircleV(pos_center, radius, RED);
}

void Renderer::render_unit(Vector2 pos, UnitInterface* unit, Color color,
                           float scale) {
    unsigned radius = TILE_SIZE * 0.8 / 2 * scale;

    if (dynamic_cast<UnitWarrior*>(unit)) {
        DrawCircleV(pos, radius, color);
    } else if (dynamic_cast<UnitKnight*>(unit)) {
        DrawPoly(pos, 6, radius, 0, color);
    } else if (dynamic_cast<UnitArcher*>(unit)) {
        DrawPoly(pos, 3, radius, 0, color);
    } else if (dynamic_cast<UnitArbalet*>(unit)) {
        DrawPoly(pos, 5, radius, 0, color);
    } else if (dynamic_cast<UnitMageFrost*>(unit)) {
        DrawPoly(pos, 7, radius, 0, color);
    } else if (dynamic_cast<UnitMageFire*>(unit)) {
        DrawPoly(pos, 8, radius, 0, color);
    }
}

void Renderer::render_base(Vector2 pos, Base* base) {
    Color color = color_of(base->owner_id);
    DrawRectangleV(pos, TILE_SIZE_VEC, color);
}

void Renderer::render_reachable() {
    for (auto coors : selected_reachable) {
        overlay_tile(coors);
    }
}

void Renderer::render_unit_creation() {
    float scale = 1.5;

    int spacing = 10 * scale;
    int margins = 10 * scale;
    float tile_size_scaled = TILE_SIZE * scale;

    int total_units = available_units.size();

    Rectangle rect = positioner->rect_with_size(
        total_units * (tile_size_scaled + spacing) + margins,
        (tile_size_scaled + 20 * scale), BOTTOM_LEFT);

    DrawRectangleRounded(rect, 0.2, 8, {255, 255, 255, 220});
    DrawRectangleRoundedLines(rect, 0.2, 8, 3, BLACK);

    Rectangle unit_border = {rect.x + margins, rect.y + margins,
                             tile_size_scaled, tile_size_scaled};

    for (unsigned i = 0; i < available_units.size(); i++) {
        if (i == available_units_idx) {
            DrawRectangleRoundedLines(unit_border, 0.2, 8, 2, ORANGE);
        }
        Vector2 center = Positioner::center_of_rect(unit_border);
        render_unit(center, available_units[i], GRAY, scale);
        unit_border.x += tile_size_scaled + spacing;
    }

    string unit_info = available_units[available_units_idx]->get_info();
    Rectangle rect_info = positioner->rect_for_text(unit_info, BOTTOM_LEFT);
    draw_text_rect(unit_info, rect_info);

    Vector2 mouse_pos = GetMousePosition();
    if (CheckCollisionPointRec(mouse_pos, rect)) {
        available_units_idx =
            (mouse_pos.x - rect.x - margins) / (TILE_SIZE * scale + spacing);
    }
}

void Renderer::render_menu() {
    Rectangle rect = positioner->rect_with_size(200, 200, CENTER);

    Rectangle button = {rect.x + 20, rect.y + 20, rect.width - 20 * 2, 40};

    ClearBackground(DARKGRAY);

    DrawRectangleRounded(rect, 0.1, 10, DARKGRAY);
    DrawRectangleRoundedLines(rect, 0.1, 10, 2, BLACK);

    if (GuiButton(button, "New Game")) {
        previous_scene = current_scene;
        current_scene = SCENE_NEWGAME;
    }
    button.y += button.height + 15;

    if (GuiButton(button, "Load")) {
        game->execute(new CommandLoadGame("save.txt"));
        if (game->is_running()) {
            current_scene = SCENE_RUNNING;

            init_new_game(game->get_width(), game->get_height(),
                          game->get_players());
        }
    }
    button.y += button.height + 15;

    if (GuiButton(button, "Quit")) {
        game->execute(new CommandEndGame());
        should_close = true;
    }
}

void Renderer::render_pause() {
    Rectangle rect = positioner->rect_with_size(200, 300, CENTER);

    Rectangle button = {rect.x + 20, rect.y + 20, rect.width - 20 * 2, 40};

    DrawRectangle(0, 0, screen_width, screen_height, Fade(DARKGRAY, 0.8f));
    DrawRectangleRounded(rect, 0.1, 10, DARKGRAY);
    DrawRectangleRoundedLines(rect, 0.1, 10, 2, BLACK);

    if (GuiButton(button, "Continue")) {
        current_scene = SCENE_RUNNING;
    }
    button.y += button.height + 15;

    if (GuiButton(button, "New game")) {
        previous_scene = current_scene;
        current_scene = SCENE_NEWGAME;
    }
    button.y += button.height + 15;

    if (GuiButton(button, "Load")) {
        game->execute(new CommandLoadGame("save.txt"));
        init_new_game(game->get_width(), game->get_height(),
                      game->get_players());
    }
    button.y += button.height + 15;

    if (GuiButton(button, "Save")) {
        game->execute(new CommandSaveGame("save.txt"));
    }
    button.y += button.height + 15;

    if (GuiButton(button, "Quit")) {
        game->execute(new CommandEndGame());
        should_close = true;
    }

    if (!escape_handled && IsKeyPressed(KEY_ESCAPE)) {
        escape_handled = true;
        current_scene = SCENE_RUNNING;
    }
}

void Renderer::render_newgame() {
    Rectangle rect = positioner->rect_with_size(300, 300, CENTER);

    Rectangle button = {rect.x + 20 + 75, rect.y + 20,
                        rect.width - 20 * 2 - 100, 40};

    static unsigned width = 40;
    static unsigned height = 40;
    static unsigned players = 2;

    if (previous_scene == SCENE_PAUSE) {
        DrawRectangle(0, 0, screen_width, screen_height, Fade(DARKGRAY, 0.8f));
    } else {
        ClearBackground(DARKGRAY);
    }

    DrawRectangleRounded(rect, 0.1, 10, DARKGRAY);
    DrawRectangleRoundedLines(rect, 0.1, 10, 2, BLACK);

    // TODO positioner should do this
    width = GuiSlider(button, "Width", TextFormat("%u", width), width, 40, 500);
    button.y += button.height + 15;

    height =
        GuiSlider(button, "Height", TextFormat("%u", height), height, 40, 500);
    button.y += button.height + 15;

    players =
        GuiSlider(button, "Players", TextFormat("%u", players), players, 2, 4);
    button.y += button.height + 15;

    if (GuiButton(button, "Start")) {
        game->execute(new CommandNewGame(width, height, players));
        init_new_game(width, height, players);
        current_scene = SCENE_RUNNING;
    }
    button.y += button.height + 15;

    if (GuiButton(button, "Cancel")) {
        current_scene = previous_scene;
    }

    if (!escape_handled && IsKeyPressed(KEY_ESCAPE)) {
        current_scene = previous_scene;
        escape_handled = true;
    }
}

void Renderer::highlight_tile(Coordinates coors) {
    Vector2 pos = get_pos_at(coors);
    Rectangle rect = {pos.x, pos.y, TILE_SIZE, TILE_SIZE};
    float thickness = max(1.0f, 1.0f / (camera.zoom - 0.25f));
    DrawRectangleLinesEx(rect, thickness, WHITE);
}

void Renderer::overlay_tile(Coordinates coors) {
    Vector2 pos = get_pos_at(coors);
    Rectangle rect = {pos.x, pos.y, TILE_SIZE, TILE_SIZE};
    DrawRectangleRec(rect, color_overlay);
}

void Renderer::handle_key_presses() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (!escape_handled && !selected) {
            current_scene = SCENE_PAUSE;
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(),
                          Fade(DARKGRAY, 0.8f));
        } else {
            selected = false;
            selected_coors = {-1, -1};
        }
        escape_handled = true;
    }

    long unsigned key = GetKeyPressed();
    long unsigned key_1 = 49;
    if (key >= key_1 && key < key_1 + available_units.size())
        available_units_idx = key - key_1;

    if (IsKeyPressed(KEY_I)) {
        show_info = !show_info;
    }

    if (IsKeyPressed(KEY_F1)) {
        show_help = !show_help;
    }

    if (IsKeyPressed(KEY_R)) {
        camera_zoom(camera.zoom, 1.0f);
    }

    if (IsKeyPressed(KEY_B) && game->get_current_player()->base) {
        Coordinates coors = game->get_current_player()->base->get_coors();
        camera_focus_at(coors);
        set_selected(coors);
    }

    if (IsKeyPressed(KEY_SPACE)) {
        game->execute(new CommandNextPlayer());
        selected = false;
        selected_coors = {-1, -1};
    }

    if (IsKeyPressed(KEY_U)) {
        game->execute(new CommandUseNeutral(selected_coors));
    }
}

void Renderer::handle_mouse_presses() {
    Vector2 mouse_pos = get_real_pos(GetMousePosition());
    Coordinates mouse_coors = coors_at(mouse_pos);

    bool lmb = IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
    bool rmb = IsMouseButtonReleased(MOUSE_RIGHT_BUTTON);

    if (lmb && contains_point(mouse_pos)) {
        set_selected(mouse_coors);
    }

    if (rmb && selected) {
        if (selected_tile->get_type() == TILE_BASE) {
            Coordinates new_coors = mouse_coors;
            game->execute(new CommandCreateUnit(
                new_coors, available_units[available_units_idx]->get_type()));
            selected = false;
        } else if (selected_tile->get_unit()) {
            game->execute(new CommandUnitAction(selected_coors, mouse_coors));
            selected = false;
        }
    }

    // zooming relative to the point
    // https://godotengine.org/qa/25983/camera2d-zoom-position-towards-the-mouse
    float before = camera.zoom;
    camera.zoom += 0.05 * GetMouseWheelMove();
    camera.zoom = max(0.5f, camera.zoom);
    camera.zoom = min(2.0f, camera.zoom);
    float after = camera.zoom;
    if (before != after) {
        camera_zoom(before, after);
    }
}

void Renderer::set_selected(Coordinates coors) {
    selected = true;
    selected_coors = coors;
    selected_tile = game->tile_at(coors);

    selected_reachable.clear();
    UnitInterface* unit = selected_tile->get_unit();
    if (selected_tile->get_type() == TILE_BASE)
        selected_reachable = game->get_reachable(coors);
    else if (unit && (game->unit_can_move(unit) ||
                      !game->is_owned_by(game->get_current_player_id(), unit)))
        selected_reachable = game->get_reachable(coors);
}

void Renderer::draw_help() {
    string text;
    text += "F1: toggle help\n";
    text += "ESC: menu\n";
    text += "SPACE: next turn\n";
    text += "1-6: select unit type\n";
    text += "i: toggle info\n";
    text += "r: reset zoom\n";
    text += "b: center base\n";
    text += "u: use neutral";
    Rectangle rect = positioner->rect_for_text(text, BOTTOM_LEFT);
    rect.width += 30;
    draw_text_rect(text, rect);
}

void Renderer::draw_game_info() {
    // DrawFPS(10, 10);

    string text = game->get_info();

    Rectangle rect = positioner->rect_for_text(text, TOP_LEFT);
    draw_text_rect(text, rect);
}

void Renderer::draw_tile_info(TileInterface* tile, position box_position) {
    if (!tile) {
        return;
    }
    string text = tile->get_info();

    Rectangle rect;
    rect = positioner->rect_for_text(text, box_position);

    draw_text_rect(text, rect);

    UnitInterface* unit = tile->get_unit();
    if (unit) {
        text = unit->get_info();
        rect = positioner->rect_for_text(text, box_position);
        draw_text_rect(text, rect);
    }

    Powerup* powerup = (Powerup*)tile->get_neutral();
    if (powerup) {
        text = powerup->get_info();
        rect = positioner->rect_for_text(text, box_position);
        draw_text_rect(text, rect);
    }
}

void Renderer::draw_text_rect(string text, Rectangle rect) {
    // roundness is a percentage, so using this hack to
    // make all rects with roughly the same rounded corners
    float roundness = 0.2 * 150 / rect.height;
    DrawRectangleRounded(rect, roundness, 8, {255, 255, 255, 220});
    DrawRectangleRoundedLines(rect, roundness, 8, 3, BLACK);

    rect.x += 3;
    rect.y += 3;
    rect.width -= 10;
    rect.height -= 10;

    DrawText(text.c_str(), rect.x + 10, rect.y + 10, 20, BLACK);
}

Camera2D Renderer::camera_init() {
    Camera2D camera;
    camera.target = {0, 0};
    camera.offset = {75, 75};
    camera.zoom = 1.0f;
    camera.rotation = 0;

    return camera;
}

void Renderer::camera_update() {
    if (IsKeyDown(KEY_A)) {
        camera.offset.x += 20;
    }
    if (IsKeyDown(KEY_D)) {
        camera.offset.x -= 20;
    }
    if (IsKeyDown(KEY_W)) {
        camera.offset.y += 20;
    }
    if (IsKeyDown(KEY_S)) {
        camera.offset.y -= 20;
    }
    camera_fit();
}

void Renderer::camera_fit() {
    camera.offset.x = min(camera.offset.x, screen_width / 2.0f);
    camera.offset.x =
        max(camera.offset.x, screen_width - content_rect.width * camera.zoom -
                                 screen_width / 2.0f);
    camera.offset.y = min(camera.offset.y, screen_height / 2.0f);
    camera.offset.y =
        max(camera.offset.y, screen_height - content_rect.height * camera.zoom -
                                 screen_height / 2.0f);
}

void Renderer::camera_zoom(float before, float after) {
    Vector2 mouse_pos = get_real_pos(GetMousePosition());
    camera.offset.x = camera.offset.x + (mouse_pos.x) * (before - after);
    camera.offset.y = camera.offset.y + (mouse_pos.y) * (before - after);
}

void Renderer::camera_focus_at(Coordinates coors) {
    camera.offset.x =
        -(coors.x * TILE_SIZE + TILE_SIZE / 2) * camera.zoom + screen_width / 2;
    camera.offset.y = -(coors.y * TILE_SIZE + TILE_SIZE / 2) * camera.zoom +
                      screen_height / 2;
}

Vector2 Renderer::get_real_pos(Vector2 pos) {
    pos.x = (pos.x - camera.offset.x) / camera.zoom;
    pos.y = (pos.y - camera.offset.y) / camera.zoom;
    return pos;
}

bool Renderer::contains_point(Vector2 pos) {
    return CheckCollisionPointRec(pos, content_rect);
}

Vector2 Renderer::get_pos_at(Coordinates coors) {
    return {(float)(coors.x * TILE_SIZE), (float)(coors.y * TILE_SIZE)};
}

Vector2 Renderer::get_pos_center_at_pos(Vector2 pos) {
    return {pos.x + TILE_SIZE / 2.0f, pos.y + TILE_SIZE / 2.0f};
}

Coordinates Renderer::coors_at(Vector2 pos) {
    return {(int)(pos.x / TILE_SIZE), (int)(pos.y / TILE_SIZE)};
}

Color Renderer::color_of(unsigned player_id) {
    return player_colors[player_id];
}
