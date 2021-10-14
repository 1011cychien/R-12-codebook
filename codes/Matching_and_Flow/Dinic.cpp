template <typename Cap = int64_t>
class Dinic{
private:
  struct Edge{
    int to, rev;
    Cap cap;
  };
  int n, st, ed;
  vector<vector<Edge>> G;
  vector<int> lv, idx;
  bool BFS(){
    fill(lv.begin(), lv.end(), -1);
    queue<int> bfs;
    bfs.push(st); lv[st] = 0;
    while(!bfs.empty()){
      int u = bfs.front(); bfs.pop();
      for(auto e: G[u]){
        if(e.cap <= 0 or lv[e.to]!=-1) continue;
        bfs.push(e.to); lv[e.to] = lv[u] + 1;
      }
    }
    return (lv[ed]!=-1);
  }
  Cap DFS(int u, Cap f){
    if(u == ed) return f;
    Cap ret = 0;
    for(int &i = idx[u]; i < (int)G[u].size(); ++i){
      auto &e = G[u][i];
      if(e.cap <= 0 or lv[e.to]!=lv[u]+1) continue;
      Cap nf = DFS(e.to, min(f, e.cap));
      ret += nf; e.cap -= nf; f -= nf;
      G[e.to][e.rev].cap += nf;
      if(f == 0) return ret;
    }
    if(ret == 0) lv[u] = -1;
    return ret;
  }
public:
  void init(int n_, int st_, int ed_){
    n = n_, st = st_, ed = ed_;
    G.resize(n); lv.resize(n);
    fill(G.begin(), G.end(), vector<Edge>());
  }
  void add_edge(int u, int v, Cap c){
    G[u].push_back({v, (int)G[v].size(), c});
    G[v].push_back({u, ((int)G[u].size())-1, 0});
  }
  Cap max_flow(){
    Cap ret = 0;
    while(BFS()){
      idx.assign(n, 0);
      Cap f = DFS(st, numeric_limits<Cap>::max());
      ret += f;
      if(f == 0) break;
    }
    return ret;
  }
};
