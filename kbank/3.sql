-- places: id, name, host_id
-- place_reviews: id, place_id, created_at, reviewer_id, comments
-- 구로구는 올해 잠시 지낼만한 "cozy"라는 후기가 달린 공간의 아이디와 이름 조회
-- cozy, Cozy 둘 다 해당. oracle case sensitive.

WITH FG AS (
    SELECT 
        CASE 
            WHEN COMMENTS(SUBSTR(Cozy)) OR COMMENTS(SUBSTR(cozy))
            THEN 1
            ELSE 0
        END AS FLAG, PLACE_ID
    FROM PLACE_REVIEWS
)

SELECT PLACES.ID, PLACES.NAME
FROM PLACES, FG
WHERE PLACES.ID = FG.PLACE_ID

-- 이 쿼리는 문법도 로직도 둘 다 문제가 있어요. 하나씩 짚을게요.
-- 1. COMMENTS(SUBSTR(Cozy)) — 완전히 잘못된 호출 방식

-- COMMENTS는 컬럼이지 함수가 아닙니다. 컬럼을 함수처럼 호출할 수 없어요.
-- SUBSTR는 "문자열에서 부분 문자열을 잘라내는" 함수지 "포함 여부를 체크하는" 함수가 아닙니다. 시그니처도 SUBSTR(문자열, 시작위치, 길이)예요.
-- Cozy처럼 따옴표 없이 쓰면 Oracle은 컬럼명으로 해석합니다. 문자열 리터럴은 'cozy'처럼 작은따옴표로.

-- 문자열 "포함" 체크는 셋 중 하나:

-- LIKE '%cozy%'
-- INSTR(COMMENTS, 'cozy') > 0
-- REGEXP_LIKE(COMMENTS, 'cozy')

-- 2. 대소문자 무시 처리가 안 됨
-- Oracle은 기본이 case-sensitive라 'cozy', 'Cozy', 'COZY'가 다 다릅니다. 둘 다 잡으려면:

-- LOWER(COMMENTS) LIKE '%cozy%'
-- 또는 REGEXP_LIKE(COMMENTS, 'cozy', 'i') ← 'i' 플래그가 case-insensitive

-- 3. FLAG 만들어놓고 안 씀 — 로직 자체가 깨져 있음
-- CTE에서 FLAG를 1/0으로 만들었는데 바깥 WHERE에 FG.FLAG = 1 조건이 없어요. 그래서 설령 문법이 맞아도 리뷰가 달린 모든 장소가 나옵니다. cozy 필터 효과가 0.
-- 4. "올해" 조건 누락
-- PLACE_REVIEWS.CREATED_AT을 올해로 필터해야 하는데 어디에도 없어요.

-- EXTRACT(YEAR FROM CREATED_AT) = EXTRACT(YEAR FROM SYSDATE)
-- 또는 CREATED_AT >= TRUNC(SYSDATE, 'YYYY')

-- 5. "구로구" 조건 — 스키마에 컬럼이 없음
-- 주신 스키마는 places: id, name, host_id뿐이라 주소/지역 컬럼이 없습니다. 원래 문제에 address 같은 컬럼이 있었던 거 아닐까요? 그게 없으면 구로구 필터 자체가 불가능해요.
-- 6. 같은 장소에 cozy 리뷰가 여러 개면 중복 — DISTINCT 필요

고친 버전 (places에 address 컬럼이 있다고 가정):

SELECT DISTINCT P.ID, P.NAME
FROM PLACES P
JOIN PLACE_REVIEWS PR ON P.ID = PR.PLACE_ID
WHERE REGEXP_LIKE(PR.COMMENTS, 'cozy', 'i')
  AND PR.CREATED_AT >= TRUNC(SYSDATE, 'YYYY')
  AND P.ADDRESS LIKE '%구로구%';

CTE를 굳이 쓰고 싶다면:

WITH FG AS (
    SELECT DISTINCT PLACE_ID
    FROM PLACE_REVIEWS
    WHERE LOWER(COMMENTS) LIKE '%cozy%'
      AND CREATED_AT >= TRUNC(SYSDATE, 'YYYY')
)
SELECT P.ID, P.NAME
FROM PLACES P
JOIN FG ON P.ID = FG.PLACE_ID
WHERE P.ADDRESS LIKE '%구로구%';

-- 핵심: 필터링은 CTE 안에서 끝내고, FLAG 컬럼 만들어서 바깥에서 거르는 패턴은 굳이 안 써도 됩니다. 어차피 WHERE로 바로 거르는 게 더 깔끔하고 인덱스도 잘 타요.