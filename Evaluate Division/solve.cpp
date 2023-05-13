#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // Criando o grafo e adicionando as arestas
        unordered_map<string, unordered_map<string, double>> graph;
        for (int i = 0; i < equations.size(); i++) {
            string u = equations[i][0];
            string v = equations[i][1];
            double w = values[i];
            graph[u][v] = w;
            graph[v][u] = 1.0 / w;
        }
        
        // Executando Dijkstra para cada query
        vector<double> res;
        for (auto q : queries) {
            string src = q[0];
            string dest = q[1];
            
            if (graph.find(src) == graph.end() || graph.find(dest) == graph.end()) {
                // Se não existir algum dos nós, retornar -1.0
                res.push_back(-1.0);
            } else if (src == dest) {
                // Se for a mesma variável, retornar 1.0
                res.push_back(1.0);
            } else {
                // Executando Dijkstra
                unordered_map<string, double> dist;
                dist[src] = 1.0;
                priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;
                pq.push(make_pair(1.0, src));
                
                while (!pq.empty()) {
                    double d = pq.top().first;
                    string u = pq.top().second;
                    pq.pop();
                    
                    if (u == dest) {
                        break;
                    }
                    
                    for (auto v : graph[u]) {
                        double w = v.second;
                        if (dist.find(v.first) == dist.end() || d * w < dist[v.first]) {
                            dist[v.first] = d * w;
                            pq.push(make_pair(dist[v.first], v.first));
                        }
                    }
                }
                
                // Verificando se encontrou um caminho
                if (dist.find(dest) == dist.end()) {
                    res.push_back(-1.0);
                } else {
                    res.push_back(dist[dest]);
                }
            }
        }
        
        return res;
    }
};
