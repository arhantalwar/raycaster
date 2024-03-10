#include <math.h>
#include <raylib.h>

#define width 1024
#define height 720
#define pi 3.14159

#define world_size 8

typedef struct Quad {
    Vector3 x1;
    Vector3 x2;
    Vector3 y1;
    Vector3 y2;
} Quad;

typedef struct PlayerVector {
    float px;
    float py;
    float pdx;
    float pdy;
    float pa;
} pVector;

void draw_map(int map[][world_size]) {
    for (int i = 0; i < world_size; i++) {
        for (int j = 0; j < world_size; j++) {
            if (map[j][i] == 1) {

                DrawRectangle(i * 64, j * 64, 64, 64, WHITE);
                DrawLine(0, j * 64, 512, j * 64, RAYWHITE);
                DrawLine(i * 64, 0, i * 64, 512, RAYWHITE);

            } else {

                DrawRectangle(i * 64, j * 64, 64, 64, BLACK);
                DrawLine(0, j * 64, 512, j * 64, RAYWHITE);
                DrawLine(i * 64, 0, i * 64, 512, RAYWHITE);

            }
        }
    }
}

void draw_player(pVector player_position) {
    DrawRectangle(player_position.px, player_position.py, 32, 32, RED);
}

void draw_ray(pVector player_position) {

    Ray r = {
        .direction = (Vector3) {
            .x = player_position.pdx,
            .y = player_position.pdy,
            .z = 0
        },
        .position = (Vector3) {
            .x = player_position.px + 16,
            .y = player_position.py + 16,
            .z = 0
        }
    };

    DrawRay(r, GREEN);

}

int main() {

    int map[world_size][world_size] = {
        {1, 1, 1, 1, 1, 1, 1 ,1},
        {1, 0, 1, 0, 0, 0, 0 ,1},
        {1, 0, 1, 0, 0, 0, 0 ,1},
        {1, 0, 1, 0, 0, 0, 0 ,1},
        {1, 0, 1, 0, 0, 0, 0 ,1},
        {1, 0, 0, 0, 0, 1, 0 ,1},
        {1, 0, 0, 0, 0, 0, 0 ,1},
        {1, 1, 1, 1, 1, 1, 1 ,1},
    };

    SetTraceLogLevel(LOG_WARNING);
    SetTargetFPS(60);
    InitWindow(width, height, "3D");

    pVector player_position = {
        .pa = 0,
        .px = 64 * 4,
        .py = 64 * 4,
    };

    draw_map(map);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);

        draw_map(map);

        if (IsKeyDown(KEY_A)) {

            player_position.pa -= 0.1;

            if (player_position.pa < 0) {
                player_position.pa += 2 * pi;
            }

            player_position.pdx = cos(player_position.pa) * 3;
            player_position.pdy = sin(player_position.pa) * 3;

        } else if (IsKeyDown(KEY_D)) {

            player_position.pa += 0.1;

            if (player_position.pa > 2 * pi) {
                player_position.pa -= 2 * pi;
            }

            player_position.pdx = cos(player_position.pa) * 3;
            player_position.pdy = sin(player_position.pa) * 3;

        }

        if (IsKeyDown(KEY_W)) {

            player_position.px += player_position.pdx;
            player_position.py += player_position.pdy;

        } else if (IsKeyDown(KEY_S)) {

            player_position.px -= player_position.pdx;
            player_position.py -= player_position.pdy;

        }

        draw_player(player_position);
        draw_ray(player_position);

        EndDrawing();

    }


    return 0;

}
