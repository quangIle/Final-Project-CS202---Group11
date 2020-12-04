#pragma once
#include "player.h"

//
void Player::InitString()
{
    _STRING.assign(3, "");
    _STRING[0] = " o ";
    _STRING[1] = "/|\\";
    _STRING[2] = "/ \\";
}

//
void Player::Up()
{
    _Pos.SetY(6 * -floor(_Distance));
}
void Player::Left()
{
    _Pos.SetX(-floor(_Distance));
}
void Player::Right()
{
    _Pos.SetX(floor(_Distance));
}
void Player::Down()
{
    _Pos.SetY(6 * floor(_Distance));
}

//
Player::Player()
{
    Player::InitString();
}
Player::~Player() {}

//
void Player::InputFromKeyboard(const int &ElapsedTime)
{
    _DistanceSum = 1.0 * ElapsedTime / DIVIDE_CONSTANT;
    _Distance += _DistanceSum;

    if ((GetAsyncKeyState((unsigned short)'A') & 0x8000))
        Player::Left();

    if ((GetAsyncKeyState((unsigned short)'D') & 0x8000))
        Player::Right();

    if ((GetAsyncKeyState((unsigned short)'W') & 0x8000))
        Player::Up();

    if ((GetAsyncKeyState((unsigned short)'S') & 0x8000))
        Player::Down();

    if (_Distance > 1)
        _Distance = 0;
}