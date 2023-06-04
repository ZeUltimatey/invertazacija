#include <string>
#include <fstream>


// User class
struct User {
    std::string username;
    std::string password;
};


// Worker class
class Worker {
private:
    int id;
    std::string name;
    std::string surname;
    std::string hiringDate;

public:
    // Constructor
    Worker(int id, std::string name, std::string surname, std::string hiringDate)
            : id(id), name(std::move(name)), surname(std::move(surname)), hiringDate(std::move(hiringDate)) {}

    // Getter functions
    int getID() const {
        return id;
    }

    std::string getName() const {
        return name;
    }

    std::string getSurname() const {
        return surname;
    }

    std::string getHiringDate() const {
        return hiringDate;
    }
};


// Item class
class Item {
private:
    int id;
    std::string name;
    int quantity;
    double price;

public:
    // Constructor
    Item(int id, std::string name, int quantity, double price)
            : id(id), name(std::move(name)), quantity(quantity), price(price) {}

    // Getter functions
    int getID() const {
        return id;
    }

    std::string getName() const {
        return name;
    }

    int getQuantity() const {
        return quantity;
    }

    double getPrice() const {
        return price;
    }
};


// Shelf class
class Shelf {
private:
    int id;
    std::string location;

public:
    // Constructor
    Shelf(int id, std::string location)
            : id(id), location(std::move(location)) {}

    // Getter functions
    int getID() const {
        return id;
    }

    std::string getLocation() const {
        return location;
    }
};


void generateSummaryWorker(const std::vector<Worker>& Workers) {
    std::cout << "Summary of the Worker Database:" << std::endl;
    // Summary for the Worker table
    std::cout << "Workers:" << std::endl;
    for (const Worker& Worker : Workers) {
        std::cout << "Worker ID: " << Worker.getID() << std::endl;
        std::cout << "Name: " << Worker.getName() << std::endl;
        std::cout << "Surname: " << Worker.getSurname() << std::endl;
        std::cout << "Hiring Date: " << Worker.getHiringDate() << std::endl;
        std::cout << std::endl;
    }
}


void generateSummaryItem(const std::vector<Item>& items) {
    std::cout << "Summary of the Item Database:" << std::endl;
    // Summary for the Item table
    std::cout << "Items:" << std::endl;
    for (const Item& item : items) {
        std::cout << "Item ID: " << item.getID() << std::endl;
        std::cout << "Name: " << item.getName() << std::endl;
        std::cout << "Quantity: " << item.getQuantity() << std::endl;
        std::cout << "Price: " << item.getPrice() << std::endl;
        std::cout << std::endl;
    }
}

void generateSummaryShelf(const std::vector<Shelf>& shelves) {
    std::cout << "Summary of the Shelf Database:" << std::endl;
    // Summary for the Shelf table
    std::cout << "Shelves:" << std::endl;
    for (const Shelf& shelf : shelves) {
        std::cout << "Shelf ID: " << shelf.getID() << std::endl;
        std::cout << "Location: " << shelf.getLocation() << std::endl;
        std::cout << std::endl;
    }
}


bool fileExists (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

void createFile(const std::string name) {
    if (name == "worker") {
        std::fstream workerF ("worker.txt", std::ios::out);
        if (workerF.is_open()) {
            workerF << "=======================================DATABASE: WORKER.TXT=======================================" << std::endl;
            workerF << "==================================================================================================" << std::endl;
            workerF << "||          ID          ||         NAME         ||       SUR-NAME       ||     WORKER SINCE     ||" << std::endl;
            workerF << "==================================================================================================" << std::endl;
            workerF.close();
        } else {
            std::cout << "Error; worker file didn't open" << std::endl;
        }
    }
    if (name == "item") {
        std::fstream itemF ("item.txt", std::ios::out);
        if (itemF.is_open()) {
            itemF << "================================================================DATABASE: ITEM.TXT================================================================" << std::endl;
            itemF << "==================================================================================================================================================" << std::endl;
            itemF << "||          ID          ||         NAME         ||      STOCKED BY      ||         VALUE        ||       SHELF ID       ||          QTY         ||" << std::endl;
            itemF << "==================================================================================================================================================" << std::endl;
            itemF.close();
        } else {
            std::cout << "Error; item file didn't open" << std::endl;
        }
    }
    if (name == "shelf") {
        std::fstream shelfF ("shelf.txt", std::ios::out);
        if (shelfF.is_open()) {
            shelfF << "========================================DATABASE: SHELF.TXT=======================================" << std::endl;
            shelfF << "==================================================================================================" << std::endl;
            shelfF << "||          ID          ||       SECTION.X      ||       SECTION.Y      ||       SECTION.Z      ||" << std::endl;
            shelfF << "==================================================================================================" << std::endl;
            shelfF.close();
        } else {
            std::cout << "Error; shelf file didn't open" << std::endl;
        }
    }
};


void inputToFile(std::string fileName, std::string query) {
    add_to_file:
    if (fileExists(fileName + ".txt")) {
        std::fstream fileF (fileName + ".txt", std::ios::app);
        fileF << query;
        fileF.close();
    } else {
        createFile(fileName);
        goto add_to_file;
    }
}

void deleteFromFile (std::string fileName, std::string ID) {
    fileName = fileName + ".txt";
    std::fstream fileF (fileName, std::ios::in);
    std::string line;
    std::string tempFileName = "temp.tmp";
    std::ofstream tempFile(tempFileName); // make temp file to write contents to

    bool deleted = false;

    while (std::getline(fileF, line)) {
        if (line.find(ID) == std::string::npos) { // write to temp file if ID not found in line
            tempFile << line << std::endl;
        } else {
            deleted = true;
        }
    }

    fileF.close();
    tempFile.close();

    if (deleted) {
        remove(fileName.c_str());
        rename(tempFileName.c_str(), fileName.c_str());
        std::cout << "Worker successfully deleted from table." << std::endl;
    } else {
        std::cout << "Worker ID not found." << std::endl;
    }

}

void dropDatabase(std::string fileName) {
    fileName = fileName + ".txt";
    std::cout << "Are you sure you want to delete table " + fileName + "?" << std::endl;
    std::cout << "type \'confirm\' to confirm deletion." << std::endl;
    std::string answer;
    std::cin >> answer;
    if (answer == "confirm") {
        remove(fileName.c_str());
        std::cout << "Table successfully deleted." << std::endl;
    }
    else {
        std::cout << "Deletion cancelled..." << std::endl;
    }
}

void displayDatabase(std::string fileName) {
    std::fstream fileF (fileName + ".txt", std::ios::in);
    std::string line;

    if(fileExists(fileName + ".txt")) {
        while (std::getline(fileF, line)) {
            std::cout << line << std::endl;
        }
    }
    else {
        std::cout << "Error: table doesn't exist" << std::endl;
    }
}


void writeUsersToFile(const std::vector<User>& users) {
    std::ofstream file("users.txt", std::ios::out);
    if (file.is_open()) {
        for (const User& user : users) {
            file << user.username << "|||" << user.password << std::endl;
        }
        file.close();
    }
}

std::vector<User> readUsersFromFile() {
    std::vector<User> users;
    std::ifstream file("users.txt", std::ios::in);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            User user;
            int spaceIndex = line.find("|||");
            user.username = line.substr(0, spaceIndex);
            user.password = line.substr(spaceIndex + 1);
            users.push_back(user);
        }
        file.close();
    }
    return users;
}

void registerUser(std::vector<User>& users) {
    User user;
    std::cout << "Enter username: ";
    std::cin >> user.username;
    erase(user.username, ' ');
    while (std::cin.fail() || user.username.empty()) {
        std::cout << "Invalid username. Please try again: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin >> user.username;
    }
    std::cout << "Enter password: ";
    std::cin >> user.password;
    erase(user.password, ' ');
    while (std::cin.fail() || user.password.empty()) {
        std::cout << "Invalid password. Please try again: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin >> user.password;
    }
    for (const User& u : users) {
        if (u.username == user.username) {
            std::cout << "Username already exists. Please choose a different username." << std::endl;
            return;
        }
    }
    users.push_back(user);
    writeUsersToFile(users);
    std::cout << "Registration successful!" << std::endl;
}


bool loginUser(const std::vector<User>& users) {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}
