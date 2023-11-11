
#ifndef PASSENGER_H
#define PASSENGER_H




class Passenger
{
private:
    // этаж, на котором ожидает пассажир
    int from_floor;
    // этаж, на который пассажир хочет переместиться
    int to_floor;

public:
    Passenger();
    Passenger(int from, int to);

    int to();
    int from();
};

#endif // PASSENGER_H
