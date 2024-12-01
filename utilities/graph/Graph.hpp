#include <climits>  // 引入 INT_MAX
#include <stack>  // 引入标准库中的 stack
using std::stack;  // 使用标准库中的 stack

typedef enum { V_UNDISCOVERED, V_DISCOVERED, V_VISITED } VStatus;
typedef enum { E_UNDISCOVERED, E_TREE, E_CROSS, E_FORWARD, E_BACKWARD } EStatus;

template <typename Tv, typename Te>
class Graph {
private:
    void reset() {
        for (int i = 0; i < n; i++) {
            status(i) = V_UNDISCOVERED; dTime(i) = fTime(i) = -1;
            parent(i) = -1; priority(i) = INT_MAX;
            for (int j = 0; j < n; j++)
                if (exists(i, j)) status(i, j) = E_UNDISCOVERED;
        }
    }
    void BFS(int, int &);
    void DFS(int, int &);
    void BCC(int, int &, stack<int> &);
    bool TSort(int, int &, stack<int> &);
    template <typename PU> void PFS(int, PU);
public:
    int n;
    virtual int insert(Tv const &) = 0;
    virtual Tv remove(int) = 0;
    virtual Tv& vertex(int) = 0;
    virtual int inDegree(int) = 0;
    virtual int outDegree(int) = 0;
    virtual int firstNbr(int) = 0;
    virtual int nextNbr(int, int) = 0;
    virtual VStatus& status(int) = 0;
    virtual int& dTime(int) = 0;
    virtual int& fTime(int) = 0;
    virtual int& parent(int) = 0;
    virtual int& priority(int) = 0;

    int e;
    virtual bool exists(int, int) = 0;
    virtual void insert(Te const &, int, int) = 0;
    virtual Te remove(int, int) = 0;    
    virtual EStatus& status(int, int) = 0;
    virtual Te& edge(int, int) = 0;
    virtual int& weight(int, int) = 0;

    void bfs(int);
    void dfs(int);
    void bcc(int);
    stack<Tv> *tSort(int);
    void prim(int);
    void dijkstra(int);
    template<typename PU> void pfs(int, PU);
};


// BFS Implementation
template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock) {
    std::queue<int> Q;
    status(v) = DISCOVERED;
    Q.push(v);
    
    while (!Q.empty()) {
        int curr = Q.front();
        Q.pop();
        dTime(curr) = ++clock;
        
        // Explore neighbors
        for (int w = firstNbr(curr); w > -1; w = nextNbr(curr, w)) {
            if (status(w) == UNDISCOVERED) {
                status(w) = DISCOVERED;
                parent(w) = curr;
                Q.push(w);
            }
        }
        
        status(curr) = VISITED;
    }
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s) {
    int clock = 0;
    // Reset graph
    for (int i = 0; i < n; i++) 
        status(i) = UNDISCOVERED;
    
    // Traverse from start vertex
    BFS(s, clock);
}

// DFS Implementation
template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock) {
    dTime(v) = ++clock;
    status(v) = DISCOVERED;
    
    // Explore neighbors
    for (int w = firstNbr(v); w > -1; w = nextNbr(v, w)) {
        // Unvisited: tree edge
        if (status(w) == UNDISCOVERED) {
            parent(w) = v;
            DFS(w, clock);
        }
        // Discovered but not visited: back edge
        else if (status(w) == DISCOVERED) {
            // Cycle detection
            status(v, w) = BACKWARD;
        }
        // Fully visited: cross or forward edge
        else {
            status(v, w) = (dTime(v) < dTime(w)) ? FORWARD : CROSS;
        }
    }
    
    status(v) = VISITED;
    fTime(v) = ++clock;
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s) {
    int clock = 0;
    // Reset graph
    for (int i = 0; i < n; i++) 
        status(i) = UNDISCOVERED;
    
    // Start DFS from given vertex
    DFS(s, clock);
}

// Dijkstra's Shortest Path Algorithm
template <typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra(int s) {
    // Reset
    for (int i = 0; i < n; i++) {
        status(i) = UNDISCOVERED;
        priority(i) = INT_MAX;
        parent(i) = -1;
    }
    
    // Starting vertex
    priority(s) = 0;
    
    // Priority queue for efficient selection
    std::priority_queue<
        std::pair<int, int>, 
        std::vector<std::pair<int, int>>, 
        std::greater<std::pair<int, int>>
    > pq;
    
    pq.push({0, s});
    
    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        // Skip if already processed
        if (status(u) == VISITED) continue;
        
        status(u) = VISITED;
        
        // Explore neighbors
        for (int v = firstNbr(u); v > -1; v = nextNbr(u, v)) {
            if (status(v) == VISITED) continue;
            
            // Relaxation
            int newDist = dist + weight(u, v);
            if (newDist < priority(v)) {
                priority(v) = newDist;
                parent(v) = u;
                pq.push({newDist, v});
            }
        }
    }
}

// Prim's Minimum Spanning Tree Algorithm
template <typename Tv, typename Te>
void Graph<Tv, Te>::prim(int s) {
    // Reset
    for (int i = 0; i < n; i++) {
        status(i) = UNDISCOVERED;
        priority(i) = INT_MAX;
        parent(i) = -1;
    }
    
    // Starting vertex
    priority(s) = 0;
    
    // Priority queue for efficient selection
    std::priority_queue<
        std::pair<int, int>, 
        std::vector<std::pair<int, int>>, 
        std::greater<std::pair<int, int>>
    > pq;
    
    pq.push({0, s});
    
    int mstWeight = 0;
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        // Skip if already in MST
        if (status(u) == VISITED) continue;
        
        status(u) = VISITED;
        
        // If not the start vertex, add the edge to MST
        if (parent(u) != -1) {
            mstWeight += weight(parent(u), u);
        }
        
        // Explore neighbors
        for (int v = firstNbr(u); v > -1; v = nextNbr(u, v)) {
            if (status(v) == VISITED) continue;
            
            // Update priority (edge weight)
            if (weight(u, v) < priority(v)) {
                priority(v) = weight(u, v);
                parent(v) = u;
                pq.push({priority(v), v});
            }
        }
    }
}