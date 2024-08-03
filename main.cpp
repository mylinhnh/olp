#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

// Lớp hỗ trợ chuyển đổi biểu thức
class InfixToPostfix {
private:
    string infix, postfix;

    // Hàm kiểm tra xem ký tự có phải là toán hạng không
    bool isOperand(char ch) {
        return isalnum(ch); // Trả về true nếu ký tự là chữ hoặc số
    }

    // Hàm trả về độ ưu tiên của toán tử
    int precedence(char op) {
        switch (op) {
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            case '^':
                return 3;
            default:
                return 0;
        }
    }
    // Hàm tính toán hai toán hạng với toán tử
    int applyOperation(int a, int b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return a / b;
        }
        return 0;
    }

public:
    // Hàm khởi tạo
    InfixToPostfix(string infixExpr) : infix(infixExpr) {}

    // Hàm chuyển đổi biểu thức infix thành postfix
    string convert() {
        stack<char> s;
        for (char ch : infix) {
            if (isOperand(ch)) {
                postfix += ch; // Thêm toán hạng vào chuỗi kết quả
            } else if (ch == '(') {
                s.push(ch); // Đẩy '(' vào stack
            } else if (ch == ')') {
                while (!s.empty() && s.top() != '(') {
                    postfix += s.top(); // Thêm tất cả các toán tử trong stack vào chuỗi kết quả
                    s.pop();
                }
                s.pop(); // Loại bỏ '(' khỏi stack
            } else {
                // Nếu là toán tử
                while (!s.empty() && precedence(s.top()) >= precedence(ch)) {
                    postfix += s.top(); // Thêm toán tử từ stack vào chuỗi kết quả nếu có độ ưu tiên cao hơn hoặc bằng toán tử hiện tại
                    s.pop();
                }
                s.push(ch); // Đẩy toán tử hiện tại vào stack
            }
        }

        // Thêm các toán tử còn lại trong stack vào chuỗi kết quả
        while (!s.empty()) {
            postfix += s.top();
            s.pop();
        }
        return postfix;
    }
    // Hàm tính toán kết quả từ biểu thức postfix
    int evaluatePostfix() {
        stack<int> s;
        for (char ch : postfix) {
            if (isOperand(ch)) {
                s.push(ch - '0'); // Chuyển ký tự số sang số nguyên và đẩy vào stack
            } else {
                int val2 = s.top(); s.pop();
                int val1 = s.top(); s.pop();
                int result = applyOperation(val1, val2, ch);
                s.push(result); // Đẩy kết quả vào stack
            }
        }
        return s.top();
    }
};

int main() {
    string infixExpr;
    cout << "infix: ";
    cin >> infixExpr;

    InfixToPostfix converter(infixExpr);
    string postfixExpr = converter.convert();

    cout << "postfix: " << postfixExpr << endl;
    cout << "result = " << converter.evaluatePostfix();
    return 0;
}
