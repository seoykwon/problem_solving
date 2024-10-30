SELECT
    CATEGORY,
    SUM(SALES) AS TOTAL_SALES
FROM
    BOOK NATURAL JOIN BOOK_SALES
WHERE
    YEAR(SALES_DATE) = 2022 AND
    MONTH(SALES_DATE) = 1
GROUP BY
    CATEGORY
ORDER BY
    CATEGORY ASC
;

-- NATURAL JOIN을 사용할 때는 두 테이블 간의 조인 기준이 되는 열의 이름이 동일해야 하며, 이러한 열이 무엇인지 명확하게 이해하고 있어야 합니다.
-- 중복된 열이 자동으로 제거되므로, 예기치 않은 결과가 나올 수 있으므로 주의가 필요합니다.

-- 2022년 1월의 도서 판매 데이터를 기준으로 저자 별, 카테고리 별 매출액(TOTAL_SALES = 판매량 * 판매가) 을 구하여, 
-- 저자 ID(AUTHOR_ID), 저자명(AUTHOR_NAME), 카테고리(CATEGORY), 매출액(SALES) 리스트를 출력하는 SQL문을 작성해주세요.
결과는 저자 ID를 오름차순으로, 저자 ID가 같다면 카테고리를 내림차순 정렬해주세요.
SELECT A.AUTHOR_ID, A.AUTHOR_NAME, B.CATEGORY, SUM(SALES*PRICE) AS TOTAL_SALES
FROM BOOK_SALES S
JOIN BOOK B 
ON S.BOOK_ID = B.BOOK_ID -- SALES + 도서 정보
JOIN AUTHOR A
ON B.AUTHOR_ID = A.AUTHOR_ID
WHERE YEAR(SALES_DATE) = '2022' AND MONTH(SALES_DATE) = '1'
GROUP BY B.AUTHOR_ID, B.CATEGORY
ORDER BY A.AUTHOR_ID ASC, B.CATEGORY DESC

-- FOOD_PRODUCT 테이블에서 식품분류별로 가격이 제일 비싼 식품의 분류, 가격, 이름을 조회하는 SQL문을 작성해주세요. 
-- 이때 식품분류가 '과자', '국', '김치', '식용유'인 경우만 출력시켜 주시고 결과는 식품 가격을 기준으로 내림차순 정렬해주세요.
SELECT CATEGORY, MAX(PRICE) AS PRICE, PRODUCT_NAME
FROM FOOD_PRODUCT
WHERE CATEGORY = '과자' 
OR CATEGORY = '국' 
OR CATEGORY = '김치' 
OR CATEGORY = '식용유'
GROUP BY CATEGORY
ORDER BY PRICE DESC
-- 틀린 코드임
-- 문제의 원인
-- MAX(PRICE)로 카테고리별 최고 가격을 구하고 있지만, PRODUCT_NAME이 GROUP BY에 포함되지 않기 때문에 
-- 각 카테고리에서 최고 가격에 해당하는 제품 이름을 정확히 선택하지 못할 가능성이 있습니다. 
-- SQL 엔진은 보통 집계되지 않은 열에 대해 임의의 행을 선택하므로, 
-- MAX(PRICE)에 해당하는 올바른 PRODUCT_NAME이 아닌 다른 이름이 선택될 수 있습니다.

-- 이를 해결하기 위해 서브쿼리를 사용하여 각 카테고리별로 최고 가격을 먼저 구한 뒤, 
-- 그 가격에 해당하는 제품을 다시 조인하는 방식으로 접근할 수 있습니다.
SELECT FP.CATEGORY, FP.PRICE, FP.PRODUCT_NAME
FROM FOOD_PRODUCT AS FP
JOIN (
    SELECT CATEGORY, MAX(PRICE) AS MAX_PRICE
    FROM FOOD_PRODUCT
    WHERE CATEGORY IN ('과자', '국', '김치', '식용유')
    GROUP BY CATEGORY
) AS MAX_PRODUCTS ON FP.CATEGORY = MAX_PRODUCTS.CATEGORY AND FP.PRICE = MAX_PRODUCTS.MAX_PRICE
ORDER BY FP.PRICE DESC;

-- REST_INFO 테이블에서 음식종류별로 즐겨찾기수가 가장 많은 식당의 
-- 음식 종류, ID, 식당 이름, 즐겨찾기수를 조회하는 SQL문을 작성해주세요. 
-- 이때 결과는 음식 종류를 기준으로 내림차순 정렬해주세요.
SELECT FOOD_TYPE, REST_ID, REST_NAME, FAVORITES
    FROM REST_INFO
    WHERE FAVORITES IN (SELECT MAX(FAVORITES)
            FROM REST_INFO
            GROUP BY FOOD_TYPE)
    GROUP BY FOOD_TYPE
    ORDER BY FOOD_TYPE DESC

