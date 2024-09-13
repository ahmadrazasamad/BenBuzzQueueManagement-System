#include <iostream>
#include <string>
#include <ctime>     // for time
#include <chrono>    // for doing addition and subtraction with time
#include <iomanip>   // for converting time from chrono to time_t
#include <algorithm> // for find
#include <vector>    // for drink type and customization
#include <fstream>   // for file handling
#include <limits>    // for numeric limits
using namespace std;

struct Order
{
    int orderNumber;
    string customerName, drinkType;
    vector<string> customization;                // since customizations can be multiple
    time_t orderPlacementTime, orderServingTime; // time is in minutes
    Order *next;
};
Order *head = nullptr; // singly linked-list

vector<string> drinkTypes;     // will initialize it from file
vector<string> customizations; // will also initialize it from file

// helper function start here
string trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == string::npos || last == string::npos)
        return ""; // If the string contains only whitespace characters
    return str.substr(first, last - first + 1);
}

int takeIntegerInput(int rangeStart, int rangeEnd)
{
    int choice = 0;
    while (true)
    {
        cin >> choice;

        if (cin.fail() || choice < rangeStart || choice > rangeEnd)
        {
            cout << "Invalid input! Kindly re-enter a number that indicates your choice between " << rangeStart << "(inclusive) and " << rangeEnd << "(inclusive): ";
            cin.clear();                                         // Clear the error flag set by invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        }
        else
        {
            cin.ignore(); // input buffer
            break;
        }
    }
    return choice;
}

string takeStringInput(string comment)
{
    string str = "";
    getline(cin, str);
    str = trim(str);
    while (str.empty())
    {
        cout << comment << " cannot be empty or contain only spaces...\nKindly re-enter: ";
        getline(cin, str);
        str = trim(str);
    }
    return str;
}

string selectDrink()
{
    ifstream inFile("menu.txt");
    string line = "";
    int drinkCount = 0;
    while (getline(inFile, line)) // read line by line
    {
        if (line == "Customizations:") // stop if "Customizations:" is found
            break;

        if (!line.empty())
        {
            if (line != "Coffee-Based Drinks:" || line != "Non-Coffee Beverages:" || line != "Specialty and Seasonal Drinks:")
            {
                drinkCount++;
                cout << drinkCount << line.substr(1) << endl;
            }
            else
                cout << line << endl;
        }
    }
    inFile.close();

    int choice = 0;
    cout << "Which drink would you like to order, enter your choice (1-" << drinkTypes.size() << "): ";
    choice = takeIntegerInput(1, drinkTypes.size());
    return drinkTypes[choice - 1];
}

vector<string> selectCustomizations(string drinkName)
{
    char option = '\0';
    cout << "Do you want any customization(s) in your drink '" << drinkName << "':\no) Yes\no) None - Just enjoy your drink.\nEnter your choice('Y' for yes and 'anyother-key' for no): ";
    cin >> option;
    option = tolower(option);
    cin.ignore(); // input buffer

    vector<string> choosenCustomizations;
    if (option == 'y')
    {
        ifstream inFile("menu.txt");
        string line = "";
        while (getline(inFile, line))
        {
            if (line == "Customizations:")
                break;
        }
        cout << line << endl;

        int customizationCount = 0;
        while (getline(inFile, line))
        {
            customizationCount++;
            cout << customizationCount << line.substr(1) << endl;
        }
        inFile.close();

        int choice = 0;
        char option = '\0';
        while (true)
        {
            choice = 0; // reset on every loop run
            cout << "Which customization would you like, enter your choice (1-" << customizations.size() << "): ";
            choice = takeIntegerInput(1, customizations.size());
            choosenCustomizations.push_back(customizations[choice - 1]);

            option = '\0'; // reset on every loop run
            cout << "Do you want to add another customization, press 'Y' for yes and 'anyother-key' for no: ";
            cin >> option;
            cin.ignore(); // input buffer
            option = tolower(option);

            if (option != 'y')
                break;
        }
    }
    else
        choosenCustomizations.push_back("None");
    return choosenCustomizations;
}

void showOrderSummary(bool isUpdated, const string &drinkName, const vector<string> &choosenCustomizations)
{
    cout << "\n--- " << (isUpdated ? "Updated " : "") << "Order Summary ---\n";
    cout << "Drink: " << drinkName << endl;
    cout << "Customization" << (choosenCustomizations.size() > 1 ? "s:\n" : (": " + choosenCustomizations[0]));
    for (string customization : choosenCustomizations)
        cout << "   o) " << customization << endl;
    cout << "---------------------\n";
}

string drinkAndCustomizationNameValidation(bool isDrinkName)
{
    string name = "";
    cout << "Enter name of the " << (isDrinkName ? "drink" : "customization") << " you want to add in the menu(name should not contain '-'): ";
    getline(cin, name);
    name = trim(name);
    while (name.empty() || (name.find('-') != string::npos))
    {
        if ((name.find('-') != string::npos))
        {
            cout << (isDrinkName ? "Drink" : "Customization") << "'s Name name should not contain '-'!\n";

            // giving suggestion
            string partition1 = name.substr(0, name.find('-'));
            if (!partition1.empty()) // means '-' is at index 0
            {
                string partition2 = name.substr(name.find('-') + 1, name.length());
                if (partition2.find('-') == string::npos)
                { // means in partition 2 there is no other '-'
                    char choice = '\0';
                    cout << "Do you mean the " << (isDrinkName ? "drink" : "customization") << " name should be \"" << partition1 << " " << partition2 << "\", Press 'Y' for yes and 'anyother key' for no: ";
                    cin >> choice;
                    cin.ignore(); // input buffer
                    choice = tolower(choice);
                    if (choice == 'y')
                    {
                        name = partition1 + " " + partition2;
                        return name;
                    }
                    else
                        cout << "Kindly re-enter: ";
                }
                else
                    cout << "Kindly re-enter: ";
            }
            else
                cout << "Kindly re-enter: ";
        }
        else
            cout << (isDrinkName ? "Drink" : "Customization") << "'s Name name cannot be empty or contain only spaces...\nKindly re-enter: ";
        getline(cin, name);
        name = trim(name);
    }

    return name;
}

string convertStringToLowerCase(string str)
{
    for (int i = 0; i < str.length(); i++)
        str[i] = tolower(str[i]);
    return str;
}

void writeNewDrinkInFile(string lineAtWhichToBreak, string drinkName, string drinkDescription)
{
    ifstream inFile("menu.txt");
    string line = "";
    string data = "";

    while (getline(inFile, line))
    {
        if (line == lineAtWhichToBreak)
            break;
        if (!line.empty())
            data += line + "\n";
    }
    data += "o) " + drinkName + " - " + drinkDescription + "\n\n";
    data += lineAtWhichToBreak + "\n";
    while (getline(inFile, line))
    {
        data += line;
        if (inFile.peek() != EOF) // Check if the next character is not EOF
            data += "\n";
    }
    inFile.close();

    ofstream outFile("menu.txt");
    outFile << data;
    outFile.close();
}

void initializeMenu()
{
    ifstream inFile("menu.txt");
    string line = "";

    while (getline(inFile, line)) // extracting drinks
    {
        if (line == "Customizations:") // stop if "Customizations:" is found
            break;
        if (line == "Coffee-Based Drinks:" || line == "Non-Coffee Beverages:" || line == "Specialty and Seasonal Drinks:")
            getline(inFile, line);
        if (!line.empty())
        {
            string extractedDrink = "";
            int i = 3; // as line[0] is 'o' line[1] is ')' and line[2] is ' '
            while (i < line.size() && line[i + 1] != '-')
            {
                extractedDrink += line[i];
                i++;
            }
            drinkTypes.push_back(extractedDrink);
        }
    }

    while (getline(inFile, line)) // extracting cutomizations
    {
        string extractedCustomization = "";
        int i = 3; // as line[0] is 'o' line[1] is ')' and line[2] is ' '
        while (i < line.size() && line[i + 1] != '-')
        {
            extractedCustomization += line[i];
            i++;
        }
        customizations.push_back(extractedCustomization);
    }
    inFile.close();
}
// helper function end here

int orderCount = 0; // initially no-orders, for having unique orderNumbers, like a ticket
void placeOrder()
{
    string name = "";
    cout << "Enter your name: ";
    name = takeStringInput("Customer's name");

    cout << "\t\t\tMenu:\n";
    string drinkName = selectDrink();
    vector<string> choosenCustomizations = selectCustomizations(drinkName);

    showOrderSummary(false, drinkName, choosenCustomizations);
    char option = '\n';
    cout << "Would you like to confirm your order? Press 'Y' for yes and 'anyother-key' for no: ";
    cin >> option;
    cin.ignore();
    option = tolower(option);
    if (option != 'y')
    {
        while (true)
        {
            int choice = 0;
            cout << "What would you like to update(re-order):\n1) Drink or\n2) Customization" << (choosenCustomizations.size() > 1) ? "s" : "";
            choice = takeIntegerInput(1, 2);

            if (choice == 1)
                drinkName = selectDrink();
            else // choice == 2
                choosenCustomizations = selectCustomizations(drinkName);
            showOrderSummary(true, drinkName, choosenCustomizations);

            option = '\0'; // reset option variable
            cout << "Do you want to update anything else further more, press 'Y' for yes and 'anyother-key' for no: ";
            cin >> option;
            cin.ignore();
            option = tolower(option);
            if (option != 'y')
                break;
        }
    }
    auto now = chrono::system_clock::now();
    time_t orderPlacementTime = chrono::system_clock::to_time_t(now);

    Order *temp = new Order(); // new object
    temp->customerName = name;
    temp->drinkType = drinkName;
    temp->customization = choosenCustomizations;
    temp->orderNumber = ++orderCount;
    temp->next = nullptr;
    temp->orderPlacementTime = orderPlacementTime;

    cout << "o) " << temp->customerName << ", your order is placed.\n";
    cout << "   Your order number is " << temp->orderNumber << ".\n";
    cout << "   Your drink type is " << temp->drinkType << ".\n";
    cout << "   Your drink customization" << ((temp->customization.size() > 1) ? "s are:\n" : " is: ");
    if (temp->customization[0] == "None")
        cout << "None\n";
    else
    {
        if (temp->customization.size() > 1)
        {
            int i = 1;
            for (string customizationVariable : temp->customization)
            {
                cout << "      " << i << ") " << customizationVariable << endl;
                i++;
            }
        }
        else
            cout << temp->customization[0] << endl;
    }

    if (head == nullptr)
    {
        auto estOrderServingTime = now + chrono::minutes(3); // as for a drink maximum three minutes
        time_t orderServingTime = chrono::system_clock::to_time_t(estOrderServingTime);

        temp->orderServingTime = orderServingTime;
        head = temp;

        cout << "   Your order will be ready in 3 minutes.\n\n";
        return;
    }

    Order *current = head;
    int personsPresentInQueue = 2; // as head is the person that is already in the queue, and the person ordering is the next person
    while (current->next != nullptr)
    {
        personsPresentInQueue++;
        current = current->next;
    }
    auto estOrderServingTime = now + chrono::minutes(personsPresentInQueue * 3);
    time_t orderServingTime = chrono::system_clock::to_time_t(estOrderServingTime);
    current->next = temp;

    auto estWaitingTime = chrono::system_clock::from_time_t(temp->orderServingTime) - chrono::system_clock::from_time_t(temp->orderPlacementTime);
    auto minutes = chrono::duration_cast<chrono::minutes>(estWaitingTime).count();
    cout << "   Your order will be ready in " << minutes << " minutes.\n\n";
}

void serveOrder()
{
    if (head == nullptr)
    {
        cout << "No one is present in the queue to be served.\n";
        return;
    }

    auto now = chrono::system_clock::now();
    time_t nowTime = chrono::system_clock::to_time_t(now);

    if (head->orderServingTime <= nowTime)
    {
        Order *nextPersonAfterHead = head->next;
        cout << head->drinkType << " served to " << head->customerName << ".\n";
        cout << head->customerName << ", we hope you enjoy your drink.\n";

        // Writing in the file
        ifstream inFile("servedOrdersDetails.txt");
        string data = "";
        string line = "";
        while (getline(inFile, line))
            data += line;
        inFile.close();

        ofstream outFile("servedOrdersDetails.txt", ios::out | ios::app);
        if (!data.empty())
            outFile << endl;
        outFile << "o) Order Number: " << head->orderNumber << endl;
        outFile << "   Customer Name: " << head->customerName << endl;
        outFile << "   Drink Name: " << head->drinkType << endl;
        outFile << "   Customization" << (head->customization.size() > 1 ? "s:\n" : (": " + head->customization[0]));
        for (string customization : head->customization)
            outFile << "    o) " << customization << endl;
        outFile << "   Order Placement Time: " << ctime(&head->orderPlacementTime);
        time_t orderDeliveryTime = time(nullptr);
        string orderDeliveryTimeStr = ctime(&orderDeliveryTime);
        orderDeliveryTimeStr.erase(orderDeliveryTimeStr.length() - 1);
        outFile << "   Order Delivery Time: " << orderDeliveryTimeStr;
        outFile.close();

        delete head;
        head = nextPersonAfterHead;
    }
    else
    {
        auto estWaitingTime = chrono::system_clock::from_time_t(head->orderServingTime) - now;
        auto minutes = chrono::duration_cast<chrono::minutes>(estWaitingTime).count();
        auto seconds = chrono::duration_cast<chrono::seconds>(estWaitingTime).count() % 60;
        cout << head->customerName << "'s Drink Serving Estimated Waiting Time: " << minutes << " minute(s) and " << seconds << " second(s).\n\n";
    }
}

void displayQueueStatus()
{
    if (head == nullptr)
    {
        cout << "The queue is empty.\n";
        return;
    }
    cout << "Orders in the queue:\n";
    Order *current = head;
    int numOfPersons = 1;
    string details = "";
    while (current != nullptr)
    {
        numOfPersons++;
        details += "o) Customer Order Number: " + to_string(current->orderNumber) + "\n";
        details += "   Customer Name: " + current->customerName + "\n";
        details += "   Customer Drink Type: " + current->drinkType + "\n";
        details += "   Customer Drink Customization" + string((current->customization.size() > 1) ? "s:\n" : ": ");

        if (current->customization[0] == "None")
            details += "None\n\n";
        else
        {
            if (current->customization.size() > 1)
            {
                int i = 1;
                for (string customizationVariable : current->customization)
                {
                    details += "      " + to_string(i) + ") " + customizationVariable + "\n";
                    i++;
                }
                details += "\n";
            }
            else
                details += current->customization[0] + "\n\n";
        }

        current = current->next;
    }
    cout << "There " << (numOfPersons == 1 ? "is only one person" : ("are " + to_string(numOfPersons) + " persons")) << "in the queue.\nDetails:\n";
    cout << details;
}

void displayOrderDetails()
{
    if (head == nullptr)
    {
        cout << "The queue is empty, no orders to show details of.\n";
        return;
    }
    int orderNum = 0;
    cout << "Enter you order number: "; // since order number is unique, name can be same
    while (true)
    {
        cin >> orderNum;
        if (cin.fail())
        {
            cout << "Invalid input! Do not enter character or string, Kindly enter a valid order number: ";
            cin.clear();                                         // Clear the error flag set by invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        }
        else if (orderNum < 1)
        {
            cout << "Invalid input! The order number shoul be greater than 0, Kindly enter a valid order number: ";
            cin.ignore();
        }
        else
        {
            cin.ignore();
            break;
        }
    }

    Order *current = head;
    bool found = false;
    while (current != nullptr)
    {
        if (current->orderNumber == orderNum)
        {
            found = true;

            auto now = chrono::system_clock::now();
            time_t nowTime = chrono::system_clock::to_time_t(now);

            cout << "o) Customer Name: " << current->customerName << endl;
            cout << "   Customer Drink Type: " << current->drinkType << endl;
            cout << "   Customer Drink Customization" << ((current->customization.size() > 1) ? "s:\n" : ": ");
            if (current->customization[0] == "None")
                cout << "None\n";
            else
            {
                if (current->customization.size() > 1)
                {
                    int i = 1;
                    for (string customizationVariable : current->customization)
                    {
                        cout << "      " << i << ") " << customizationVariable << endl;
                        i++;
                    }
                }
                else
                    cout << current->customization[0] << endl;
            }

            if (current->orderServingTime <= nowTime)
                cout << "   Customer your drink is ready to be served. Kindly ask the management to serve your order.\n";
            else
            {
                auto estWaitingTime = chrono::system_clock::from_time_t(current->orderServingTime) - now;
                auto minutes = chrono::duration_cast<chrono::minutes>(estWaitingTime).count();
                auto seconds = chrono::duration_cast<chrono::seconds>(estWaitingTime).count() % 60;
                cout << "   Customer's Drink Serving Estimated Waiting Time: " << minutes << " minute(s) and " << seconds << " second(s).\n\n";
            }

            break; // break the loop
        }
        current = current->next;
    }

    if (!found)
    {
        cout << "No order of this order number: '" << orderNum << "', found.\n";
        return;
    }
}

void addNewDrink()
{
    string drinkName = "", drinkDescription = "";
    drinkName = drinkAndCustomizationNameValidation(true);

    cout << "Describe the drink by giving some description. Kindly enter: ";
    drinkDescription = takeStringInput("Drink's description");

    int choice = 0;
    cout << "Is it a\n1) Coffee-Based Drink\n2) Non-Coffee Beverage\n3) Specialty and Seasonal Drink\nChoose one(enter choice 1-3): ";
    choice = takeIntegerInput(1, 3);

    if (choice == 1)
        writeNewDrinkInFile("Non-Coffee Beverages:", drinkName, drinkDescription);
    else if (choice == 2)
        writeNewDrinkInFile("Specialty and Seasonal Drinks:", drinkName, drinkDescription);
    else // choice == 3
        writeNewDrinkInFile("Customizations:", drinkName, drinkDescription);

    initializeMenu();
}

void addNewCustomization()
{
    string customizationName = "", customizationDescription = "";
    customizationName = drinkAndCustomizationNameValidation(false);

    cout << "Describe the customization by giving some description: ";
    customizationDescription = takeStringInput("Customization's description");

    ofstream outFile("menu.txt", ios::out | ios::app);
    outFile << endl;
    outFile << "o) " << customizationName << " - " << customizationDescription;
    outFile.close();

    customizations.push_back(customizationName);
}

void removeDrink()
{
    string drinkName = "";
    cout << "Please insert the name of the drink to remove from the menu: ";
    drinkName = takeStringInput("Drink's name");

    bool found = false;
    string tempDrinkName = convertStringToLowerCase(drinkName);
    for (auto it = drinkTypes.begin(); it != drinkTypes.end(); ++it)
    {
        if (tempDrinkName == convertStringToLowerCase(*it))
        {
            found = true;
            drinkTypes.erase(it);

            // removing from the file
            ifstream inFile("menu.txt");
            string data = "";
            string line = "";
            while (getline(inFile, line))
            {
                if (convertStringToLowerCase(line).find(tempDrinkName) != string::npos)
                    break;
                data += line + "\n";
            }
            while (getline(inFile, line))
            {
                data += line;
                if (inFile.peek() != EOF)
                    data += "\n";
            }
            inFile.close();

            ofstream outFile("menu.txt");
            outFile << data;
            outFile.close();

            cout << drinkName << " removed from the menu sucessfully.\n";
            break;
        }
    }

    if (!found)
        cout << "No drink with this name \"" << drinkName << "\" not found in the menu!\n";
}

void removeCustomization()
{
    string customizationName = "";
    cout << "Please insert the name of the customization to remove from the menu: ";
    customizationName = takeStringInput("Customization's name");

    bool found = false;
    string tempCustomizatioName = convertStringToLowerCase(customizationName);
    for (auto it = customizations.begin(); it != customizations.end(); ++it)
    {
        if (tempCustomizatioName == convertStringToLowerCase(*it))
        {
            found = true;
            customizations.erase(it);

            // removing from the file
            ifstream inFile("menu.txt");
            string data = "";
            string line = "";
            while (getline(inFile, line))
            {
                if (line.find(tempCustomizatioName) != string::npos)
                    break;
                data += line + "\n";
            }
            while (getline(inFile, line))
                data += line + "\n";
            inFile.close();

            data = data.substr(0, data.length() - 1);

            ofstream outFile("menu.txt");
            outFile << data;
            outFile.close();

            cout << customizationName << " removed from the menu sucessfully.\n";
            break;
        }
    }
    if (!found)
        cout << "No customization with this name \"" << customizationName << "\" not found in the menu!\n";
}

void viewServedOrderHistory()
{
    ifstream inFile("servedOrdersDetails.txt");
    string data = "";
    string line = "";
    while (getline(inFile, line))
        data += line;

    if (data.empty())
        cout << "No orders served yet.\n";
    else
        cout << data << endl;
    inFile.close();
}

int main()
{
    initializeMenu();

    int choice;
    cout << "\t\t\t\tWelcome to the BenBuzz's Digital Ordering System\n";
    do
    {
        cout << "Hey Management! What operation would you like to perform:\n";
        cout << "1. Place Order\n2. Serve Order\n3. Display Queue Status\n4. Display Order Details\n5. Add new drink in the menu\n6. Add new customization in the menu\n7. Remove a drink from the menu\n 8. Remove a customization from the mneu\n9. View history of all the served orders\n10. Exit\n";
        cout << "Enter your choice: ";
        choice = takeIntegerInput(1, 9);

        switch (choice)
        {
        case 1:
            placeOrder();
            break;
        case 2:
            serveOrder();
            break;
        case 3:
            displayQueueStatus();
            break;
        case 4:
            displayOrderDetails();
            break;
        case 5:
            addNewDrink();
            break;
        case 6:
            addNewCustomization();
            break;
        case 7:
            removeDrink();
            break;
        case 8:
            removeCustomization();
            break;
        case 9:
            viewServedOrderHistory();
            break;
        case 10:
            cout << "Exiting program..." << endl;
            break;
        }
    } while (choice != 10);

    exit(0); // 10 is pressed

    return 0;
}