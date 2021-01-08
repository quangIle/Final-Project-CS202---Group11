#pragma once
#include "vehicle.h"

#define WIDTH Console::MAP_WIDTH
#define HEIGHT Console::MAP_HEIGHT
#define MAP Console::MAP_LOCATION

//
Car::Car(int x, int y)
{
    _Direction = 1;
    _Pos = { x, y };
    _Pos.SetMax(MAP._x + WIDTH - 1, MAP._y + HEIGHT - 1);
    _Pos.SetMin(MAP._x - 4, MAP._y + 1);

    _STRING.assign(4, "");
    _STRING[0] = "  ______";
    _STRING[1] = " /|_||_\\`.__";
    _STRING[2] = "(   _    _ _\\";
    _STRING[3] = "=`-(_)--(_)-'";
}
Car::~Car() {}

//
Truck::Truck(int x, int y)
{
    _Direction = -1;
    _Pos = { x, y };
    _Pos.SetMax(MAP._x + WIDTH - 1, MAP._y + HEIGHT - 1);
    _Pos.SetMin(MAP._x - 18, MAP._y + 1);

    _STRING.assign(5, "");
    _STRING[0] = "        __________";
    _STRING[1] = "  ___  |          |";
    _STRING[2] = " /_| | |          |";
    _STRING[3] = "|    |_|__________|";
    _STRING[4] = "\"-O----O-O`    O`O`";
}
Truck::~Truck() {}

//
void Vehicle::CarMove(const int& ElapsedTime)
{
    for (auto i : _CarLane)
    {
        if (i->_Pos._x == i->_Pos.max_x)
        {
            delete i;
            _CarLane.pop_back();
        }
        else
            i->Move(ElapsedTime);
    }
}
void Vehicle::TruckMove(const int& ElapsedTime)
{
    int k = 0;
    for (auto i : _TruckLane)
    {
        if (i->_Pos._x == i->_Pos.min_x)
        {
            delete i;
            _TruckLane.pop_front();
        }
        else
            i->Move(ElapsedTime);
    }
}

//
Vehicle::Vehicle(const int& level, const bool& call_CreateObj)
{
    if (call_CreateObj)
        Vehicle::CreateObj();
    Object::ChangeLevel(level);
}
Vehicle::~Vehicle()
{
    for (auto i : _CarLane)
        delete i;
    for (auto i : _TruckLane)
        delete i;
}

//
void Vehicle::CreateObj()
{
    srand(time(NULL));
    Object* v;
    int _RandomDistance, NEW_LOCATION;
    //create 4 car obj with random distance
    //car1 car2 car3 car4
    for (int i = 0; i < 3; i++)
    {
        if (!i)
            v = new Car(MAP._x + 2, MAP._y + CAR_LOCATION_Y);
        else
        {
            _RandomDistance = rand() % 25 + 1;
            NEW_LOCATION = _CarLane[i - 1]->_Pos._x + CAR_LENGTH + _RandomDistance;

            v = new Car(NEW_LOCATION, MAP._y + CAR_LOCATION_Y);
        }
        _CarLane.push_back(v);
    }
}
void Vehicle::Move(const int& ElapsedTime)
{
    Vehicle::CarMove(ElapsedTime);
    Vehicle::AddRandomCar();

    Vehicle::TruckMove(ElapsedTime);
    Vehicle::AddRandomTruck();
}