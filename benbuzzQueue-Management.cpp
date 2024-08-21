#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
using namespace std;

struct Order
{
    string customerName, drinkType, customization;
    int orderNumber;
    time_t orderPlacementTime, orderServingTime; // time is in minutes
    Order *next;
};
Order *head = nullptr;

string trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == string::npos || last == string::npos)
        return ""; // If the string contains only whitespace characters
    return str.substr(first, last - first + 1);
}

int orderCount = 0; // initially no-orders, for having unique orderNumbers, like a ticket
void placeOrder()
{
    string name = "", type = "", customization = "";
    cout << "Enter your name: ";
    getline(cin, name);
    name = trim(name);

    while (name.empty())
    {
        cout << "Customer's name cannot be empty or contain only spaces...\nKindly re-enter: ";
        getline(cin, name);
        name = trim(name);
    }

    cout << "\t\t\tMenu:\n"; // Menu printing starts here

    cout << "Coffee-Based Drinks:\n";
    cout << "1. Latte - Espresso with steamed milk and a light layer of foam on top.\n";
    cout << "2. Cappuccino - Equal parts espresso, steamed milk, and a thick layer of foam.\n";
    cout << "3. Espresso - A small, concentrated shot of coffee with a bold flavor.\n";
    cout << "4. Drip Coffee - Traditional brewed coffee made by dripping hot water through ground coffee.\n";
    cout << "5. Iced Coffee - Regular brewed coffee served over ice, often with milk or sweetener.\n";
    cout << "6. Americano - Espresso diluted with hot water.\n";
    cout << "7. Flat White - A smoother and creamier version of a latte with a higher ratio of coffee to milk.\n";
    cout << "8. Macchiato - Espresso topped with a small amount of foamed milk.\n";
    cout << "9. Mocha - A chocolate-flavored variant of a latte.\n";
    cout << "10. Cortado - Equal parts espresso and steamed milk.\n";
    cout << "11. Affogato - Espresso poured over a scoop of vanilla ice cream.\n";
    cout << "12. Café au Lait - Drip coffee mixed with steamed milk.\n";
    cout << "13. Ristretto - A short shot of espresso, stronger and more concentrated.\n";
    cout << "14. Nitro Cold Brew - Cold brew coffee infused with nitrogen for a creamy texture.\n\n";

    cout << "Non-Coffee Beverages:\n";
    cout << "15. Chai Latte - Spiced tea concentrate mixed with steamed milk.\n";
    cout << "16. Matcha Latte - A green tea powder whisked into hot water or milk.\n";
    cout << "17. Hot Chocolate - A classic chocolate drink, often topped with whipped cream.\n";
    cout << "18. Golden Milk - A turmeric-based drink mixed with milk, often with spices like cinnamon and ginger.\n";
    cout << "19. Herbal Teas - Various blends of caffeine-free teas made from herbs, spices, and fruits.\n";
    cout << "20. Lemonade - A refreshing blend of lemon juice, water, and sugar, often served cold.\n\n";

    cout << "Specialty and Seasonal Drinks:\n";
    cout << "21. Pumpkin Spice Latte - A seasonal favorite, often available in the fall.\n";
    cout << "22. Peppermint Mocha - A wintertime drink combining chocolate, espresso, and peppermint.\n";
    cout << "23. Caramel Macchiato - Espresso, milk, and vanilla syrup topped with caramel drizzle.\n";
    cout << "24. Iced Matcha Latte - Matcha green tea served cold with milk.\n";
    cout << "25. Frappuccino - A blended ice coffee drink, available in various flavors.\n\n";

    int choice = 0;
    cout << "Which drink would you like to order, enter your choice (1-25): ";
    cin >> choice;
    cin.ignore(); // input buffer

    while (choice < 1 || choice > 25) // ask until a valid drink's choice is made.
    {
        cout << "Invalid choice.\nKindly re-enter the number of the drink of your choice from the menu: ";
        cin >> choice;
        cin.ignore(); // clear the input buffer
    }

    switch (choice)
    {
    case 1:
        type = "Latte";
        break;
    case 2:
        type = "Cappuccino";
        break;
    case 3:
        type = "Espresso";
        break;
    case 4:
        type = "Drip Coffee";
        break;
    case 5:
        type = "Iced Coffee";
        break;
    case 6:
        type = "Americano";
        break;
    case 7:
        type = "Flat White";
        break;
    case 8:
        type = "Macchiato";
        break;
    case 9:
        type = "Mocha";
        break;
    case 10:
        type = "Cortado";
        break;
    case 11:
        type = "Affogato";
        break;
    case 12:
        type = "Café au Lait";
        break;
    case 13:
        type = "Ristretto";
        break;
    case 14:
        type = "Nitro Cold Brew";
        break;
    case 15:
        type = "Chai Latte";
        break;
    case 16:
        type = "Matcha Latte";
        break;
    case 17:
        type = "Hot Chocolate";
        break;
    case 18:
        type = "Golden Milk";
        break;
    case 19:
        type = "Herbal Teas";
        break;
    case 20:
        type = "Lemonade";
        break;
    case 21:
        type = "Pumpkin Spice Latte";
        break;
    case 22:
        type = "Peppermint Mocha";
        break;
    case 23:
        type = "Caramel Macchiato";
        break;
    case 24:
        type = "Iced Matcha Latte";
        break;
    case 25:
        type = "Frappuccino";
        break;
    }

    choice = 0; // reset for customization selection
    cout << "Customizations:\n";
    cout << "1. Extra Shot - Add an additional shot of espresso for a stronger coffee.\n";
    cout << "2. Flavored Syrups - Choose from various flavors like vanilla, caramel, hazelnut, or seasonal options.\n";
    cout << "3. Milk Alternatives - Options like almond, oat, soy, coconut, or lactose-free milk.\n";
    cout << "4. Decaf - Decaffeinated versions of coffee drinks.\n";
    cout << "5. Whipped Cream - Add a topping of whipped cream to your drink.\n";
    cout << "6. Sweeteners - Options like sugar, honey, stevia, or agave syrup.\n";
    cout << "7. Foam Preference - Choose light, regular, or no foam for drinks like lattes and cappuccinos.\n";
    cout << "8. Ice Levels - Adjust the amount of ice (light, regular, extra) in cold drinks.\n";
    cout << "9. Temperature Adjustments - Options for extra hot, warm, or iced versions.\n";
    cout << "10. Toppings - Add-ons like cinnamon, cocoa powder, or chocolate drizzle.\n";
    cout << "11. Cup Size - Small, medium, large, or extra large options.\n";
    cout << "12. Strength - Choose the strength of the coffee (regular, strong, extra strong).\n";
    cout << "13. Sweetness Level - Customize the sweetness (unsweetened, light, regular, extra sweet).\n";
    cout << "14. Blended Option - Blend your drink for a smoother, frozen texture (e.g., frappés).\n";
    cout << "15. Espresso Strength - Adjust the concentration of the espresso shot (ristretto, regular, lungo).\n";
    cout << "16. Alternative Sweeteners - Like sugar-free syrups or zero-calorie sweeteners.\n";
    cout << "17. Soy-Free - Soy-free versions of milk alternatives.\n";
    cout << "18. Organic Options - Choose organic coffee beans or organic milk.\n";
    cout << "19. Cold Foam - Add a layer of cold, frothy milk foam on iced drinks.\n";
    cout << "20. Custom Spice Blend - Add a mix of spices like nutmeg, cloves, or cardamom.\n";
    cout << "21. None - Just enjoy your drink.\n\n";

    cout << "Which customization would you like, enter your choice (1-21): ";
    cin >> choice;
    cin.ignore(); // input buffer

    while (choice < 1 || choice > 21) // ask until a valid customization choice is made.
    {
        cout << "Invalid choice.\nKindly re-enter the number of the cutomization of your choice from the menu: ";
        cin >> choice;
        cin.ignore(); // clear the input buffer
    }

    switch (choice)
    {
    case 1:
        customization = "Extra Shot";
        break;
    case 2:
        customization = "Flavored Syrups";
        break;
    case 3:
        customization = "Milk Alternatives";
        break;
    case 4:
        customization = "Decaf";
        break;
    case 5:
        customization = "Whipped Cream";
        break;
    case 6:
        customization = "Sweeteners";
        break;
    case 7:
        customization = "Foam Preference";
        break;
    case 8:
        customization = "Ice Levels";
        break;
    case 9:
        customization = "Temperature Adjustments";
        break;
    case 10:
        customization = "Toppings";
        break;
    case 11:
        customization = "Cup Size";
        break;
    case 12:
        customization = "Strength";
        break;
    case 13:
        customization = "Sweetness Level";
        break;
    case 14:
        customization = "Blended Option";
        break;
    case 15:
        customization = "Espresso Strength";
        break;
    case 16:
        customization = "Alternative Sweeteners";
        break;
    case 17:
        customization = "Soy-Free";
        break;
    case 18:
        customization = "Organic Options";
        break;
    case 19:
        customization = "Cold Foam";
        break;
    case 20:
        customization = "Custom Spice Blend";
        break;
    case 21:
        customization = "None";
        break;
    }

    auto now = chrono::system_clock::now();
    time_t orderPlacementTime = chrono::system_clock::to_time_t(now);

    Order *temp = new Order(); // new object
    temp->customerName = name;
    temp->drinkType = type;
    temp->customization = customization;
    temp->orderNumber = ++orderCount;
    temp->next = nullptr;
    temp->orderPlacementTime = orderPlacementTime;

    if (head == nullptr)
    {
        auto estOrderServingTime = now + chrono::minutes(3); // as for a drink maximum three minutes
        time_t orderServingTime = chrono::system_clock::to_time_t(estOrderServingTime);

        head = temp;
        head->orderServingTime = orderServingTime;

        cout << "o) " << head->customerName << ", your order is placed.\n";
        cout << "   Your order number is " << head->orderNumber << ".\n";
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

    cout << "o) " << temp->customerName << ", your order is placed.\n";
    cout << "   Your order number is " << temp->orderNumber << ".\n";

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
        details += "o) Customer Name: " + current->customerName + "\n";
        details += "   Customer Drink Type: " + current->drinkType + "\n";
        details += "   Customer Drink Customization: " + current->customization + "\n\n";

        current = current->next;
    }
    cout << "There " << (numOfPersons == 1 ? "is only one person" : ("are " + to_string(numOfPersons) + " persons")) << "in the queue.\n\nDetails:\n";
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
    cin >> orderNum;
    cin.ignore();

    Order *current = head;
    Order *orderToFind = nullptr;
    bool found = false;
    while (current != nullptr)
    {
        if (current->orderNumber == orderNum)
        {
            found = true;
            orderToFind = current;
            break;
        }
        current = current->next;
    }

    if (!found)
    {
        cout << "No order of this order number: " << orderNum << ", found.\n";
        return;
    }

    auto now = chrono::system_clock::now();
    time_t nowTime = chrono::system_clock::to_time_t(now);

    cout << "o) Customer Name: " << orderToFind->customerName << endl;
    cout << "   Customer Drink Type: " << orderToFind->drinkType << endl;
    cout << "   Customer Drink Customization: " << orderToFind->customization << endl;
    if (orderToFind->orderServingTime <= nowTime)
        cout << "   Customer your drink is ready to be served.";
    else
    {
        auto estWaitingTime = chrono::system_clock::from_time_t(orderToFind->orderServingTime) - now;
        auto minutes = chrono::duration_cast<chrono::minutes>(estWaitingTime).count();
        auto seconds = chrono::duration_cast<chrono::seconds>(estWaitingTime).count() % 60;
        cout << "   Customer's Drink Serving Estimated Waiting Time: " << minutes << " minute(s) and " << seconds << " second(s).\n\n";
    }
}

int main()
{
    int choice;
    cout << "\t\t\t\tWelcome to the BenBuzz's Digital Ordering System\n";
    do
    {
        cout << "Hey Management! What operation would you like to perform:\n";
        cout << "1. Place Order\n2. Serve Order\n3. Display Queue Status\n4. Display Order Details\n5. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

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
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice! Please enter a number between 1 and 5." << endl;
        }
        cout << endl;
    } while (choice != 5);

    exit(0); // 5 is pressed

    return 0;
}