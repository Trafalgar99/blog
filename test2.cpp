#include <iostream>
#include <string>
#include <vector>


class Window_mgr
{
public:
    // 窗口中每个屏幕的编号
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex);
    //向窗口添加一个Screen，返回他的编号
    ScreenIndex addScreen(const Screen&);

private:
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};


class Screen
{
public:
    friend void Window_mgr::clear(ScreenIndex);
    typedef std::string::size_type pos;
    Screen() = default;

    Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht * wd, c) {}
    char get() const { return contents[cursor]; }
    inline char get(pos ht, pos wd) const;
    Screen &move(pos r, pos c);
    void some_member() const;
    Screen &set(char);
    Screen &set(pos, pos, char);

    Screen &display(std::ostream &os)
    {
        do_display(os);
        return *this;
    }
    const Screen &display(std::ostream &os) const
    {
        do_display(os);
        return *this;
    }
    pos size()const;

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    mutable size_t access_ctr;
    void do_display(std::ostream &os) const
    {
        os << contents;
    }
};



inline Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline Screen &Screen::set(pos r, pos col, char ch)
{
    contents[r * width + col] = ch;
    return *this;
}

void Screen::some_member() const
{
    ++access_ctr; // 保存一个计数值，用于记录成员函数被调用的次数
}

void Window_mgr::clear(ScreenIndex i)
{
    //s是一个Screen的引用，指向我们想清空的那个屏幕
    Screen &s = screens[i];
    //将那个选定的Screen 重置为空白
    s.contents = std::string(s.height * s.width, ' ');
}

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size()-1;
}

Screen::pos Screen::size()const{
    return height * width;
}