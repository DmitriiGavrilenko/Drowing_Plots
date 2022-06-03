// Drowing_Plots.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <conio.h>
#include <limits>
//#include <matplot.h>
#include "exprtk.hpp"
//#include "matplotlibcpp.h"
#include "bitmap-master/bitmap_image.hpp"

using namespace std;

unsigned int height = 1080, width = 1620;

void copyletter(string name,unsigned int i, unsigned int j, unsigned int x, unsigned int y)
{
    bitmap_image image(name);
    bitmap_image sourceimage("letters.bmp");
    bitmap_image region;
    sourceimage.region(20 * i+2, 20 * j, 16, 20, region);
    image.copy_from(region, x, y);
    image.save_image(name);
}

void drawtext(string text, string name,unsigned int x, unsigned int y)
{
    //bitmap_image image(name);
    //bitmap_image sourceimage("letters.bmp");
    

    unsigned int textsize = size(text);
    //bitmap_image region;
    unsigned int symbolcode;
    int i=0, j=0;
    for (int l = 0; l < textsize; l++)
    {
        symbolcode = text[l]-16;
        j = symbolcode / 16-1;
        
        i = symbolcode % 16;
        //cout << "symbolcode=" << symbolcode << "i=" << i << "j=" << j << endl;
        copyletter(name, i, j,x+16*l,y);
    }
    //image.save_image(name);
}

string numbertotext(double val)
{
    int intpart;
    double fracpart, digitnumber;
    string text, text1, text2, reducedtext1, reducedtext2, output;
    bool sgnm;
    if (val < 0)
    {
        sgnm = 0;
    }
    else
    {
        sgnm = 1;
    }
    digitnumber = (int)log10(abs(val));
    fracpart = modf((log10(abs(val)) + 100), &digitnumber);
    digitnumber = digitnumber - 100;
    val = round(abs(val) * pow(10, -digitnumber + 1)) / pow(10, -digitnumber + 1);
    text1 = to_string(val * pow(10, -digitnumber));
    text2 = to_string(digitnumber);
    text = text1.substr(0, 3) + "*10^" + text2.substr(0, 3);
    if (!sgnm)
    {
        output = "-" + text;
    }
    else
    {
        output = "" + text;
    }
    return (output);
}

void drawticks(string name, unsigned int dx, unsigned int dy, unsigned int N_width, unsigned int N_height, double xmin, double xmax, double ymin, double ymax)
{
    bitmap_image image(name);
    image_drawer draw(image);
    draw.pen_width(3);
    draw.pen_color(255, 150, 50);
    unsigned int tick_number = 6;

    for (int k = 0; k < tick_number + 1; k++)
    {

        draw.vertical_line_segment(height - height / (4 * dy), height - 3 * height / (4 * dy), k * N_width / tick_number + width / dx);
        draw.horiztonal_line_segment(width / (4 * dx), 3 * width / (4 * dx), k * N_height / tick_number + height / dy);

    }



    image.save_image(name);



    int intpart;
    double fracpart,val, digitnumber;
    string text, text1, text2, reducedtext1, reducedtext2,output;
    bool sgnm;

    for (int k = 0; k < tick_number; k++)
    {
        
        val = (xmax - xmin) * k / tick_number + xmin;

        drawtext(numbertotext(val), name, k * N_width / tick_number + width / dx, height - 3 * height / (4 * dy) - 20);

        val = ymax - (ymax - ymin) * (k + 1) / tick_number;
        drawtext(numbertotext(val), name, 3 * width / (4 * dx), (k+1) * N_height / tick_number + height / dy-25);

    }
}

void drawaxes(string name, unsigned int dx, unsigned int dy, unsigned int N_width, unsigned int N_height, double xmin, double xmax, double ymin, double ymax)
{
    bitmap_image image(name);
    image_drawer draw(image);
    draw.pen_width(3);
    draw.pen_color(255, 150, 50);
    draw.horiztonal_line_segment(0, width - width / (2 * dx), height - height / (2 * dy));
    draw.line_segment(width - width / (2 * dx), height - height / (2 * dy), width - width / dx, height - 3 * height / (4 * dy));
    draw.line_segment(width - width / (2 * dx), height - height / (2 * dy), width - width / dx, height - height / (4 * dy));
    draw.vertical_line_segment(height / (2 * dy), height, width / (2 * dx));
    draw.line_segment(width / (2 * dx), height / (2 * dy), width / (4 * dx), 3 * height / (4 * dy));
    draw.line_segment(width / (2 * dx), height / (2 * dy), 3 * width / (4 * dx), 3 * height / (4 * dy));

    image.save_image(name);

    drawticks(name, dx, dy, N_width, N_height, xmin, xmax, ymin, ymax);

    copyletter(name, 8, 5, width - width / dx, height - 3 * height / (4 * dy) - 20);
    copyletter(name, 9, 5, 3 * width / (4 * dx), width / (2 * dx));
}



template <typename T>
string single_var_function()
{
    typedef exprtk::symbol_table<T> symbol_table_t;
    typedef exprtk::expression<T>   expression_t;
    typedef exprtk::parser<T>       parser_t;

    cout << "Input single variable function" << endl;
    string user_expression;
    getline(cin, user_expression);
    string name = user_expression + ".bmp";
    string filename = user_expression + ".txt";

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

    //writting in file

    //cout << "Do you want write in file?\n 0 - Yes   1 - No" << endl;
    //bool writeafile;
    //cin >> writeafile;
    /*if (writeafile)
    {
        ofstream fout;
        fout.open(filename);
    }*/
    ofstream fout;
    fout.open(filename);



    for (x = lower_limit; x < higher_limit; x += step)
    {
        y = expression.value();
        /*if (writeafile)
        {
            fout << x << "   " << y << endl;
        }*/
        fout << x << "   " << y << endl;
        if (y > max) max = y;
        if (y < min) min = y;
    }
    /*if (writeafile)
    {
        fout.close();
    }*/
    fout.close();

    /*cout << "Input widh" << endl;
    cin >> width;
    cout << "Input height" << endl;
    cin >> height;*/
    unsigned int d = 20, dy = 20, dx = 25;
    dx = (unsigned int) dy * width / height;


    bitmap_image image(width, height);
    image_drawer draw(image);
    unsigned int N_height = height - height * 2 / dy;
    unsigned int N_width = width - width * 2 / dx;
    unsigned int i = 0, j = N_height/20;

    
    
    image.set_all_channels(255, 255, 255);
    draw.pen_width(3);
    draw.pen_color(255, 150, 50);




    T y1, y2;
    int j1, j2;
    while (i < width - 2 * width / dx)
    {
        x = lower_limit + (higher_limit - lower_limit) * i / N_width;
        y1 = expression.value();
        j1 = (y1 - min) / (max - min) * N_height + height / dy;
        x = lower_limit + (higher_limit - lower_limit) * (i+1) / N_width;
        y2 = expression.value();
        j2 = (y2 - min) / (max - min) * N_height + height / dy;
        draw.line_segment(i + width / dx, height - j1, i + 1 + width / dx, height - j2);
        i++;
        //cout << j2 << i << endl;
    }

    //name = string::name.substr(0,10);
    //image.save_image(output.bmp);
    image.save_image(name);
    drawaxes(name, dx, dy, N_width, N_height, lower_limit, higher_limit, min, max);
    drawtext(user_expression, name, 500, 100);
    return user_expression;
}


int main()
{
    //trig_function/*<double>*/();
    string user_expression = single_var_function<double>();
    //string name = user_expression + ".bmp";
    //drawtext(user_expression, name, 100, 100);
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
