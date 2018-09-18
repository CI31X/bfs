/****************************************************************************

Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).

Ввод: v:кол-во вершин(макс. 50000), n:кол-во ребер(макс. 200000), n пар реберных вершин, пара вершин v, w для запроса.
Вывод: количество кратчайших путей от v к w

 | in  | out |
 |-----|-----|
 |4    |  2  |
 |5    |     |
 |0 1  |     |
 |0 2  |     |
 |1 2  |     |
 |1 3  |     |
 |2 3  |     |
 |     |     |
 |0 3  |     |

****************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

struct Node {
    int depth { 0 };
    bool visited { false };
    int father { -1 };
    int number { 0 }; // number of a short paths
};

class CListGraph  {
    typedef std::vector< int > TVList;
    std::vector< TVList > data_;
    int size;

public:
    CListGraph( int N );

    void AddEdge( int from, int to );
    void GetNextVertices( int vertex, TVList &verticies ) const;
    int VerticesCount() const;

    int bfs( int from, int to ); // return number of short paths
};

CListGraph::CListGraph( int N )
    : data_( N ), size ( N )
{}

void CListGraph::AddEdge( int from, int to ) {
    data_[ from ].push_back( to );
    data_[ to ].push_back( from );
}

void CListGraph::GetNextVertices( int vertex, TVList &verticies ) const {
    verticies = data_[ vertex ];
}

int CListGraph::VerticesCount() const {
    return data_.size();
}
int CListGraph::bfs( int from, int to ) {
    std::vector< Node > help ( size );
    std::queue< int > q;
    help[ from ].visited = true;
    help[ from ].number = 1;
    q.push( from );
    while( !q.empty() ) {
        std::vector< int > next;
        int current = q.front();
        q.pop();
        GetNextVertices( current, next );
        for( int i = 0; i < next.size(); ++i ) {
            int n = next[ i ]; //next vertex
            if( !help[ n ].visited ) {
                q.push( n );
                help[ n ].father = current;
                help[ n ].depth = help[ current ].depth + 1;
                help[ n ].visited = true;
                help[ n ].number = help[ current ].number;
            }
            else if( n != help[ current ].father && help[ n ].depth == help[ current ].depth + 1 ) {
                help[ n ].number = help[ current ].number + help[ n ].number;
            }
        }
    }
    return help[ to ].number;
}


int main()
{
    int n; // count of vertices
    int m; // count of strings
    std::cin >> n >> m;
    CListGraph graph( n );
    int a,b;
    for( int i = 0; i < m; ++i ) {
        std::cin >> a >> b;
        graph.AddEdge( a, b );
    }
    int from, to;
    std::cin >> from >> to;
    std::cout << graph.bfs( from, to );

    return 0;
}

