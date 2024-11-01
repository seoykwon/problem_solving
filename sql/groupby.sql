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

-- CAR_RENTAL_COMPANY_RENTAL_HISTORY 테이블에서 2022년 10월 16일에 대여 중인 자동차인 경우 '대여중' 이라고 표시하고, 
-- 대여 중이지 않은 자동차인 경우 '대여 가능'을 표시하는 컬럼(컬럼명: AVAILABILITY)을 추가하여 
-- 자동차 ID와 AVAILABILITY 리스트를 출력하는 SQL문을 작성해주세요. 
-- 이때 반납 날짜가 2022년 10월 16일인 경우에도 '대여중'으로 표시해주시고 결과는 자동차 ID를 기준으로 내림차순 정렬해주세요.
SELECT CAR_ID
     , CASE
        WHEN MAX('2022-10-16' BETWEEN START_DATE AND END_DATE) = 1 THEN '대여중'
        ELSE '대여 가능'
        END AS AVAILABILITY
FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY
GROUP BY CAR_ID
ORDER BY CAR_ID DESC
-- 이 쿼리는 MAX 함수를 사용하여 CAR_ID별로 대여 기록 중 하나라도 '2022-10-16'이 START_DATE와 END_DATE 사이에 있는 경우를 확인합니다.
-- '2022-10-16' BETWEEN START_DATE AND END_DATE는 참(TRUE)일 때 1, 거짓(FALSE)일 때 0으로 평가됩니다. 
-- 그러므로 MAX 함수는 1이 있는 경우 대여중으로 표시하고, 그렇지 않으면 대여 가능으로 처리합니다.
-- 이 쿼리는 하나의 CAR_ID에 여러 대여 기록이 있는 경우에도 모든 기록을 확인하고, 
-- 최소 하나의 대여 기록이 '2022-10-16'에 해당하는지 여부에 따라 대여중 또는 대여 가능을 결정합니다.

-- 틀린 코드
SELECT A.CAR_ID, 
CASE WHEN A.START_DATE <= '2022-10-16'
AND A.END_DATE >= '2022-10-16'
THEN '대여중'
ELSE '대여 가능'
END AS AVAILABILITY
FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY A
GROUP BY CAR_ID
ORDER BY CAR_ID DESC;
-- 두 번째 쿼리가 틀린 이유는 GROUP BY절에서 필드의 집계 함수 없이 CASE WHEN 조건을 사용하는 것에 있습니다. 
-- 이로 인해 SQL 엔진이 CAR_ID별로 단일 결과만 반환하려 하지만, 개별 대여 기록이 하나 이상인 경우 원하는 결과를 보장하지 못할 수 있습니다. 
-- 프로그래머스 문제에서 요구하는 대로 CAR_ID별로 모든 대여 기록을 확인해, 
-- 하나라도 '2022-10-16'에 해당하면 대여중으로 정확히 표시되도록 하기 위해서는 MAX 함수를 사용한 쿼리가 더 적합합니다.
-- 집계 함수(Aggregate Function)는 SQL에서 데이터를 요약하거나 그룹화하여 계산된 결과를 반환하는 함수입니다. 
-- 여러 행의 데이터를 그룹으로 묶어 하나의 요약된 값을 산출하는 데 사용되며, GROUP BY 절과 자주 함께 사용됩니다.

-- CAR_RENTAL_COMPANY_RENTAL_HISTORY 테이블에서 대여 시작일을 기준으로 2022년 8월부터 2022년 10월까지 총 대여 횟수가 5회 이상인 
-- 자동차들에 대해서 해당 기간 동안의 월별 자동차 ID 별 총 대여 횟수(컬럼명: RECORDS) 리스트를 출력하는 SQL문을 작성해주세요. 
-- 결과는 월을 기준으로 오름차순 정렬하고, 월이 같다면 자동차 ID를 기준으로 내림차순 정렬해주세요. 특정 월의 총 대여 횟수가 0인 경우에는 결과에서 제외해주세요.
SELECT MONTH(START_DATE) AS MONTH
     , CAR_ID
     , COUNT(*) AS RECORDS 
FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY
WHERE
    CAR_ID IN (SELECT CAR_ID
              FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY
              WHERE START_DATE BETWEEN '2022-08-01' AND '2022-10-31'
              GROUP BY CAR_ID
              HAVING COUNT(CAR_ID) >= 5)
    AND START_DATE BETWEEN '2022-08-01' AND '2022-10-31'
GROUP BY MONTH, CAR_ID
ORDER BY MONTH ASC, CAR_ID DESC

-- 우선 맨 아래에 날짜 조건을 추가해준 이유는 WHERE절에서의 서브 쿼리에서 날짜 조건을 추가하여 CAR_ID를 가져오긴 하였으나, 
-- 해당 CAR_ID를 날짜조건을 추가해주지 않으면 11월 달에 대여한 CAR_ID가 있게 되면 그 값도 들어가게 되기 때문에 해당 조건을 추가해준 것입니다.

-- CAR_RENTAL_COMPANY_CAR 테이블에서 '통풍시트', '열선시트', '가죽시트' 중 하나 이상의 옵션이 포함된 자동차가 
-- 자동차 종류 별로 몇 대인지 출력하는 SQL문을 작성해주세요. 
-- 이때 자동차 수에 대한 컬럼명은 CARS로 지정하고, 결과는 자동차 종류를 기준으로 오름차순 정렬해주세요.

-- 틀린 코드
SELECT CAR_TYPE, COUNT(*) CARS
FROM CAR_RENTAL_COMPANY_CAR
WHERE OPTIONS IN ('%통풍시트%', '%열선시트%', '%가죽시트%')
GROUP BY CAR_TYPE
ORDER BY 1
-- IN 연산자는 정확히 일치하는 값을 찾을 때 사용되므로, 부분 일치를 표현하기 위해서는 LIKE 조건과 함께 사용해야 합니다.

SELECT CAR_TYPE, COUNT(*) AS CARS
FROM CAR_RENTAL_COMPANY_CAR
WHERE OPTIONS LIKE '%통풍시트%' 
   OR OPTIONS LIKE '%열선시트%' 
   OR OPTIONS LIKE '%가죽시트%'
GROUP BY CAR_TYPE
ORDER BY CAR_TYPE ASC;

-- 상반기 동안 각 아이스크림 성분 타입과 성분 타입에 대한 아이스크림의 총주문량을 총주문량이 
-- 작은 순서대로 조회하는 SQL 문을 작성해주세요. 이때 총주문량을 나타내는 컬럼명은 TOTAL_ORDER로 지정해주세요.
SELECT B.INGREDIENT_TYPE, SUM(A.TOTAL_ORDER) AS TOTAL_ORDER
FROM FIRST_HALF AS A
NATURAL JOIN ICECREAM_INFO AS B
GROUP BY INGREDIENT_TYPE
ORDER BY 2

SELECT BOOK_ID, DATE_FORMAT(PUBLISHED_DATE, "%Y-%m") AS PUBLISHED_DATE
FROM BOOK AS B
WHERE CATEGORY = '인문' AND YEAR(PUBLISHED_DATE)
ORDER BY PUBLISHED_DATE ASC
-- 신기한 점. "%Y-%M" 이라고 하면 월이 영문으로 나옴. m으로 해야 숫자 월이 나옴

SELECT COUNT(*) AS COUNT
FROM ECOLI_DATA
WHERE (GENOTYPE & 2) = 0  -- 2번 형질이 없는 경우 (2진수에서 2는 10₍₂₎)
AND (GENOTYPE & 1 <> 0 OR GENOTYPE & 4 <> 0);  -- 1번 형질(1₍₂₎) 또는 3번 형질(100₍₂₎)이 있는 경우