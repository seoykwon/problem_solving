-- videos: id(int), title(varchar(n)), rate (numeric(n, m), num_view(int), release_date(date), mpaa_rate(varchar(n)))
-- 평점 상위 다섯 개 영화와 관객 수 상위 다섯 개 영화 제목 조회
-- 1~5까지 순위, 평점 1~5 영화 제목, 1~5 관객 수 영화 제목.
-- 평점 같으면 영화 ID 기준 오름차순 정렬

WITH RT AS (
    SELECT RATE, TITLE
    FROM VIDEOS
    ORDER BY RATE DESC
    FETCH 5 ROWS RANK BY (1, 5) AS RNK;
)

WITH VW AS (
    SELECT NUM_VIEW, TITLE
    FROM VIDEOS
    ORDER BY NUM_VIEW DESC
    FETCH 5 ROWS RANK BY (1, 5) AS RNK;
)

SELECT RNK, RT.TITLE, VW.TITLE
FROM RT, VW
WHERE RT.RNK = VW.RNK

이 쿼리는 사실상 새로 짜야 할 정도로 잘못 됐어요. 문제점부터 짚을게요.
1. FETCH 5 ROWS RANK BY (1, 5) AS RNK — 존재하지 않는 문법
이런 구문은 Oracle에도, 어떤 SQL 방언에도 없습니다. Oracle에 있는 건 FETCH FIRST 5 ROWS ONLY(단순 페이지네이션)뿐이고, 거기서 순위 번호를 컬럼으로 만들어주지는 않아요. 순위가 필요하면 윈도우 함수 ROW_NUMBER() / RANK() / DENSE_RANK()를 써야 합니다.
2. WITH를 두 번 쓰면 안 됨
CTE는 WITH 한 번에 콤마로 연결합니다.
-- ❌ 잘못
WITH RT AS (...);
WITH VW AS (...);
SELECT ...

-- ✅ 맞음
WITH RT AS (...),
     VW AS (...)
SELECT ...
게다가 CTE 정의 끝의 ;는 statement를 끝내버려서 그 자체로도 깨집니다.
3. CTE 안의 ORDER BY만으로 상위 N개를 못 자름
CTE 안의 정렬은 바깥에서 보장되지도 않고, 자르는 기능도 아닙니다. 자르려면 윈도우 함수로 순위 매기고 바깥에서 WHERE RNK <= 5로 거르거나, ROW_NUMBER를 같이 매겨야 해요.
4. 동점 정렬 규칙 누락
"평점 같으면 ID 오름차순"이 들어가야 하는데 빠져 있습니다. 윈도우 함수의 OVER (ORDER BY ...)에 같이 넣어줘야 해요.

고치면:
WITH RT AS (
    SELECT ID, TITLE,
           ROW_NUMBER() OVER (ORDER BY RATE DESC, ID ASC) AS RNK
    FROM VIDEOS
),
VW AS (
    SELECT ID, TITLE,
           ROW_NUMBER() OVER (ORDER BY NUM_VIEW DESC, ID ASC) AS RNK
    FROM VIDEOS
)
SELECT RT.RNK AS RANK_NO,
       RT.TITLE AS RATE_TITLE,
       VW.TITLE AS VIEW_TITLE
FROM RT
JOIN VW ON RT.RNK = VW.RNK
WHERE RT.RNK <= 5
ORDER BY RT.RNK;

핵심 변화:

WITH 한 번 + 콤마로 두 CTE 묶음
ROW_NUMBER() OVER (ORDER BY ... DESC, ID ASC)로 순위 + 동점 처리 동시에
5개 자르는 건 바깥 WHERE RNK <= 5로
두 CTE를 RNK로 JOIN해서 1~5위가 한 행씩 나오게

참고로 RANK()를 쓰면 동점일 때 같은 순위가 나오고 다음이 건너뛰어요(1,1,3...). 위 문제처럼 "1~5위에 정확히 한 영화씩"을 원하면 ROW_NUMBER()가 맞습니다.