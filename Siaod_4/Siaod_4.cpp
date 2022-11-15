#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <map>

using namespace std;

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

/// <summary>
/// Преобразование в древовидную 
/// </summary>

class Node {
	string val;
	Node *left, *right;

public:
	Node(string val) { this->val = val; }
	static Node parseUpn(vector<string> vec) {
		vector<string> signs = {
			"*", "/", "+", "-"
		};

		stack<Node> stk;

		for (auto el : vec) {
			Node *node = new Node(el);
			auto it = find(signs.begin(), signs.end(), el);
			if (it != signs.end()) {
				node->right = &stk.top();
				stk.pop();
				node->left = &stk.top();	
				stk.pop();
			}
			stk.push(*node);
		}
		auto res = stk.top();
		stk.pop();
		return res;
	}
	string toString() {
		return this->left ? this->val : this->left->toString() + ' ' + this->val + ' ' + this->right->toString();
	}
};



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

	cout << Node::parseUpn(vec2).toString() << endl;

    return 0;
}