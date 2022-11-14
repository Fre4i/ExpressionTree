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

//string lexStr(string str, int &pos) {
//	while (pos < str.length()) {
//		if 
//	}
//}

/// <summary>
/// Перечисление возможных операций
/// </summary>

enum Signs {
	DIV, MUL, 
	MIN, PLUS,
	LEFT_BRACKET, RIGHT_BRACKET,
};

map <Signs, string> mp = {
	{LEFT_BRACKET, "("},
	{RIGHT_BRACKET, ")"},
	{DIV, "/"},
	{MUL, "*"},
	{MIN, "-"},
	{PLUS, "+"},
};
// обратная польская запись
vector<string> reversePolishNotaion(string exp) {
	vector<string> res;
	stack<Signs> stk; // в стеке храним только знаки операций и скобки

	int i = 0;
	while (i < exp.length()) {
		switch (exp[i]) {
			case '(':
				stk.push(LEFT_BRACKET);
				i++;
				break;
			case ')':
				// уничтажаем обе скобки
				while (stk.top() != LEFT_BRACKET) {
					if (stk.top() != LEFT_BRACKET || stk.top() != RIGHT_BRACKET) {
						res.push_back(mp[stk.top()]);
					}
					stk.pop();
				}
				i++;
				stk.pop();
				break;
			case '/':
				if (stk.empty() || stk.top() > MUL) {
					stk.push(DIV);
				}
				else {
					res.push_back(mp[stk.top()]);
				}
				i++;
				break;
			case '*':
				if (stk.empty() || stk.top() > MUL) {
					stk.push(MUL);
				}
				else {
					res.push_back(mp[stk.top()]);
				}
				i++;
				break;
			case '-':
				if (stk.empty() || stk.top() > PLUS) {
					stk.push(MIN);
				} else {
					res.push_back(mp[stk.top()]);
				}
				i++;
				break;
			case '+':
				if (stk.empty() || stk.top() > PLUS) {
					stk.push(PLUS);
				} else {
					res.push_back(mp[stk.top()]);
				}
				i++;
				break;
			default:
				string t = "";

				do {
					t += exp[i];
					i++;
					if (i >= exp.length())
						break;
				} while (exp[i] >= 'a' && exp[i] <= 'z' || exp[i] >= '0' && exp[i] <= '9');

				res.push_back(t);

		}
	}

	// если стек не пуст, извлекаем из него все операции
	while (!stk.empty()) {
		res.push_back(mp[stk.top()]);
		stk.pop();
	}

	return res;
}

int main()	{

	string exp1 = "a+(b-c)*d";
	string exp2 = "a+b*c";
	string exp3 = "21+2*3";

	vector<string> vec1 = reversePolishNotaion(exp1);
	for (auto el : vec1) {
		cout << el << ' ';
	}

	cout << '\n';

	vector<string> vec2 = reversePolishNotaion(exp2);
	for (auto el : vec2) {
		cout << el << ' ';
	}

	cout << '\n';

	vector<string> vec3 = reversePolishNotaion(exp3);
	for (auto el : vec3) {
		cout << el << ' ';
	}

    return 0;
}