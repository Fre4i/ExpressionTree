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

auto counter = 0;

class Node {
public:
	string val;
	Node *left, *right;

public:
	Node(string val) { this->val = val; }
	static Node* parseUpn(vector<string> vec) {
		vector<string> signs = {
			"*", "/", "+", "-"
		};

		stack<Node*> stk;

		for (auto el : vec) {
			Node *node = new Node(el);
			auto it = find(signs.begin(), signs.end(), el);
			if (it != signs.end()) {
				node->right = stk.top();
				stk.pop();
				node->left = stk.top();	
				stk.pop();
				//cout << node->left->val + ' ' + node->val + ' ' + node->right->val;
			}
			stk.push(node);
		}
		auto res = stk.top();
		stk.pop();
		return res;
	}

	void print(Node* abranch, int counter) {
		 if (!abranch) return; //Если ветки не существует выходим
		 counter+=5;//считаем отступы
		 print(abranch->left, counter);
		 for (int i = 0; i < counter; i++)
		 {
		 cout << " ";
		 }
		 cout << abranch->val << endl;
		 print(abranch->right, counter);
		 counter = counter - 5;
		 return;
		}
	
	int getHeight() {
		int count = 1;
		while (this->left)
			count++;

		return count;
	}

	//void print(Node *node, int counter) {
	//		if (!node) return; //Если ветки не существует выходим
	//		counter -= 5;//считаем отступы
	//		print(node->left, counter);
	//		counter -= 5;
	//		for (int i = 0; i < counter; i++)
	//		{
	//			cout << " ";
	//		}
	//		cout << node->val << endl;
	//		if (node->right)
	//		{
	//			counter += 5;
	//		}
	//		print(node->right, counter);
	//		return;
	//	}
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

	cout << '\n';


	auto nd = Node::parseUpn(vec1);
	cout << nd->getHeight() << endl;
	//nd->print(nd, nd->getHeight() + 5);
	nd->print(nd, nd->getHeight() + 5);
    return 0;
}