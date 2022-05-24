// Drowing_Plots.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <cmath>
#include <conio.h>
#include <limits>
//#include <matplot.h>
#include "exprtk.hpp"
//#include "matplotlibcpp.h"
#include "bitmap-master/bitmap_image.hpp"



using namespace std;


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
    
    T y;

    T step = (higher_limit - lower_limit) / 1000;
    /*cout << "Input step" << endl;
    cin >> step;
    for (x = lower_limit; x < higher_limit; x += step)
    {
        y = expression.value();
        printf("%19.15f\t%19.15f\n", x, y);
    }*/


    x = lower_limit;
    T max = expression.value();
    T min = expression.value();
    /*T max = numeric_limits<T>::min();
    T min = numeric_limits<T>::max();*/
    for (x = lower_limit; x < higher_limit; x += step)
    {
        y = expression.value();
        if (y > max) max = y;
        if (y < min) min = y;
    }


    unsigned int height, widh;

    height = 600;
    widh = 800;
    cout << "Input widh" << endl;
    cin >> widh;
    cout << "Input height" << endl;
    cin >> height;/**/
    unsigned int d = 20, dy = 20, dx = 25;
    dx = (int) dy * widh / height;


    bitmap_image image(widh, height);
    image_drawer draw(image);
    unsigned int N_height = height - height * 2 / dy;
    unsigned int N_widh = widh - widh * 2 / dx;
    unsigned int i = 0, j = N_height/20;

    
    
    image.set_all_channels(255, 255, 255);
    draw.pen_width(3);
    draw.pen_color(255, 150, 50);




    T y1, y2;
    int j1, j2;
    while (i < widh - 2 * widh / dx)
    {
        x = lower_limit + (higher_limit - lower_limit) * i / N_widh;
        y1 = expression.value();
        j1 = (y1 - min) / (max - min) * N_height + height / dy;
        x = lower_limit + (higher_limit - lower_limit) * (i+1) / N_widh;
        y2 = expression.value();
        j2 = (y2 - min) / (max - min) * N_height + height / dy;
        draw.line_segment(i + widh / dx, height - j1, i + 1 + widh / dx, height - j2);
        i++;
        //cout << j2 << i << endl;
    }

    //axes
    draw.horiztonal_line_segment(0, widh - widh / (2*dx), height - height / (2 * dy));
    draw.line_segment(widh - widh / (2 * dx), height - height / (2 * dy), widh - widh / dx, height - 3 * height / (4 * dy));
    draw.line_segment(widh - widh / (2 * dx), height - height / (2 * dy), widh - widh / dx, height - height / (4 * dy));
    draw.vertical_line_segment(height / (2 * dy), height, widh / (2 * dx));
    draw.line_segment(widh / (2 * dx), height / (2 * dy), widh / (4 * dx), 3*height / (4 * dy));
    draw.line_segment(widh / (2 * dx), height / (2 * dy), 3*widh / (4 * dx), 3 * height / (4 * dy));


    //ticks
    unsigned int tick_number = 6;

    for (int k = 0; k < tick_number + 1; k++)
    {
        draw.vertical_line_segment(height - height / (4 * dy), height - 3 * height / (4 * dy), k * N_widh / tick_number + widh / dx);
        draw.horiztonal_line_segment(widh / (4 * dx), 3 * widh / (4 * dx), k * N_height / tick_number + height / dy);
    }

    string name =user_expression + ".bmp";
    //name = string::name.substr(0,10);
    //image.save_image(output.bmp);
    image.save_image(name);

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
