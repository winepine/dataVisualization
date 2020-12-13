#include<iostream>
#include<string>
#include<ctime>
#include <SFML/Graphics.hpp>
using namespace sf;
bool isFULL = false;
#define CIRCLE_RAD 35.f
#define MARGIN 90.f
class list {
public:
    int data;
    RectangleShape* line;
    CircleShape* shape;
    list* next;
    list(int val) :data(val) {
        srand(time(NULL));
        shape = new CircleShape(CIRCLE_RAD, 4);
        shape->setFillColor(Color(rand() % 256 + 1, rand() % 256 + 1, rand() % 256
            + 1));
    }
};
void deleteElement(list*& arg, int val) {
    if (arg == NULL) {
        std::cout << "LinkedList Empty\n";
        return;
    }
    if (arg->data == val) {

        list* temp = arg;
        if (arg->next != NULL) {
            arg = arg->next;
        }
        else {
            arg = NULL;
        }
        free(temp);
        return;
    }
    list* traverse = arg;
    while (traverse->next != nullptr) {
        if (traverse->next->data == val) {
            list* temp = traverse->next;
            traverse->next = traverse->next->next;
            free(temp);
            return;
        }
        traverse = traverse->next;
    }
    std::cout << "No Element Found\n";
}
void addElement(list*& arg, int val) {
    if (arg == NULL) {
        arg = new list(val);
        arg->shape->setPosition(50.f, MARGIN);
        arg->line = new RectangleShape(Vector2f(35, 2));
        arg->line->setPosition(50.f + CIRCLE_RAD * 2, MARGIN + CIRCLE_RAD);
        return;
    }
    float pos = 3;
    list* traverse = arg;
    while (traverse->next != NULL) {
        traverse = traverse->next;
        pos = pos + 2;
    }
    if (pos <= 22) {
        traverse->next = new list(val);
        traverse->next->line = new RectangleShape(Vector2f(35, 2));
    }
    else if (pos <= 33) {
        traverse->next = new list(val);
        traverse->next->line = new RectangleShape(Vector2f(2, 35));
    }
    else {
        traverse->next = new list(val);
        traverse->next->line = new RectangleShape(Vector2f(35, 2));
        if (pos > 52) {
            isFULL = true;
            std::cout << "LIST FULL\n";
        }
    }
}
void updateVal(list*& arg, int node, int newVal) {
    if (!arg) {
        std::cout << "No Element In LinkedList\n";
        return;
    }
    list* traverse = arg;
    for (int i = 1; i < node; i++, traverse = traverse->next) {
        if (traverse->next == NULL) {
            return;
        }
    }
    traverse->data = newVal;
}
void display(list*& arg) {
    if (!arg) {
        std::cout << "No Element In LinkedList\n";
        return;
    }
    list* traverse = arg;
    while (traverse) {
        std::cout << traverse->data << " ";
        traverse = traverse->next;
    }
}
void searchNode(list*& arg, int val) {
    if (!arg) {
        std::cout << "No Element In LinkedList\n";
        return;
    }
    list* traverse = arg;
    int pos = 1;
    while (traverse != NULL) {
        if (traverse->data == val) {
            std::cout << "The position of requested node is " << pos << std::endl;
            return;
        }
        pos++;
        traverse = traverse->next;
    }
    std::cout << "Value Not Found.\n";
}
void swapNodes(list*& arg, int node1, int node2) {
    if (!arg) {
        std::cout << "No Element In LinkedList\n";
        return;
    }
    list* n1 = arg;
    list* n2 = arg;
    for (int i = 1; i < node1; i++, n1 = n1->next) {
        if (n1 == NULL) {
            return;
        }
    }
    for (int i = 1; i < node2; i++, n2 = n2->next) {
        if (n2 == NULL) {
            return;
        }
    }
    std::swap(n1->data, n2->data);
}
int main() {
    Font font;
    if (!font.loadFromFile("FuturaBQ.otf"))
    {
        std::cout << "NOPS";
    }
    Text name;
    name.setFont(font);
    name.setString("Linked List Demo");
    name.setCharacterSize(30);
    name.setPosition(450, 10);
    Text val;
    val.setFont(font);
    val.setCharacterSize(25);
    list* data = NULL;
    RenderWindow window(VideoMode(1200, 800), "Linked List Visualizer");
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        if (!isFULL) {
            int user;
            std::cout << "1. Insert New Node.\n";
            std::cout << "2. Delete A Node.\n";
            std::cout << "3. Update Value Of Node.\n";
            std::cout << "4. Swap Values Between 2 Nodes.\n";
            std::cout << "5. Search Node By Value.\nEnter A Number:";
            std::cin >> user;
            if (user == 1) {
                std::cout << "Enter Value For New Node:";
                std::cin >> user;
                addElement(data, user);
                system("cls");
            }
            else if (user == 2) {
                std::cout << "Enter Value To Delete Node:";
                std::cin >> user;
                deleteElement(data, user);
                system("cls");
            }
            else if (user == 3) {
                int newVal;
                std::cout << "Enter Node Number:";
                std::cin >> user;
                std::cout << "Enter New Value:";
                std::cin >> newVal;
                updateVal(data, user, newVal);
                system("cls");
            }
            else if (user == 4) {
                int newVal;
                std::cout << "Enter First Node:";
                std::cin >> user;
                std::cout << "Enter Second Node:";
                std::cin >> newVal;
                swapNodes(data, user, newVal);
                system("cls");
            }
            else if (user == 5) {
                std::cout << "Enter Value To Search:";
                std::cin >> user;
                system("cls");
                searchNode(data, user);
            }
        }
        float pos = 1;
        list* traverse = data;
        float defSize = 1.35;
        while (traverse) {
            val.setString(std::to_string(traverse->data));
            defSize = 1.35;
            if (traverse->data > 99) {
                defSize = 3.7;
            }
            else if (traverse->data > 9) {
                defSize = 2;
            }
            if (pos <= 22) {
                traverse->line->setPosition((50 * pos) + CIRCLE_RAD * 2, MARGIN +
                    CIRCLE_RAD);
                traverse->shape->setPosition(((50.f * pos)), MARGIN);
                if ((50 * pos) + CIRCLE_RAD * 2 == 1120) {
                    traverse->line = new RectangleShape(Vector2f(2, 35));
                    traverse->line->setPosition(1120 - CIRCLE_RAD, MARGIN + CIRCLE_RAD
                        * 2);
                }
                val.setPosition(((50.f * pos) + CIRCLE_RAD / defSize),
                    MARGIN + CIRCLE_RAD / 2);
            }
            else if (pos <= 33) {
                traverse->shape->setPosition(((50.f * 21)), 50.f * (pos - 19));
                traverse->line->setPosition(1120 - CIRCLE_RAD, (50.f * (pos - 19)) +
                    CIRCLE_RAD * 2);
                if (pos == 33) {
                    traverse->line = new RectangleShape(Vector2f(35, 2));
                    traverse->line->setPosition(((1050) - ((pos - 33) * 50.f)) -
                        CIRCLE_RAD, 700 + CIRCLE_RAD);
                }
                val.setPosition(((50.f * 21) + CIRCLE_RAD / defSize), 50.f * (pos -
                    19) + CIRCLE_RAD / 2);
            }
            else {
                traverse->shape->setPosition(((1050) - ((pos - 33) * 50.f)), 700);
                traverse->line->setPosition(((1050) - ((pos - 33) * 50.f)) -
                    CIRCLE_RAD, 700 + CIRCLE_RAD);
                val.setPosition(((1050) - ((pos - 33) * 50.f)) + CIRCLE_RAD / defSize,
                    700 + CIRCLE_RAD / 2);
            }
            window.draw(*(traverse->shape));
            window.draw(*(traverse->line));
            traverse = traverse->next;
            window.draw(val);
            pos = pos + 2;
        }
        window.draw(name);
        window.display();
        display(data);
    }
    return 0;
}