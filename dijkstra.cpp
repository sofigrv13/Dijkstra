#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

vector<vector<pair<int, int>>> list_ad;
vector<int> dist;

void create_list(int n)
{
    for (int i = 0; i < n; i++)
    {
        dist.push_back(2147483647);
        vector<pair<int, int>> node = {};
        list_ad.push_back(node);
    }
}

void add_neighbour(int node1, int node2, int weight)
{
    list_ad[node1].push_back(pair<int, int>(node2, weight));
    list_ad[node2].push_back(pair<int, int>(node1, weight));
}

void print_list_ad()
{
    for (int i = 0; i < list_ad.size(); i++)
    {
        cout << "Node " << i << ": ";
        for (int j = 0; j < list_ad[i].size(); j++)
        {
            cout << "neighbour " << list_ad[i][j].first << " with weight " << list_ad[i][j].second << " ";
        }
        cout << endl;
    }
}

int dijkstra(int node, int finalNode)
{
    dist[node] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> next;
    next.push(pair<int, int>(0, node));
    while (!next.empty())
    {
        int node = next.top().second;
        int distance = next.top().first;
        next.pop();
        if (node != finalNode && distance <= dist[node])
        {
            for (int i = 0; i < list_ad[node].size(); i++)
            {
                int neighbour = list_ad[node][i].first;
                int weight = list_ad[node][i].second;
                if (dist[neighbour] > dist[node] + weight)
                {
                    dist[neighbour] = dist[node] + weight;
                    next.push(pair<int, int>(dist[neighbour], neighbour));
                }
            }
        }
    }

    return dist[finalNode];
}

int main()
{
    create_list(5);
    add_neighbour(0, 1, 4);
    add_neighbour(0, 2, 2);
    add_neighbour(1, 3, 8);
    add_neighbour(2, 3, 10);
    add_neighbour(2, 4, 2);
    add_neighbour(3, 4, 3);

    int costeShortestPath = dijkstra(0, 3);
    if (costeShortestPath != 2147483647)
    {
        cout << "The shortest path to get from 0 to 3 is of ";
        cout << costeShortestPath << "\n";
    }
    else
    {
        cout << "There's no path to get from 0 to 3 \n";
    }
    return 0;
}
