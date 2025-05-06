-- 1단계: 각 회원별 리뷰 개수 구하기
WITH ReviewCounts AS (
    SELECT
        MEMBER_ID,
        COUNT(*) AS ReviewCount
    FROM REST_REVIEW
    GROUP BY MEMBER_ID
),

-- 2단계: 가장 리뷰를 많이 쓴 회원 찾기
MaxReviewers AS (
    SELECT MEMBER_ID
    FROM ReviewCounts
    WHERE ReviewCount = (
        SELECT MAX(ReviewCount) FROM ReviewCounts
    )
),

-- 3단계: 가장 많이 리뷰를 쓴 회원의 리뷰 상세 정보
FinalResult AS (
    SELECT
        MP.MEMBER_NAME,
        RR.REVIEW_TEXT,
        DATE_FORMAT(RR.REVIEW_DATE, '%Y-%m-%d') AS REVIEW_DATE
    FROM
        MEMBER_PROFILE MP
    JOIN REST_REVIEW RR ON MP.MEMBER_ID = RR.MEMBER_ID
    WHERE MP.MEMBER_ID IN (SELECT MEMBER_ID FROM MaxReviewers)
)

-- 4단계: 정렬
SELECT *
FROM FinalResult
ORDER BY REVIEW_DATE ASC, REVIEW_TEXT ASC;
