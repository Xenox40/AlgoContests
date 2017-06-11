//Bytering PA 2013
//Binsearch + Dijkstra + K-max structure
//Complexity O(n * log n)

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int infty = 1000000000;

vector<int> cost;

struct cmp
{
    bool operator() (const int &a, const int &b)
    {
        if (cost[a] < cost[b]) return true;
        if (cost[a] > cost[b]) return false;
        return a<b;
    }
};

struct MaxQueue
{
    stack<LL> normal;
    stack<LL> backword;
    stack<LL> prefMax;
    LL maxX;

    void push(LL a)
    {
        if(normal.empty())
            maxX = a;
        else
            maxX = max(a, maxX);
        normal.push(a);
    }
    void pop()
    {
        if(!backword.empty())
        {
            backword.pop();
            prefMax.pop();
        }
        else
        {
            while(!normal.empty())
            {
                LL a = normal.top();
                normal.pop();
                if(backword.empty())
                    prefMax.push(a);
                else
                    prefMax.push(max(prefMax.top(), a));
                backword.push(a);
            }
            maxX = 0;
            pop();
        }
    }
    bool isEmpty()
    {
        if(normal.empty() && backword.empty())
            return true;
        return false;
    }
    LL getMax()
    {
        if(prefMax.empty())
            return maxX;
        return max(prefMax.top(), maxX);
    }
};

set<int, cmp> heap;

void dijkstra(int n, int s, vector< vector<pair<int,int>> > &g)
{
    int v, u, c;
    cost.clear();
    cost.resize(n, infty);

    cost[s] = 0;
    heap.clear();
    heap.insert(s);

    while( !heap.empty() )
    {
        u = *(heap.begin());
        heap.erase(heap.begin());

        for (int i=0; i<g[u].size(); i++)
        {
            v = g[u][i].first;
            c = g[u][i].second;
            if (cost[u]+c < cost[v])
            {
                if(heap.find(v) != heap.end())
                    heap.erase(heap.find(v));
                cost[v] = cost[u]+c;
                heap.insert(v);
            }
        }
    }


}

//Checks if the shortest road longer than x NOT exist
bool notExist(int n, int x, vector< vector<pair<int,int>> > &g)
{
    vector<bool> visited (n);
    MaxQueue q;
    int l, p, sumP = 0, sumL = 0;

    visited[1] = 1;
    for(p = 1; p < n-1; ++p)
    {
        sumP += g[p][1].second;
        visited[p] = 1;
        if(sumP >= x)
            break;
    }
    for(l = n-1; l > 1; --l)
    {
        sumL += g[l][1].second;
        if(sumL >= x)
            break;
    }
    if(p == n-1 || l == 1)
        return true;

    sumP -= g[p][1].second;
    sumL -= g[l][1].second;

    for(int i = p+1; i <= l; ++i)
    {
        q.push(cost[i]);
    }

    for(int i = 1; i < n; ++i)
    {
        if(!q.isEmpty())
        {
            int m = q.getMax();
            if(m + cost[i] >= x)
                return false;
        }
        if(i == n-1)
            break;

        if(p != i)
            sumP -= g[i][1].second;
        else
        {
            p++;
            visited[p] = 1;
            if(!q.isEmpty())
                q.pop();
        }
        sumL += g[i][1].second;
        visited[i] = 0;

        while(true)
        {
            sumP += g[p][1].second;
            if(sumP >= x)
            {
                sumP -= g[p][1].second;
                break;
            }
            ++p;
            if(p >= n)
                p = (p%n)+1;
            visited[p] = 1;
            if(!q.isEmpty())
                q.pop();
        }
        while(sumL >= x)
        {
            ++l;
            if(l >= n)
                l = (l%n)+1;
            sumL -= g[l][1].second;
            if(!visited[l])
                q.push(cost[l]);
        }
    }
    return true;
}

//Classic binsearch
void solve(int n, vector< vector<pair<int,int>> > &g)
{
    dijkstra(n, 0, g);

    int p = 0, k = 1e9, s, res;

    while(p <= k)
    {
        s = (p+k)/2;
        if(notExist(n, s, g))
        {
            k = s-1;
        }
        else
        {
            res = s;
            p = s+1;
        }
    }
    for(int i = 1; i < n; ++i)
    {
        if(res < cost[i])
        {
            res = cost[i];
        }
    }
    cout << res << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    vector< vector<pair<int,int>> > g;
    int n, x;

    cin >> n;
    g.resize(n);
    g[1].push_back({0,0});
    for(int i = 1; i < n-1; ++i)
    {
        cin >> x;
        g[i].push_back(pair<int, int> (i+1, x));
        g[i+1].push_back(pair<int, int> (i, x));
    }

    cin >> x;
    g[n-1].push_back(pair<int, int> (1, x));
    g[1][0] = {n-1, x};

    for(int i = 1; i < n; ++i)
    {
        cin >> x;
        g[0].push_back(pair<int, int> (i, x));
        g[i].push_back(pair<int, int> (0, x));
    }

    solve(n, g);

    return 0;
}


