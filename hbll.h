#pragma once
#include "global.h"
#include "betweenness_centrality.h"
class HBLL
{
public:
    struct Triple
    {
        int l, h, d;
        Triple(){l = h = d = 0;}
        Triple(int L, int H, int D): l(L), h(H), d(D) {}
    };
    int n;
    vector < vector <Triple> > L;
    vector < vector <pair <int,int> > > prew;
    void build_hbll(Graph G);
    pair <int,pair <int, pair <int,int> > > GET_WD_build(int u, int v, int h, vector <int> id);
    int GET_WD(int u, int v, int h);
    int GET_UD(int u, int v);
    vector <int> GET_MWP(int u, int v, int h);
    void output_L();
    void clear();
};