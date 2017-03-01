#include <bits/stdc++.h>

using namespace std;

const long long base = 99999959;
const long long mod = 1e9+696969;

vector<long long> powers;
vector<long long> c, l, in;

long long fixMod(long long n)
{
    return ((n%mod)+mod)%mod;
}

void genPow(int n)
{
    powers.resize(n);
    powers[0]=1;
    for(int i = 1;i < n;++i)
    {
        powers[i] = (powers[i-1]*base);
        powers[i] = fixMod(powers[i]);
    }
}

void hashSeq(long long k, long long sum)
{
    long long res = 0;
    long long hasz = 0;
    for(int i = 0;i < sum;++i)
    {
        hasz += powers[in[i]];
        hasz = fixMod(hasz);
    }
    int p = 0;
    for(int i = sum;i < in.size();++i)
    {
        if(hasz == k)
            ++res;
        hasz -= powers[in[p]];
        hasz = fixMod(hasz);
        hasz += powers[in[i]];
        hasz = fixMod(hasz);
        ++p;
    }
    if(hasz == k)
        ++res;
    printf("%lld\n", res);
}

long long hashC(vector<int> &colors)
{
    long long hasz = 0;
    for(int i = 0;i < colors.size();++i)
    {
        hasz += (long long)powers[colors[i]];
        hasz  = fixMod(hasz);
    }
    return hasz;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    c.resize(m); l.resize(m);
    in.resize(n);

    for(auto &I : l)
        scanf("%d", &I);
    for(auto &I : c)
        scanf("%d", &I);

    vector<int> colors;

    for(int i = 0;i < m;++i)
    {
        for(int j = 0;j < l[i];++j)
        {
            colors.push_back(c[i]);
            if(colors.size() > n)
            {
                printf("0\n");
                return 0;
            }
        }
    }

    for(auto &I : in)
        scanf("%d", &I);


    genPow(n+5);
    long long key = hashC(colors);

    hashSeq(key, colors.size());

    return 0;
}
