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

    int maxsize;
    int growth;
    int poison;
    int gatecnt;

  public:
    Snake(int s = 3, int y = 10, int x = 16) : maxsize(3), growth(0), poison(0), gatecnt(0)
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

    void setMaxsize(int s);
    int getMaxsize() const;
    void setGrowth();
    int getGrowth() const;
    void setGatecnt();
    int getGatecnt() const;
    void setPoison();
    int getPoison() const;
};