
#define CELL_NUM (5)
#define MAX_COST (1000)

typedef struct Cell
{
    int north;
    int south;
    int west;
    int east;
    int cost;
} Cell;

Cell cells[CELL_NUM * CELL_NUM];

static void printCells(void);
static void updateCost(int x, int y, int cost);
static void resetCost(void);
static void cutConnection(int x0, int y0, int x1, int y1);

Cell *getCell(int x, int y)
{
    return &cells[y * CELL_NUM + x];
}

void initialize(void)
{
    for (int i = 0; i < CELL_NUM; i++)
    {
        for (int j = 0; j < CELL_NUM; j++)
        {
            Cell *c = getCell(i, j);
            c->cost = -1;
            if (i == 0)
            {
                c->west = 0;
            }
            else
            {
                c->west = -1;
            }
            if (i == CELL_NUM - 1)
            {
                c->east = 0;
            }
            else
            {
                c->east = -1;
            }
            if (j == 0)
            {
                c->south = 0;
            }
            else
            {
                c->south = -1;
            }
            if (j == CELL_NUM - 1)
            {
                c->north = 0;
            }
            else
            {
                c->north = -1;
            }
        }
    }

    cutConnection(0, 0, 1, 0);
    cutConnection(0, 1, 1, 1);
    cutConnection(0, 2, 1, 2);
    cutConnection(0, 3, 1, 3);
    resetCost();
    printCells();

    printf("%d %d %d %d %d\n", getCell(0, 0)->north, getCell(0, 0)->south, getCell(0, 0)->east, getCell(0, 0)->west, getCell(0, 0)->cost);
    printf("%d %d %d %d %d\n", getCell(1, 0)->north, getCell(1, 0)->south, getCell(1, 0)->east, getCell(1, 0)->west, getCell(1, 0)->cost);

    updateCost(2, 2, 0);
    printCells();

    return;
}

static void cutConnection(int x0, int y0, int x1, int y1)
{
    if (x0 == x1 && y0 < y1)
    {
        getCell(x0, y0)->north = 0;
        getCell(x1, y1)->south = 0;
    }
    if (x0 == x1 && y0 > y1)
    {
        getCell(x1, y1)->north = 0;
        getCell(x0, y0)->south = 0;
    }
    if (y0 == y1 && x0 < x1)
    {
        getCell(x0, y0)->east = 0;
        getCell(x1, y1)->west = 0;
    }
    if (y0 == y1 && x0 > x1)
    {
        getCell(x1, y1)->east = 0;
        getCell(x0, y0)->west = 0;
    }
}

static void resetCost(void)
{
    for (int i = 0; i < CELL_NUM; i++)
    {
        for (int j = 0; j < CELL_NUM; j++)
        {
            getCell(i, j)->cost = MAX_COST;
        }
    }
}

static void updateCost(int x, int y, int cost)
{
    Cell *c = getCell(x, y);
    if (c->cost <= cost)
    {
        return;
    }

    c->cost = cost;
    if (c->north != 0)
    {
        updateCost(x, y + 1, cost + 1);
    }
    if (c->south != 0)
    {
        updateCost(x, y - 1, cost + 1);
    }
    if (c->east != 0)
    {
        updateCost(x + 1, y, cost + 1);
    }
    if (c->west != 0)
    {
        updateCost(x - 1, y, cost + 1);
    }
}

static void printCells(void)
{
    for (int j = CELL_NUM - 1; j >= 0; j--)
    {
        for (int i = 0; i < CELL_NUM; i++)
        {
            printf("%3d", getCell(i, j)->cost);
        }
        printf("\n");
    }
}

void solve(void)
{

    return;
}