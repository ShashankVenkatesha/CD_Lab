#include <iostream>
#include <iomanip>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct Quadruple {
    string op;
    string operand1;
    string operand2;
    string result;
};

struct Triple {
    string op;
    string operand1;
    string operand2;
};

struct ThreeAddressCode {
    string op;
    string arg1;
    string arg2;
    string result;
};

class IntermediateCodeGenerator {
private:
    int tempCount;
    vector<Quadruple> quadruples;
    vector<Triple> triples;
    vector<ThreeAddressCode> threeAddressCodes;

public:
    IntermediateCodeGenerator() : tempCount(0) {}

    string generateTemp() {
        return "t" + to_string((tempCount++));
    }

    void generateIntermediateCode(const string& expression) {
        stack<char> operators;
        stack<string> operands;

        for (char token : expression) {
            if (isspace(token))
                continue;
            else if (isalpha(token)) {
                operands.push(string(1, token));
            } else if (token == '(') {
                operators.push(token);
            } else if (token == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    char op = operators.top();
                    operators.pop();

                    string operand2 = operands.top();
                    operands.pop();

                    string operand1 = operands.top();
                    operands.pop();

                    string temp = generateTemp();
                    Quadruple quad;
                    quad.op = op;
                    quad.operand1 = operand1;
                    quad.operand2 = operand2;
                    quad.result = temp;
                    quadruples.push_back(quad);
                    operands.push(temp);
                }
                operators.pop(); // Pop '('
            } else if (token == '+' || token == '-' || token == '*' || token == '/') {
                while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                    char op = operators.top();
                    operators.pop();

                    string operand2 = operands.top();
                    operands.pop();

                    string operand1 = operands.top();
                    operands.pop();

                    string temp = generateTemp();
                    Quadruple quad;
                    quad.op = op;
                    quad.operand1 = operand1;
                    quad.operand2 = operand2;
                    quad.result = temp;
                    quadruples.push_back(quad);
                    operands.push(temp);
                }
                operators.push(token);
            }
        }

        while (!operators.empty()) {
            char op = operators.top();
            operators.pop();

            string operand2 = operands.top();
            operands.pop();

            string operand1 = operands.top();
            operands.pop();

            string temp = generateTemp();
            Quadruple quad;
            quad.op = op;
            quad.operand1 = operand1;
            quad.operand2 = operand2;
            quad.result = temp;
            quadruples.push_back(quad);
            operands.push(temp);
        }

        // Generate Triples
        for (const auto& quad : quadruples) {
            Triple triple;
            triple.op = quad.op;
            triple.operand1 = quad.operand1;
            triple.operand2 = quad.operand2;
            triples.push_back(triple);
        }

        for (const auto& triple : triples) {
            ThreeAddressCode tac;
            tac.op = triple.op;
            tac.arg1 = triple.operand1;
            tac.arg2 = triple.operand2;
            tac.result = triple.op == "=" ? triple.operand1 : generateTemp();
            threeAddressCodes.push_back(tac);
        }
    }

    int precedence(char op) {
        if (op == '+' || op == '-')
            return 1;
        else if (op == '*' || op == '/')
            return 2;
        else
            return 0;
    }

    void printQuadruples() {
        cout << "Quadruples:" << endl;
        cout << setw(8) << "OP" << setw(8) << "Operand1" << setw(8) << "Operand2" << setw(8) << "Result" << endl;
        for (const auto& quad : quadruples) {
            cout << setw(8) << quad.op << setw(8) << quad.operand1 << setw(8) << quad.operand2 << setw(8) << quad.result << endl;
        }
    }

    void printTriples() {
        cout << "Triples:" << endl;
        cout << setw(8) << "OP" << setw(8) << "Operand1" << setw(8) << "Operand2" << endl;
        for (size_t i = 0; i < triples.size(); ++i) {
            cout << setw(8) << triples[i].op << setw(8) << triples[i].operand1 << setw(8) << triples[i].operand2 << endl;
        }
    }

    void printThreeAddressCode() {
        cout << "Three-Address Code:" << endl;
        for (const auto& tac : threeAddressCodes) {
            cout << tac.result << " = " << tac.arg1 << " " << tac.op << " " << tac.arg2 << endl;
        }
    }
};

int main() {
    IntermediateCodeGenerator generator;
    string expression;
    cout << "Enter the expression: ";
    getline(cin, expression);
       
    generator.generateIntermediateCode(expression);
    generator.printThreeAddressCode();
    generator.printQuadruples();
    cout << endl;
    generator.printTriples();
    cout << endl;


    return 0;
}
