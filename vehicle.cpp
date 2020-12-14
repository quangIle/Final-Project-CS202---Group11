#pragma once
#include "vehicle.h"

//
Vehicle::Vehicle() {}
Vehicle::~Vehicle() {}

//
Car::Car() {}
Car::Car(int x, int y) : Vehicle()
{
    _Direction = 1;
    _Pos = {x, y};
    _Pos.SetMax(MAP_LOCATION._x + Console::MAP_WIDTH - 1, MAP_LOCATION._y + Console::MAP_HEIGHT - 1);
    _Pos.SetMin(MAP_LOCATION._x - 4, MAP_LOCATION._y + 1);
    _STRING.assign(4, "");
    _STRING[0] = "  ______";
    _STRING[1] = " /|_||_\\`.__";
    _STRING[2] = "(   _    _ _\\";
    _STRING[3] = "=`-(_)--(_)-'";
}
Car::~Car() {}

//
Truck::Truck() {}
Truck::Truck(int x, int y) : Vehicle()
{
    _Direction = -1;
    _Pos = {x, y};
    _Pos.SetMax(MAP_LOCATION._x + Console::MAP_WIDTH - 1, MAP_LOCATION._y + Console::MAP_HEIGHT - 1);
    _Pos.SetMin(MAP_LOCATION._x - 18, MAP_LOCATION._y + 1);
    _STRING.assign(5, "");
    _STRING[0] = "        __________";
    _STRING[1] = "  ___  |          |";
    _STRING[2] = " /_| | |          |";
    _STRING[3] = "|    |_|__________|";
    _STRING[4] = "\"-O----O-O`    O`O`";
}
Truck::~Truck() {}

//
void VehicleControl::CarMove(const int &ElapsedTime)
{
    for (auto i : _CarLane)
    {
        if (i->_Pos._x == i->_Pos.max_x)
        {
            delete i;
            _CarLane.pop_back();
        }
        else
        {
            i->_DistanceSum = 1.0 * ElapsedTime / DIVIDE_CONSTANT;
            i->_Distance += i->_DistanceSum;
            i->_Pos.SetX(i->_Direction * floor(i->_Distance));
            if (i->_Distance > 1)
                i->_Distance = 0;
        }
    }
}
void VehicleControl::TruckMove(const int &ElapsedTime)
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
        {
            i->_DistanceSum = 1.0 * ElapsedTime / DIVIDE_CONSTANT;
            i->_Distance += i->_DistanceSum;
            i->_Pos.SetX(i->_Direction * floor(i->_Distance));
            if (i->_Distance > 1)
                i->_Distance = 0;
        }
    }
}

//
VehicleControl::VehicleControl(const int &level, const bool &b)
{
    if (b)
        VehicleControl::CreateObj();
    DIVIDE_CONSTANT -= 70000 * sqrt(level);
}
VehicleControl::~VehicleControl()
{
    for (auto i : _CarLane)
        delete i;
    for (auto i : _TruckLane)
        delete i;
}
//
void VehicleControl::CreateObj()
{
    srand(time(NULL));
    Vehicle *v;
    int _RandomDistance, NEW_LOCATION;
    //create 4 car obj with random distance
    //car1 car2 car3 car4
    for (int i = 0; i < 2; i++)
    {
        if (!i)
            v = new Car(MAP_LOCATION._x + 2, MAP_LOCATION._y + CAR_LOCATION_Y);
        else
        {
            _RandomDistance = rand() % 30 + 1;
            NEW_LOCATION = _CarLane[i - 1]->_Pos._x + CAR_LENGTH + _RandomDistance;

            v = new Car(NEW_LOCATION, MAP_LOCATION._y + CAR_LOCATION_Y);
        }
        _CarLane.push_back(v);
    }

    //create 4 truck obj with random distance
    //truck4 truck3 truck2 truck1
    for (int i = 0; i < 2; i++)
    {
        if (!i)
            v = new Truck(MAP_LOCATION._x + Console::MAP_WIDTH - 1, MAP_LOCATION._y + TRUCK_LOCATION_Y);
        else
        {
            _RandomDistance = rand() % 30 + 1;
            NEW_LOCATION = _TruckLane.front()->_Pos._x - TRUCK_LENGTH - _RandomDistance;

            v = new Truck(NEW_LOCATION, MAP_LOCATION._y + TRUCK_LOCATION_Y);
        }
        _TruckLane.push_front(v);
    }
}
void VehicleControl::Move(const int &ElapsedTime)
{
    VehicleControl::CarMove(ElapsedTime);
    VehicleControl::AddCar();

    VehicleControl::TruckMove(ElapsedTime);
    VehicleControl::AddTruck();
}

//
void VehicleControl::AddCar()
{
    srand(time(NULL));
    if (_CarLane.front()->_Pos._x > rand() % 35 + CAR_LENGTH + 1)
        _CarLane.push_front(new Car(MAP_LOCATION._x - 4, MAP_LOCATION._y + CAR_LOCATION_Y));
}
void VehicleControl::AddTruck()
{
    srand(time(NULL));
    if (_TruckLane.back()->_Pos._x < MAP_LOCATION._x + Console::MAP_WIDTH - rand() % 35 - TRUCK_LENGTH - 1)
        _TruckLane.push_back(new Truck(MAP_LOCATION._x + Console::MAP_WIDTH - 1, MAP_LOCATION._y + TRUCK_LOCATION_Y));
}