#include <bits/stdc++.h>
using namespace std;

#define DEBUG 2

#define FileIO                        \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

class GhostSensor
{
public:
    int n, m, k;
    double p;
    vector<vector<double>> grid;
    vector<vector<double>> backupGrid;

    GhostSensor(int n, int m, int k)
    {
        this->n = n;
        this->m = m;
        this->k = k;
        p = 0.9;
        Initialize();
    }

    void Initialize()
    {
        grid.resize(n);
        for (int i = 0; i < n; i++)
        {
            grid[i].resize(m);
        }
    }

    void MakeGrid()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                grid[i][j] = 1.0 / (n * m - k);
            }
        }
        for (int i = 0; i < k; i++)
        {
            int u, v;
            cin >> u >> v;
            grid[u][v] = 0;
        }
        backupGrid = grid;
    }

    void PrintGrid()
    {
        cout << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << fixed << setprecision(3) << grid[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }

    double EdgeProbability(int u, int v)
    {
        return p / CountEdge(u, v);
    }

    int CountEdge(int u, int v)
    {
        int duEdge[4] = {1, -1, 0, 0};
        int dvEdge[4] = {0, 0, 1, -1};

        int countEdge = 0;

        for (int i = 0; i < 4; i++)
        {
            int new_u = u + duEdge[i];
            int new_v = v + dvEdge[i];

            if (!IsOutside(new_u, new_v) and !IsObstacle(new_u, new_v))
            {
                countEdge++;
            }
        }
        return countEdge;
    }

    double CornerProbability(int u, int v)
    {
        return (1 - p) / (CountCorner(u, v) + 1);
    }

    int CountCorner(int u, int v)
    {
        int duCorner[4] = {1, -1, 1, -1};
        int dvCorner[4] = {1, 1, -1, -1};

        int countCorner = 0;

        for (int i = 0; i < 4; i++)
        {
            int new_u = u + duCorner[i];
            int new_v = v + dvCorner[i];

            if (!IsOutside(new_u, new_v) and !IsObstacle(new_u, new_v))
            {
                countCorner++;
            }
        }
        return countCorner;
    }

    bool IsOutside(int u, int v)
    {
        if (u < 0 or u >= n or v < 0 or v >= m)
        {
            return true;
        }
        return false;
    }

    bool IsObstacle(int u, int v)
    {
        if (grid[u][v] == 0)
        {
            return true;
        }
        return false;
    }

    double CalculateTransition(int u, int v)
    {
        double ans = 0;

        int duEdge[4] = {1, -1, 0, 0};
        int dvEdge[4] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++)
        {
            int new_u = u + duEdge[i];
            int new_v = v + dvEdge[i];

            if (!IsOutside(new_u, new_v) and !IsObstacle(new_u, new_v))
            {
                ans += grid[new_u][new_v] * EdgeProbability(u, v);
            }
        }

        int duCorner[4] = {1, -1, 1, -1};
        int dvCorner[4] = {1, 1, -1, -1};

        for (int i = 0; i < 4; i++)
        {
            int new_u = u + duCorner[i];
            int new_v = v + dvCorner[i];

            if (!IsOutside(new_u, new_v) and !IsObstacle(new_u, new_v))
            {
                ans += grid[new_u][new_v] * CornerProbability(u, v);
            }
        }
        ans += grid[u][v] * (1 - p) / (CountCorner(u, v) + 1);

        return ans;
    }

    void ApplyTransition()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] != 0)
                {
                    backupGrid[i][j] = CalculateTransition(i, j);
                }
            }
        }
        grid = backupGrid;
    }

    void Normalize()
    {
        double sum = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                sum += grid[i][j];
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                grid[i][j] = grid[i][j] / sum;
            }
        }
    }

    void PrintEdgeGrid()
    {
        cout << "Printing Edge Amount" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] != 0)
                {
                    cout << CountEdge(i, j) << "\t";
                }
                else
                {
                    cout << "X"
                         << "\t";
                }
            }
            cout << endl;
        }
    }

    void PrintCornerGrid()
    {
        cout << "Printing Corner Amount" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] != 0)
                {
                    cout << CountCorner(i, j) << "\t";
                }
                else
                {
                    cout << "X"
                         << "\t";
                }
            }
            cout << endl;
        }
    }
};

int main()
{
    FileIO;
    int n, m, k;
    cin >> n >> m >> k;
    cout << "Input Successful" << endl;
    cout << "n= " << n << " m= " << m << " k= " << k << endl
         << endl;

    GhostSensor *ghostsensor;
    ghostsensor = new GhostSensor(n, m, k);
    ghostsensor->MakeGrid();
    cout << "MakeGrid Successful" << endl;

    ghostsensor->PrintGrid();
    if (DEBUG==1)
    {
        ghostsensor->PrintEdgeGrid();
        ghostsensor->PrintCornerGrid();
    }

    char c;
    while (cin >> c)
    {
        if (c == 'Q')
        {
            cout << "Quiting Program" << endl;
            break;
        }
        else if (c == 'C')
        {
            cout << "Caster's Location is " << endl;
        }
        else if (c == 'R')
        {
            int u, v, b;
            cin >> u >> v >> b;
        }
        else if (c == 'K')
        {
            cout << "Apply Transition" << endl;
            ghostsensor->ApplyTransition();
            ghostsensor->PrintGrid();

            cout << "Normalize" << endl;
            ghostsensor->Normalize();
            ghostsensor->PrintGrid();
        }
    }

    return 0;
}
