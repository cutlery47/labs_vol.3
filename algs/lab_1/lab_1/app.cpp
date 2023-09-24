#include "app.h"

void Application::hideCursor() {
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &cursor);
}

Application::Application() {
    exec();
}

void Application::station() {
    Stack* ops = new Stack(0);
    std::string infix = "";
    std::string result = "";
    char cur;

    std::cout << "Enter an expression in Reverse Polish Notation ... \n";
    std::cout << "Valid operations: +, -, *, /, sin (s), cos(c), (, ). \n";
    std::getline(std::cin, infix);

    for (int i = 0; i < infix.size(); ++i) {
        if (infix[i] == ' ') {
            continue;
        }

        cur = infix[i];

        if (cur >= 48 && cur <= 57) {
            result.append(1, cur);
            result.append(1, ' ');

        } else if ((cur >= '(' && cur <= '+') || (cur == '-') || (cur == '/') || (cur == 's') || (cur == 'c')) {
            
            if (cur == '+' || cur == '-') {
                while (ops->top() == '*' || ops->top() == '/') {
                    result.append(1, ops->pop());
                    result.append(1, ' ');
                }
                ops->push(cur);
                
            } else if (cur == ')') {
                while (ops->top() != '(') {
                    result.append(1, ops->pop());
                    result.append(1, ' ');
                }
                
                ops->pop();

                if (ops->top() == 's' || ops->top() == 'c') {
                    result.append(1, ops->pop());
                    result.append(1, ' ');
                }

            } else {
                ops->push(cur);
            }
        }
       
    }

    while (ops->size != 0) {
        result.append(1, ops->pop());
        result.append(1, ' ');
    }
    
    std::cout << std::endl << result << std::endl;
    
}

void Application::exec() {
    //hideCursor();

    /*List* list = new List(5);
    ListNode* node = list->find(5);

    if (node) {
        std::cout << node->data;
    } 
     
    std::cout << std::endl;
    list->print();
    
    list->insert(0, 123);

    std::cout << std::endl;
    list->print();*/

    /*Stack* stack = new Stack(0);
    
    stack->pop();
    stack->print();*/
    station();
}