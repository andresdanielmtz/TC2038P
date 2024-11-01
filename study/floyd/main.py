from typing import List

INF = 999999 # inf 

def floyd_warshall(graph: List[List[int]]):
    dist = list(map(lambda i: list(map(lambda j: j, i)), graph))
    for k in range(len(graph)):
        for i in range(len(graph)):
            for j in range(len(graph)):
                dist[i][j] = min(dist[i][j],
                                 dist[i][k] + dist[k][j]
                                 )
    print(dist)


def main(): 
    graph = [[0, 5, INF, 10],
             [INF, 0, 3, INF],
             [INF, INF, 0,   1],
             [INF, INF, INF, 0]
            ]
    floyd_warshall(graph)

if __name__ == "__main__":
    main()
