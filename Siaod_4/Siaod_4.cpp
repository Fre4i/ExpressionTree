#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>

using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;
};

class tree {
	Node* root; // корень

public:
	tree() {
		root = NULL;
	}
	void printTree(Node** p) {
		if (*p != NULL) {
			printTree(&((**p).right), 1);
			cout << (**p).key << '\n';
			printTree(&((**p).left), 1);
		}
	}
	void printTree(Node** p, int n) {
		if (*p != NULL) {
			printTree(&((**p).right), n);
			cout << (**p).key << '\n';
			printTree(&((**p).left), n);
		}
	}
	Node** getRoot() { return &root; }
	void Tree(int n, Node** p) {
		Node* now;
		int x, nl, nr;
		now = *p;
		if (n == 0) {
			*p = NULL;
		} else {
			nl = n / 2; 
			nr = n - nl - 1;
			cin >> x;
			now = new(Node);
			(*now).key = x;
			Tree(nl, &((*now).left));
			Tree(nr, &((*now).right));
			*p = now;
		}
	}
};

/// <summary>
/// Перечисление возможных операций
/// </summary>

//string lexStr(string str, int &pos) {
//	while (pos < str.length()) {
//		if 
//	}
//}


enum Signs {
	DIV, MUL, 
	MIN, PLUS,
	LEFT_BRACKET, RIGHT_BRACKET,
};

map <Signs, char> mp = {
	{LEFT_BRACKET, '('},
	{RIGHT_BRACKET, ')'},
	{DIV, '/'},
	{MUL, '*'},
	{MIN, '-'},
	{PLUS, '+'},
};
// обратная польская аннотация
string reversePolishNotaion(string exp) {
	string res = "";
	stack<Signs> stk; // в стеке храним только знаки операций и скобки

	int i = 0;
	while (i < exp.length()) {
		switch (exp[i]) {
			case '(':
				stk.push(LEFT_BRACKET);
				break;
			case ')':
				// уничтажаем обе скобки
				while (stk.top() != LEFT_BRACKET) {
					if (stk.top() != LEFT_BRACKET || stk.top() != RIGHT_BRACKET) {
						res += mp[stk.top()];
					}
					stk.pop();
				}
				stk.pop();
				break;
			case '/':
				if (stk.empty() || stk.top() > MUL) {
					stk.push(DIV);
				}
				else {
					res += mp[stk.top()];
				}
				break;
			case '*':
				if (stk.empty() || stk.top() > MUL) {
					stk.push(MUL);
				}
				else {
					res += mp[stk.top()];
				}
				break;
			case '-':
				if (stk.empty() || stk.top() > PLUS) {
					stk.push(MIN);
				} else {
					res += mp[stk.top()];
				}
				break;
			case '+':
				if (stk.empty() || stk.top() > PLUS) {
					stk.push(PLUS);
				} else {
					res += mp[stk.top()];
				}
				break;
			default:
				res += exp[i];
		}
		i++;
	}

	// если стек не пуст, извлекаем из него все операции
	while (!stk.empty()) {
		res += mp[stk.top()];
		stk.pop();
	}

	return res;
}

int main()	{

	string exp1 = "a+(b-c)*d";
	string exp2 = "a+b*c";
	cout << reversePolishNotaion(exp1) << '\n';
	cout << reversePolishNotaion(exp2) << '\n';

    return 0;
}