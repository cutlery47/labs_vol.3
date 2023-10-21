
#ifndef PASSENGER_H
#define PASSENGER_H




class Passenger
{
private:
    int from_floor;
    int to_floor;
    int elevator_num;

public:
    Passenger();
    Passenger(int from, int to, int num);

    int to();
    int from();
    int elevator();
};

#endif // PASSENGER_H
