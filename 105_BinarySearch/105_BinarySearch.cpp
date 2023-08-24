#include <ctime>
#include <iostream>
#include <string> // for getline

// Define a class representing a Flight
class Flight {
public:
    int flightNumber;
    std::string destination;
    std::string departureTime;

    // Constructor to initialize Flight attributes
    Flight(int number, const std::string& dest, const std::string& time)
        : flightNumber(number), destination(dest), departureTime(time) {}
};

// Define a class for managing flights using a binary search tree
class FlightManager {
private:
    // Nested struct representing a Node in the binary search tree
    struct Node {
        Flight flight;
        Node* left;
        Node* right;

        // Node constructor to initialize with Flight data
        Node(const Flight& f) : flight(f), left(nullptr), right(nullptr) {}
    };

    Node* root; // Root node of the binary search tree

    // Recursive function to insert a flight node into the tree
    Node* insertRecursive(Node* current, const Flight& flight) {
        if (current == nullptr) {
            return new Node(flight);
        }
        if (flight.flightNumber < current->flight.flightNumber) {
            current->left = insertRecursive(current->left, flight);
        }
        else {
            current->right = insertRecursive(current->right, flight);
        }
        return current;
    }

    // Recursive function to search for a flight by flight number
    Node* searchRecursive(Node* current, int flightNumber) {
        if (current == nullptr || current->flight.flightNumber == flightNumber) {
            return current;
        }
        if (flightNumber < current->flight.flightNumber) {
            return searchRecursive(current->left, flightNumber);
        }
        return searchRecursive(current->right, flightNumber);
    }

    //Minimum search function
    Node* findMinRecursive(Node* current) {
        if (current == nullptr) {
            return nullptr; // Tree is empty
        }
        if (current->left == nullptr) {
            return current; // Leftmost node has the minimum value
        }
        return findMinRecursive(current->left);
    }

    //Maximum search function
    Node* findMaxRecursive(Node* current) {
        if (current == nullptr) {
            return nullptr; // Tree is empty
        }
        if (current->right == nullptr) {
            return current; // Rightmost node has the maximum value
        }
        return findMaxRecursive(current->right);
    }

    //Function to complie the flight tree contents in order and cout them a list
    void inOrderTraversal(Node* current) {
        if (current){
            inOrderTraversal(current->left);
            std::cout << " Flight Number: " << current->flight.flightNumber << std::endl;
            std::cout << " Destination : " << current->flight.destination << std::endl;
            std::cout << " Departutre Time : " << current->flight.departureTime << std::endl;
            inOrderTraversal(current->right);
        }
    }


public:
    // Constructor to initialize FlightManager with an empty root
    FlightManager() : root(nullptr) {}

    // Method to add a flight to the binary search tree
    void addFlight(const Flight& flight) {
        root = insertRecursive(root, flight);
    }

    //Method to Find Minimum Flight
    Flight* findMinFlight() {
        Node* minNode = findMinRecursive(root);
        if (minNode) {
            return &(minNode->flight);
        }
        return nullptr;
    }

    //Method to Find Maximum Flight
    Flight* findMaxFlight() {
        Node* maxNode = findMaxRecursive(root);
        if (maxNode) {
            return &(maxNode->flight);
        }
        return nullptr;
    }

    // Method to search for a flight by flight number
    Flight* searchFlight(int flightNumber) {
        Node* result = searchRecursive(root, flightNumber);
        if (result) {
            return &(result->flight);
        }
        return nullptr;
    }

    void printAllFlightNumbers() {
        std::cout << "All Flight Numbers:" << std::endl;
        inOrderTraversal(root);
    }
};

int main() {
    FlightManager manager;

    // Create Flight objects
    Flight flight1(101, "New York", "08:00 AM");
    Flight flight2(202, "Los Angeles", "10:30 AM");
    Flight flight3(303, "Chicago", "12:45 PM");

    // Add flights to the FlightManager
    manager.addFlight(flight1);
    manager.addFlight(flight2);
    manager.addFlight(flight3);

    std::cout << "WELCOME TO FLIGHT TRACKER" << std::endl;

    int choice;
    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Search Flight by Number" << std::endl;
        std::cout << "2. Find Minimum Flight" << std::endl;
        std::cout << "3. Find Maximum Flight" << std::endl;
        std::cout << "4. View All Flight Numbers" << std::endl;
        std::cout << "5. Enter New Flights" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int searchFlightNumber;
            std::cout << "Enter Flight Number to search: ";
            std::cin >> searchFlightNumber;
            Flight* searchedFlight = manager.searchFlight(searchFlightNumber);

            if (searchedFlight) {
                std::cout << "Flight Number: " << searchedFlight->flightNumber << std::endl;
                std::cout << "Destination: " << searchedFlight->destination << std::endl;
                std::cout << "Departure Time: " << searchedFlight->departureTime << std::endl;
            }
            else {
                std::cout << "Flight with number " << searchFlightNumber << " not found." << std::endl;
            }
            break;
        }
        case 2: {
            Flight* minFlight = manager.findMinFlight();
            if (minFlight) {
                std::cout << "Minimum Flight:" << std::endl;
                std::cout << "Flight Number: " << minFlight->flightNumber << std::endl;
                std::cout << "Destination: " << minFlight->destination << std::endl;
                std::cout << "Departure Time: " << minFlight->departureTime << std::endl;
            }
            else {
                std::cout << "No flights found." << std::endl;
            }
            break;
        }
        case 3: {
            Flight* maxFlight = manager.findMaxFlight();
            if (maxFlight) {
                std::cout << "Maximum Flight:" << std::endl;
                std::cout << "Flight Number: " << maxFlight->flightNumber << std::endl;
                std::cout << "Destination: " << maxFlight->destination << std::endl;
                std::cout << "Departure Time: " << maxFlight->departureTime << std::endl;
            }
            else {
                std::cout << "No flights found." << std::endl;
            }
            break;
        }
        case 4: {
            manager.printAllFlightNumbers();
            break;
        }
        case 5: {
            int newFlightNumber;
            std::string newDestination;
            std::string newDepartureTime;

            std::cout << "Enter new Flight Number: ";
            std::cin >> newFlightNumber;
            std::cout << "Enter new Destination: ";
            std::cin.ignore(); // Clear the newline character from previous input
            std::getline(std::cin, newDestination);
            std::cout << "Enter new Departure Time: ";
            std::getline(std::cin, newDepartureTime);

            Flight newFlight(newFlightNumber, newDestination, newDepartureTime);
            manager.addFlight(newFlight);

            std::cout << "New flight added successfully!" << std::endl;
            break;
        }
        case 6: {
            std::cout << "Exiting the program." << std::endl;
            return 0;
        }
        default:
            std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }

    } while (choice != 6);

    return 0;
}
