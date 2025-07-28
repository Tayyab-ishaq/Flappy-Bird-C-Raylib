
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

Texture2D birdTex;
Texture2D bgTex;
Sound wingSound;
Sound swooshSound;
Sound pointSound;
Sound hitSound;
Sound dieSound;
#define SCREEN_WIDTH 1151
#define SCREEN_HEIGHT 720
#define GRAVITY 0.5f
#define FLAP_STRENGTH -8.0f
#define PIPE_WIDTH 80
#define PIPE_GAP 150
#define PIPE_COUNT 3
#define PIPE_SPACING 300
#define WOOD (Color){139, 69, 19, 255}

typedef struct
{
    float x, y, speedY;
    bool alive;
} Bird;
typedef struct
{
    float x, gapY;
    bool passed;
} Pipe;
static Bird bird;
static Pipe pipes[PIPE_COUNT];
static int score = 0;

void InitGame()
{
    bird.x = 100;
    bird.y = SCREEN_HEIGHT / 2;
    bird.speedY = 0;
    bird.alive = true;
    score = 0;
    srand(time(0));
    for (int i = 0; i < PIPE_COUNT; i++)
    {
        pipes[i].x = SCREEN_WIDTH + i * PIPE_SPACING;
        pipes[i].gapY = 100 + rand() % (SCREEN_HEIGHT - PIPE_GAP - 200);
        pipes[i].passed = false;
    }
}

bool CheckCollisionBirdPipe(Bird b, Pipe p)
{
    Rectangle birdR = {b.x - 10, b.y - 10, 20, 20};
    Rectangle top = {p.x, 0, PIPE_WIDTH, p.gapY};
    Rectangle bot = {p.x, p.gapY + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - p.gapY - PIPE_GAP};
    return CheckCollisionRecs(birdR, top) || CheckCollisionRecs(birdR, bot);
}

void ResetPipe(Pipe *p)
{
    p->x = SCREEN_WIDTH + PIPE_SPACING;
    p->gapY = 100 + rand() % (SCREEN_HEIGHT - PIPE_GAP - 200);
    p->passed = false;
}

void UpdateGame()
{
    if (bird.alive)
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            bird.speedY = FLAP_STRENGTH;
            PlaySound(wingSound);
        }
        bird.speedY += GRAVITY;
        bird.y += bird.speedY;

        for (int i = 0; i < PIPE_COUNT; i++)
        {
            pipes[i].x -= 3;
            if (!pipes[i].passed && bird.x > pipes[i].x + PIPE_WIDTH)
            {
                score++;
                pipes[i].passed = true;
                PlaySound(pointSound);
            }
            if (pipes[i].x < -PIPE_WIDTH)
                ResetPipe(&pipes[i]);
            if (CheckCollisionBirdPipe(bird, pipes[i]))
            {
                bird.alive = false;
                PlaySound(hitSound);
                PlaySound(dieSound);
            }
        }
        if (bird.y > SCREEN_HEIGHT || bird.y < 0)
        {
            bird.alive = false;
            PlaySound(dieSound);
        }
    }
    else if (IsKeyPressed(KEY_R))
    {
        PlaySound(swooshSound); // restart whoosh
        InitGame();
    }
}

void DrawGame()
{
    ClearBackground(RAYWHITE);
    DrawTexture(bgTex, 0, 0, WHITE);
    Vector2 birdPos = {bird.x - 25, bird.y - 18};                    // Adjust for center alignment
    Vector2 scale = {50.0f / birdTex.width, 36.0f / birdTex.height}; // Target size: 50x36
    DrawTextureEx(birdTex, birdPos, 0.0f, scale.x, WHITE);

    for (int i = 0; i < PIPE_COUNT; i++)
    {
        DrawRectangle(pipes[i].x, 0, PIPE_WIDTH, pipes[i].gapY, WOOD);
        DrawRectangle(pipes[i].x, pipes[i].gapY + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - pipes[i].gapY - PIPE_GAP, WOOD);
    }
    DrawRectangle(0, SCREEN_HEIGHT - 40, SCREEN_WIDTH, 40, DARKGRAY);
    DrawText(TextFormat("Score: %d", score), 10, 10, 24, BLACK);
    if (!bird.alive)
    {
        DrawText("GAME OVER", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 30, 40, RED);
        DrawText("Press R to Restart", SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT / 2 + 20, 20, DARKGRAY);
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird Clone - Raylib");
    birdTex = LoadTexture("bird.png");
    bgTex = LoadTexture("background.jpg");

    SetTargetFPS(60);
    InitAudioDevice();

    wingSound = LoadSound("sfx_wing.wav");
    swooshSound = LoadSound("sfx_swooshing.wav");
    pointSound = LoadSound("sfx_point.wav");
    hitSound = LoadSound("sfx_hit.wav");
    dieSound = LoadSound("sfx_die.wav");

    InitGame();
    while (!WindowShouldClose())
    {
        UpdateGame();
        BeginDrawing();
        DrawGame();
        EndDrawing();
    }
    UnloadTexture(birdTex);
    UnloadTexture(bgTex);
    UnloadSound(wingSound);
    UnloadSound(swooshSound);
    UnloadSound(pointSound);
    UnloadSound(hitSound);
    UnloadSound(dieSound);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

Texture2D birdTex;
Texture2D bgTex;
Sound wingSound;
Sound swooshSound;
Sound pointSound;
Sound hitSound;
Sound dieSound;
#define SCREEN_WIDTH 1151
#define SCREEN_HEIGHT 720
#define GRAVITY 0.5f
#define FLAP_STRENGTH -8.0f
#define PIPE_WIDTH 80
#define PIPE_GAP 150
#define PIPE_COUNT 3
#define PIPE_SPACING 300
#define WOOD (Color){139, 69, 19, 255}

typedef struct
{
    float x, y, speedY;
    bool alive;
} Bird;
typedef struct
{
    float x, gapY;
    bool passed;
} Pipe;
static Bird bird;
static Pipe pipes[PIPE_COUNT];
static int score = 0;

void InitGame()
{
    bird.x = 100;
    bird.y = SCREEN_HEIGHT / 2;
    bird.speedY = 0;
    bird.alive = true;
    score = 0;
    srand(time(0));
    for (int i = 0; i < PIPE_COUNT; i++)
    {
        pipes[i].x = SCREEN_WIDTH + i * PIPE_SPACING;
        pipes[i].gapY = 100 + rand() % (SCREEN_HEIGHT - PIPE_GAP - 200);
        pipes[i].passed = false;
    }
}

bool CheckCollisionBirdPipe(Bird b, Pipe p)
{
    Rectangle birdR = {b.x - 10, b.y - 10, 20, 20};
    Rectangle top = {p.x, 0, PIPE_WIDTH, p.gapY};
    Rectangle bot = {p.x, p.gapY + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - p.gapY - PIPE_GAP};
    return CheckCollisionRecs(birdR, top) || CheckCollisionRecs(birdR, bot);
}

void ResetPipe(Pipe *p)
{
    p->x = SCREEN_WIDTH + PIPE_SPACING;
    p->gapY = 100 + rand() % (SCREEN_HEIGHT - PIPE_GAP - 200);
    p->passed = false;
}

void UpdateGame()
{
    if (bird.alive)
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            bird.speedY = FLAP_STRENGTH;
            PlaySound(wingSound);
        }
        bird.speedY += GRAVITY;
        bird.y += bird.speedY;

        for (int i = 0; i < PIPE_COUNT; i++)
        {
            pipes[i].x -= 3;
            if (!pipes[i].passed && bird.x > pipes[i].x + PIPE_WIDTH)
            {
                score++;
                pipes[i].passed = true;
                PlaySound(pointSound);
            }
            if (pipes[i].x < -PIPE_WIDTH)
                ResetPipe(&pipes[i]);
            if (CheckCollisionBirdPipe(bird, pipes[i]))
            {
                bird.alive = false;
                PlaySound(hitSound);
                PlaySound(dieSound);
            }
        }
        if (bird.y > SCREEN_HEIGHT || bird.y < 0)
        {
            bird.alive = false;
            PlaySound(dieSound);
        }
    }
    else if (IsKeyPressed(KEY_R))
    {
        PlaySound(swooshSound); // restart whoosh
        InitGame();
    }
}

void DrawGame()
{
    ClearBackground(RAYWHITE);
    DrawTexture(bgTex, 0, 0, WHITE);
    Vector2 birdPos = {bird.x - 25, bird.y - 18};                    // Adjust for center alignment
    Vector2 scale = {50.0f / birdTex.width, 36.0f / birdTex.height}; // Target size: 50x36
    DrawTextureEx(birdTex, birdPos, 0.0f, scale.x, WHITE);

    for (int i = 0; i < PIPE_COUNT; i++)
    {
        DrawRectangle(pipes[i].x, 0, PIPE_WIDTH, pipes[i].gapY, WOOD);
        DrawRectangle(pipes[i].x, pipes[i].gapY + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - pipes[i].gapY - PIPE_GAP, WOOD);
    }
    DrawRectangle(0, SCREEN_HEIGHT - 40, SCREEN_WIDTH, 40, DARKGRAY);
    DrawText(TextFormat("Score: %d", score), 10, 10, 24, BLACK);
    if (!bird.alive)
    {
        DrawText("GAME OVER", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 30, 40, RED);
        DrawText("Press R to Restart", SCREEN_WIDTH / 2 - 110, SCREEN_HEIGHT / 2 + 20, 20, DARKGRAY);
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird Clone - Raylib");
    birdTex = LoadTexture("bird.png");
    bgTex = LoadTexture("background.jpg");

    SetTargetFPS(60);
    InitAudioDevice();

    wingSound = LoadSound("sfx_wing.wav");
    swooshSound = LoadSound("sfx_swooshing.wav");
    pointSound = LoadSound("sfx_point.wav");
    hitSound = LoadSound("sfx_hit.wav");
    dieSound = LoadSound("sfx_die.wav");

    InitGame();
    while (!WindowShouldClose())
    {
        UpdateGame();
        BeginDrawing();
        DrawGame();
        EndDrawing();
    }
    UnloadTexture(birdTex);
    UnloadTexture(bgTex);
    UnloadSound(wingSound);
    UnloadSound(swooshSound);
    UnloadSound(pointSound);
    UnloadSound(hitSound);
    UnloadSound(dieSound);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
