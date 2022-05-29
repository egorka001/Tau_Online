#ifndef MAPS
#define MAPS

struct Maps
{
    int width;
    int height;

    char** map;

    Maps() : width(0), height(0), map(nullptr) {}
    Maps(int uWidth, int uHeight) : width(uWidth), height(uHeight)
    {
        map = new char* [width];
        for(int i = 0; i < width; ++i)
            map[i] = new char [height];

        for(int i = 0; i < width; ++i)
            for(int j = 0; j < height; ++j)
                map[i][j] = 0;
    }
    Maps(Maps const& uMap) : Maps(uMap.width, uMap.height) 
    {
        for(int i = 0; i < width; ++i)
            for(int j = 0; j < height; ++j)
                map[i][j] = uMap.map[i][j];
    }
    ~Maps()
    {
        for(int i = 0; i < width; ++i)
            delete[] map[i];
        delete[] map;
    }

    void write(char** uMap) //rewrite map 
    {
        for(int i = 0; i < width; ++i)
            for(int j = 0; j < height; ++j)
                map[i][j] = uMap[i][j];
    }

    char** read()//get full map array
    {
        return map;
    }
};

#endif
