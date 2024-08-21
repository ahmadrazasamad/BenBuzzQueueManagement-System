# BenBuzz Queue Management System
This C++ program simulates a digital ordering system for beverages, where customers can place orders, and the system manages a queue to serve them in order. The program offers features to place orders, serve them, display the current queue status, and retrieve specific order details.
## Features
- **Place Order:** Allows customers to choose their drink and any customizations, then adds the order to the queue.
- **Serve Order:** Processes the next order in the queue and provides an estimated wait time for the customer.
- **Display Queue Status:** Shows all current orders in the queue with details like customer name, drink type, and customizations.
- **Display Order Details:** Retrieves detailed information about a specific order using its unique order number.
## Usage
1. **Place Order:** Enter your name and select your desired drink and customization options from the menu.
2. **Serve Order:** The system automatically serves the first order in the queue once it's ready.
3. **Queue Status:** View the current queue and see how many orders are ahead.
4. **Order Details:** Check the status of a specific order using the order number provided at the time of ordering.
## Future Development
1. **Multiple Customizations:** Allow customers to select multiple customizations instead of just one. You can modify the customization selection to loop until the user is done selecting.
2. **Order Summary Before Confirmation:** After the user selects the drink and customizations, display a summary of the order and ask for confirmation before placing the order.
3. **Order Cancellation:** Add a feature to cancel an order from the queue by order number, which could be useful in real-world applications.
4. **Order History:** Store and display a history of all served orders, which could be useful for generating reports or for customer service.
5. **Dynamic Menu:** Allow management to add or remove items from the menu dynamically, possibly saving the menu to a file that can be loaded on startup.
6. **Auto-Serve Orders:** Automatically serve orders when their serving time is reached without needing a manual call to serveOrder().
## Contributing
Contributions are welcome! If you find a bug or have a suggestion for improvement, please open an issue or submit a pull request.
