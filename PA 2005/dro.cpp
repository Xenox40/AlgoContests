//Task: Drogi PA 2005
//Author: Piotr Zieliñski

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> graphNormal, graphTrans;
vector<vector<int>> graphSSSNormal, graphSSSTrans;
vector<bool> visited;
int sss[10000+5], nSSS;
int sssFirst[10000+5], nFirst;

void input(int &n, int &m)
{
    int a, b;
    scanf("%d %d", &n, &m);
    graphNormal.resize(n);
    graphTrans.resize(n);
    graphSSSNormal.resize(n);
    graphSSSTrans.resize(n);

    for(int i = 0;i < m;++i)
    {
        scanf("%d%d", &a, &b);
        graphNormal[a-1].push_back(b-1);
        graphTrans[b-1].push_back(a-1);
    }
}

void sssDfs1(int s)
{
    visited[s] = true;
    for(auto I : graphNormal[s])
    {
        if(!visited[I])
        {
            sssDfs1(I);
        }
    }
    sssFirst[nFirst++] = s;
}

void sssDfs2(int s)
{
    visited[s] = true;
    for(auto I : graphTrans[s])
    {
        if(!visited[I])
        {
            sssDfs2(I);
        }
    }
    sss[s] = nSSS;
}

void computeSSS(int n)
{
    visited.clear();
    visited.resize(n);
    for(int i = 0;i < n;++i)
    {
        if(!visited[i])
            sssDfs1(i);
    }

    visited.clear();
    visited.resize(n);
    for(int i = nFirst-1;i >= 0;--i)
    {
        if(!visited[sssFirst[i]])
        {
            sssDfs2(sssFirst[i]);
            ++nSSS;
        }
    }
}

void buildSSSGraph(int n)
{
    for(int i = 0;i < n;++i)
        for(auto J : graphNormal[i])
            if(sss[i] != sss[J])
            {
                graphSSSNormal[sss[i]].push_back(sss[J]);
                graphSSSTrans[sss[J]].push_back(sss[i]);
            }
}

void countRes()
{
    if(nSSS == 1)
    {
        printf("0\n");
        return;
    }
    int res1 = 0, res2 = 0;
    for(int i = 0;i < nSSS;++i)
    {
        if(graphSSSNormal[i].empty())
            ++res1;
        if(graphSSSTrans[i].empty())
            ++res2;
    }
    printf("%d\n", max(res1, res2));
}

int main()
{
    int n, m;
    input(n, m);
    computeSSS(n);
    buildSSSGraph(n);
    countRes();

    return 0;
}
