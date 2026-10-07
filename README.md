# restaurant-database


1. The `Restaurant` class stores information about a single restaurant, its `ID`, `name`, `cuisine type`, and a list of menu items (stored as strings like `"Burger 9.99"`).

Explore the `Restaurant.hpp` file and check the member variables, constructor, and public methods. In the coming tasks, we’ll start the implementations.

2. Let’s move to `RestaurantIO.cpp` and work on the `addRestaurant()` function to create a more user-friendly interface.

Start by printing clear and friendly prompts asking the user to enter the restaurant’s details. You should ask for:

```
Enter restaurant ID: Enter restaurant name: Enter cuisine type: 
```

3. Collect the information for the restaurant. Use `cin >>` to read the ID of the restaurant and store it in `restaurantID`. For inputs for `restaurantName` and `cuisineType`, use `getline()` with `cin` to ensure that multi-word entries such as ‘The Pasta Place’ or ‘South Indian Cuisine’ are read correctly without being truncated.
4. You must ensure the user enters a valid number for the restaurant’s `ID`. If they enter something that isn’t an integer (like a word or symbol), show the following error message and return:

```
Invalid input.
```

To handle this, use `input.fail()` to detect the invalid input. If it fails, use `input.clear()` to reset the error state, and use `cin.ignore()` to ignore the remaining characters up to a new line. You can assume the stream will never have more than 1000 characters, so ignore all of them.

5. Once the restaurant’s ID, name, and cuisine type have been collected, create a `Restaurant(name, id, cuisineType)` object to temporarily store this information. This object will be used to add menu items before saving the complete data to the database.

Place the code immediately after the input section and initialize the object using the specified constructor.

6. After collecting the basic details of the restaurant, the next step is to gather its menu items. We can start by obtaining the number of menu items. To get this number, give the user the following prompt:

```
Enter the number of menu items:
```

Store the input in a variable named `menuItemCount`. This value will determine how many times to repeat the process of collecting each item’s name and price.

7. Users might enter invalid values, such as negative numbers or non-numeric input. These cases should be handled gracefully to avoid unexpected crashes.

If the input for `menuItemCount` is invalid or is less than zero, print the following message:

```
Invalid number.
```

Then, return from the function.

Use `fail()` to detect non-numeric input. If it fails, call `clear()` to reset the stream and `ignore()` to discard up to 1000 characters or a new line, ensuring smooth future input operations.

8. Now that we know how many menu items the user wants to add, create a loop that loops for `menuItemCount` times and gives the following prompts:

```
Enter item <i> name:
```

```
Enter item <i> price:
```

Where `i` is the current item (item 1, item 2, etc).

Do not collect the input now. You will do this later.

9. Inside the loop, below each prompt, read the user’s input using `getline()` and `cin`.

Store the item name in a `string` variable called `itemName` and the item’s price in a `double` variable called `itemPrice`.

10. After reading `itemPrice`, verify whether the input is invalid due to non-numeric input or a negative number.

If the input is invalid, print the following error message:

```
Invalid price.
```

11. Each menu item should be stored as a single string in the format:

```
ItemName Price
```

To do this, create a `stringstream` named `itemEntryStream` inside the loop. Use the stream insertion operator (`<<`) to write `itemName` and `itemPrice` into it.

Apply `fixed` and `setprecision(2)` to ensure the price always displays with two decimal places (e.g., `12.99`).

## Saving and Loading using Operator Overloading

12. To save a `Restaurant` object in a structured and readable format, you’ll implement the `<<` operator.

In the `Restaurant.cpp` file, define the logic inside the `operator<<` function. Use the `outputStream` to write the following fields, in order, and they need to be separated by the `#` character:

- `id`
- `name`
- `cuisine`
- the number of items in the `menuItems` vector

After that, write each menu item on the same line, separated by `#` as well.

Here’s an example of what the final output should look like in the file:

```
202#Green Fork Diner#American#3#Burger 9.99#Grilled Cheese 7.50#Garden Salad 6.25
```

13. Now that the restaurant’s core information has been written to the `outputStream`, the next step is to serialize the menu items.

Inside the `operator<<` function, loop through the `menuItems` vector and write each item to the stream. Each item is already a formatted string like `"Pizza 12"`, so you can insert it directly.

Prefix each menu item with a `#` to maintain consistency with the earlier field separators.

14. To deserialize a `Restaurant` object from an input stream, you’ll overload the `>>` operator. This allows the program to read a complete restaurant record from a formatted line and convert it into a `Restaurant` object.

Inside the `operator>>` function, start by creating a `string` variable named `rawLine`. Declare this at the top of the function, this will be used to hold the entire line of input read from the stream.

15. To ensure we don’t accidentally mix new input with any previous data, you must clear the `menuItems` vector before reading new entries into it.

Use the `clear()` function to reset the menu list each time a new restaurant is deserialized.

16. To prevent errors caused by empty or incorrect files, your first step should be to securely read an entire line from the input stream.

Use the `getline()` function with `inputStream` to read a full line into `rawLine`.

Wrap the `getline()` call in an `if` condition using the following pattern:

```cpp
if (!getline(stream, variable)) {
	return stream;
}
```

This ensures that the function will exit immediately if `getline` fails (for example, if it reaches the end of the file).

At the end of the function, remember to return `inputStream` so it can be used for further reads.

17. Now that the full restaurant record is stored in the `rawLine` variable, the next step is to parse it field by field.

Create a `stringstream` named `lineStream` and initialize it using `rawLine`. You’ll also need a `string` variable named `field` to temporarily hold each part as it’s extracted.

Make sure to declare the `field` variable before calling `getline()` to extract individual fields from the stream.

18. Next, parse the first three fields from `lineStream`: the restaurant’s `id`, `name`, and `cuisine`. These fields are separated by the `#` delimiter.

Use `getline(lineStream, field, '#')` to extract each field in order.

Convert the first field to an integer using `stoi(field)` and store it in `restaurant.id`. Then, use `getline(lineStream, restaurant.name, '#')` and `getline(lineStream, restaurant.cuisine, '#')` to assign the next two fields directly.

19. After extracting the initial fields, you’ll now parse the menu count. This value is also separated by `#` and represents how many items are listed in the menu.

Extract the token from the stream, convert it to an integer using `stoi`, and assign it to a local variable named `itemCount`.

20. After extracting the restaurant’s core fields, the next step is to read its menu items from the stream.

The number of expected items is stored in the variable `itemCount`. Each item is saved as a single string in the format:

```
Pizza 12.99#Mushroom Pasta 10.50#...
```

Use a loop that runs `itemCount` times. In each iteration, extract the next menu item using:

```cpp
if (!getline(lineStream, field, '#')) {
	return inputStream;
}
```

This ensures that the function exits safely if the data is incomplete or corrupted.

After extracting each item, add it to `restaurant.menuItems` using the `push_back()` function.

## Saving Restaurant Data to a File

21. Implement the `saveDatabase()` function to write all restaurant records to a file.

Open the `RestaurantIO.cpp` file and find the `saveDatabase()` function. Inside it, create an `ofstream` object named `outputFile` using the provided `filename`. This file will store the serialized data for each restaurant.

22. After opening the file, verify whether the stream is valid. If `outputFile` fails to open, use `cerr` to print an error message and return early to avoid writing to an invalid stream. The error message should look like:

```
[ERR] Could not open {filename} for writing.
```

23. Iterate over the `database` vector using a range-based for loop. For each `restaurant` in the list, write it to the `outputFile` stream using the stream insertion operator (`<<`). Add a newline after each restaurant to ensure each entry appears on its own line in the file.
24. After all restaurants have been written to the file, use the `close()` function to properly release the file resource.

## Loading the Restaurant Data from File

25. Inside the `RestaurantIO.cpp` file locate the `loadDatabase()` function.

Create an `ifstream` object named `inputFile` using the provided `filename`. This file will be used to read all restaurant records.

26. Inside `loadDatabase()`, after opening the file, check if `inputFile` is in a good state. If it fails to open, print an error and return `false` to signal that loading failed. The warning message will look like:

```
[WARN] Could not open {filename} for reading.
```

27. Inside the same function, create a loop that reads from the input file until all data has been processed. In each iteration, use the overloaded `>>` operator to extract a `Restaurant` object from the stream, and add it to the `database` vector using `push_back()`.

After the loop finishes reading all restaurants successfully, return `true` to indicate that the loading process completed without errors.

## Running and Testing the Application

28. In the terminal, compile all your source files together by runnig the following command:

```
g++ Restaurant.cpp RestaurantIO.cpp main.cpp -o restaurant_app
```

29. Use the terminal to run your app:

```
./restaurant_app
```

Try adding a few restaurants and select the “Save and exit” option to check if it saves the restaurants in the `restaurants.txt` file. Then, relaunch the app to display all the restaurants in the console.

30. Run the application again using the same command:

```
./restaurant_app
```

This time, select option 2: “View Restaurants” and check whether the previously saved restaurants are displayed in the console. If they appear correctly, it means loading from the file is working as expected.

31. Open the `restaurants.txt` file located in the Codecademy workspace.

Each restaurant should appear on a single line, with all fields separated by the `#` character. Menu items follow the main details and are also separated by `#`.

Reviewing this file will help you understand the structure of your serialization logic and confirm that it’s working as intended.

32. Congratulations! You’ve built a fully functional Restaurant Database System using C++ streams.

You’ve practiced reading and writing to files, validating input, formatting output, parsing structured data, and overloading stream operators—great work!

If you’d like to take this project further, here are some ideas:

- Allow users to delete or update a restaurant
- Save menu items as structured objects instead of strings
- Add categories or ratings for each restaurant
- Sort the list by name or cuisine before displaying
