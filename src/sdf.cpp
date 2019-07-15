#include <iostream>


using namespace std;

class CharShape
{
public:
   	CharShape(char ch);    //带参数的构造函数声明 —— 重载
    virtual void Show() = 0;
protected:
    char _ch;       //组成图形的字符
};

class Triangle: public CharShape
{
public:
    Triangle(char ch, int rows);	//带参数的构造函数声明 —— 重载
    void Show();
private:
    int _rows;      //行数
};

class Rectangle: public CharShape
{
public:
    Rectangle(char ch, int rows, int cols);	//带参数的构造函数声明 —— 重载
    void Show();
private:
    int _rows, _cols;        //行数和列数
};

//构造函数初始化

CharShape::CharShape(char ch)
{
    _ch = ch;
}

Triangle::Triangle(char ch, int rows) : CharShape(ch)
{
    _rows = rows;
}

Rectangle::Rectangle(char ch, int rows, int cols) : CharShape(ch)
{
    _rows = rows;
    _cols = cols;
}

void Triangle::Show()       //输出字符组成的三角形
{
    for (int i = 1; i <= _rows; i++)
    {
        for (int j = 1; j <= i; j++)
            cout << _ch;
        cout << endl;
    }
}

void Rectangle::Show()      //输出字符组成的矩形
{
    for (int i = 1; i <= _rows; i++)
    {
        for (int j = 1; j <= _cols; j++)
            cout << _ch;
        cout << endl;
    }
}

void fun(CharShape& cs)
{
    cs.Show();
}
int main()
{
    //输出三角形
    char ch;
    int row, col;
    cout << "Please enter a character: ";   //输入一个字符
    cin >> ch;
    cout << "Please enter the number of rows: ";
    cin >> row;
    Triangle triangle(ch, row);
    fun(triangle);

    //输出矩形
    cout << "Please enter a character: ";
    cin >> ch;
    cout << "Please enter the number of rows: ";
    cin >> row;
    cout << "Please enter the number of cols: ";
    cin >> col;
    Rectangle rectangle(ch, row, col);
    fun(rectangle);
    return 0;

}