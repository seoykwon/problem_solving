import sys
from collections import deque
from typing import List, Tuple
input = sys.stdin.readline

# 1. 메두사 클래스 생성
class Medusa:
    # 1-1.
    def __init__(self,
                 Sr:int,
                 Sc:int,
                 Er:int,
                 Ec:int):
        # 1-1-1. 메두사 위치 선언
        self.index = (Sr, Sc)
        # 1-1-2. 공원 위치 선언
        self.park = (Er, Ec)
        # 1-1-3. 메두사 이동 경로 생성
        self.route = self._get_route(Sr, Sc)
        # 1-1-4. 방향 별 시야 딕셔너리 생성
        self.dirs = {
            (-1, 0): [(-1, -1), (-1, 0), (-1, 1)],
            (1, 0): [(1, -1), (1, 0), (1, 1)],
            (0, -1): [(-1, -1), (0, -1), (1, -1)],
            (0, 1): [(-1, 1), (0, 1), (1, 1)]
        }
    # 1-2. 최단 경로 선정 함수 생성
    def _get_route(self,
                   Sr:int,
                   Sc:int) -> List[Tuple]:
        # 1-2-1. 큐 생성 후 메두사 위치 삽입
        queue = deque([(Sr, Sc)])
        # 1-2-2. 역추적 그래프 후 현재 위치 방문 처리
        backtracking_graph = [[False for _ in range(N)] for _ in range(N)]
        backtracking_graph[Sr][Sc] = True
        # 1-2-3.
        while queue:
            # 위치 인덱스 반환
            x, y = queue.popleft()
            for dir_x, dir_y in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                # 다음 위치 설정
                nx, ny = x+dir_x, y+dir_y
                # 예외 처리
                if nx<0 or nx>=N or ny<0 or ny>=N or graph[nx][ny] == 1: continue
                # 다음 위치에 방문한 적이 없는 경우
                if not backtracking_graph[nx][ny]:
                    # 역추적 그래프에 현재 위치 삽입
                    backtracking_graph[nx][ny] = (x, y)
                    # 공원에 도달한 경우
                    if (nx, ny) == self.park:
                        # 이동경로 리스트 생성 및 반환
                        route = []
                        Rx, Ry = nx, ny
                        while backtracking_graph[Rx][Ry] != True:
                            route.append((Rx, Ry))
                            Rx, Ry = backtracking_graph[Rx][Ry]
                        return route[::-1]
                    # 큐에 다음 위치 삽입
                    queue.append((nx, ny))
        # 1-2-4. 공원에 도달하지 못했으므로 빈 리스트 반환
        return []

    # 1-3. 이동 함수 생성
    def move(self, warrior_graph) -> None:
        self.warrior_graph = warrior_graph

        # 1-3-1. 메두사 위치 업데이트
        self.index = self.route.pop(0)
        # 1-3-2. 이동한 곳에 전사가 있는 경우 처리
        x, y = self.index
        if self.warrior_graph[x][y]:
            self.warrior_graph[x][y] = 0

    # 1-4. 메두사 시야 추출 함수 생성
    def _view_extract(self, dir:Tuple) -> List[List[bool]]:
        # 1-4-1. 큐 생성 후 메두사 위치 삽입
        x, y = self.index
        queue = deque([(x, y)])
        # 1-4-2. 시야 여부 그래프 생성
        visible_graph = [[False for _ in range(N)] for _ in range(N)]
        # 1-4-3. 시야 내 전사 리스트 생성
        exposed_warriors = []
        # 1-4-4.
        while queue:
            # 위치 인덱스 반환
            x, y = queue.popleft()
            for dir_x, dir_y in self.dirs[dir]:
                # 다음 위치 설정
                nx, ny = x+dir_x, y+dir_y
                # 예외 처리
                if nx<0 or nx>=N or ny<0 or ny>=N: continue
                # 해당 위치를 본 적이 없는 경우
                if not visible_graph[nx][ny]:
                    # 시야 처리
                    visible_graph[nx][ny] = True
                    # 해당 위치에 전사가 있는 경우 시야 내 전사 리스트 업데이트
                    if self.warrior_graph[nx][ny] :
                        exposed_warriors.append((nx, ny))
                    # 큐에 다음 위치 삽입
                    queue.append((nx, ny))
        # 1-4-5.
        for x, y in exposed_warriors:
            # 전사 위치가 메두사 시야에 노출된 경우
            if visible_graph[x][y]:
                # 메두사로부터의 방향 선정
                diff_x = x - self.index[0]
                diff_y = y - self.index[1]
                warrior_dirs = [
                    self.dirs[dir][1],
                    (
                        int(diff_x/abs(diff_x)) if diff_x else 0,
                        int(diff_y/abs(diff_y)) if diff_y else 0
                    )
                ]
                # 큐 생성 후 전사 위치 삽입
                queue = deque([(x, y)])
                while queue:
                    # 위치 인덱스 반환
                    x, y = queue.popleft()
                    for dir_x, dir_y in warrior_dirs:
                        # 다음 위치 설정
                        nx, ny = x+dir_x, y+dir_y
                        # 예외 처리
                        if nx<0 or nx>=N or ny<0 or ny>=N: continue
                        # 해당 위치가 보이는 경우
                        if visible_graph[nx][ny]:
                            # 시야 처리
                            visible_graph[nx][ny] = False
                            # 큐에 다음 위치 삽입
                            queue.append((nx, ny))
        # 1-4-6. 시야 여부 그래프 반환
        return visible_graph

    # 1-5. 노출된 전사 수 체크 함수 생성
    def _check_warriors(self,
                        visible_graph:List[List[bool]]) -> int:
        cnt = 0
        # 1-5-1.
        for x in range(N):
            for y in range(N):
                # 시야가 노출된 경우 전사 수 카운트
                if visible_graph[x][y]:
                    cnt += self.warrior_graph[x][y]
        # 1-5-2. 노출된 전사 수 반환
        return cnt

    # 1-6. 메두사 시선 함수 생성
    def gaze(self) -> None:
        # 1-6-1. 노출된 전사 수 초기화 선언
        self.warrior_cnt = 0
        # 1-6-2.
        for dir in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            # 메두사 시야 추출
            visible_graph = self._view_extract(dir)
            # 노출된 전사 수 체크
            # 노출된 전사 수가 선언된 값보다 많을 경우
            if self.warrior_cnt < (warrior_cnt:=self._check_warriors(visible_graph)):
                # 노출된 전사 수 업데이트
                self.warrior_cnt = warrior_cnt
                # 시야 그래프 선언
                self.visible_graph = visible_graph

# 2. 전사 클래스 생성
class Warrior:
    # 2-1.
    def __init__(self,
                 warriors:List[Tuple]):
        # 2-1-1. 전사 인덱스 리스트 선언
        self.warriors = warriors
        # 2-1-2. 전사 위치 그래프 생성
        self.warrior_graph = self._create_warrior_graph()

    # 2-2. 전사 위치 그래프 생성 함수 생성
    def _create_warrior_graph(self) -> List[List[int]]:
        # 2-2-1. 전사 위치 그래프 초기화
        warrior_graph = [[0 for _ in range(N)] for _ in range(N)]
        # 2-2-2.
        for warrior in self.warriors:
            # 전사 위치 그래프 업데이트
            x, y = warrior
            warrior_graph[x][y] += 1
        # 2-2-3. 전사 위치 그래프 반환
        return warrior_graph

    # 2-3. 우선 순위에 따른 이동 함수 생성
    def _move(self,
              warrior_x:int,
              warrior_y:int,
              priority_dirs:List[Tuple]) -> Tuple[int]:
        # 2-3-1.
        for dir_x, dir_y in priority_dirs:
            # 다음 위치 설정
            nx, ny = warrior_x+dir_x, warrior_y+dir_y
            # 예외 처리
            if nx<0 or nx>=N or ny<0 or ny>=N: continue
            # 다음 위치가 메두사의 시야 내에서 벗어나면서 메두사와 가까워지는 경우
            mx, my = self.medusa_index
            if not self.visible_graph[nx][ny] and abs(mx-warrior_x)+abs(my-warrior_y) > abs(mx-nx)+abs(my-ny):
                # 다음 위치 반환
                return (nx, ny)
        # 2-3-2. 이동이 불가하므로 현재 위치 반환
        return (warrior_x, warrior_y)

    # 2-4. 이동 함수 생성
    def move(self, warrior_graph, medusa_index, visible_graph) -> None:
        self.warrior_graph = warrior_graph
        self.medusa_index, self.visible_graph = medusa_index, visible_graph
        self.sub_warrior_graph = [[0 for _ in range(N)] for _ in range(N)]

        # 2-4-1. 이동 거리 및 공격 횟수 선언
        self.distance, self.attack_cnt = 0, 0
        # 2-4-2.
        for x in range(N):
            for y in range(N):
                # 현재 위치가 메두사의 시야에서 벗어나면서 기사가 있는 경우
                if not self.visible_graph[x][y] and self.warrior_graph[x][y]:
                    px, py = x, y
                    for priority_dirs in [
                        [(-1, 0), (1, 0), (0, -1), (0, 1)],
                        [(0, -1), (0, 1), (-1, 0), (1, 0)]
                    ]:
                        # 우선 순위에 따른 이동
                        nx, ny = self._move(px, py, priority_dirs)
                        # 이동을 하지 않은 경우 break
                        if (px, py) == (nx, ny):
                            break
                        # 이동 처리
                        else:
                            self.distance += self.warrior_graph[x][y]
                        # 메두사에게 도달한 경우
                        if (nx, ny) == self.medusa_index:
                            # 공격 횟수 업데이트
                            self.attack_cnt += self.warrior_graph[x][y]
                            break
                        px, py = nx, ny
                    # 이동이 마무리되었다면 이동 처리
                    if (nx, ny) != self.medusa_index:
                        self.sub_warrior_graph[nx][ny] += self.warrior_graph[x][y]
                # 기사가 움직일 수 없는 경우 전사 위치 그래프 업데이트
                elif self.warrior_graph[x][y]:
                    self.sub_warrior_graph[x][y] += self.warrior_graph[x][y]
        # 2-4-3. 전사 위치 그래프 업데이트
        self.warrior_graph = self.sub_warrior_graph[:][:]

N, M = map(int, input().split())
Sr, Sc, Er, Ec = map(int, input().split())
length = len(sub_index:=list(map(int, input().split())))
warriors = [(sub_index[idx], sub_index[idx+1]) for idx in range(0, length, 2)]
graph = [list(map(int, input().split())) for _ in range(N)]

# 3. 전사 object 생성
warrior = Warrior(warriors)
# 4. 메두사 object 생성
medusa = Medusa(Sr, Sc, Er, Ec)
# 5. 이동 경로가 존재하지 않는 경우 -1 출력
if not medusa.route:
    print(-1)
else:
    # 6.
    while True:
        # 6-1. 메두사 이동
        medusa.move(warrior_graph=warrior.warrior_graph)
        # 6-2. 메두사가 공원에 도착한 경우 0 출력 후 while문 탈출
        if medusa.index == (Er, Ec):
            print(0)
            break
        # 6-3. 메두사 시선
        medusa.gaze()
        # 6-4. 전사 이동 및 공격
        warrior.move(warrior_graph=warrior.warrior_graph,
                     medusa_index=medusa.index,
                     visible_graph=medusa.visible_graph)
        # 6-5. 결과 출력
        print(warrior.distance, medusa.warrior_cnt, warrior.attack_cnt)