#pragma once    //Only include once

#include <iostream>
#include <string>

namespace listsSpace {  //library namespace
    template<class listType>    //lists template class
    class lists {
    public:
        void forceInit() {  //in some situation we want force init
            init();
            std::cerr << "forceInit:LIST_FORCE_INIT!" << std::endl; //force init is not recommended
        }

        bool destroy() {
            if (ifInit) {
                listnodes *thisnode = nullptr;
                listnodes *nextnode = nullptr;
                listnodes *lastnode = getAddr(members - 1);
                thisnode = firstnode;
                for (int i = 0; i < members; i++) {
                    if (thisnode != lastnode) {
                        nextnode = thisnode->Next;
                        delete thisnode;
                        memLeak--;
                        thisnode = nextnode;
                    }
                }
                delete lastnode;
                memLeak--;
                thisnode = nullptr;
                nextnode = nullptr;
                lastnode = nullptr;
                ifInit = false;
                return true;
            } else {
                std::cerr << "NOT_INIT_YET" << std::endl;
                return false;
            }
        }

        void append(listType appVal) {
            listnodes *listnode = nullptr;
            listnodes *prevnode = nullptr;
            if (ifInit) {
                prevnode = getAddr(members - 1);
                listnode = new listnodes;
                memLeak++;
                listnode->val = appVal;
                listnode->Prev = prevnode;
                listnode->Next = nullptr;
                prevnode->Next = listnode;
                prevnode = nullptr;
                listnode = nullptr;
                members++;
            } else {
                init();
                append(appVal);
            }
        }

        void printList() {
            if (!ifInit) {
                std::cerr << "NOT_INIT_YET" << std::endl;
                return;
            }
            listnodes *thisnode = nullptr;
            listnodes *nextnode = nullptr;
            thisnode = firstnode;
            while (true) {
                if (thisnode->Next != nullptr) {
                    nextnode = thisnode->Next;
                    std::cout << "\033[1;33m" << nextnode->val << "\033[0m";
                    thisnode = nextnode;
                    if (thisnode->Next != nullptr) {
                        std::cout << "\033[1;34m" << "->" << "\033[0m";
                    }
                } else {
                    std::cout << std::endl;
                    thisnode = nullptr;
                    nextnode = nullptr;
                    return;
                }
            }
        }

        listType getMemberNo(int place) {
            if (!ifInit) {
                std::cerr << "NOT_INIT_YET" << std::endl;
                listType val;
                return val;
            }
            listnodes *thisnode = nullptr;
            listnodes *nextnode = nullptr;
            thisnode = firstnode;
            listType val;
            if (place >= members || place == 0) {
                thisnode = nullptr;
                nextnode = nullptr;
                std::cout << "getMemberNo:List Overflow!" << std::endl;
                return val;
            } else {
                for (int i = 0; i < place; i++) {
                    if (thisnode->Next != nullptr) {
                        nextnode = thisnode->Next;
                        thisnode = nextnode;
                        val = nextnode->val;
                    }
                }
                thisnode = nullptr;
                nextnode = nullptr;
                return val;
            }
        }

        void backspace() {
            if (!ifInit) {
                std::cerr << "NOT_INIT_YET" << std::endl;
                return;
            }
            listnodes *thisnode = nullptr;
            listnodes *nextnode = nullptr;
            listnodes *prevnode = nullptr;
            thisnode = firstnode;
            while (true) {
                if (thisnode->Next != nullptr) {
                    nextnode = thisnode->Next;
                    thisnode = nextnode;
                } else {
                    prevnode = thisnode->Prev;
                    delete thisnode;
                    memLeak--;
                    prevnode->Next = nullptr;
                    members--;
                    thisnode = nullptr;
                    nextnode = nullptr;
                    prevnode = nullptr;
                    return;
                }
            }
        }

        bool insert(listType value, int place) {
            if (!ifInit) {
                std::cerr << "NOT_INIT_YET" << std::endl;
                return false;
            }
            if (!(place > 0 && place < members)) {
                std::cerr << "insert:List Overflow!" << std::endl;
                return false;
            }
            listnodes *thisnode = nullptr;
            listnodes *nextnode = nullptr;
            listnodes *prevnode = nullptr;
            thisnode = firstnode;
            for (int i = 0; i < place; i++) {
                if (thisnode->Next != nullptr) {
                    nextnode = thisnode->Next;
                    thisnode = nextnode;
                } else {
                    thisnode = nullptr;
                    nextnode = nullptr;
                    std::cerr << "insert:List Overflow!" << std::endl;
                    return false;
                }
            }
            prevnode = thisnode->Prev;
            prevnode->Next = new listnodes;
            memLeak++;
            nextnode = prevnode->Next;
            nextnode->Prev = prevnode;
            nextnode->Next = thisnode;
            thisnode->Prev = nextnode;
            nextnode->val = value;
            members++;
            prevnode = nullptr;
            thisnode = nullptr;
            nextnode = nullptr;
            return true;
        }

        bool replace(listType value, int place) {
            if (!ifInit) {
                std::cerr << "NOT_INIT_YET" << std::endl;
                return false;
            }
            if (!(place > 0 && place < members)) {
                std::cerr << "insert:List Overflow!" << std::endl;
                return false;
            }
            listnodes *thisnode = nullptr;
            listnodes *nextnode = nullptr;
            thisnode = firstnode;
            for (int i = 0; i < place; i++) {
                if (thisnode->Next != nullptr) {
                    nextnode = thisnode->Next;
                    thisnode = nextnode;
                } else {
                    thisnode = nullptr;
                    nextnode = nullptr;
                    std::cerr << "replace:List Overflow!" << std::endl;
                    return false;
                }
            }
            thisnode->val = value;
            thisnode = nullptr;
            nextnode = nullptr;
            return true;
        }

        bool cutBetween(int place1, int place2) {
            if (!ifInit) {
                std::cerr << "NOT_INIT_YET" << std::endl;
                return false;
            }
            listnodes *list1 = getAddr(place1);
            listnodes *list2 = getAddr(place2);
            listnodes *thisnode = nullptr;
            listnodes *nextnode = nullptr;
            thisnode = list1->Next;
            if (place1 < 0 || place2 >= members) {
                return false;
            } else {
                while (true) {
                    if (thisnode != list2) {
                        nextnode = thisnode->Next;
                        delete thisnode;
                        memLeak--;
                        thisnode = nextnode;
                        members--;
                    } else {
                        break;
                    }
                }
                list1->Next = list2;
                list2->Prev = list1;
                return true;
            }

        }

        int getLength() {
            return members;
        }

        int ifMemoryLeak() {
            return memLeak;
        }

    private:
        bool ifInit = false;    //ifInit
        int members = 0;
        int memLeak = 0;
        struct listnodes {      //List node struct
            listType val;
            listnodes *Next;
            listnodes *Prev;
        };
        listnodes *firstnode = nullptr;

        void init() {
            firstnode = new listnodes;
            memLeak++;
            members++;
            firstnode->Next = nullptr;
            firstnode->val = -1;
            firstnode->Prev = nullptr;
            ifInit = true;
        }

        listnodes *getAddr(int place) { //get address of specific node
            listnodes *thisnode = nullptr;
            listnodes *nextnode = nullptr;
            if (place == 0) {
                return firstnode;
            }
            thisnode = firstnode;
            for (int i = 0; i < place; i++) {
                if (thisnode->Next != nullptr && place < members) {
                    nextnode = thisnode->Next;
                    thisnode = nextnode;
                } else {
                    thisnode = nullptr;
                    nextnode = nullptr;
                    std::cerr << "getAddr:List Overflow!" << std::endl;
                    return nullptr;
                }
            }
            nextnode = nullptr;
            return thisnode;
        }
    };

    //For Test:
    class testInTerminal {  //an emulated terminal to test the program
    public:
        void init() {
            msgLoop();  //Call the emulator
        }

    private:
        bool defaultAct = true;
        bool errHappend = false;
        lists<std::string> demolist; //the list for test

        void msgLoop() {    //to create an emulated terminal
            std::string inBuffer;
            std::cout << "A test demo to test list in demo." << std::endl;
            std::cout << "Use \"help()\" to display help and \"quit()\" to quit." << std::endl << std::endl;
            while (true) {  //get command from terminal
                std::cout << ">>> ";
                std::getline(std::cin, inBuffer);
                msgProcess(inBuffer);
            }
        }

        void msgProcess(std::string buffer) {   //input function process
            defaultAct = true;
            errHappend = false; //cant use string in switch, so I use for
            if (buffer.find("quit") != std::string::npos) {
                defaultAct = false;
                quit();
            }
            if (buffer.find("help") != std::string::npos) {
                defaultAct = false;
                helpMsg(true, 0);
            }
            if (buffer.find("append") != std::string::npos) {    //01
                defaultAct = false;
                if (buffer.find("(") != std::string::npos && buffer.find(")") != std::string::npos) {
                    buffer = buffer.substr(buffer.find("(") + 1, buffer.find(")") - buffer.find("(") - 1);
                    std::cout << "Appended: " << buffer << std::endl;
                    demolist.append(buffer);
                } else {
                    errHappend = true;
                    helpMsg(false, 1);
                }
            }
            if (buffer.find("destroy") != std::string::npos) {    //02
                defaultAct = false;
                if (buffer.find("(") != std::string::npos && buffer.find(")") != std::string::npos) {
                    demolist.destroy();
                } else {
                    errHappend = true;
                    helpMsg(false, 2);
                }
            }
            if (buffer.find("printList") != std::string::npos) {    //03
                defaultAct = false;
                if (buffer.find("(") != std::string::npos && buffer.find(")") != std::string::npos) {
                    demolist.printList();
                } else {
                    errHappend = true;
                    helpMsg(false, 3);
                }
            }
            if (buffer.find("ls") != std::string::npos) {    //03
                defaultAct = false;
                demolist.printList();
            }
            if (buffer.find("getMemberNo") != std::string::npos) {    //04
                defaultAct = false;
                if (buffer.find("(") != std::string::npos && buffer.find(")") != std::string::npos) {
                    buffer = buffer.substr(buffer.find("(") + 1, buffer.find(")") - buffer.find("(") - 1);
                    try {
                        std::cout << demolist.getMemberNo(std::stoi(buffer.c_str())) << std::endl;
                    }
                    catch (...) {
                        errHappend = true;
                        helpMsg(false, 4);
                    }
                } else {
                    errHappend = true;
                    helpMsg(false, 4);
                }
            }
            if (buffer.find("backspace") != std::string::npos) {    //05
                defaultAct = false;
                if (buffer.find("(") != std::string::npos && buffer.find(")") != std::string::npos) {
                    demolist.backspace();
                } else {
                    errHappend = true;
                    helpMsg(false, 5);
                }
            }
            if (buffer.find("insert") != std::string::npos) {    //06
                defaultAct = false;
                if (buffer.find("(") != std::string::npos && buffer.find(")") != std::string::npos &&
                    buffer.find(",") != std::string::npos) {
                    buffer = buffer.substr(buffer.find("(") + 1, buffer.find(")") - buffer.find("(") - 1);
                    std::string value, place;
                    value = buffer.substr(0, buffer.find(","));
                    place = buffer.substr(buffer.find(",") + 1, buffer.length());
                    try {
                        demolist.insert(value, stoi(place));
                    }
                    catch (...) {
                        errHappend = true;
                        helpMsg(false, 6);
                    }
                } else {
                    errHappend = true;
                    helpMsg(false, 6);
                }
            }
            if (buffer.find("replace") != std::string::npos) {    //07
                defaultAct = false;
                if (buffer.find("(") != std::string::npos && buffer.find(")") != std::string::npos &&
                    buffer.find(",") != std::string::npos) {
                    buffer = buffer.substr(buffer.find("(") + 1, buffer.find(")") - buffer.find("(") - 1);
                    std::string value, place;
                    value = buffer.substr(0, buffer.find(","));
                    place = buffer.substr(buffer.find(",") + 1, buffer.length());
                    try {
                        demolist.replace(value, stoi(place));
                    }
                    catch (...) {
                        errHappend = true;
                        helpMsg(false, 7);
                    }
                } else {
                    errHappend = true;
                    helpMsg(false, 7);
                }
            }
            if (buffer.find("cutBetween") != std::string::npos) {    //08
                defaultAct = false;
                if (buffer.find("(") != std::string::npos && buffer.find(")") != std::string::npos &&
                    buffer.find(",") != std::string::npos) {
                    buffer = buffer.substr(buffer.find("(") + 1, buffer.find(")") - buffer.find("(") - 1);
                    std::string place1, place2;
                    place1 = buffer.substr(0, buffer.find(","));
                    place2 = buffer.substr(buffer.find(",") + 1, buffer.length());
                    try {
                        demolist.cutBetween(stoi(place1), stoi(place2));
                    }
                    catch (...) {
                        errHappend = true;
                        helpMsg(false, 8);
                    }
                } else {
                    errHappend = true;
                    helpMsg(false, 8);
                }
            }
            if (buffer.find("getLength") != std::string::npos) {    //09
                defaultAct = false;
                if (buffer.find("(") != std::string::npos && buffer.find(")") != std::string::npos) {
                    std::cout << "The length of the list is: " << demolist.getLength() << std::endl;
                } else {
                    errHappend = true;
                    helpMsg(false, 9);
                }
            }
            if (buffer.find("ifMemoryLeak") != std::string::npos) {    //10
                defaultAct = false;
                if (buffer.find("(") != std::string::npos && buffer.find(")") != std::string::npos) {
                    std::cout << "Memory Leaks: " << demolist.ifMemoryLeak() << std::endl;
                } else {
                    errHappend = true;
                    helpMsg(false, 10);
                }
            }
            if (defaultAct) {
                std::cerr << "No valid commands! Try help() to display help." << std::endl;
            }
        }

        void helpMsg(bool mode, int num) {  //mode:[1]print all msg. [2]print No.{num}message.
            const int helplen = 11;
            std::string helpStr[helplen] = {
                    "List Demo Ver 1.0 by Kira Mint"
                    "Usage: \"function(argv)\" or \"function(argv)\" .\n"
                    "Only one function at a time.\n"
                    "The first function to run should be append().\n\n"
                    "help help():\t\t\tDisplay this message.\n"
                    "quit quit():\t\t\tQuit the program.\n",
                    "append([value]):\t\tAppend [value] to the list.\n",
                    "destroy():\t\t\tDestroy the entire list after using it.\n",
                    "ls printList():\t\t\tPrint the entire list to the console. (You can also use \"ls\")\n",
                    "getMemberNo([value]):\t\tReturns the value of the [value] element in the list, counting from 1.\n",
                    "backspace():\t\t\tDeletes the last value at the end of the list.\n",
                    "insert([value],[place]):\tInsert [value] before the [place] element, counting from 1.\n",
                    "replace([value],[place]):\tChange the [place] element to [value], counting from 1.\n",
                    "cutBetween(place1,place2):\tDelete elements within [place1] and [place2], excluding [place1] and [place2].\n",
                    "getLength():\t\t\tGet list length (number of elements).\n",
                    "ifMemoryLeak():\t\t\tUsed for debugging to check for memory leaks.\n"
            };
            if (mode) {
                for (int i = 0; i < helplen; i++) {
                    std::cout << helpStr[i];
                }
                std::cout << std::endl;
            }
            if (errHappend) {
                std::cout << "Syntax Error!" << std::endl;
                std::cout << "Usage: " << helpStr[num];
            }
        }

        void quit() {
            demolist.destroy();
            exit(0);
        }
    };
}