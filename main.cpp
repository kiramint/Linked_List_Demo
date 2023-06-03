#include <iostream>
#include "lists.h"

#ifdef _WIN32   //windows and linux have different clear command.
#define CL "cls"
#elif __linux__
#define CL "clear"
#elif __APPLE__
#define CL "clear"
#endif

void test() {   //test once
    listsSpace::lists<std::string> list;
    list.append("Never");
    list.append("wanna");
    list.append("give");
    list.append("you");
    list.append("up");
    list.append(",");
    list.append("never");
    list.append("wanna");
    list.append("let");
    list.append("you");
    list.append("down");
    std::cout << "The list is: ";
    list.printList();
    std::cout << std::endl << "The third element is: \033[1;31m" << list.getMemberNo(3) << "\033[0m" << std::endl;
    std::cout << std::endl << "Delete the last element:" << std::endl;
    list.backspace();
    list.printList();
    std::cout << std::endl << "There are " << list.getLength() << " elements remain is the list" << std::endl;
    std::cout << std::endl << "Inset a element before the third one:" << std::endl;
    list.insert("WORD", 3);
    list.printList();
    std::cout << std::endl << "There are " << list.getLength() << " elements remain is the list" << std::endl;
    std::cout << std::endl << "Replace the fourth element into `HAPPY`:" << std::endl;
    list.replace("HAPPY", 4);
    list.printList();
    std::cout << std::endl << "Cut elements between 5~8:" << std::endl;
    list.cutBetween(5, 8);
    list.printList();
    std::cout << std::endl << "There are " << list.getLength() << " elements remain is the list" << std::endl;
    list.destroy();
    std::cout << "Check memory leak:" << list.ifMemoryLeak() << std::endl;
}

int main() {
    std::string ans;
    std::cout << "Do you want to test the linked list using a terminal instead of a demo?";
    std::cout << "(y/n/l [l:Loop test(Stop by using Ctrl-C)] default:y):";
    std::getline(std::cin, ans);
    if (ans == "n" || ans == "N") {
        system(CL);
        test();
    } else {
        if (ans == "l" || ans == "L") {
            system(CL);
            while (true) {
                test();
            }
        } else {
            system(CL);
            listsSpace::testInTerminal testIT;
            testIT.init();
        }
    }
    return 0;
}
