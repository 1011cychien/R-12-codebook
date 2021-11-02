class MiniCostMaxiFlow{
  using Cap = int; using Wei = int64_t;
  using PCW = pair<Cap,Wei>;
  static constexpr Cap INF_CAP = 1 << 30;
  static constexpr Wei INF_WEI = 1LL<<60;
private:
  struct Edge{
    int to, back;
    Cap cap; Wei wei;
    Edge() {}
    Edge(int a,int b, Cap c, Wei d):
      to(a),back(b),cap(c),wei(d)
    {}
  };
  int ori, edd;
  vector<vector<Edge>> G;
  vector<int> fa, wh;
  vector<bool> inq;
  vector<Wei> dis;
  PCW SPFA(){
    fill(inq.begin(),inq.end(),false);
    fill(dis.begin(),dis.end(),INF_WEI);
    queue<int> qq; qq.push(ori);
    dis[ori] = 0;
    while(not qq.empty()){
      int u=qq.front();qq.pop();
      inq[u] = false;
      for(int i=0;i<SZ(G[u]);++i){
        Edge e=G[u][i];
        int v=e.to; Wei d=e.wei;
        if(e.cap<=0||dis[v]<=dis[u]+d)
          continue;
        dis[v] = dis[u] + d;
        fa[v] = u, wh[v] = i;
        if (inq[v]) continue;
        qq.push(v);
        inq[v] = true;
      }
    }
    if(dis[edd]==INF_WEI) return {-1, -1};
    Cap mw=INF_CAP;
    for(int i=edd;i!=ori;i=fa[i])
      mw=min(mw,G[fa[i]][wh[i]].cap);
    for (int i=edd;i!=ori;i=fa[i]){
      auto &eg=G[fa[i]][wh[i]];
      eg.cap -= mw;
      G[eg.to][eg.back].cap+=mw;
    }
    return {mw, dis[edd]};
  }
public:
  void init(int a,int b,int n){
    ori=a,edd=b;
    G.clear();G.resize(n);
    fa.resize(n);wh.resize(n);
    inq.resize(n); dis.resize(n);
  }
  void add_edge(int st, int ed, Cap c, Wei w){
    G[st].emplace_back(ed,SZ(G[ed]),c,w);
    G[ed].emplace_back(st,SZ(G[st])-1,0,-w);
  }
  PCW solve(){
    Cap cc=0; Wei ww=0;
    while(true){
      PCW ret=SPFA();
      if(ret.first==-1) break;
      cc+=ret.first;
      ww+=ret.first * ret.second;
    }
    return {cc,ww};
  }
} mcmf;
