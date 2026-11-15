
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
#include <vector>

    using namespace std;

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
{
    // 1. 방문 여부 배열 생성
    // 처음에는 모든 정점을 방문하지 않은 상태
    vector<bool> visited(graph.size(), false);

    // 2. BFS에 사용할 큐
    queue<int> q;

    // 3. 시작 정점 방문 처리
    visited[start] = true;

    // 4. 시작 정점을 큐에 삽입
    q.push(start);

    cout << "BFS: ";

    // 5. 큐가 비어 있지 않은 동안 반복
    while (!q.empty())
    {
        // 큐의 맨 앞 정점 확인
        int current = q.front();

        // 맨 앞 정점 제거
        q.pop();

        // 현재 방문한 정점 출력
        cout << current << " ";

        // 현재 정점에 연결된 모든 이웃 탐색
        for (int next : graph[current])
        {
            // 아직 방문하지 않은 정점이라면
            if (!visited[next])
            {
                // 방문 처리
                visited[next] = true;

                // 다음에 탐색할 정점을 큐에 추가
                q.push(next);
            }
        }
    }

    cout << '\n';
}

// ========================================
// 실습 2. BFS 최단 거리 계산
// ========================================

// 시작 정점에서 각 정점까지의 최소 거리를
// vector<int>로 반환하는 함수

vector<int> BFSDistances(
    const vector<vector<int>>& graph,
    int start)
{
    // 1. 거리 배열 생성
    // -1: 아직 발견하지 않은 정점
    vector<int> dist(graph.size(), -1);

    // 2. BFS 큐 생성
    queue<int> q;

    // 3. 시작 정점의 거리는 0
    dist[start] = 0;

    // 4. 시작 정점을 큐에 추가
    q.push(start);

    // 5. BFS 실행
    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        // 현재 정점의 모든 이웃 확인
        for (int next : graph[current])
        {
            // 아직 발견하지 않은 정점이라면
            if (dist[next] == -1)
            {
                // 현재 정점보다 한 간선 더 이동
                dist[next] = dist[current] + 1;

                // 큐에 추가
                q.push(next);
            }
        }
    }

    // 6. 모든 정점까지의 최소 거리 반환
    return dist;
}

// ========================================
// 실습 3. 게임 미로 최단 이동 횟수
// ========================================

// 반환값
// 0 이상: 최소 이동 횟수
// -1: 도달 불가능하거나 유효하지 않은 미로

int MazeShortestMoves(
    const vector<string>& maze)
{
    // ------------------------------------
    // 1. 미로 크기 확인
    // ------------------------------------

    if (maze.empty() || maze[0].empty())
    {
        return -1;
    }

    int rows = static_cast<int>(maze.size());
    int cols = static_cast<int>(maze[0].size());

    // 시작 좌표와 목표 좌표
    pair<int, int> start = { -1, -1 };
    pair<int, int> goal = { -1, -1 };

    // ------------------------------------
    // 2. 시작점 S와 목표 G 찾기
    // ------------------------------------

    for (int r = 0; r < rows; r++)
    {
        // 모든 행의 길이가 동일해야 함
        if (static_cast<int>(maze[r].size()) != cols)
        {
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
