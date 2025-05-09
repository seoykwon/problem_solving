WITH RECURSIVE TBL AS (
    SELECT
        ID,
        PARENT_ID,
        1 AS GENERATION
    FROM
        ECOLI_DATA
    WHERE
        PARENT_ID IS NULL

    UNION ALL

    SELECT
        e.ID,
        e.PARENT_ID,
        GENERATION + 1
    FROM
        ECOLI_DATA e INNER JOIN TBL t
        ON e.PARENT_ID = t.ID
)

SELECT ID
FROM TBL
WHERE GENERATION = 3
ORDER BY ID ASC;
  
-- ###############################
SELECT
    c.ID
FROM (
    SELECT ID,PARENT_ID FROM ECOLI_DATA WHERE PARENT_ID IS NULL) a
    INNER JOIN ECOLI_DATA b ON a.ID = b.PARENT_ID 
    INNER JOIN ECOLI_DATA c ON b.ID = c.PARENT_ID
ORDER BY
    c.ID ASC;

-- ################################
WITH TBL AS (
    SELECT EMP_NO, AVG(SCORE) AS AVG_SCORE
    FROM HR_GRADE
    GROUP BY EMP_NO
)

SELECT 
    E.EMP_NO,
    E.EMP_NAME,
    CASE
        WHEN T.AVG_SCORE >= 96 THEN 'S'
        WHEN T.AVG_SCORE >= 90 THEN 'A'
        WHEN T.AVG_SCORE >= 80 THEN 'B'
        ELSE 'C'
    END AS GRADE,
    CASE
        WHEN T.AVG_SCORE >= 96 THEN E.SAL * 0.2
        WHEN T.AVG_SCORE >= 90 THEN E.SAL * 0.15
        WHEN T.AVG_SCORE >= 80 THEN E.SAL * 0.1
        ELSE 0
    END AS BONUS
FROM
    HR_EMPLOYEES E
    INNER JOIN TBL T ON E.EMP_NO = T.EMP_NO
GROUP BY
    T.EMP_NO

-- ########################
WITH CTE AS (
    SELECT 
        CASE
            WHEN SKILL_CODE & (SELECT SUM(CODE) FROM SKILLCODES WHERE CATEGORY = 'Front End') > 0
                AND SKILL_CODE & (SELECT SUM(CODE) FROM SKILLCODES WHERE NAME = 'Python') > 0
            THEN 'A'
            WHEN SKILL_CODE & (SELECT SUM(CODE) FROM SKILLCODES WHERE NAME = 'C#') > 0
            THEN 'B'
            WHEN SKILL_CODE & (SELECT SUM(CODE) FROM SKILLCODES WHERE CATEGORY = 'Front End') > 0
            THEN 'C'
            ELSE NULL
        END AS GRADE,
        ID, EMAIL
    FROM 
        DEVELOPERS
)

SELECT *
FROM CTE
WHERE GRADE IS NOT NULL
ORDER BY GRADE ASC, ID ASC;

-- ###########################
WITH CODE_SUM AS (
    SELECT 
        (SELECT SUM(CODE) FROM SKILLCODES WHERE CATEGORY = 'Front End') AS FRONT_END,
        (SELECT SUM(CODE) FROM SKILLCODES WHERE NAME = 'Python') AS PYTHON,
        (SELECT SUM(CODE) FROM SKILLCODES WHERE NAME = 'C#') AS CSHARP
),
CTE AS (
    SELECT 
        CASE 
            WHEN SKILL_CODE & C.FRONT_END > 0 AND SKILL_CODE & C.PYTHON > 0 THEN 'A'
            WHEN SKILL_CODE & C.CSHARP > 0 THEN 'B'
            WHEN SKILL_CODE & C.FRONT_END > 0 THEN 'C'
        END AS GRADE,
        ID, EMAIL
    FROM DEVELOPERS, CODE_SUM C
)
SELECT *
FROM CTE
WHERE GRADE IS NOT NULL
ORDER BY GRADE, ID;

-- #############################
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

-- ###########################
SELECT s.member_name, f.review_text, DATE_FORMAT(f.review_date,"%Y-%m-%d") review_date
from rest_review f
join member_profile s
on f.member_id = s.member_id
WHERE f.member_id = (
    SELECT member_id
    FROM rest_review
    GROUP BY member_id
    ORDER BY COUNT(*) DESC
    LIMIT 1
)
order by f.review_date asc, f.review_text asc;

-- ######################
WITH CTE1 AS (
    SELECT MEMBER_ID, COUNT(*) AS REVIEW_COUNT
    FROM REST_REVIEW
    GROUP BY MEMBER_ID),

    CTE2 AS (
        SELECT MAX(REVIEW_COUNT) AS MAX_COUNT
        FROM CTE1)

SELECT
    member.MEMBER_NAME,
    review.REVIEW_TEXT,
    DATE_FORMAT(review.REVIEW_DATE, '%Y-%m-%d') AS REVIEW_DATE
FROM
    CTE1
    INNER JOIN CTE2 ON CTE1.REVIEW_COUNT = CTE2.MAX_COUNT
    LEFT JOIN REST_REVIEW review ON CTE1.MEMBER_ID = review.MEMBER_ID
    LEFT JOIN MEMBER_PROFILE member ON CTE1.MEMBER_ID = member.MEMBER_ID
ORDER BY
    REVIEW_DATE ASC,
    review.REVIEW_TEXT ASC;

-- ##############################
-- 5월 식품들의 총매출 조회하기
WITH CTE AS (
    SELECT 
        PRODUCT_ID, AMOUNT
    FROM 
        FOOD_ORDER
    WHERE 
        MONTH(PRODUCE_DATE) = 5 AND YEAR(PRODUCE_DATE) = 2022
),
SALES AS (
    SELECT 
        SUM(CTE.AMOUNT) * FP.PRICE AS INDI_SALE, CTE.PRODUCT_ID, FP.PRODUCT_NAME
    FROM 
        CTE
    INNER JOIN 
        FOOD_PRODUCT FP
    ON 
        CTE.PRODUCT_ID = FP.PRODUCT_ID
    GROUP BY
        PRODUCT_ID
)
SELECT 
    PRODUCT_ID, PRODUCT_NAME, INDI_SALE AS TOTAL_SALES
FROM 
    SALES
ORDER BY TOTAL_SALES DESC, PRODUCT_ID ASC

-- 버전 2
SELECT
    o.PRODUCT_ID,
    p.PRODUCT_NAME,
    SUM(o.AMOUNT * p.PRICE) AS TOTAL_SALES
FROM
    FOOD_PRODUCT p INNER JOIN FOOD_ORDER o
    ON p.PRODUCT_ID = o.PRODUCT_ID
WHERE
    o.PRODUCE_DATE REGEXP '2022-05'
GROUP BY
    o.PRODUCT_ID
ORDER BY
    TOTAL_SALES DESC,
    PRODUCT_ID ASC;

-- 버전 3
WITH MAY_ORDER_AMT AS (
    SELECT PRODUCT_ID
            ,SUM(AMOUNT) AS ORDER_AMT
    FROM FOOD_ORDER
    WHERE DATE_FORMAT(PRODUCE_DATE, '%Y-%m') = '2022-05'
    GROUP BY PRODUCT_ID
)

SELECT P.PRODUCT_ID
        ,P.PRODUCT_NAME
        ,ORDER_AMT * P.PRICE AS TOTAL_SALES
FROM FOOD_PRODUCT AS P
JOIN MAY_ORDER_AMT AS O
ON P.PRODUCT_ID = O.PRODUCT_ID
ORDER BY TOTAL_SALES DESC, P.PRODUCT_ID

-- ################################
