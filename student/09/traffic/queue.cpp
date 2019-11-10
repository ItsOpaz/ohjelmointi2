#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle)
{
    this->cycle_ = cycle;
    this->vehiclesPassed = 0;
}


// Destructor that deletes all the remaining vehicles from the queue.
Queue::~Queue()
{
    // Destroy linked list
}


void Queue::enqueue(string reg)
{

    if (is_green_ && vehiclesPassed <= cycle_) {
        vehiclesPassed++;
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;

        return;
    }

    if (first_ == nullptr) {

        first_ = new Vehicle({reg, nullptr});
        last_ = first_;

    } else {
        Vehicle* nextInQueue = new Vehicle({reg, nullptr});
        last_->next = nextInQueue;
        last_ = nextInQueue;
    }

}

bool Queue::dequeue()
{
    if (first_ == nullptr) {
        return false;
    }
    Vehicle* second = first_->next;

    if (second == nullptr) {

        cout << first_->reg_num << " ";
        delete first_;
        last_->next = nullptr;
        last_ = nullptr;
        first_ = last_;
        return true;
    }

    cout << first_->reg_num << " ";
    delete first_;
    first_ = second;

    return true;
}

void Queue::switch_light()
{
    is_green_ = !is_green_;
    string lightColor = (is_green_) ? "GREEN" : "RED";
    cout << lightColor << ": ";

    if (is_green_) {

        if (first_ != nullptr) {
            cout << "Vehicle(s) ";
            for (vehiclesPassed = 0; vehiclesPassed < cycle_; vehiclesPassed++) {
                if (!dequeue()) {
                    break;
                }
            }

            cout << "can go on" << endl;

            this->is_green_ = false;

        } else {
            cout << "No vehicles waiting in traffic lights" << endl;
        }

    } else {
        if (first_ != nullptr) {
            cout << "Vehicle(s) ";
        } else {
            cout << "No vehicles waiting in traffic lights" << endl;
        }

        vehiclesPassed = 0;
    }
}

void Queue::update()
{
    if (!is_green_) {
        this->vehiclesPassed = 0;
    }


    if (this->vehiclesPassed >= this->cycle_) {
        this->is_green_ = false;
        this->vehiclesPassed = 0;
    }
}


void Queue::reset_cycle(unsigned int cycle)
{
    this->cycle_ = cycle;
}

void Queue::print()
{
    this->update();
    string lightColor = (is_green_) ? "GREEN" : "RED";
    cout << lightColor << ": ";

    if (is_green_) {

        if (first_ != nullptr) {
            Vehicle* vehicleInQueue = first_;
            cout << "Vehicle(s) ";

            while (vehicleInQueue != nullptr) {
                cout << vehicleInQueue->reg_num << " ";
                vehicleInQueue = vehicleInQueue->next;
            }
            cout << "are waiting in traffic lights" << endl;
        } else {
            cout << "No vehicles waiting in traffic lights" << endl;
        }

    } else {
        if (first_ != nullptr) {
            Vehicle* vehicleInQueue = first_;
            cout << "Vehicle(s) ";

            while (vehicleInQueue != nullptr) {
                cout << vehicleInQueue->reg_num << " ";
                vehicleInQueue = vehicleInQueue->next;
            }

            cout << "waiting in traffic lights" << endl;

        } else {
            cout << "No vehicles waiting in traffic lights" << endl;
        }
    }


}
