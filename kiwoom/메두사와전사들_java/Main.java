import java.io.*;
import java.util.*;

public class Main {
    static int N, M;
    static int[][] board;
    static int Sr, Sc, Er, Ec;
    static int[][] warriors;

    // 1차 이동/메두사 이동: 상, 하, 좌, 우
    static final int[] dr  = {-1, 1, 0, 0};
    static final int[] dc  = { 0, 0,-1, 1};
    // 2차 이동: 좌, 우, 상, 하
    static final int[] dr2 = { 0, 0,-1, 1};
    static final int[] dc2 = {-1, 1, 0, 0};

    public static void main(String[] args) throws IOException {
        File f = new File("input.txt");
        Reader rd = f.exists() ? new FileReader(f) : new InputStreamReader(System.in);
        StreamTokenizer in = new StreamTokenizer(new BufferedReader(rd));

        in.nextToken(); N = (int) in.nval;
        in.nextToken(); M = (int) in.nval;
        in.nextToken(); Sr = (int) in.nval;
        in.nextToken(); Sc = (int) in.nval;
        in.nextToken(); Er = (int) in.nval;
        in.nextToken(); Ec = (int) in.nval;

        warriors = new int[N][N];
        for (int i = 0; i < M; i++) {
            in.nextToken(); int r = (int) in.nval;
            in.nextToken(); int c = (int) in.nval;
            warriors[r][c]++;
        }

        board = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                in.nextToken(); board[i][j] = (int) in.nval;
            }
        }

        int[][] dist = bfsFromPark();

        if (dist[Sr][Sc] == -1) {
            System.out.println(-1);
            return;
        }
        if (Sr == Er && Sc == Ec) {
            System.out.println(0);
            return;
        }

        StringBuilder sb = new StringBuilder();
        int mr = Sr, mc = Sc;

        while (true) {
            // 1. 메두사 이동
            int nr = -1, nc = -1;
            for (int d = 0; d < 4; d++) {
                int rr = mr + dr[d], cc = mc + dc[d];
                if (rr < 0 || rr >= N || cc < 0 || cc >= N) continue;
                if (dist[rr][cc] == dist[mr][mc] - 1) { nr = rr; nc = cc; break; }
            }
            mr = nr; mc = nc;
            warriors[mr][mc] = 0; // 메두사 칸의 전사는 사라짐

            if (mr == Er && mc == Ec) {
                sb.append(0).append('\n');
                System.out.print(sb);
                return;
            }

            // 2. 메두사 시선 (상,하,좌,우 우선순위로 가장 많이 보는 방향)
            int bestCount = -1;
            boolean[][] bestVision = null;
            int[][] bestStoned = null;
            for (int d = 0; d < 4; d++) {
                boolean[][] vis = new boolean[N][N];
                int[][] stn = new int[N][N];
                int cnt = computeVision(mr, mc, d, vis, stn);
                if (cnt > bestCount) {
                    bestCount = cnt;
                    bestVision = vis;
                    bestStoned = stn;
                }
            }
            int stoneCount = bestCount;

            // 돌화된 전사 임시 제거
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    warriors[i][j] -= bestStoned[i][j];

            // 3. 전사 이동 (각자 최대 2칸)
            int totalMove = 0;
            int[][] next = new int[N][N];
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (warriors[i][j] == 0) continue;
                    int cnt = warriors[i][j];
                    int cr = i, cc = j;
                    int moves = 0;

                    int d1 = pickDir(cr, cc, mr, mc, bestVision, dr, dc);
                    if (d1 != -1) {
                        cr += dr[d1]; cc += dc[d1]; moves++;
                        if (!(cr == mr && cc == mc)) {
                            int d2 = pickDir(cr, cc, mr, mc, bestVision, dr2, dc2);
                            if (d2 != -1) {
                                cr += dr2[d2]; cc += dc2[d2]; moves++;
                            }
                        }
                    }
                    totalMove += moves * cnt;
                    next[cr][cc] += cnt;
                }
            }

            // 돌화된 전사 복구
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    next[i][j] += bestStoned[i][j];

            warriors = next;

            // 4. 전사 공격 (메두사 위치의 전사들 사라짐)
            int attacks = warriors[mr][mc];
            warriors[mr][mc] = 0;

            sb.append(totalMove).append(' ')
              .append(stoneCount).append(' ')
              .append(attacks).append('\n');
        }
    }

    static int pickDir(int r, int c, int mr, int mc, boolean[][] vis,
                       int[] ddr, int[] ddc) {
        int cur = Math.abs(r - mr) + Math.abs(c - mc);
        for (int d = 0; d < 4; d++) {
            int nr = r + ddr[d], nc = c + ddc[d];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if (vis[nr][nc]) continue;
            int nd = Math.abs(nr - mr) + Math.abs(nc - mc);
            if (nd < cur) return d;
        }
        return -1;
    }

    static int[][] bfsFromPark() {
        int[][] dist = new int[N][N];
        for (int[] row : dist) Arrays.fill(row, -1);
        ArrayDeque<int[]> q = new ArrayDeque<>();
        q.add(new int[]{Er, Ec});
        dist[Er][Ec] = 0;
        while (!q.isEmpty()) {
            int[] cur = q.poll();
            for (int d = 0; d < 4; d++) {
                int nr = cur[0] + dr[d], nc = cur[1] + dc[d];
                if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
                if (dist[nr][nc] != -1) continue;
                if (board[nr][nc] != 1 && !(nr == Sr && nc == Sc)) continue;
                dist[nr][nc] = dist[cur[0]][cur[1]] + 1;
                q.add(new int[]{nr, nc});
            }
        }
        return dist;
    }

    // d: 0=상, 1=하, 2=좌, 3=우. 시선 칸은 vis[][]=true, 돌화 카운트는 stn[][]에 기록
    static int computeVision(int mr, int mc, int d, boolean[][] vis, int[][] stn) {
        int cnt = 0;
        if (d == 0 || d == 1) {
            int sign = (d == 0) ? -1 : 1;
            boolean[] blocked = new boolean[N];
            for (int k = 1; k < N; k++) {
                int r = mr + sign * k;
                if (r < 0 || r >= N) break;
                int cl = Math.max(0, mc - k);
                int cR = Math.min(N - 1, mc + k);
                for (int c = cl; c <= cR; c++) {
                    if (blocked[c]) continue;
                    vis[r][c] = true;
                    if (warriors[r][c] > 0) {
                        stn[r][c] = warriors[r][c];
                        cnt += warriors[r][c];
                        blocked[c] = true;
                    }
                }
            }
        } else {
            int sign = (d == 2) ? -1 : 1;
            boolean[] blocked = new boolean[N];
            for (int k = 1; k < N; k++) {
                int c = mc + sign * k;
                if (c < 0 || c >= N) break;
                int rt = Math.max(0, mr - k);
                int rb = Math.min(N - 1, mr + k);
                for (int r = rt; r <= rb; r++) {
                    if (blocked[r]) continue;
                    vis[r][c] = true;
                    if (warriors[r][c] > 0) {
                        stn[r][c] = warriors[r][c];
                        cnt += warriors[r][c];
                        blocked[r] = true;
                    }
                }
            }
        }
        return cnt;
    }
}
