#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <fstream>

using namespace std;
using namespace this_thread;
using namespace chrono;

void draw(int, int);

struct Request
{
    int passengerCount;
    int destination;
};

ofstream logFile("logs.txt"); 
time_t currentTime = time(0); 

class Elevator
{
    int currentFloor;
    bool inMaintainence = false;
    
    public:
    int speed;
    
    Elevator(int currentFloor, int speed)
    {
        this->currentFloor = currentFloor;
        this->speed = speed;
        initiaize();      
    }

    bool isInMaintainence()
    {
        return inMaintainence;
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
        logFile << "[" << ctime(&currentTime) << "]" << " --> " << "Initialized at floor " << this->currentFloor << endl;
    }

    void moveElevator(Request req)
    {   
        cout << "How many passengers?: ";
        cin >> req.passengerCount;

        if (req.passengerCount*65 > 800)
        {
            cout << "Weight Limit Exceeded!" << endl;
            logFile << "Weight Limit Exceeded" << endl;
            cout << "Lift in Maintainence, due to exceeded weight limit.." << endl;
            cout << "Wait for 5 seconds..." << endl;
            sleep_for(seconds(5));
            cout << "Fixed!" << endl;
        }
        else
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
                                cout << "Floor " << i << ": " << "\t" << "| " << req.passengerCount << "P" << " |" << endl;
                            else
                                cout << "Floor " << i << ": " << "\t" << "|   |" << endl;
                        }
                        
                        sleep_for(seconds(1/this->speed));
                        this->currentFloor++;
                        system("cls");
                    }

                    draw(this->currentFloor, req.passengerCount);
                    logFile << "[" << ctime(&currentTime) << "]" << " --> "  << "Moved to: " << this->currentFloor << endl;
                }
                else if (req.destination < this->currentFloor)
                {
                    while (this->currentFloor != req.destination)
                    {
                        for (int i = 10; i >= 1; i--)
                        {
                            if (i == this->currentFloor)
                                cout << "Floor " << i << ": " << "\t" << "| " << req.passengerCount << "P" << " |" << endl;
                            else
                                cout << "Floor " << i << ": " << "\t" << "|   |" << endl;
                        }
                        
                        sleep_for(seconds(1/this->speed));
                        this->currentFloor--;
                        system("cls");
                    }

                    draw(this->currentFloor, req.passengerCount);
                    logFile << "[" << ctime(&currentTime) << "]" << " --> "  << "Moved to: " << this->currentFloor << endl;
                }
                else if (req.destination == this->currentFloor)
                    cout << "Already at desired floor" << endl;
                else
                    cout << "Invalid Input" << endl;
            }
        }
        
    }

};

int main()
{
    Elevator E1(5, 1);
    Request r1;

    int cmnd;
    while (1)
    {
        cout << "Command? --> ";
        cin >> cmnd;

        if (cmnd >= 1 && cmnd <= 10)
        {
            r1.destination = cmnd;
            sleep_for(milliseconds(500));
            system("cls");
        
            E1.moveElevator(r1);
            sleep_for(seconds(1));
        }
        else if (cmnd == 11)
        {
            cout << "What should the speed be: ";
            cin >> E1.speed;
            cout << "Speed set!" << endl;
        }
        else
            exit(0);
    }
    
    return 0;
}

void draw(int floor, int passengers)
{
    for (int i = 10; i >= 1; i--)
    {
        if (i == floor)
        {
            cout << "Floor " << i << ": " << "\t" << "| " << passengers << "P" << " |" << endl;
            
            sleep_for(seconds(1));
            cout << "\x1b[1A"; 
            cout << "\x1b[2K"; 
            
            cout << "\rFloor " << i << ": " << "\t" << "| E |" << endl;
        }
        else
            cout << "Floor " << i << ": " << "\t" << "|   |" << endl;

    }
}