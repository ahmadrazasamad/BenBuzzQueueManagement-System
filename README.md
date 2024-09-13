# BenBuzz Queue Management System
This C++ program simulates a digital ordering system for beverages, where customers can place orders, and the system manages a queue to serve them in order. The program offers features to place orders, serve them, display the current queue status, and retrieve specific order details, also the management can dynamically manage (add or remove) a drink or customization, and also can view history of all the served orders.
## Features
- **Place Order:** Allows customers to choose their drink and any customizations, then adds the order to the queue.
- **Serve Order:** Processes the next order in the queue and provides an estimated wait time for the customer.
- **Display Queue Status:** Shows all current orders in the queue with details like customer name, drink type, and customizations.
- **Display Order Details:** Retrieves detailed information about a specific order using its unique order number.
- **Add New Drink:** Dynamically adds a new drink to the menu.
- **Add New Customization:** Dynamically adds a new customization to the menu.
- **Remove Drink:** Removes a drink from the menu.
- **Remove Customization:** Removes a customization from the menu.
- **View Served Orders Details:** Retrives history of all the served orders and displays it, useful for making reports.
## Usage
1. **Place Order:** Enter your name and select your desired drink and customization options from the menu.
2. **Serve Order:** The system automatically serves the first order in the queue once it's ready.
3. **Queue Status:** View the current queue and see how many orders are ahead.
4. **Order Details:** Check the status of a specific order using the order number provided at the time of ordering.
5. **Adding a New Drink:** Management can add a new drink by inserting the name and description of it.
6. **Adding a New Customization:** Management can add a new customzation by inserting the name and description of it.
7. **Removing a Drink:** Management can remove a drink from the menu by inserting the name of that particular drink.
8. **Removing a Customization:** Management can remove a customization from the menu by inserting the name of that particular customization.
9. **View Details of all the Served Orders:** View the details of the served orders, that can be useful for customer satisfaction as by seeing the delivery time.
## Important:
Please if you are forking or cloning this repo and working on it kindly remember to keep both `menu.txt` and `servedOrdersDetails.txt` in the same folder as the program file.
## Future Development
- **Order Cancellation:** Add a feature to cancel an order from the queue by order number, which could be useful in real-world applications.
## Contributing
Contributions are welcome! If you find a bug or have a suggestion for improvement, please open an issue or submit a pull request.
