#define SIZE 21

class Snake
{
  private:
    int size;
    int heady;
    int headx;
    int taily;
    int tailx;

    bool gate;

  public:
    Snake(int s = 3, int y = 10, int x = 8)
    {
        size = s;
        heady = y;
        headx = x;
        taily = y;
        tailx = x + 2;
        gate = false;
    }

    void setSize(int s);
    int getSize() const;

    void setHeady(int y);
    int getHeady() const;
    void setHeadx(int x);
    int getHeadx() const;

    void setTaily(int y);
    int getTaily() const;
    void setTailx(int x);
    int getTailx() const;

    void setGate();
    bool getGate() const;
};