sort(ord.begin(), ord.end(), [&](int i, int j) {
  return pair(deg[i], i) > pair(deg[j], j); });
for (int i = 0; i < n; i++) rnk[ord[i]] = i;
if (rnk[u] < rnk[v]) D[u].push_back(v); // D: new DAG
for (int x = 0; x < n; x++) { // c3
  for (int y : D[x]) vis[y] = 1;
  for (int y : D[x]) for (int z : D[y]) ans += vis[z];
  for (int y : D[x]) vis[y] = 0;
}
for (int x = 0; x < n; x++) { // c4
  for (int y : D[x]) for (int z : adj[y])
    if (rnk[z] > rnk[x]) ans += vis[z]++;
  for (int y : D[x]) for (int z : adj[y])
    if (rnk[z] > rnk[x]) vis[z]--;
} // both are O(M * sqrt(M))
