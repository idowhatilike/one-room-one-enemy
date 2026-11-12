#include "src/entities/player/player.hpp"
#include "src/entities/enemies/enemy.hpp"
#include <cassert>
#include <cmath>

namespace {
    bool pressedKeys[512]{};
    Rectangle drawnSource{} , drawnDestination{};
    Vector2 drawnOrigin{};
    float drawnRotation = 0.0f;
}

extern "C" bool IsKeyDown(int key) {return pressedKeys[key];}
extern "C" int GetScreenWidth() {return 1200;}
extern "C" int GetScreenHeight() {return 900;}
extern "C" void DrawTexturePro(Texture2D , Rectangle source , Rectangle destination , Vector2 origin , float rotation , Color) {
    drawnSource = source , drawnDestination = destination;
    drawnOrigin = origin , drawnRotation = rotation;
}

void clearInput() {
    for (bool &pressed : pressedKeys) pressed = false;
}

bool closeEnough(float actual , float expected) {
    return std::abs(actual - expected) < 0.01f;
}

void checkDrawBounds() {
    const float angle = drawnRotation * DEG2RAD;
    for (float x : {0.0f , drawnDestination.width}) {
        for (float y : {0.0f , drawnDestination.height}) {
            const float offsetX = x - drawnOrigin.x , offsetY = y - drawnOrigin.y;
            const float screenX = drawnDestination.x + offsetX * std::cos(angle) - offsetY * std::sin(angle);
            const float screenY = drawnDestination.y + offsetX * std::sin(angle) + offsetY * std::cos(angle);
            assert(screenX >= kRoomBorderWidth && screenX <= 1200 - kRoomBorderWidth);
            assert(screenY >= kRoomBorderWidth && screenY <= 900 - kRoomBorderWidth);
        }
    }
}

void checkEnemyHelpers() {
    Enemy range;
    range._position = {0 , 0};
    assert(closeEnough(range.distanceTo(Vector2{3 , 4}) , 5));
    const Vector2 direction = range.directionTo(Vector2{3 , 4});
    assert(closeEnough(direction.x , 0.6f) && closeEnough(direction.y , 0.8f));
    const Vector2 zeroDirection = range.directionTo(range.getPos());
    assert(zeroDirection.x == 0 && zeroDirection.y == 0);
    assert(range.isPlayerInRange(Vector2{0 , 0}));
    assert(range.isPlayerInRange(Vector2{Enemy::kAtkRange , 0}));
    assert(!range.isPlayerInRange(Vector2{Enemy::kAtkRange + 0.01f , 0}));

    Player target;
    assert(!range.isPlayerInRange(target));
    range._position = target.getPos();
    assert(range.isPlayerInRange(target));

    Enemy chaser;
    const float initialDistance = chaser.distanceTo(target.getPos());
    chaser.chasePlayer(target , 0.1f);
    assert(closeEnough(chaser.distanceTo(target.getPos()) , initialDistance - 30));
    assert(chaser._state == MOVE_RUNNING && !chaser._facingRight);
    chaser.chasePlayer(target , 100);
    assert(closeEnough(chaser._position.x , target._position.x));
    assert(closeEnough(chaser._position.y , target._position.y));
    assert(chaser.isPlayerInRange(target));
    chaser.chasePlayer(target , 0.1f);
    assert(chaser._state == MOVE_IDLE);

    Enemy diagonalChaser;
    diagonalChaser.chasePlayer(Vector2{500 , 300} , 100);
    assert(closeEnough(diagonalChaser._position.x , 500));
    assert(closeEnough(diagonalChaser._position.y , 300));

    Enemy stopped;
    const Vector2 stoppedPosition = stopped.getPos();
    stopped.chasePlayer(target , 0);
    assert(stopped._position.x == stoppedPosition.x && stopped._state == MOVE_IDLE);
    stopped._moveSpeed._current = 0;
    stopped.chasePlayer(target , 1);
    assert(stopped._position.x == stoppedPosition.x && stopped._state == MOVE_IDLE);

    Player controlled;
    pressedKeys[KEY_D] = true;
    controlled.update(Vector2{-1 , 0} , 0.1f);
    assert(closeEnough(controlled._position.x , 570));
    clearInput();
}

int main() {
    checkEnemyHelpers();
    const Texture2D texture = {1 , 1920 , 1920 , 1 , PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
    Player player;
    player.inputHandler(0.1f);
    assert(player._state == MOVE_IDLE && player._animationTime == 0);
    player.draw(texture);
    assert(drawnDestination.width == 80 && drawnDestination.height == 80);
    assert(drawnDestination.x == 600 && drawnDestination.y == 450);
    assert(drawnOrigin.x == 40 && drawnOrigin.y == 40);
    assert(drawnRotation == 0);

    pressedKeys[KEY_D] = true;
    player.inputHandler(0.1f);
    assert(closeEnough(player._position.x , 630));
    assert(player._state == MOVE_RUNNING && player._facingRight);
    player.draw(texture);
    assert(drawnSource.width == 1920);
    assert(drawnDestination.y < player._position.y);
    assert(drawnDestination.width > 80 && drawnDestination.height < 80);
    assert(drawnRotation > 0 && drawnRotation <= 3);
    assert(closeEnough(drawnOrigin.x , drawnDestination.width / 2));

    clearInput();
    player.inputHandler(0.1f);
    player.draw(texture);
    assert(player._state == MOVE_IDLE && player._animationTime == 0);
    assert(drawnDestination.width == 80 && drawnDestination.height == 80);
    assert(drawnDestination.y == player._position.y && drawnRotation == 0);

    pressedKeys[KEY_A] = true;
    player.inputHandler(0.1f);
    player.draw(texture);
    assert(!player._facingRight && drawnSource.width == -1920);
    clearInput();
    pressedKeys[KEY_W] = true;
    player.inputHandler(0.1f);
    assert(!player._facingRight);

    clearInput();
    Player diagonal;
    pressedKeys[KEY_D] = true , pressedKeys[KEY_S] = true;
    diagonal.inputHandler(0.5f);
    assert(closeEnough(std::hypot(diagonal._position.x - 600 , diagonal._position.y - 450) , 150));

    clearInput();
    Player arrows;
    pressedKeys[KEY_UP] = true , pressedKeys[KEY_RIGHT] = true;
    arrows.inputHandler(0.5f);
    assert(closeEnough(std::hypot(arrows._position.x - 600 , arrows._position.y - 450) , 150));

    clearInput();
    Player opposite;
    pressedKeys[KEY_A] = true , pressedKeys[KEY_D] = true;
    opposite.inputHandler(0.5f);
    assert(opposite._position.x == 600 && opposite._state == MOVE_IDLE);

    clearInput();
    Player once , split;
    pressedKeys[KEY_D] = true;
    once.inputHandler(0.5f);
    for (int step = 0; step < 50; step ++) split.inputHandler(0.01f);
    assert(closeEnough(once._position.x , split._position.x));
    assert(closeEnough(once._animationTime , split._animationTime));

    Player blocked;
    blocked.inputHandler(100);
    const float wallX = blocked._position.x;
    assert(wallX + Player::kRadius <= 1200 - kRoomBorderWidth);
    blocked.inputHandler(0.5f);
    assert(blocked._position.x == wallX && blocked._state == MOVE_IDLE);

    Player paused;
    paused.inputHandler(0);
    assert(paused._position.x == 600 && paused._state == MOVE_IDLE);
    paused._moveSpeed._current = 0;
    paused.inputHandler(0.1f);
    assert(paused._position.x == 600 && paused._state == MOVE_IDLE);

    const int horizontalKeys[] = {KEY_A , KEY_D};
    const int verticalKeys[] = {KEY_W , KEY_S};
    for (int horizontalKey : horizontalKeys) {
        for (int verticalKey : verticalKeys) {
            clearInput();
            pressedKeys[horizontalKey] = true , pressedKeys[verticalKey] = true;
            Player corner;
            corner.inputHandler(100);
            const Vector2 cornerPosition = corner.getPos();
            corner.inputHandler(0.1f);
            assert(corner._position.x == cornerPosition.x && corner._position.y == cornerPosition.y);
            assert(corner._state == MOVE_IDLE);

            for (int phase = 0; phase < 360; phase ++) {
                corner._state = MOVE_RUNNING;
                corner._animationTime = static_cast<float>(phase) * DEG2RAD / 12.0f;
                corner.draw(texture);
                checkDrawBounds();
            }
        }
    }

    static_assert(Enemy::kRadius == Player::kRadius * 1.25f);
    Enemy portrait;
    portrait.draw(Texture2D{1 , 335 , 597 , 1 , PIXELFORMAT_UNCOMPRESSED_R8G8B8A8});
    assert(closeEnough(drawnDestination.height , 100));
    assert(closeEnough(drawnDestination.width , 100.0f * 335 / 597));
    assert(closeEnough(drawnOrigin.x , drawnDestination.width / 2));
    assert(closeEnough(drawnOrigin.y , 50));

    Enemy enemy;
    enemy.draw(texture);
    assert(drawnDestination.width == 100 && drawnDestination.height == 100);
    assert(drawnOrigin.x == 50 && drawnOrigin.y == 50);
    assert(enemy.getPos().x == 850 && enemy.getPos().y == 450);
    enemy.update(Vector2{} , 0.1f);
    assert(enemy.getPos().x == 850 && enemy.getPos().y == 450);
    assert(enemy._state == MOVE_IDLE);
    enemy.update(Vector2{-1 , -1} , 0.5f);
    assert(closeEnough(std::hypot(enemy._position.x - 850 , enemy._position.y - 450) , 150));
    assert(enemy._state == MOVE_RUNNING && !enemy._facingRight);
    enemy.draw(texture);
    assert(drawnSource.width < 0);
    enemy.update(Vector2{} , 0.1f);
    assert(enemy._state == MOVE_IDLE && enemy._animationTime == 0);

    Enemy enemyOnce , enemySplit;
    enemyOnce.update(Vector2{-1 , 0} , 0.5f);
    for (int step = 0; step < 50; step ++) enemySplit.update(Vector2{-1 , 0} , 0.01f);
    assert(closeEnough(enemyOnce._position.x , enemySplit._position.x));

    for (float x : {-1.0f , 1.0f}) {
        for (float y : {-1.0f , 1.0f}) {
            Enemy corner;
            corner.update(Vector2{x , y} , 100);
            const Vector2 cornerPosition = corner.getPos();
            corner.update(Vector2{x , y} , 0.1f);
            assert(corner._position.x == cornerPosition.x && corner._position.y == cornerPosition.y);
            assert(corner._state == MOVE_IDLE);
            for (int phase = 0; phase < 360; phase ++) {
                corner._state = MOVE_RUNNING;
                corner._animationTime = static_cast<float>(phase) * DEG2RAD / 12.0f;
                corner.draw(texture);
                checkDrawBounds();
            }
        }
    }
}
