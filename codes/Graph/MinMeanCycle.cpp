// WARNING: TYPE matters
struct Edge { int s, t; llf c; };
llf solve(vector<Edge> &e, int n) {
  // O(VE), returns inf if no cycle, mmc otherwise
  vector<VI> prv(n + 1, VI(n)), prve = prv;
  vector<vector<llf>> d(n + 1, vector<llf>(n, inf));
  d[0] = vector<llf>(n, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (int)e.size(); j++) {
      auto [s, t, c] = e[j];
      if (d[i][s] < inf && d[i + 1][t] > d[i][s] + c) {
        d[i + 1][t] = d[i][s] + c;
        prv[i + 1][t] = s; prve[i + 1][t] = j;
      }
    }
  }
  llf mmc = inf; int st = -1;
  for (int i = 0; i < n; i++) {
    llf avg = -inf;
    for (int k = 0; k < n; k++) {
      if (d[n][i] < inf - eps)
        avg = max(avg, (d[n][i] - d[k][i]) / (n - k));
      else avg = inf;
    }
    if (avg < mmc) tie(mmc, st) = tie(avg, i);
  }
  if (st == -1) return inf;
  vector<int> vst(n), eid, cycle, rho;
  for (int i = n; !vst[st]; st = prv[i--][st]) {
    vst[st]++; eid.emplace_back(prve[i][st]);
    rho.emplace_back(st);
  }
  while (vst[st] != 2) {
    int v = rho.back(); rho.pop_back();
    cycle.emplace_back(v); vst[v]++;
  }
  reverse(all(eid)); eid.resize(cycle.size());
  return mmc;
}
