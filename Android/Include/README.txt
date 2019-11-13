User interface backend for when the Android app needs to make query requests to the MySQL database.

PHP class purposes:
Constant.php: Defines the MySQL database host address, username, password, and database name
DbConnect.php: Connects to the MySQL database
DbOperation.php: Contains all the functions to query from database as needed
Fetchdata.php: main class that calls previous three php classes to fetch data from MySQL database and
sends it the Android App via JSON format
Dbtest.php: Test PHP classes