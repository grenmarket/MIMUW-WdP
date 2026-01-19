#include <stdio.h>
#include <stdlib.h>

/* ===== Pomocnicze DFS dla grafu nieskierowanego (cykl + spójność) ===== */
static int dfs_undirected(int v, int parent,
                          int n, int **adj, int *deg,
                          char *vis)
{
    vis[v] = 1;
    for (int i = 0; i < deg[v]; i++) {
        int u = adj[v][i];
        if (!vis[u]) {
            if (!dfs_undirected(u, v, n, adj, deg, vis))
                return 0; // wykryto cykl niżej
        } else if (u != parent) {
            // u odwiedzony i nie jest rodzicem -> cykl
            return 0;
        }
    }
    return 1;
}

/* Sprawdza czy graf nieskierowany jest drzewem */
int is_tree_undirected(int n, int **adj, int *deg)
{
    if (n <= 0) return 0;
    if (n == 1) {
        // 1 węzeł: drzewo, jeśli brak pętli
        return (deg[0] == 0);
    }

    long long sum_deg = 0;
    for (int v = 0; v < n; v++) sum_deg += deg[v];

    // Każda krawędź liczona dwa razy w listach sąsiedztwa
    if (sum_deg % 2 != 0) return 0; // błędna reprezentacja dla nieskier.
    long long m = sum_deg / 2;
    if (m != n - 1) return 0;

    char *vis = (char*)calloc(n, sizeof(char));
    if (!vis) return 0;

    // DFS od 0: sprawdzamy acykliczność i spójność
    int ok = dfs_undirected(0, -1, n, adj, deg, vis);
    if (ok) {
        for (int v = 0; v < n; v++) {
            if (!vis[v]) { ok = 0; break; } // niespójny
        }
    }

    free(vis);
    return ok;
}

/* ===== DFS dla grafu skierowanego (osiągalność z korzenia) ===== */
static void dfs_directed(int v, int **adj, int *deg, char *vis)
{
    vis[v] = 1;
    for (int i = 0; i < deg[v]; i++) {
        int u = adj[v][i];
        if (!vis[u]) dfs_directed(u, adj, deg, vis);
    }
}

/* Sprawdza czy graf skierowany jest arborescencją (out-tree) */
int is_tree_directed_arborescence(int n, int **adj, int *deg)
{
    if (n <= 0) return 0;
    if (n == 1) {
        // 1 węzeł: arborescencja, jeśli brak pętli
        return (deg[0] == 0);
    }

    // policz liczbę krawędzi m (w skierowanym: suma out-degree)
    long long m = 0;
    for (int v = 0; v < n; v++) m += deg[v];
    if (m != n - 1) return 0;

    // oblicz indegree
    int *indeg = (int*)calloc(n, sizeof(int));
    if (!indeg) return 0;

    for (int v = 0; v < n; v++) {
        for (int i = 0; i < deg[v]; i++) {
            int u = adj[v][i];
            if (u < 0 || u >= n) { free(indeg); return 0; } // bezpieczeństwo
            indeg[u]++;
        }
    }

    int root = -1;
    for (int v = 0; v < n; v++) {
        if (indeg[v] == 0) {
            if (root != -1) { free(indeg); return 0; } // więcej niż 1 korzeń
            root = v;
        } else if (indeg[v] != 1) {
            free(indeg);
            return 0; // wierzchołek ma indeg != 1
        }
    }
    if (root == -1) { free(indeg); return 0; } // brak korzenia

    // sprawdź osiągalność z korzenia
    char *vis = (char*)calloc(n, sizeof(char));
    if (!vis) { free(indeg); return 0; }

    dfs_directed(root, adj, deg, vis);

    int ok = 1;
    for (int v = 0; v < n; v++) {
        if (!vis[v]) { ok = 0; break; }
    }

    free(vis);
    free(indeg);
    return ok;
}
