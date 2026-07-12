#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <numeric>
#include <algorithm>
using namespace std;

class ArrayGraph {
    int V;
    list<int> *adjList;
    bool isUndirected = true;
public:
    ArrayGraph(int V, bool isUndirected=true){
        this->V = V;
        adjList = new list<int>[V];         // Array of List(s)
        this->isUndirected = isUndirected;
    }
    ~ArrayGraph(){
        delete[] adjList;
    }

    void addEdge(const pair<int,int> &edge){
        int u = edge.first,  v = edge.second;
        if(u<0 || u>=V) {
            cout << "Cannot insert edge" << endl;
            return;
        }

        adjList[u].push_back(v);                    // add u--->v
        if(isUndirected) adjList[v].push_back(u);   // add v--->u
    }

    void makeGraph(vector<pair<int,int>> &edges){
        for(auto &edge : edges)
            addEdge(edge);
    }

    void printGraph(){
        cout << "--- Graph I Adjacency List ---\n";
        for(int u=0; u<V; u++){
            cout << u << ": ";
            for(auto &v : adjList[u])
                cout << v << " ";
            cout << endl;
        }
    }

    void bfs(int start=0){
        queue<int> que;
        vector<bool> vis(V, false);
        vis[start] = true;
        que.push(start);

        cout << "BFS: " << start << " ";
        while (!que.empty()) {
            int curr = que.front(); que.pop();
            list<int> &neighbors = adjList[curr];
            for(auto &v : neighbors){
                if(!vis[v]){
                    vis[v] = true;
                    que.push(v);
                    cout << v << " ";
                }
            }
        }  
    }

    void dfsHelper(int u, vector<bool>& vis){
        cout << u << " ";
        vis[u] = true;
        list<int> &neighbours = adjList[u];
        for(auto& v : neighbours){
            if(!vis[v])
                dfsHelper(v, vis);
        }
    }

    void dfs(int start=0){
        vector<bool> vis(V, false);
        cout << "DFS: ";
        dfsHelper(start, vis);
    }

    void dfsIterative(int start = 0){
        stack<int> st;
        vector<bool> vis(V, false);
        st.push(start);
        vis[start] = true;
        cout << "Iterative DFS: " ;

        while(!st.empty()){
            int curr = st.top(); st.pop();
            cout << curr << " ";
            list<int> &neighbors = adjList[curr];
            for(auto v : neighbors){
                if(!vis[v]){
                    vis[v] = true;
                    // cout << v << " ";
                    st.push(v);
                }
            }
            
        }
    }
    // Cycle detection for Undirected Graph
    bool isCycleHelper(int src, vector<bool> &vis, int parent){         // DFS
        vis[src] = true;
        list<int> &neighbors = adjList[src];
        for(auto v : neighbors){
            if(!vis[v]){
                if(isCycleHelper(v, vis, src))
                    return true;
            } 
            else if(v != parent)
                return true;
        }
        return false;
    }
    bool isCycle(int start=0){
        vector<bool> vis(V, false);
        return isCycleHelper(start, vis, -1);
    }

    // Cycle detection for Directed Graph
    bool isCycleHelper_directed(int src, vector<bool> &vis, vector<bool> &recPath){ // DFS
        vis[src] = true;
        recPath[src] = true;
        list<int> &neighbors = adjList[src];
        for(auto v : neighbors){
            if(!vis[v]){
                if(isCycleHelper_directed(v, vis, recPath))
                    return true;
            }
            if(recPath[v]) return true;
        }
        recPath[src] = false;
        return false;
    }
    bool isCycle_directed(){
        vector<bool> vis(V, false), recPath(V, false);
        bool ans = false;
        for(int i=0; i<V; i++){
            if(!vis[i])
                ans = isCycleHelper_directed(i, vis, recPath);
        }
        return ans;
    }

    // Topological Sort DFS-approach
    void topoDfs(int src, vector<bool> &vis, stack<int> &stk){
        vis[src] = true;
        list<int> &neighbors = adjList[src];
        for(auto v : neighbors){
            if(!vis[v])
                topoDfs(v, vis, stk);
        }
        stk.push(src);
    }
    void topoSortDfs(){
        vector<bool> vis(V, false);
        stack<int> stk;
        for(int i=0; i<V; i++){
            if(!vis[i])
                topoDfs(i, vis, stk);
        }
        while(!stk.empty()){
            cout << stk.top() << " ";
            stk.pop();
        }
    }

    // Topological Sort BFS-approach ## Kahn's Algorithm
    void calcIndegree(vector<int> &indegree){
        for(int u=0; u<V; u++){
            for(auto v : adjList[u])
                indegree[v]++;
        }
    }
    void topoSortBfs(){
        vector<int> indegree(V,0);
        calcIndegree(indegree);


        queue<int> q;
        for(int i=0; i<V; i++){
            if(indegree[i] == 0)
                q.push(i);
        }

        vector<int> ans;
        while(!q.empty()){
            int curr = q.front();
            q.pop();
            ans.push_back(curr);
            list<int> &neighbors = adjList[curr];
            for(auto v : neighbors){
                indegree[v]--;
                if(indegree[v] == 0)
                    q.push(v);
            }
        }

        for(auto u : indegree){
            if(u != 0){
                cout << "Graph is not Completely DAG" << endl;
                return;
            }
        }

        for(auto v : ans)
            cout << v << " ";

    }

    vector<int> shortestPath(int src=0){
        queue<int> q;
        vector<int> dist(V, INT_MAX);
        q.push(src);
        dist[src] = 0;

        while(!q.empty()){
            int curr = q.front(); q.pop();
            list<int> &neighbor = adjList[curr];
            for(auto v : neighbor){
                if(dist[v] == INT_MAX){
                    dist[v] = dist[curr] + 1;
                    q.push(v);
                }
            }
        }
        return dist;
    }

};

class MapGraph {
    unordered_map<int,list<int>> adjList;
    bool isUndirected = true;
public:
    MapGraph(bool isUndirected=true){
        this->isUndirected = isUndirected;
    }
    ~MapGraph(){}

    void addEdge(const pair<int,int> &edge){
        int u = edge.first, v = edge.second;
        
        if(adjList.find(u) == adjList.end())
            adjList[u] = list<int>();
        if(isUndirected && adjList.find(v) == adjList.end())
            adjList[v] = list<int>();
        
        adjList[u].push_back(v);
        if(isUndirected)
            adjList[v].push_back(u);
    }

    void makeGraph(vector<pair<int,int>> &edges){
        for(auto &edge : edges)
            addEdge(edge);
    }

    void printGraph(){
        cout << "--- Graph II Adjacency Map ---\n";
        for(auto it = adjList.begin(); it!=adjList.end(); it++){
            cout << it->first << ": ";
            for(auto v : it->second){
                cout << v << " ";
            }
            cout << endl;
        }
    }
    void bfs(int start){
        queue<int> que;
        unordered_map<int,bool> vis;
        
        vis[start] = true;
        que.push(start);
        
        cout << "BFS: " <<start << " ";
        while (!que.empty()) {
            int src = que.front(); que.pop();
            if(adjList.find(src) != adjList.end()){
                list<int> &neighbors = adjList[src];
                for(auto &v : neighbors){
                    if(!vis[v]){
                        vis[v] = true;
                        que.push(v);
                        cout << v << " ";
                    }
                }
            }
        } 
    }

    void dfsHelper(int u, unordered_map<int,bool>& vis){
        vis[u] = true;
        cout << u << " ";
        if(adjList.find(u) != adjList.end()){
            list<int> &neighbours = adjList[u];
            for(auto& v : neighbours){
                if(!vis[v])
                    dfsHelper(v, vis);
            }
        }       
    }

    void dfs(int start=0){
        unordered_map<int,bool> vis;
        cout << "DFS: ";
        dfsHelper(start, vis);
    }

    void dfsIterative(int start = 0){
        stack<int> st;
        unordered_map<int, bool> vis;
        st.push(start);
        vis[start] = true;
        cout << "Iterative DFS: " ;

        while(!st.empty()){
            int curr = st.top(); st.pop();
            cout << curr << " ";
            // if(adjList.find(curr) != adjList.end())  one hash lookup done by find() // <----- what will happen if i remove this line?
            // <----- this is the reason, [] operator creates the new entry for 'curr : list<int>()' if the doesn't exist in the graph previously even when curr has now outgoing edges
                // Therefore find() checks if key (curr) already exists or not
            // list<int> &neighbors = adjList[curr]     2nd hash lookup done [] operator

            unordered_map<int, list<int>>::iterator it = adjList.find(curr);
            if(it != adjList.end()){   
                list<int> &neighbors = it->second; 
                for(auto v : neighbors){
                    if(!vis[v]){
                        vis[v] = true;
                        // cout << v << " ";
                        st.push(v);
                    }
                }
            }
        }
    }
};

class WeightedArrayGraph {
    int V;
    vector<pair<int,int>> *edgeList;
    bool isUndirected = true;
public:
    WeightedArrayGraph(int V, bool isUndirected = true) {
        this->V = V;
        edgeList = new vector<pair<int,int>>[V];
        this->isUndirected = isUndirected;
    }
    ~WeightedArrayGraph(){
        delete[] edgeList;
    }

    void addEdge(const tuple<int,int,int> &edge){
        int u = get<0>(edge);
        int v = get<1>(edge);
        int w = get<2>(edge);

        edgeList[u].push_back({v, w});                    // add u--->v
        if(isUndirected) edgeList[v].push_back({u, w});   // add v--->u
    }

    void makeGraph(vector<tuple<int,int,int>> &edges){
        for(auto &edge : edges)
            addEdge(edge);
    }

    void printGraph(){
        cout << "--- Weighted Graph Adjacency List ---\n";
        for(int u=0; u<V; u++){
            cout << u <<": ";
            for(auto &v : edgeList[u])
                cout << "{" << v.first << "," << v.second <<"} ";
            cout << endl;
        }
    }

    vector<int> dijkstra(int src=0){
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;    // pair<wt, v>
        vector<int> dist(V, INT_MAX);
        pq.push({-1, src});
        dist[src] = 0;
        while(!pq.empty()){
            auto [uwt, u] = pq.top(); pq.pop();
            auto &neighbor = edgeList[u];
            for(auto [v, wt] : neighbor){
                if(dist[v] > dist[u] + wt){
                    dist[v] = dist[u] + wt;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    vector<int> bellmanFord(int src=0){
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        for(int i = 1; i < V; i++){
            for(int u=0; u < V; u++){
                auto &neighbor = edgeList[u];
                for(auto& [v, wt] : neighbor){
                    if(dist[v] > dist[u] + wt)
                        dist[v] = dist[u] + wt;
                }
            }
        }
        return dist;
    }

    int prims(int src=0){
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        vector<bool> mstSet(V, false);
        pq.push({0, src});
        int minWeight = 0;

        while(!pq.empty()){
            auto [wt_u, u] = pq.top(); pq.pop();

            if(!mstSet[u]){
                mstSet[u] = true;
                minWeight += wt_u;
                auto &neighbor = edgeList[u];
                for(auto [v, wt] : neighbor){
                    pq.push({wt, v});
                }
            }
        }
        return minWeight;
    }
};

class DisjointSet {
    vector<int> parent;
    vector<int> rank;
public:
    DisjointSet(int V) : parent(V), rank(V, 0){
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int curr){
        if(parent[curr] == curr)
            return parent[curr];
        
        return parent[curr] = find(parent[curr]);   // Path Compression
    }

    bool unionByRank(const int &a, const int &b){
        int parA = find(a);
        int parB = find(b);

        if(parA == parB) return false;

        if(rank[parA] > rank[parB]){
            parent[parB] = parA;
        } else if(rank[parA] < rank[parB]){
            parent[parA] = parB;
        } else {
            parent[parB] = parA;
            rank[parA]++;
        }
        return true;
    }
};

class Edge {
public:
    int u, v, wt;
public:
    Edge(tuple<int,int,int> edge){
        u = get<0>(edge);
        v = get<1>(edge);
        wt = get<2>(edge);
    }
};

class EdgeGraph {
    vector<Edge> edgeList;
    bool isUndirected;
    int V;
public:
    EdgeGraph(int V, bool isUndirected=true) : isUndirected(isUndirected), V(V){}

    void addEdge(const tuple<int,int,int> &edge){
        edgeList.push_back(Edge(edge));                    // add u--->v
        // if(isUndirected) edgeList.push_back(Edge(edge));   // add v--->u
        
    }

    void makeGraph(vector<tuple<int,int,int>> &edges){
        for(auto &edge : edges)
            addEdge(edge);
    }

    void printGraph(){
        for(auto e : edgeList){
            cout << e.u << ", " << e.v << ", " << e.wt << endl;
        }
    }

    int kruskals(){
        DisjointSet s(V);
        sort(edgeList.begin(), edgeList.end(), [](const Edge &a, const Edge &b){ return a.wt < b.wt;});
        int minWeight = 0;
        for(auto &e : edgeList){
            if(s.unionByRank(e.u, e.v)){
                minWeight += e.wt;
            }
        }
        return minWeight;
    }
};


int main(){
    // vector<pair<int,int>> edges = {{0,1},{0,2},{1,3},{2,4},{3,4},{3,5},{4,5},{5,6}};
    // int n = 7;
    // ArrayGraph graph(n);
    // graph.makeGraph(edges);
    // graph.printGraph();
    // // graph.bfs(5);    cout << endl;
    // graph.dfs();    cout << endl << endl;
    // graph.dfsIterative();    cout << endl << endl

    // vector<pair<int,int>> edges = {{0,1}, {1,2}, {2,3}, {3,4}, {4,0}};
    // ArrayGraph graph(5);
    // graph.makeGraph(edges);
    // graph.printGraph();
    // cout << graph.isCycle();

    // vector<pair<int,int>> edges = {{1,0}, {0,2}, {2,3}, {3,0}};
    // ArrayGraph graph(4, false);
    // graph.makeGraph(edges);
    // graph.printGraph();
    // cout << graph.isCycle_directed(1);

    // vector<pair<int,int>> edges = {{5,0}, {5,2}, {4,0}, {4,1}, {2,3}, {3,1}};
    // ArrayGraph graph(6, false);
    // graph.makeGraph(edges);
    // graph.printGraph();
    // graph.topoSortDfs(); cout << endl;
    // graph.topoSortBfs();

    // vector<pair<int,int>> edges = {{0,1}, {0,2}, {1,3}, {2,4}, {4,3}, {3,5}};
    // ArrayGraph graph(6, false);
    // graph.makeGraph(edges);
    // graph.printGraph(); cout << endl;
    // vector<int> dist;
    // dist = graph.shortestPath(0);
    // for(auto d : dist)
    //     cout << d << " ";
    
    // vector<pair<int,int>> edges = {{0,1},{0,2},{1,3},{2,4},{3,4},{3,5},{4,5},{5,6}};
    // MapGraph graph2;
    // graph2.makeGraph(edges);
    // graph2.printGraph();
    // graph2.bfs(5);   cout << endl;
    // graph2.dfs();   cout << endl << endl;

    // vector<tuple<int,int,int>> Wedges = {{0,1,2},{0,2,1},{1,3,5},{2,4,2},{3,4,2},{3,5,3},{4,5,1},{5,6,4}};
    // int m = 7;
    // WeightedArrayGraph graph3(m);
    // graph3.makeGraph(Wedges);
    // graph3.printGraph();

    // vector<tuple<int,int,int>> Wedges = {{0,1,2}, {0,2,4}, {1,3,7}, {1,2,1}, {2,4,3}, {4,3,2}, {3,5,1}, {4,5,5}};
    // int m = 6;
    // WeightedArrayGraph graph3(m, false);
    // graph3.makeGraph(Wedges);
    // graph3.printGraph();
    // vector<int> dist;
    // dist = graph3.dijkstra(0);
    // for(auto d : dist)
    //     cout << d << " ";

    // vector<tuple<int,int,int>> Wedges = {{0,1,2}, {0,2,4}, {1,2,-4}, {2,3,2}, {3,4,4}, {4,1,-1}};
    // int m = 5;
    // WeightedArrayGraph graph3(m, false);
    // graph3.makeGraph(Wedges);
    // graph3.printGraph();
    // vector<int> dist;
    // dist = graph3.bellmanFord(0);
    // for(auto d : dist)
    //     cout << d << " ";

    // vector<tuple<int,int,int>> Wedges = {{0,1,10}, {0,2,15}, {0,3,30}, {1,3,40}, {2,3,50}};
    // int m = 4;
    // WeightedArrayGraph graph3(m, true);
    // graph3.makeGraph(Wedges);
    // graph3.printGraph();
    // int minWeight;
    // minWeight = graph3.prims();
    // cout << minWeight;

    vector<tuple<int,int,int>> Wedges = {{0,1,10}, {0,2,15}, {0,3,30}, {1,3,40}, {2,3,50}};
    int m = 4;
    EdgeGraph graph4(m, true);
    graph4.makeGraph(Wedges);
    graph4.printGraph();
    int minWeight;
    minWeight = graph4.kruskals();
    cout << minWeight;

}