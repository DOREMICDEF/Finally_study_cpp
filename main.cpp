
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// ========================================
// 실습 1. BFS 방문 순서
// ========================================

// graph: 인접 리스트로 저장한 그래프
// start: 탐색을 시작할 정점
// 반환형 void: 탐색 결과를 직접 출력

void BFSVisitOrder(
    const vector<vector<int>>& graph,
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
            }
        }
    }

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

            if (nr < 0 || nr >= rows ||
                nc < 0 || nc >= cols)
            {
                continue;
            }

            // ----------------------------
            // 9. 벽 또는 방문 여부 검사
            // ----------------------------

            // 벽이면 이동할 수 없음
            if (maze[nr][nc] == '#')
            {
                continue;
            }

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
// ========================================

int main()
{
    // ------------------------------------
    // 실습 1. BFS 방문 순서
    // ------------------------------------

    cout << "[실습 1] BFS 방문 순서\n";

    vector<vector<int>> graph1 = {
        {1, 2},  // 정점 0
        {0, 3},  // 정점 1
        {0, 4},  // 정점 2
        {1},     // 정점 3
        {2}      // 정점 4
    };

    // 0번 정점에서 BFS 시작
    BFSVisitOrder(graph1, 0);

    // ------------------------------------
    // 실습 2. BFS 최단 거리
    // ------------------------------------

    cout << "\n[실습 2] 각 정점까지의 최소 거리\n";

    vector<vector<int>> graph2 = {
        {1, 2},
        {0, 3},
        {0, 4},
        {1, 5},
        {2, 5},
        {3, 4}
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

    return 0;
}
