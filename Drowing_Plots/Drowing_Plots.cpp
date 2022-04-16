// Drowing_Plots.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

#include "exprtk.hpp"

using namespace std;

//template <typename T>
void trig_function()
{
    
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double>   expression_t;
    typedef exprtk::parser<double>       parser_t;

    const std::string expression_string =
        "clamp(-1.0,sin(2 * pi * x) + cos(x / 2 * pi),+1.0)";

    double x;

    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(expression_string, expression);

    for (x = double(-5); x <= double(+5); x += double(0.001))
    {
        const double y = expression.value();
        printf("%19.15f\t%19.15f\n", x, y);
    }
}

template <typename T>
void single_var_function()
{
    typedef exprtk::symbol_table<T> symbol_table_t;
    typedef exprtk::expression<T>   expression_t;
    typedef exprtk::parser<T>       parser_t;

    cout << "Input single variable function" << endl;
    string user_expression;
    getline(cin, user_expression);

    T x;

    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;
    parser.compile(user_expression, expression);

    cout << "Input lower limit" << endl;
    T lower_limit;
    cin >> lower_limit;
    cout << "Input higher limit" << endl;
    T higher_limit;
    cin >> higher_limit;
    cout << "Input step" << endl;
    T step;
    cin >> step;

    for (x = lower_limit; x < higher_limit; x += step)
    {
        const T y = expression.value();
        printf("%19.15f\t%19.15f\n", x, y);
    }
}

int main()
{
    //trig_function/*<double>*/();
    single_var_function<double>();
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
