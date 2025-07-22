#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace this_thread;
using namespace chrono;

void draw(int);

struct Request
{
    int destination;
};

class Elevator
{
    int currentFloor;
    
    public:
    int speed;
    
    Elevator(int currentFloor, int speed)
    {
        this->currentFloor = currentFloor;
        this->speed = speed;
        initiaize();
    }

    void initiaize()
    {
        for (int i = 10; i >= 1; i--)
        {
            if (i == this->currentFloor)
                cout << "Floor " << i << ": " << "\t" << "| E |" << endl;
            else
                cout << "Floor " << i << ": " << "\t" << "|  |" << endl;
        }
    }

    void moveElevator(Request req)
    {   
        if (req.destination >= 1 && req.destination <= 10)
        {
            if (req.destination > this->currentFloor)
            {
                while (this->currentFloor != req.destination)
                {
                    for (int i = 10; i >= 1; i--)
                    {
                        if (i == this->currentFloor)
                            cout << "Floor " << i << ": " << "\t" << "| E |" << endl;
                        else
                            cout << "Floor " << i << ": " << "\t" << "|  |" << endl;
                    }
                    
                    sleep_for(seconds(1/this->speed));
                    this->currentFloor++;
                    system("cls");
                }

                draw(this->currentFloor);
            }
            else if (req.destination < this->currentFloor)
            {
                while (this->currentFloor != req.destination)
                {
                    for (int i = 10; i >= 1; i--)
                    {
                        if (i == this->currentFloor)
                            cout << "Floor " << i << ": " << "\t" << "| E |" << endl;
                        else
                            cout << "Floor " << i << ": " << "\t" << "|  |" << endl;
                    }
                    
                    sleep_for(seconds(1/this->speed));
                    this->currentFloor--;
                    system("cls");
                }

                draw(this->currentFloor);
            }
            else if (req.destination == this->currentFloor)
                cout << "Already at desired floor" << endl;
            else
                cout << "Invalid Input" << endl;

        }
    }

};

int main()
{
    Elevator E1(5, 1);
    Request r1;

    while (1)
    {
        cout << "What floor? --> ";
        cin >> r1.destination;
        sleep_for(milliseconds(500));
        system("cls");
    
        E1.moveElevator(r1);
        sleep_for(seconds(1));
    }
    

    return 0;
}

void draw(int floor)
{
    for (int i = 10; i >= 1; i--)
    {
        if (i == floor)
            cout << "Floor " << i << ": " << "\t" << "| E |" << endl;
        else
            cout << "Floor " << i << ": " << "\t" << "|  |" << endl;
    }
}