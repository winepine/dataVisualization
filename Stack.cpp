#include<iostream>
#include<string>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

Font font;
#define WIDTH 200
#define HEIGHT 45

class Stack {
public:
	int data[100];
	int pos = 0;
	void push(int arg) {
		if (pos == 100) {
			cout << "Stack is Full\n";
			return;
		}
		data[pos] = arg;
		pos++;
		return;
	}
	int pop() {
		if (!pos) {
			cout << "Stack Is Empty.\n";
			return false;
		}
		--pos;
		return data[pos];
	}
	bool isEmpty() {
		return !pos;
	}
	bool isFull() {
		if (pos == 100) {
			return true;
		}
		return false;
	}
	int top() {
		return data[pos - 1];
	}
};
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
void reverse(Stack& arg);
int x = 1;
int main() {
	Text name;
	name.setFont(font);
	name.setString("Stack Implementation");
	name.setCharacterSize(30);
	name.setPosition(250, 50);
	int choice;
	Stack yes;
	sf::RenderWindow window(sf::VideoMode(800, 1000), "SFML works!");
	font.loadFromFile("FuturaBQ.otf");


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
			cout << "1.Insert To Stack.\n";
			cout << "2.POP Stack.\n";
			cout << "3.Reverse Stack.\n";
			cout << "Your Choice:";
			cin >> choice;
			if (choice == 1) {
				cout << "Enter A Number: ";
				cin >> choice;
				yes.push(choice);
			}
			else if (choice == 2) {
				yes.pop();
			}
			else if (choice == 3) {
				reverse(yes);
			}
			window.clear();
			int temp2 = 0;
			int temptop = yes.pos - 1;
			while (temptop >= 0) {
				RectangleShape* box = new RectangleShape(Vector2f(WIDTH, HEIGHT));
				box->setFillColor(Color(rand() % 256 + 1, rand() % 256 + 1, rand() % 256 + 1));
				box->setPosition(300, (temptop * 50) + 150);
				Text no;
				if (iffibonacci(yes.data[temp2])) {
					no.setFillColor(Color(rand() % 256 + 1, rand() % 256 + 1, rand() % 256 + 1));
				}
				no.setFont(font);
				no.setCharacterSize(25);
				if (yes.data[temp2] > 99) {
					no.setPosition(380, (temptop * 50) + 155);
				}
				else if (yes.data[temp2] > 9) {
					no.setPosition(385, (temptop * 50) + 155);
				}
				else {
					no.setPosition(393, (temptop * 50) + 155);
				}
				no.setString(to_string(yes.data[temp2++]));
				temptop--;
				window.draw(*box);
				window.draw(no);
			}
			window.draw(name);
			window.display();
		}
	}
	return 0;
}
void inserte(Stack& stack, int x);
void reverse(Stack& arg) {
	if (!arg.isEmpty()) {
		int temp = arg.pop();
		reverse(arg);
		inserte(arg, temp);
	}
}
void inserte(Stack& stack, int x) {

	if (stack.isEmpty()) {
		stack.push(x);
		return;
	}
	int y = stack.pop();
	inserte(stack, x);
	stack.push(y);
}
