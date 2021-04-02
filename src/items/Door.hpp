#pragma once

class Key;

class Door
{
    static int counter;

    bool is_open = false;
    bool is_locked = true;
    int id;

public:

    Door() {}
    Door(bool, bool = false);

    void open();
    void close();
    bool get_is_open();

    friend class Key;
};
