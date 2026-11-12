#include "raylib.h"
#include "entities/player/player.hpp"
#include "entities/enemies/enemy.hpp"

const int kScreenWidth = 1200 , kScreenHeight = 900;
const int kTargetFps = 67;

void drawRoom(){
    DrawRectangleLinesEx(Rectangle{0.0f , 0.0f , static_cast<float>(kScreenWidth) , static_cast<float>(kScreenHeight)} , kRoomBorderWidth , BLACK);
}

void setupFrame(Player &player , Enemy &enemy , float deltaTime){
    player.inputHandler(deltaTime);
    if (enemy.isPlayerInRange(player)) enemy.update(Vector2{} , deltaTime);
    else enemy.chasePlayer(player , deltaTime);
}

int main(){
    InitWindow(kScreenWidth , kScreenHeight , "One Room One Enemy");
    SetTargetFPS(kTargetFps);

    const Texture2D playerTexture = LoadTexture(TextFormat("%sassets/reze_idle.png" , GetApplicationDirectory()));
    if (!IsTextureValid(playerTexture)) {
        CloseWindow();
        return 1;
    }
    SetTextureFilter(playerTexture , TEXTURE_FILTER_POINT);
    const Texture2D bossTexture = LoadTexture(TextFormat("%sassets/makima_idle.png" , GetApplicationDirectory()));
    if (!IsTextureValid(bossTexture)) {
        UnloadTexture(playerTexture);
        CloseWindow();
        return 1;
    }
    SetTextureFilter(bossTexture , TEXTURE_FILTER_POINT);
    Player player;
    Enemy enemy;

    while (!WindowShouldClose()){
        const float deltaTime = GetFrameTime();
        setupFrame(player , enemy , deltaTime);
        

        BeginDrawing();
        ClearBackground(GRAY);

        drawRoom();
        player.draw(playerTexture);
        enemy.draw(bossTexture);

        EndDrawing();
    }

    UnloadTexture(bossTexture);
    UnloadTexture(playerTexture);
    CloseWindow();
}
