<<<<<<< HEAD

<<<<<<< HEAD
<<<<<<< HEAD
#include <iostream>
#include <queue>
    ====== =
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
    >>>>>> > 30136e9 (5 - 7)
#include <string>
#include <utility>
=======
>>>>>>> cf55fce (5-11)
#include <vector>
=======
#include <algorithm>   // sort(), swap()
#include <iostream>    // cout
#include <numeric>     // iota()
#include <stdexcept>   // invalid_argument, out_of_range
#include <vector>      // vector
>>>>>>> 8dd7d41 (5-9)

using namespace std;

<<<<<<< HEAD
<<<<<<< HEAD
// ========================================
<<<<<< < HEAD
    // 실습 1. BFS 방문 순서
    // ========================================

    // graph: 인접 리스트로 저장한 그래프
    // start: 탐색을 시작할 정점
    // 반환형 void: 탐색 결과를 직접 출력

    void BFSVisitOrder(
        const vector<vector<int>>&graph,
        int start)
=======
// ============================================================
// 1. Disjoint Set Union (DSU / Union-Find)
// ============================================================

// Union-Find 자료구조를 클래스로 구현한다.
//
// 역할:
// 1. 각 정점이 속한 집합의 대표를 찾는다.
// 2. 서로 다른 두 집합을 하나로 합친다.
// 3. 두 정점이 같은 집합인지 확인한다.
// 4. 현재 남은 집합의 개수를 관리한다.

class DisjointSet
>>>>>>> 8dd7d41 (5-9)
{
private:

    // --------------------------------------------------------
    // 부모 배열
    // --------------------------------------------------------

    // parent[x]는 정점 x가 가리키는 부모 정점이다.
    //
    // 예를 들어:
    // parent[3] = 1
    //
    // 이라면 3번 정점의 부모가 1번이라는 뜻이다.
    //
    // parent[x] == x라면 x는 집합의 대표(루트)이다.
    vector<int> parent;

    // --------------------------------------------------------
    // 집합 크기 배열
    // --------------------------------------------------------

    // groupSize[root]에는 해당 집합의 크기가 저장된다.
    //
    // Union by Size 최적화에 사용한다.
    //
    // 이 값은 집합의 루트에서만
    // 현재 집합 크기로 해석해야 한다.
    vector<int> groupSize;

    // --------------------------------------------------------
    // 현재 연결 요소 개수
    // --------------------------------------------------------

    // 처음 정점이 N개라면 서로 다른 집합도 N개이다.
    //
    // 서로 다른 두 집합을 합칠 때마다
    // componentCount를 1 감소시킨다.
    int componentCount;

public:

    // ========================================================
    // 생성자 (Constructor)
    // ========================================================

    // n: 관리할 정점의 개수
    //
    // explicit:
    // int를 DisjointSet 객체로 암시적으로 변환하는 일을 막는다.
    //
    // 예:
    // DisjointSet dsu(6);

    explicit DisjointSet(int n)
        : componentCount(n)
    {
        // 음수 개수의 정점은 허용하지 않는다.
        if (n < 0)
        {
            throw invalid_argument(
                "Negative vertex count"
            );
        }

        // 정점 개수만큼 부모 배열 생성
        parent.resize(n);

        // 정점마다 집합 크기를 1로 초기화
        groupSize.assign(n, 1);

        // ----------------------------------------------------
        // iota()를 이용한 부모 배열 초기화
        // ----------------------------------------------------

        // iota(begin, end, 0)은
        // 0부터 시작해서 1씩 증가하는 값을 채운다.
        //
        // 결과:
        // parent = {0, 1, 2, 3, ...}
        //
        // 처음에는 각 정점이 자기 자신의 루트다.
        iota(
            parent.begin(),
            parent.end(),
            0
        );
    }

    // ========================================================
    // Find: 집합 대표 찾기
    // ========================================================

    // 시간 복잡도:
    // Union by Size와 함께 사용하면
    // 여러 연산에 걸쳐 O(alpha(N)) 분할 상환 비용
    //
    // 반환값:
    // 정점 x가 속한 집합의 대표(루트)

    int Find(int x)
    {
        // ----------------------------------------------------
        // 1. 잘못된 정점 번호 검사
        // ----------------------------------------------------

        if (x < 0 ||
            x >= static_cast<int>(parent.size()))
        {
            throw out_of_range(
                "Invalid vertex index"
            );
        }

        // ----------------------------------------------------
        // 2. 재귀 종료 조건
        // ----------------------------------------------------

        // 자기 자신의 부모가 자기 자신이면
        // 현재 정점이 집합의 루트이다.
        if (parent[x] == x)
        {
            return x;
        }

        // ----------------------------------------------------
        // 3. 경로 압축 (Path Compression)
        // ----------------------------------------------------

        // 재귀적으로 루트를 찾는다.
        //
        // 찾은 루트를 현재 정점의 부모로 직접 저장한다.
        //
        // 예:
        // 3 -> 2 -> 1 -> 0
        //
        // Find(3) 실행 후
        // 3 -> 0이 되도록 경로가 압축된다.
        parent[x] = Find(parent[x]);

        // ----------------------------------------------------
        // 4. 집합 대표 반환
        // ----------------------------------------------------

        return parent[x];
    }

    // ========================================================
    // Unite: 서로 다른 두 집합 합치기
    // ========================================================

    // a, b:
    // 합칠 집합에 속하는 정점 번호
    //
    // 반환값:
    // true  = 서로 다른 집합을 합쳤다.
    // false = 이미 같은 집합이었다.

    bool Unite(int a, int b)
    {
        // ----------------------------------------------------
        // 1. 각 정점이 속한 집합의 루트 찾기
        // ----------------------------------------------------

        int rootA = Find(a);
        int rootB = Find(b);

        // ----------------------------------------------------
        // 2. 이미 같은 집합인지 확인
        // ----------------------------------------------------

        // 루트가 같다면 이미 연결된 상태이다.
        //
        // Kruskal에서는 이러한 간선을 추가하면
        // 사이클이 발생할 수 있다.
        if (rootA == rootB)
        {
            return false;
        }

        // ----------------------------------------------------
        // 3. Union by Size
        // ----------------------------------------------------

        // 작은 집합을 큰 집합 아래에 합친다.
        //
        // A가 더 작다면 두 루트 변수를 교환한다.
        if (groupSize[rootA] < groupSize[rootB])
        {
            swap(rootA, rootB);
        }

        // ----------------------------------------------------
        // 4. 부모 관계 변경
        // ----------------------------------------------------

        // 작은 집합 B의 루트를
        // 큰 집합 A의 루트 아래에 연결한다.
        parent[rootB] = rootA;

        // ----------------------------------------------------
        // 5. 집합 크기 갱신
        // ----------------------------------------------------

        // 합쳐진 집합의 전체 크기
        groupSize[rootA] += groupSize[rootB];

        // ----------------------------------------------------
        // 6. 연결 요소 개수 감소
        // ----------------------------------------------------

        // 두 집합이 하나로 합쳐졌으므로
        // 전체 집합 개수가 1 감소한다.
        --componentCount;

        // 실제로 합치는 작업을 수행했다.
        return true;
    }

    // ========================================================
    // Same: 같은 집합인지 검사
    // ========================================================

    bool Same(int a, int b)
    {
        // 두 정점의 대표가 같으면 같은 집합이다.
        //
        // 루트 비교 결과를 bool로 반환한다.
        return Find(a) == Find(b);
    }

    // ========================================================
    // ComponentCount: 집합 개수 반환
    // ========================================================

    int ComponentCount() const
    {
        // const 멤버 함수:
        // 객체의 멤버 상태를 변경하지 않겠다는 의미
        return componentCount;
    }
};

// ============================================================
// 2. 그래프 간선 구조체
// ============================================================

// 던전에서 두 방 사이의 후보 통로를 표현한다.
//
// from: 한쪽 방 번호
// to  : 다른 쪽 방 번호
// cost: 통로 건설 비용
//
// 오늘의 그래프는 무방향 그래프이다.

struct Edge
{
    int from;
    int to;
    long long cost;
};

// ============================================================
// 3. 최소 신장 트리 결과 구조체
// ============================================================

// 알고리즘이 계산한 결과를
// 하나의 객체로 묶어서 반환한다.

struct MSTResult
{
    // 실제로 선택한 통로 목록
    vector<Edge> selected;

    // 선택한 모든 통로의 건설 비용
    long long totalCost = 0;

    // 최종 연결 요소 개수
    int components = 0;

    // 모든 정점이 하나의 집합인가?
    bool connected = false;
};

// ============================================================
// 4. Kruskal 최소 신장 트리 알고리즘
// ============================================================

// vertexCount:
// 던전에 존재하는 전체 방 개수
//
// edges:
// 각 방 사이에 건설할 수 있는 후보 통로
//
// 반환형:
// MSTResult
//
// 참고:
// edges를 값으로 전달받기 때문에
// 함수 내부에서 정렬해도 호출자의 원본 벡터는 변하지 않는다.

MSTResult Kruskal(
    int vertexCount,
    vector<Edge> edges)
{
    // --------------------------------------------------------
    // STEP 1. 정점 개수 검사
    // --------------------------------------------------------

    if (vertexCount <= 0)
    {
        throw invalid_argument(
            "Vertex count must be positive"
        );
    }

    // --------------------------------------------------------
    // STEP 2. 모든 간선의 정점 번호 검사
    // --------------------------------------------------------

    for (const Edge& edge : edges)
    {
        // 유효한 정점 번호는
        // 0부터 vertexCount - 1까지이다.
        if (edge.from < 0 ||
            edge.from >= vertexCount ||
            edge.to < 0 ||
            edge.to >= vertexCount)
        {
<<<<<<< HEAD
            return -1;
        }

        for (int c = 0; c < cols; c++)
        {
            if (maze[r][c] == 'S')
            {
                start = { r, c };
            }

            if (maze[r][c] == 'G')
            {
                goal = { r, c };
                ====== =
                    // 1. 기본 자료형 및 상수
                    // ========================================

                    // 이동 비용은 큰 값이 될 수 있으므로
                    // long long 자료형 사용
                    using Cost = long long;

                // 도달하지 못한 정점의 거리
                constexpr Cost INF =
                    numeric_limits<Cost>::max() / 4;

                // ========================================
                // 2. 그래프 간선 구조체
                // ========================================

                struct Edge
                {
                    int to;       // 도착 정점
                    Cost weight;  // 이동 비용
                };

                // 인접 리스트 그래프
                using Graph = vector<vector<Edge>>;

                // ========================================
                // 3. 무방향 그래프에 간선 추가
                // ========================================

                void AddUndirectedEdge(
                    Graph & graph,
                    int from,
                    int to,
                    Cost weight)
                {
                    const int n =
                        static_cast<int>(graph.size());

                    // 잘못된 정점 번호나 비용 검사
                    if (from < 0 || from >= n ||
                        to < 0 || to >= n ||
                        weight < 0 || weight >= INF)
                    {
                        throw invalid_argument(
                            "Invalid vertex or edge weight"
                        );
                    }

                    // from -> to
                    graph[from].push_back({ to, weight });

                    // to -> from
                    graph[to].push_back({ from, weight });
                }

                // ========================================
                // 4. 다익스트라 결과 구조체
                // ========================================

                struct DijkstraResult
                {
                    // 정점별 최단 거리
                    vector<Cost> dist;

                    // 최단 경로 복원을 위한 부모 정점
                    vector<int> parent;

                    // 오래된 큐 항목을 무시한 횟수
                    int skippedStale = 0;
                };

                // ========================================
                // 5. 다익스트라 알고리즘
                // ========================================

                DijkstraResult Dijkstra(
                    const Graph & graph,
                    int start)
                {
                    const int n =
                        static_cast<int>(graph.size());

                    // 시작 정점 검사
                    if (start < 0 || start >= n)
                    {
                        throw out_of_range(
                            "Invalid start vertex"
                        );
                    }

                    // 거리 배열과 부모 배열 초기화
                    DijkstraResult result{
                        vector<Cost>(n, INF),
                        vector<int>(n, -1),
                        0
                    };

                    // pair<Cost, int>
                    // first  = 시작점부터의 거리
                    // second = 정점 번호
                    using Entry = pair<Cost, int>;

                    // 최소 힙 선언
                    // 거리가 작은 원소부터 꺼낸다
                    priority_queue<
                        Entry,
                        vector<Entry>,
                        greater<Entry>
                    > pq;

                    // 시작점 거리 0
                    result.dist[start] = 0;

                    // 시작점 등록
                    pq.push({ 0, start });

                    // ------------------------------------
                    // 다익스트라 탐색 시작
                    // ------------------------------------

                    while (!pq.empty())
                    {
                        // 1. 가장 작은 거리 후보 가져오기
                        auto [currentDist, current] = pq.top();

                        // 2. 큐에서 제거
                        pq.pop();

                        // --------------------------------
                        // 3. 오래된 거리 항목 검사
                        // --------------------------------

                        // 더 짧은 경로가 이미 등록됐다면
                        // 현재 큐 항목은 오래된 데이터
                        if (currentDist != result.dist[current])
                        {
                            ++result.skippedStale;
                            continue;
                        }

                        // --------------------------------
                        // 4. 현재 정점의 모든 간선 탐색
                        // --------------------------------

                        for (const Edge& edge : graph[current])
                        {
                            // 다익스트라는 음수 가중치를 허용하지 않음
                            if (edge.weight < 0)
                            {
                                throw invalid_argument(
                                    "Dijkstra requires nonnegative weights"
                                );
                            }

                            // 거리의 표현 범위 초과 방지
                            if (edge.weight >= INF ||
                                currentDist > INF - edge.weight)
                            {
                                continue;
                            }

                            // --------------------------------
                            // 5. 새 경로 비용 계산
                            // --------------------------------

                            const Cost candidate =
                                currentDist + edge.weight;

                            // --------------------------------
                            // 6. Relaxation (거리 완화)
                            // --------------------------------

                            if (candidate < result.dist[edge.to])
                            {
                                // 더 짧은 경로 발견
                                result.dist[edge.to] = candidate;

                                // 이 정점을 어디에서 발견했는지 기록
                                result.parent[edge.to] = current;

                                // 새로운 거리 후보를 최소 힙에 추가
                                pq.push({ candidate, edge.to });
                                >>>>>> > 30136e9 (5 - 7)
                            }
                        }
                    }

                    <<<<<< < HEAD
                        // 시작점이나 목표가 존재하지 않으면 종료
                        if (start.first == -1 || goal.first == -1)
                        {
                            return -1;
                        }

                    // ------------------------------------
                    // 3. 거리 배열 생성
                    // ------------------------------------

                    // 각 칸까지의 최소 이동 횟수 저장
                    // 초기값 -1은 아직 발견하지 않았다는 뜻
                    vector<vector<int>> dist(
                        rows,
                        vector<int>(cols, -1)
                    );

                    // ------------------------------------
                    // 4. BFS 큐 생성
                    // ------------------------------------

                    // pair<int, int>
                    // first  = row
                    // second = col
                    queue<pair<int, int>> q;

                    // 상, 하, 좌, 우 이동 방향
                    const int dr[4] = { -1, 1, 0, 0 };
                    const int dc[4] = { 0, 0, -1, 1 };

                    // 시작 좌표를 큐에 추가
                    q.push(start);

                    // 시작점의 거리는 0
                    dist[start.first][start.second] = 0;

                    // ------------------------------------
                    // 5. BFS 탐색
                    // ------------------------------------

                    while (!q.empty())
                    {
                        // 큐에서 현재 좌표 가져오기
                        // C++17 구조적 바인딩
                        auto [row, col] = q.front();

                        // 현재 좌표 제거
                        q.pop();

                        // --------------------------------
                        // 6. 목표 도착 검사
                        // --------------------------------

                        if (row == goal.first &&
                            col == goal.second)
                        {
                            // 목표까지의 최소 이동 횟수 반환
                            return dist[row][col];
                        }

                        // --------------------------------
                        // 7. 네 방향 탐색
                        // --------------------------------

                        for (int dir = 0; dir < 4; dir++)
                        {
                            // 다음 위치 계산
                            int nr = row + dr[dir];
                            int nc = col + dc[dir];

                            // ----------------------------
                            // 8. 배열 범위 검사
                            // ----------------------------

                            ====== =
                                return result;
                        }

                        // ========================================
                        // 6. 최단 경로 복원
                        // ========================================

                        vector<int> RestorePath(
                            const DijkstraResult & result,
                            int goal)
                        {
                            // 목표 정점이 유효하지 않거나
                            // 도달 불가능하면 빈 경로 반환
                            if (goal < 0 ||
                                goal >= static_cast<int>(result.dist.size()) ||
                                result.dist[goal] == INF)
                            {
                                return {};
                            }

                            vector<int> path;

                            // 목표 정점부터 부모를 역추적
                            for (int v = goal;
                                v != -1;
                                v = result.parent[v])
                            {
                                path.push_back(v);
                            }

                            // 목표 -> 시작 순서이므로 뒤집기
                            reverse(path.begin(), path.end());

                            return path;
                        }

                        // ========================================
                        // 7. 게임 미로 탐색 결과
                        // ========================================

                        struct GridResult
                        {
                            // 최소 이동 비용
                            Cost cost;

                            // 실제 이동한 좌표 목록
                            vector<pair<int, int>> path;
                        };

                        // ========================================
                        // 8. 가중치 게임 맵 다익스트라
                        // ========================================

                        GridResult DijkstraGrid(
                            const vector<vector<int>>&terrain)
                        {
                            // ------------------------------------
                            // 1. 입력 검사
                            // ------------------------------------

                            if (terrain.empty() ||
                                terrain[0].empty())
                            {
                                throw invalid_argument("Empty grid");
                            }

                            const int rows =
                                static_cast<int>(terrain.size());

                            const int cols =
                                static_cast<int>(terrain[0].size());

                            for (const auto& row : terrain)
                            {
                                if (static_cast<int>(row.size()) != cols)
                                {
                                    throw invalid_argument(
                                        "Nonrectangular grid"
                                    );
                                }

                                for (int cell : row)
                                {
                                    // -1만 벽으로 사용
                                    if (cell < -1)
                                    {
                                        throw invalid_argument(
                                            "Invalid cell cost"
                                        );
                                    }
                                }
                            }

                            // 시작점 또는 목표가 벽이면 실패
                            if (terrain[0][0] < 0 ||
                                terrain[rows - 1][cols - 1] < 0)
                            {
                                return { -1,{} };
                            }

                            // ------------------------------------
                            // 2. 2차원 좌표를 정점 ID로 변환
                            // ------------------------------------

                            // 각 좌표 (r, c)를
                            // id = r * cols + c 로 표현
                            const int total = rows * cols;

                            // 목표는 오른쪽 아래 칸
                            const int goal = total - 1;

                            vector<Cost> dist(total, INF);
                            vector<int> parent(total, -1);

                            using Entry = pair<Cost, int>;

                            priority_queue<
                                Entry,
                                vector<Entry>,
                                greater<Entry>
                            > pq;

                            // 시작점 진입 비용은 부과하지 않음
                            dist[0] = 0;
                            pq.push({ 0, 0 });

                            // 상, 하, 좌, 우 이동
                            const array<int, 4> dr = { -1, 1, 0, 0 };
                            const array<int, 4> dc = { 0, 0, -1, 1 };

                            // ------------------------------------
                            // 3. 최소 힙을 이용한 탐색
                            // ------------------------------------

                            while (!pq.empty())
                            {
                                auto [cost, id] = pq.top();
                                pq.pop();

                                // 오래된 정보 무시
                                if (cost != dist[id])
                                {
                                    continue;
                                }

                                // 목표를 최소 비용으로 꺼냈다면 종료
                                if (id == goal)
                                {
                                    break;
                                }

                                // 정점 ID를 다시 좌표로 변환
                                const int r = id / cols;
                                const int c = id % cols;

                                // 네 방향 탐색
                                for (int d = 0; d < 4; ++d)
                                {
                                    const int nr = r + dr[d];
                                    const int nc = c + dc[d];

                                    // 범위 검사
                                    >>>>>> > 30136e9 (5 - 7)
                                        if (nr < 0 || nr >= rows ||
                                            nc < 0 || nc >= cols)
                                        {
                                            continue;
                                        }

                                    <<<<<<< HEAD
                                        // ----------------------------
                                        // 9. 벽 또는 방문 여부 검사
                                        // ----------------------------

                                        // 벽이면 이동할 수 없음
                                        if (maze[nr][nc] == '#')
                                            ====== =
                                            // 벽 검사
                                            if (terrain[nr][nc] == -1)
                                                >>>>>> > 30136e9 (5 - 7)
                                            {
                                                continue;
                                            }

                                    <<<<<< < HEAD
                                        // 이미 발견한 칸이면 건너뛰기
                                        if (dist[nr][nc] != -1)
                                        {
                                            continue;
                                        }

                                    // ----------------------------
                                    // 10. 최소 거리 갱신
                                    // ----------------------------

                                    // 현재 위치에서 한 칸 이동했으므로 +1
                                    dist[nr][nc] = dist[row][col] + 1;

                                    // 다음 위치를 큐에 추가
                                    q.push({ nr, nc });
                                }
                            }

                            // 목표에 도달하지 못함
                            return -1;
                        }

                        // ========================================
                        // main 함수
                        ====== =
                            // 다음 좌표를 정점 ID로 변환
                            const int next = nr * cols + nc;

                        // 다음 칸에 진입하는 비용 추가
                        const Cost nextCost =
                            cost + terrain[nr][nc];

                        // --------------------------------
                        // 4. 거리 완화
                        // --------------------------------

                        if (nextCost < dist[next])
                        {
                            // 새 최단 거리 갱신
                            dist[next] = nextCost;

                            // 부모 정점 기록
                            parent[next] = id;

                            // 최소 힙에 새 후보 등록
                            pq.push({ nextCost, next });
                        }
                    }
                }

                // ------------------------------------
                // 5. 경로가 없는 경우
                // ------------------------------------

                if (dist[goal] == INF)
                {
                    return { -1,{} };
                }

                // ------------------------------------
                // 6. 실제 경로 복원
                // ------------------------------------

                vector<pair<int, int>> path;

                // 목표부터 시작점까지 부모 역추적
                for (int id = goal;
                    id != -1;
                    id = parent[id])
                {
                    path.push_back({
                        id / cols,
                        id % cols
                        });
                }

                // 이동 순서로 변경
                reverse(path.begin(), path.end());

                return { dist[goal], path };
            }

            // ========================================
            // 9. main 함수
            >>>>>> > 30136e9 (5 - 7)
                // ========================================

                int main()
            {
                // ------------------------------------
                <<<<<< < HEAD
                    // 실습 1. BFS 방문 순서
                    // ------------------------------------

                    cout << "[실습 1] BFS 방문 순서\n";

                vector<vector<int>> graph1 = {
                    { 1, 2 },  // 정점 0
                    { 0, 3 },  // 정점 1
                    { 0, 4 },  // 정점 2
                    { 1 },     // 정점 3
                    { 2 }      // 정점 4
                };

                // 0번 정점에서 BFS 시작
                BFSVisitOrder(graph1, 0);

                // ------------------------------------
                // 실습 2. BFS 최단 거리
                // ------------------------------------

                cout << "\n[실습 2] 각 정점까지의 최소 거리\n";

                vector<vector<int>> graph2 = {
                    { 1, 2 },
                    { 0, 3 },
                    { 0, 4 },
                    { 1, 5 },
                    { 2, 5 },
                    { 3, 4 }
                };

                // 0번 정점부터 각 정점까지의 최소 거리
                vector<int> distances = BFSDistances(graph2, 0);

                // 결과 출력
                for (int i = 0;
                    i < static_cast<int>(distances.size());
                    i++)
                {
                    cout << "Vertex " << i
                        << ": " << distances[i]
                        << '\n';
                }

                // ------------------------------------
                // 실습 3. 미로 최단 이동 횟수
                // ------------------------------------

                cout << "\n[실습 3] 미로 최단 이동 횟수\n";

                vector<string> maze = {
                    "S...",
                    ".##.",
                    "....",
                    ".##G"
                };

                // BFS를 사용해 최단 이동 횟수 계산
                int moves = MazeShortestMoves(maze);

                // 결과 출력
                cout << "Minimum moves: "
                    << moves << '\n';
                ====== =
                    // PART 1. 일반 가중치 그래프
                    // ------------------------------------

                    Graph graph(5);

                // 정점과 간선의 이동 비용 등록
                AddUndirectedEdge(graph, 0, 1, 4);
                AddUndirectedEdge(graph, 0, 2, 1);
                AddUndirectedEdge(graph, 2, 1, 2);
                AddUndirectedEdge(graph, 1, 3, 1);
                AddUndirectedEdge(graph, 2, 3, 5);
                AddUndirectedEdge(graph, 3, 4, 3);
                AddUndirectedEdge(graph, 1, 4, 7);
                AddUndirectedEdge(graph, 2, 4, 12);

                // 정점 0에서 다익스트라 실행
                const auto result = Dijkstra(graph, 0);

                cout << "[1] Weighted graph\n";

                // 모든 정점의 최단 거리 출력
                for (int i = 0;
                    i < static_cast<int>(result.dist.size());
                    ++i)
                {
                    cout << i << ": "
                        << (result.dist[i] == INF
                            ? -1 : result.dist[i])
                        << '\n';
                }

                // 목표 4까지 경로 복원
                const auto path = RestorePath(result, 4);

                cout << "Path 0 -> 4: ";

                for (size_t i = 0; i < path.size(); ++i)
                {
                    if (i)
                    {
                        cout << " -> ";
                    }

                    cout << path[i];
                }

                cout << "\nCost: " << result.dist[4];

                cout << "\nStale queue entries skipped: "
                    << result.skippedStale
                    << "\n\n";

                // ------------------------------------
                // PART 2. 게임 가중치 미로
                // ------------------------------------

                // -1 : 벽
                // 양수: 칸에 진입하는 이동 비용
                const vector<vector<int>> terrain = {
                    { 1,  1, 5,  1, 1 },
                    { 2, -1, 2, -1, 1 },
                    { 2,  2, 1,  1, 1 },
                    { 9, -1, 9, -1, 1 }
                };

                // 가중치 미로에서 최소 경로 탐색
                const GridResult grid = DijkstraGrid(terrain);

                cout << "[2] Weighted grid\n";

                cout << "Min cost: " << grid.cost << '\n';

                // 실제 이동 경로 출력
                cout << "Path: ";

                for (size_t i = 0; i < grid.path.size(); ++i)
                {
                    if (i)
                    {
                        cout << " -> ";
                    }

                    cout << '('
                        << grid.path[i].first
                        << ','
                        << grid.path[i].second
                        << ')';
                }

                cout << "\nMap:\n";

                // 경로를 표시할 문자 맵 생성
                vector<string> drawn(
                    terrain.size(),
                    string(terrain[0].size(), '.')
                );

                // 벽 표시
                for (size_t r = 0; r < terrain.size(); ++r)
                {
                    for (size_t c = 0;
                        c < terrain[r].size();
                        ++c)
                    {
                        if (terrain[r][c] == -1)
                        {
                            drawn[r][c] = '#';
                        }
                    }
                }

                // 최단 경로에 * 표시
                for (const auto& [r, c] : grid.path)
                {
                    drawn[r][c] = '*';
                }

                // 시작점과 목표 표시
                drawn[0][0] = 'S';
                drawn.back().back() = 'G';

                // 최종 경로 맵 출력
                for (const auto& row : drawn)
                {
                    cout << row << '\n';
                }
                >>>>>> > 30136e9 (5 - 7)

                    return 0;
            }
=======
            throw out_of_range(
                "Invalid edge endpoint"
            );
        }
    }

    // --------------------------------------------------------
    // STEP 3. 간선을 건설 비용이 작은 순서로 정렬
    // --------------------------------------------------------

    // sort():
    // STL 정렬 알고리즘
    //
    // 람다 함수:
    // 두 간선의 정렬 순서를 결정한다.
    sort(
        edges.begin(),
        edges.end(),
        [](const Edge& a, const Edge& b)
        {
            // 첫 번째 기준: 비용이 낮은 간선
            if (a.cost != b.cost)
            {
                return a.cost < b.cost;
            }

            // 두 번째 기준: 출발 정점 번호
            if (a.from != b.from)
            {
                return a.from < b.from;
            }

            // 세 번째 기준: 도착 정점 번호
            //
            // 비용이 같은 경우에도
            // 결과의 처리 순서를 일정하게 만든다.
            return a.to < b.to;
        }
    );

    // --------------------------------------------------------
    // STEP 4. Union-Find 생성
    // --------------------------------------------------------

    // 처음에는 모든 방이 서로 연결되지 않은 상태
    DisjointSet dsu(vertexCount);

    // MST 결과 객체
    MSTResult result;

    // --------------------------------------------------------
    // STEP 5. 정렬된 간선을 순서대로 검사
    // --------------------------------------------------------

    for (const Edge& edge : edges)
    {
        // ----------------------------------------------------
        // 5-1. 사이클 검사 및 집합 합치기
        // ----------------------------------------------------

        // Unite()가 false를 반환한다는 것은
        // 두 정점이 이미 같은 집합이라는 뜻이다.
        //
        // 이미 연결된 방 사이에 다시 간선을 추가하면
        // 사이클이 만들어지므로 건너뛴다.
        if (!dsu.Unite(edge.from, edge.to))
        {
            continue;
        }

        // ----------------------------------------------------
        // 5-2. 통로 선택
        // ----------------------------------------------------

        // 서로 다른 연결 구역을 합치는 간선이므로
        // 현재 통로를 MST에 포함한다.
        result.selected.push_back(edge);

        // ----------------------------------------------------
        // 5-3. 건설 비용 누적
        // ----------------------------------------------------

        result.totalCost += edge.cost;

        // ----------------------------------------------------
        // 5-4. MST 완성 여부 검사
        // ----------------------------------------------------

        // 정점 N개를 모두 연결하는 트리에는
        // 반드시 N-1개의 간선이 존재한다.
        //
        // 이 수를 만족하면 나머지 간선은 볼 필요 없다.
        if (static_cast<int>(result.selected.size())
            == vertexCount - 1)
        {
            break;
        }
    }

    // --------------------------------------------------------
    // STEP 6. 최종 연결 상태 확인
    // --------------------------------------------------------

    // 남아 있는 연결 요소가 몇 개인지 저장
    result.components = dsu.ComponentCount();

    // 연결 요소가 하나라면
    // 모든 방이 서로 연결된 것이다.
    result.connected = (result.components == 1);

    // --------------------------------------------------------
    // STEP 7. 결과 반환
    // --------------------------------------------------------

    // 연결되어 있다면 MST 결과이고,
    // 연결되지 않았다면 최소 신장 숲 결과이다.
    return result;
}

// ============================================================
// 5. MST 결과 출력 함수
// ============================================================

// const MSTResult&:
//
// 결과 객체를 복사하지 않고 읽기 전용으로 사용한다.
//
// PrintMST 함수는 알고리즘을 실행하지 않고
// 전달받은 결과를 출력하는 역할만 담당한다.

void PrintMST(const MSTResult& result)
{
    cout << "Selected corridors:\n";

    // 선택한 모든 간선 출력
    for (const Edge& edge : result.selected)
    {
        cout << "  "
            << edge.from
            << " - "
            << edge.to
            << " (cost "
            << edge.cost
            << ")\n";
    }

    // 비용 합계 출력
    cout << "Total cost: "
        << result.totalCost
        << '\n';

    // 전체 연결 여부 출력
    cout << "Connected: "
        << (result.connected ? "Yes" : "No")
        << '\n';

    // 연결 요소 개수 출력
    cout << "Components: "
        << result.components
        << '\n';
}

// ============================================================
// 6. main 함수
// ============================================================

int main()
{
    // ========================================================
    // PART 1. Union-Find 실습
    // ========================================================

    cout << "[1] Union-Find\n";

    // 0~5번 정점 관리
    DisjointSet dsu(6);

    // 0번과 1번을 같은 집합으로 합친다.
    dsu.Unite(0, 1);

    // 1번과 2번을 같은 집합으로 합친다.
    //
    // 1번은 이미 0번과 같은 집합이므로
    // 결과적으로 {0,1,2} 집합이 만들어진다.
    dsu.Unite(1, 2);

    // 3번과 4번을 같은 집합으로 합친다.
    //
    // 결과적으로 {3,4} 집합이 만들어진다.
    dsu.Unite(3, 4);

    // 현재 집합:
    //
    // A = {0,1,2}
    // B = {3,4}
    // C = {5}

    // 0과 2는 같은 집합이므로 Yes
    cout << "Same group (0, 2): "
        << (dsu.Same(0, 2) ? "Yes" : "No")
        << '\n';

    // 0과 3은 서로 다른 집합이므로 No
    cout << "Same group (0, 3): "
        << (dsu.Same(0, 3) ? "Yes" : "No")
        << '\n';

    // 서로 다른 집합이 3개 남아 있다.
    cout << "Components: "
        << dsu.ComponentCount()
        << "\n\n";

    // ========================================================
    // PART 2. 던전 통로 최소 비용 연결
    // ========================================================

    cout << "[2] Dungeon minimum spanning tree\n";

    // 방 6개 사이에 건설할 수 있는 후보 통로
    //
    // {방 A, 방 B, 통로 건설 비용}
    vector<Edge> corridors = {
        {0, 1, 4},
        {0, 2, 3},
        {1, 2, 1},
        {1, 3, 2},
        {2, 3, 4},
        {2, 4, 6},
        {3, 4, 5},
        {3, 5, 7},
        {4, 5, 2},
        {1, 5, 9}
    };

    // 방의 개수 6개를 전달하고
    // Kruskal로 최소 비용 통로를 선택한다.
    MSTResult dungeon = Kruskal(
        6,
        corridors
    );

    // 선택한 통로와 최종 비용 출력
    PrintMST(dungeon);

    // ========================================================
    // PART 3. 그래프가 연결되지 않은 경우
    // ========================================================

    cout << "\n[3] Disconnected dungeon\n";

    // 방이 4개지만 다음 통로만 존재한다.
    //
    // 0 - 1 (비용 2)
    // 2 - 3 (비용 3)
    //
    // 두 구역을 연결할 후보 통로가 없으므로
    // 전체를 하나로 연결할 수 없다.
    vector<Edge> disconnected = {
        {0, 1, 2},
        {2, 3, 3}
    };

    // 이 경우 전체 MST는 존재하지 않는다.
    //
    // 대신 연결 요소별 최소 신장 트리의
    // 집합인 최소 신장 숲이 반환된다.
    MSTResult forest = Kruskal(
        4,
        disconnected
    );

    // Connected: No
    // Components: 2
    //
    // 연결 실패 여부를 명확하게 확인할 수 있다.
    PrintMST(forest);

    // 프로그램 정상 종료
    return 0;
}
>>>>>>> 8dd7d41 (5-9)
=======
long long fibonacciMemo(
	int n,
	vector<long long>& memo)
{
	//memoization
	if (n <= 1)
	{
		return n;
	}

	if (memo[n] != -1)
	{
		return memo[n];
	}

	long long left = fibonacciMemo(n - 1, memo);
	long long right = fibonacciMemo(n - 2, memo);

	memo[n] = left + right;

	return memo[n];
}


int main()
{
	//coin
	vector<int> coins = { 1, 3, 4 };

	int amount = 6;

	const int INF = 100000000;

	vector<int> dp(amount + 1, INF);

	dp[0] = 0;
	
	for (int x = 1; x <= amount; x++)
	{
		for (int coin : coins)
		{
			if (coin > x)
			{
				continue;
			}

			if (dp[x - coin] == INF)
			{
				continue;
			}

			dp[x] = min(dp[x], dp[x - coin] + 1);
		}
	}
	// LCS
	for ( i = 1; i <= a.size(); i++)
	{
		for (size_t j = 1; j <= b.size(); j++)
		{
			if (a[i - 1] == b[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else
			{
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
}
>>>>>>> cf55fce (5-11)
