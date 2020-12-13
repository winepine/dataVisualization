#include<iostream>
#include<string>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class BST;
BST* yos;
int height(BST*& arg, int h = 0);
void setLine(BST*& arg, int val, float multiplier = height(yos));
Font font;
#define X 50
#define Y 90
ContextSettings settings(0, 0, 8, 0, 0, 0, 0);
int iffibonacci(int n)
{
    int a = 0;
    int b = 1;
    if (n == a || n == b) {
        return true;
    }
    int c = a + b;
    while (c <= n) {
        if (c == n) {
            return true;
        }
        a = b;
        b = c;
        c = a + b;
    }
    return false;
}
bool ifamstrong(int n) {
    int temp = n;
    int sum = 0;
    while (temp > 0)
    {
        sum = sum + ((temp % 10) * (temp % 10) * (temp % 10));
        temp = temp / 10;
    }
    if (sum == n)return true;
    return false;
}
bool ifpalindrome(int n) {
    int temp = n;
    int sum = 0;
    while (temp > 0)
    {
        sum = (sum * 10) + temp % 10;
        temp = temp / 10;
    }
    if (sum == n)return true;
    return false;
}
class BST {
public:
    int data;
    BST* left = NULL;
    BST* right = NULL;
    CircleShape* Space = NULL;
    RectangleShape* linkleft = NULL;
    RectangleShape* linkright = NULL;
    Text* valdisp;
    BST(int val) {
        data = val;
        Space = new CircleShape(30, 20);
        valdisp = new Text(to_string(data), font, 40);
        if (iffibonacci(val)) {
            Space->setFillColor(Color(0, 255, 0, 200));
        }
        else if (ifamstrong(val)) {
            Space->setFillColor(Color(255, 0, 0, 200));
        }
        else if (ifpalindrome(val)) {
            Space->setFillColor(Color(0, 0, 255, 200));
        }
        else {
            Space->setFillColor(Color(100, 100, 100));
        }
    }
};
void insert(BST*& arg, int data) {
    if (!arg) {
        arg = new BST(data);
        setLine(yos, data);
        return;
    }
    if (data > arg->data) {
        if (arg->right) {
            insert(arg->right, data);
        }
        else {
            arg->right = new BST(data);
            setLine(yos, data);
        }
    }
    if (data < arg->data) {
        if (arg->left) {
            insert(arg->left, data);
        }
        else {
            arg->left = new BST(data);
            setLine(yos, data);
        }
    }
}
void setPositionsOfLeftCircles(BST*& arg, int i = 8, int j = 2) {
    if (!arg)return;
    setPositionsOfLeftCircles(arg->left, i - 2, j + 1);
    arg->Space->setPosition(i * X, j * Y);
    arg->valdisp->setPosition(i * X + 15, j * Y);
    if (arg->linkleft) {
        arg->linkleft->setPosition(i * X + 30, j * Y + 60);
    }
    if (arg->linkright) {
        arg->linkright->setPosition(i * X + 30, j * Y + 60);
    }
    setPositionsOfLeftCircles(arg->right, i + 1, j + 1);
}
void setPositionsOfRightCircles(BST*& arg, int i = 12, int j = 2) {
    if (!arg)return;
    setPositionsOfLeftCircles(arg->left, i - 1, j + 1);
    arg->Space->setPosition(i * X, j * Y);
    arg->valdisp->setPosition(i * X + 15, j * Y);
    if (arg->linkleft) {
        arg->linkleft->setPosition(i * X + 30, j * Y + 60);
    }
    if (arg->linkright) {
        arg->linkright->setPosition(i * X + 30, j * Y + 60);
    }
    setPositionsOfLeftCircles(arg->right, i + 2, j + 1);
}
void setpositionsCircles(BST*& arg) {
    if (!arg)return;
    arg->Space->setPosition(X * 10, Y * 1);
    arg->valdisp->setPosition(X * 10 + 15, Y * 1);
    if (arg->linkleft) {
        arg->linkleft->setPosition(X * 10 + 30, Y * 1 + 60); //30 is radius
    }
    if (arg->linkright) {
        arg->linkright->setPosition(X * 10 + 30, Y * 1 + 60);
    }
    setPositionsOfLeftCircles(arg->left);
    setPositionsOfRightCircles(arg->right);
}
void setLine(BST*& arg, int val, float multiplier) {
    if (!arg) {
        return;
    }
    if (val < arg->data) {
        if (arg->left) {
            if (arg->left->data == val) {
                arg->linkleft = new RectangleShape(Vector2f(2.0f,
                    90.0f));
                arg->linkleft->setRotation(55.f);
                arg->linkleft->setPosition(X * (multiplier - 1), Y *
                    multiplier);
            }
        }
    }
    if (val > arg->data) {
        if (arg->right) {
            if (arg->right->data == val) {
                arg->linkright = new RectangleShape(Vector2f(2.0f,
                    90.0f));
                arg->linkright->setRotation(-55.f);
                arg->linkright->setPosition(X * (multiplier + 1), Y *
                    multiplier);
            }
        }
    }
    setLine(arg->left, val, multiplier + 4);
    setLine(arg->right, val, multiplier + 4);
    return;
}
BST* smallest(BST*& arg) {
    if (!arg) {
        return NULL;
    }
    BST* temp = arg;
    while (temp->left) {
        temp = temp->left;
    }
    return temp;
}
BST* deleteleaf(BST*& arg, int data) {
    if (!arg) {
        return arg;
    }
    if (data > arg->data) {
        arg->right = deleteleaf(arg->right, data);
    }
    else if (data < arg->data) {
        arg->left = deleteleaf(arg->left, data);
    }
    else if (data == arg->data) {
        if (!arg->left) {
            BST* temp = arg;
            arg = arg->right;
            free(temp);
            return arg;
        }
        if (!arg->right) {
            BST* temp = arg;
            arg = arg->left;
            free(temp);
            return arg;
        }
        BST* tmp = smallest(arg->right);
        arg->data = tmp->data;
        arg->valdisp->setString(to_string(tmp->data));
        arg->right = deleteleaf(arg->right, arg->data);
    }
    return arg;
}
RenderWindow window(sf::VideoMode(1200, 900), "SFML works!", Style::Default,
    settings);
void inorder(BST*& arg) {
    if (!arg)return;
    inorder(arg->left);
    if (arg->linkleft) {
        window.draw(*(arg->linkleft));
    }
    if (arg->linkright) {
        window.draw(*(arg->linkright));
    }
    window.draw(*(arg->Space));
    window.draw(*(arg->valdisp));
    inorder(arg->right);
}
void mirror(BST* arg) {
    if (!arg)return;
    swap(arg->left, arg->right);
    mirror(arg->left);
    mirror(arg->right);
}
void inorderT(BST*& arg) {
    if (!arg)return;
    inorderT(arg->left);
    cout << arg->data << " ";
    inorderT(arg->right);
}
void searchElement(BST*& arg, int val) {
    if (!arg)return;
    if (val > arg->data) {
        searchElement(arg->right, val);
    }
    if (val < arg->data) {
        searchElement(arg->left, val);
    }
    if (val == arg->data) {
        arg->Space->setOutlineThickness(7);
        arg->Space->setOutlineColor(sf::Color(250, 150, 100));
    }
}
int main() {
    Text name;
    name.setFont(font);
    name.setString("Binary Search Tree Implementation");
    name.setCharacterSize(40);
    name.setPosition(330, 20);
    int choice, cal;
    font.loadFromFile("Squad Goals OTF.otf");
    //------------------------------------------
    Text color1("Default", font, 25);
    Text color2("Fibbonacci", font, 25);
    Text color3("Armstrong", font, 25);
    Text color4("Palindrome", font, 25);
    RectangleShape box1(Vector2f(20, 20));
    RectangleShape box2(Vector2f(20, 20));
    RectangleShape box3(Vector2f(20, 20));
    RectangleShape box4(Vector2f(20, 20));
    box1.setFillColor(Color(100, 100, 100));
    box2.setFillColor(Color(0, 255, 0, 200));
    box3.setFillColor(Color(255, 0, 0, 200));
    box4.setFillColor(Color(0, 0, 255, 200));
    box1.setPosition(100, 700);
    box2.setPosition(100, 740);
    box3.setPosition(100, 780);
    box4.setPosition(100, 820);
    color1.setPosition(130, 695);
    color2.setPosition(130, 735);
    color3.setPosition(130, 775);
    color4.setPosition(130, 815);
    //------------------------------------------
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        while (true)
        {
            system("cls");
            cout << "1.Insert To BST.\n";
            cout << "2.Delete From BST.\n";
            cout << "4.Get Mirror.\n";
            cout << "5.Search Element.\n";
            cout << "Your Choice:";
            cin >> choice;
            if (choice == 1) {
                cout << "Enter New Element: ";
                cin >> cal;
                insert(yos, cal);
            }
            else if (choice == 2) {
                cout << "Enter Element To Delete: ";
                cin >> cal;
                yos = deleteleaf(yos, cal);
            }
            else if (choice == 3) {
                inorderT(yos); cout << endl;
            }
            else if (choice == 4) {
                mirror(yos);
            }
            else if (choice == 5) {
                cout << "Enter Value To Search: ";
                cin >> cal;
                searchElement(yos, cal);
            }
            window.clear();
            window.draw(name);
            //======
            window.draw(box1);
            window.draw(box2);
            window.draw(box3);
            window.draw(box4);
            window.draw(color1);
            window.draw(color2);
            window.draw(color3);
            window.draw(color4);
            //======
            setpositionsCircles(yos);
            inorder(yos);
            window.display();
        }
    }
    return 0;
}
int height(BST*& arg, int h) {
    if (!arg) {
        return h;
    }
    int temp = height(arg->left, h + 1);
    h = height(arg->right, h + 1);
    if (temp > h) {
        h = temp;
    }
    return h;
}