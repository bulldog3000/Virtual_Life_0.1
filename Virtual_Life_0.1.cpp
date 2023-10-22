#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <ctime>

class Person {
public:
    Person(const std::string& name, int age) : name(name), age(age), health(100), fitness(0) {}

    void eat() {
        std::cout << name << " is eating." << std::endl;
        health += 10;
        if (health > 200) {
            health = 200;
        }
    }

    void sleep() {
        std::cout << name << " is sleeping." << std::endl;
        health += 20;
        if (health > 200) {
            health = 200;
        }
    }

    void work() {
        std::cout << name << " is working." << std::endl;
        health -= 2;  // Health decreases over time
    }

    void introduce() {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }

    void makeFriend(Person& otherPerson) {
        std::cout << name << " and " << otherPerson.getName() << " are becoming friends." << std::endl;
        acquaintances.push_back(&otherPerson);
        otherPerson.acquaintances.push_back(this);
    }

    void talkToFriends() {
        std::cout << name << " is talking to friends:" << std::endl;
        for (const auto& acquaintance : acquaintances) {
            std::cout << "- " << acquaintance->getName() << std::endl;
        }
    }

    const std::string& getName() const {
        return name;
    }

    void runVirtualLife() {
        while (true) {
            auto currentTime = std::chrono::system_clock::now();
            auto timeNow = std::chrono::system_clock::to_time_t(currentTime);

            struct tm* timeInfo;
            timeInfo = localtime(&timeNow);

            int hour = timeInfo->tm_hour;
            int minute = timeInfo->tm_min;

            if (hour == 6 && minute == 0) {
                wakeUp();
            }
            else if (hour == 8 && minute == 0) {
                eat();
            }
            else if (hour == 14 && minute == 30) {
                eat();
            }
            else if (hour == 19 && minute == 0) {
                eat();
            }
            else if (hour == 23 && minute == 30) {
                goToSleep();
            }
            else {
                work();
            }

            if (hour % 2 == 0) {
                // Health decreases every hour
                health -= 2;
            }

            // Add entertainment and hobbies here
            if (hour == 18 && minute == 0) {
                haveFun();
            }

            // Fun factor depends on the number of friends
            int funFactor = 1 + acquaintances.size();
            if (hour == 18 && minute == 0) {
                haveFun(funFactor);
            }

            health -= 2;  // Health decreases over time
            if (health <= 0) {
                std::cout << name << " has passed out from poor health and is rushed to the hospital." << std::endl;
                break;
            }

            std::this_thread::sleep_for(std::chrono::minutes(30));
        }
    }

private:
    std::string name;
    int age;
    int health;
    int fitness;
    std::vector<Person*> acquaintances;

    void wakeUp() {
        std::cout << name << " wakes up." << std::endl;
    }

    void goToSleep() {
        std::cout << name << " goes to sleep." << std::endl;
    }

    void haveFun(int funFactor = 1) {
        std::cout << name << " is having fun and enjoying a hobby." << std::endl;
        fitness += 5 * funFactor;  // Fitness increases during entertainment
        health += 5 * funFactor;
    }
};

int main() {
    std::vector<Person> people;
    people.push_back(Person("Alice", 25));
    people.push_back(Person("Bob", 30));

    people[0].makeFriend(people[1]);

    std::thread thread1(&Person::runVirtualLife, &people[0]);
    std::thread thread2(&Person::runVirtualLife, &people[1]);

    thread1.join();
    thread2.join();

    return 0;
}