#include <math.h>
#include <raylib.h>
#include <stdio.h>

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

Quad getQuad(Vector2 p1, Vector2 p2) {
    return (Quad){
        .x1 = (Vector3){.x = p1.x, .y = p1.y, .z = -5},
        .x2 = (Vector3){.x = p1.x, .y = p1.y, .z = 5},
        .y1 = (Vector3){.x = p2.x, .y = p2.y, .z = -5},
        .y2 = (Vector3){.x = p2.x, .y = p2.y, .z = 5}
    };
}

void draw_map(int map[][world_size], Quad quad_map[][4]) {
    for (int i = 0; i < world_size; i++) {
        for (int j = 0; j < world_size; j++) {
            if (map[j][i] == 1) {

                DrawRectangle(i * 64, j * 64, 64, 64, WHITE);

                //DrawCircle((i * 64), (j * 64), 5, BLUE);
                //DrawCircle((i * 64) + 64, (j * 64), 5, RED);
                //DrawCircle((i * 64) + 64, (j * 64) + 64, 5, GREEN);
                //DrawCircle((i * 64), (j * 64) + 64, 5, PURPLE);

                int points[4][2] = {
                    {(i * 64), (j * 64)},
                    {(i * 64) + 64, (j * 64)},
                    {(i * 64) + 64, (j * 64) + 64},
                    {(i * 64), (j * 64) + 64},
                };
                
                for (int l = 0; l < 2; l++) {

                    for (int k = 0; k < 4; k++) {

                        quad_map[0][k] = getQuad(
                                (Vector2) {
                                    .x = (i * 64),
                                    .y = (j * 64)
                                },
                                (Vector2) {
                                    .x = (i * 64) + 64,
                                    .y = (j * 64)
                                }
                        );

                    }
                
                }
                

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

void draw_ray(pVector player_position, Quad quad_map[][4]) {

    for (int i = 0; i < 4; i++) {

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

        Quad q;

        q = quad_map[0][i];

        RayCollision rc = GetRayCollisionQuad(r, q.x1, q.x2, q.y1, q.y2);

        if (rc.hit == true) {
            printf("HIT!\n");
        }

        DrawRay(r, GREEN);

    }

}

int main() {

    int map[world_size][world_size] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
    };

        /* {1, 1, 1, 1, 1, 1, 1 ,1}, */
        /* {1, 0, 1, 0, 0, 0, 0 ,1}, */
        /* {1, 0, 1, 0, 0, 0, 0 ,1}, */
        /* {1, 0, 1, 0, 0, 0, 0 ,1}, */
        /* {1, 0, 1, 0, 0, 0, 0 ,1}, */
        /* {1, 0, 0, 0, 0, 1, 0 ,1}, */
        /* {1, 0, 0, 0, 0, 0, 0 ,1}, */
        /* {1, 1, 1, 1, 1, 1, 1 ,1}, */

    Quad quad_map[1][4];

    SetTraceLogLevel(LOG_WARNING);
    SetTargetFPS(60);
    InitWindow(width, height, "3D");

    pVector player_position = {
        .pa = 0,
        .px = 64 * 4,
        .py = 64 * 4,
    };

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(BLACK);


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

        draw_map(map, quad_map);
        draw_player(player_position);
        draw_ray(player_position, quad_map);

        EndDrawing();

    }


    return 0;

}
