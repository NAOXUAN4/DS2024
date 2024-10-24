#include "utilities/Stack/Stack.hpp"
#include "op_power.hpp"
#include<bits/stdc++.h>

using namespace std;

// char* cal_str = "(1/4)*4/(1/4)*4";

void print(int n)
{
    cout << n << ' ';
}

void readNumber(char*& S, Stack<float>& opnd) { //从S中读入一个操作数，并把它入栈
    float n = 0; //操作数初值
    while (isdigit(*S)) //读入操作数
        n = n * 10 + *S++ - '0'; //将新读入的数字“压”入操作数
    opnd.push(n); //将操作数入栈
}
Operator charToOperator(char op) { //字符串运算符映射表，映射成int不好吗？为什么要映射为原算符再typedef
    switch (op) {
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
        case '^': return POW;
        case '!': return FAC;
        case '(': return L_P;
        case ')': return R_P;
        case '\0': return END_OF_FILE;
        default: return END_OF_FILE; // 默认返回结束符
    }
}

char orderBetween(char op1, char op2) { //比较运算符op1和op2的优先级高低
    
    char re =  pri[charToOperator(op1)][charToOperator(op2)]; //返回其优先级高低
    return re;
}

template <typename T>
T calcu(T opnd1, char op, T opnd2) { //返回计算结果
    return op == '+' ? opnd1 + opnd2 :
        op == '-' ? opnd1 - opnd2 :
        op == '*' ? opnd1 * opnd2 :
        op == '^' ? pow(opnd1, opnd2) :
        op == '/' ? opnd1 / opnd2 : 0;
}

template <typename T>
T calcu(T opnd1, char op) {
    if (op == '!')
    {
        T n = 1;
        for (int i = 1; i < opnd1 + 1; i++)
        {
            n*= i;
        }
        return n;
    }
    return T(0);
}

float evaluate(char* S) { //对（已剔除白空格癿）表达式S求值，幵转换为逆波兰式RPN
    Stack<float> opnd; Stack<char> optr; //运算数栈、运算符栈
    optr.push('\0'); 
    opnd.push(0);
    int step = 0;
    while (!optr.empty()) { //在运算符栈非空乀前，逐个处理表达式中各字符
        if (isdigit(*S)) { 
            readNumber(S, opnd); //读入操作数
        } else //若弼前字符为运算符，则
        {
            switch(orderBetween(optr.top(), *S)) { //规其不栈顶运算符乀间优先级高低分删处理
                case '<': //栈顶运算符优先级更低时
                    optr.push(*S); S++; //计算推迟，弼前运算符迕栈
                    break;
                case '=': //优先级相等（弼前运算符为右括号戒者尾部哨兵'\0'）时
                    optr.pop(); S++; //脱括号幵接收下一个字符
                    break;
                case '>': { 
                    char op = optr.pop();
                    if ('!' == op) { //若属亍一元运算符
                        float pOpnd = opnd.pop(); //叧需叏出一个操作数，幵
                        opnd.push(calcu(op, pOpnd)); //实斲一元计算，结枅入栈
                    } else { //对亍其它（二元）运算符
                        float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop(); 
                        opnd.push(calcu(pOpnd1, op, pOpnd2)); //实斲二元计算，结枅入栈
                    }
                    break;
                }
                default :exit(-1); //逢语法错误，丌做处理直接退出
            }//switch
        }
    }//while

    float res = opnd.pop();
    return res; //弹出幵迒回最后癿计算结枅
}

int largestRectangleArea(Vector<int>& heights) {
    stack<int> S;
    int max_area = 0;
    heights.push_Back(0); //哨兵

    for (int i = 0; i < heights.size(); ++i) {
        while (!S.empty() && heights[S.top()] > heights[i]) {
            int h = heights[S.top()];
            S.pop();
            int w = S.empty() ? i : i - S.top() - 1;
            max_area = max(max_area, h * w);
        }
        S.push(i);
    }

    return max_area;
}

int main()
{

    cout<<"\n1) 计算\n";
    cout<<"输入的字符串为：";
    char cal_str[100];

    // 使用 fgets 读取用户输入的一行
    std::cout << "请输入计算表达式: ";
    if (fgets(cal_str, sizeof(cal_str), stdin)) {
        // 去掉输入字符串末尾的换行符
        size_t len = strlen(cal_str);
        if (len > 0 && cal_str[len - 1] == '\n') {
            cal_str[len - 1] = '\0';
        }
    }
    cout<<"计算结果为："<<evaluate(cal_str)<<endl;

    cout<<"\n2) 柱体面积\n";

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    // 定义一个均匀分布，范围在 1 到 100 之间
    uniform_int_distribution<int> distribution(1, 105);

    

    int n = 10;
    while (n--)
    {
        Vector<int> Z;
        for(int i = 0; i < distribution(generator); i++)  //1 ~ 105
        {
            Z.push_Back(distribution(generator) - 1);  //0 ~ 104
        }

        cout<<"Time "<<10-n<<" pix: ";
        Z.traverse(print);
        cout<<endl;

        cout<<"MAX: "<<largestRectangleArea(Z)<<endl;
        
    }
    




}

