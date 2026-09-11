#include <vector>
#include <numeric>
using namespace std;
class DSU {
    vector<int> par;
    vector<int> rank;
    
public:
    DSU(int n) : par(n), rank(n, 0){
        iota(par.begin(), par.end(),0);
    }
    
    int find(int key){
        if(par[key] == key) return key;
        return par[key] = find(par[key]);
    }
    
    void unite(int a, int b){
        int pa = find(a);
        int pb = find(b);
        
        if(pa == pb) return;
        
        if(rank[pa]==rank[pb]){
            par[pb] = pa;
            rank[pa]++;
        } else if(rank[pa]>rank[pb])
            par[pb] = pa;
        else 
            par[pa] = pb;
    }
};