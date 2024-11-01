-- CAR_RENTAL_COMPANY_CAR 테이블에서 자동차 종류가 'SUV'인 자동차들의 평균 일일 대여 요금을 출력하는 SQL문을 작성해주세요. 
-- 이때 평균 일일 대여 요금은 소수 첫 번째 자리에서 반올림하고, 컬럼명은 AVERAGE_FEE 로 지정해주세요.
SELECT ROUND(AVG(DAILY_FEE),0) AS AVERAGE_FEE
FROM CAR_RENTAL_COMPANY_CAR
GROUP BY CAR_TYPE
HAVING CAR_TYPE = 'SUV'
-- round(): 소수점을 반올림하지 않고 절사만 원한다면 TRUNC 함수를 사용해야 한다.
-- ROUND("값", "자리수")
-- round("11.11", 1) => 11.1
-- round("11.3255", 2) => 11.33
-- round("1235.32", -2) => 1200

-- ONLINE_SALE 테이블에서 동일한 회원이 동일한 상품을 재구매한 데이터를 구하여, 재구매한 회원 ID와 재구매한 상품 ID를 출력하는 SQL문을 작성해주세요. 
-- 결과는 회원 ID를 기준으로 오름차순 정렬해주시고 회원 ID가 같다면 상품 ID를 기준으로 내림차순 정렬해주세요.
SELECT DISTINCT o1.USER_ID, o1.PRODUCT_ID
FROM ONLINE_SALE o1, ONLINE_SALE o2
WHERE o1.USER_ID = o2.USER_ID 
    AND o1.PRODUCT_ID = o2.PRODUCT_ID 
    AND o1.SALES_DATE != o2.SALES_DATE
ORDER BY o1.USER_ID, o1.PRODUCT_ID DESC

-- 동물 보호소에 들어온 모든 동물의 이름과 보호 시작일을 조회하는 SQL문을 작성해주세요. 
-- 이때 결과는 ANIMAL_ID 역순으로 보여주세요. SQL을 실행하면 다음과 같이 출력되어야 합니다.
SELECT NAME, DATETIME 
FROM ANIMAL_INS 
ORDER BY ANIMAL_ID DESC;

-- 동물 보호소에 들어온 동물 중 아픈 동물1의 아이디와 이름을 조회하는 SQL 문을 작성해주세요. 이때 결과는 아이디 순으로 조회해주세요.
SELECT ANIMAL_ID, NAME
FROM ANIMAL_INS 
WHERE INTAKE_CONDITION = 'Sick'
ORDER BY ANIMAL_ID;

-- 동물 보호소에 들어온 동물 중 젊은 동물1의 아이디와 이름을 조회하는 SQL 문을 작성해주세요. 이때 결과는 아이디 순으로 조회해주세요.
SELECT ANIMAL_ID, name
FROM ANIMAL_INS
WHERE INTAKE_CONDITION != 'Aged'
ORDER BY ANIMAL_ID;

-- 동물 보호소에 들어온 모든 동물의 아이디와 이름을 ANIMAL_ID순으로 조회하는 SQL문을 작성해주세요. SQL을 실행하면 다음과 같이 출력되어야 합니다.
SELECT ANIMAL_ID, NAME
FROM ANIMAL_INS
ORDER BY ANIMAL_ID;

-- 아이템의 희귀도가 'RARE'인 아이템들의 모든 다음 업그레이드 아이템의 아이템 ID(ITEM_ID), 아이템 명(ITEM_NAME), 
-- 아이템의 희귀도(RARITY)를 출력하는 SQL 문을 작성해 주세요. 이때 결과는 아이템 ID를 기준으로 내림차순 정렬주세요.
SELECT A.ITEM_ID, A.ITEM_NAME, A.RARITY FROM ITEM_INFO A,
(SELECT D.ITEM_ID FROM ITEM_INFO B, ITEM_TREE C, ITEM_TREE D -- 업그레이드인 아이템 ID만 추출
WHERE B.ITEM_ID = C.ITEM_ID 
AND C.ITEM_ID = D.PARENT_ITEM_ID -- C의 ITEM_ID와 D의 PARENT_ITEM_ID 조인
AND B.RARITY ='RARE' -- 조건은 RARE
) E
WHERE A.ITEM_ID = E.ITEM_ID
ORDER BY A.ITEM_ID DESC -- 정렬조건은 ITEM_ID 내림차순

SELECT ITEM_ID, ITEM_NAME, RARITY FROM ITEM_INFO 
 WHERE ITEM_ID IN
 (SELECT ITEM_ID FROM ITEM_TREE WHERE PARENT_ITEM_ID IN  -- 2) 
  (SELECT ITEM_ID FROM ITEM_INFO WHERE RARITY = 'RARE') -- 1) 
 ) 
  ORDER BY ITEM_ID DESC

-- 상반기 아이스크림 총주문량이 3,000보다 높으면서 아이스크림의 주 성분이 과일인 아이스크림의 맛을 총주문량이 큰 순서대로 조회하는 SQL 문을 작성해주세요.
SELECT  A.FLAVOR
FROM  FIRST_HALF AS A
JOIN  ICECREAM_INFO AS B
ON  A.FLAVOR = B.FLAVOR
WHERE  A.TOTAL_ORDER > 3000 AND B.INGREDIENT_TYPE = 'FRUIT_BASED'
ORDER BY  A.TOTAL_ORDER DESC;

-- MEMBER_PROFILE 테이블에서 생일이 3월인 여성 회원의 ID, 이름, 성별, 생년월일을 조회하는 SQL문을 작성해주세요. 
-- 이때 전화번호가 NULL인 경우는 출력대상에서 제외시켜 주시고, 결과는 회원ID를 기준으로 오름차순 정렬해주세요.
SELECT MEMBER_ID, MEMBER_NAME, GENDER, SUBSTRING(DATE_OF_BIRTH, 1, 10) AS DATE_OF_BIRTH
FROM MEMBER_PROFILE
WHERE SUBSTRING(DATE_OF_BIRTH, 6, 2) = '03'  -- 월이 3월인 경우
  AND TLNO IS NOT NULL
  AND GENDER = 'W'
ORDER BY MEMBER_ID ASC;

-- REST_INFO와 REST_REVIEW 테이블에서 서울에 위치한 식당들의 식당 ID, 식당 이름, 음식 종류, 즐겨찾기수, 주소, 리뷰 평균 점수를 조회하는 SQL문을 작성해주세요. 
-- 이때 리뷰 평균점수는 소수점 세 번째 자리에서 반올림 해주시고 결과는 평균점수를 기준으로 내림차순 정렬해주시고, 평균점수가 같다면 즐겨찾기수를 기준으로 내림차순 정렬해주세요.
SELECT I.REST_ID, REST_NAME, FOOD_TYPE, FAVORITES, ADDRESS, ROUND(AVG(REVIEW_SCORE),2) AS SCORE
FROM REST_INFO I
JOIN REST_REVIEW R
ON I.REST_ID = R.REST_ID
WHERE ADDRESS LIKE '서울%'
GROUP BY I.REST_ID
ORDER BY SCORE DESC, FAVORITES DESC
-- GROUP BY REST_INFO.REST_ID, REST_NAME, FOOD_TYPE, FAVORITES, ADDRESS: AVG(REVIEW_SCORE)를 사용하므로 그룹화가 필요합니다. 각 식당별로 그룹화하여 평균 평점을 계산합니다.

-- DOCTOR 테이블에서 진료과가 흉부외과(CS)이거나 일반외과(GS)인 의사의 이름, 의사ID, 진료과, 고용일자를 조회하는 SQL문을 작성해주세요. 
-- 이때 결과는 고용일자를 기준으로 내림차순 정렬하고, 고용일자가 같다면 이름을 기준으로 오름차순 정렬해주세요.
SELECT DR_NAME, DR_ID, MCDP_CD, SUBSTRING(HIRE_YMD, 1, 10) AS HIRE_YMD
FROM DOCTOR
WHERE MCDP_CD = 'CS' OR MCDP_CD = 'GS'
ORDER BY HIRE_YMD DESC, DR_NAME ASC;

-- ONLINE_SALE 테이블과 OFFLINE_SALE 테이블에서 2022년 3월의 오프라인/온라인 상품 판매 데이터의 판매 날짜, 상품ID, 유저ID, 판매량을 출력하는 SQL문을 작성해주세요. 
-- OFFLINE_SALE 테이블의 판매 데이터의 USER_ID 값은 NULL 로 표시해주세요. 
-- 결과는 판매일을 기준으로 오름차순 정렬해주시고 판매일이 같다면 상품 ID를 기준으로 오름차순, 상품ID까지 같다면 유저 ID를 기준으로 오름차순 정렬해주세요.
SELECT DATE_FORMAT(SALES_DATE,'%Y-%m-%d') SALES_DATE, 
       PRODUCT_ID, 
       USER_ID, 
       SALES_AMOUNT
FROM   ONLINE_SALE
WHERE  SALES_DATE LIKE '2022-03%'
UNION
SELECT DATE_FORMAT(SALES_DATE,'%Y-%m-%d') SALES_DATE, 
       PRODUCT_ID, 
       NULL,
       SALES_AMOUNT
FROM   OFFLINE_SALE
WHERE  SALES_DATE LIKE '2022-03%'
-- ORDER BY 1, 2, 3
ORDER BY SALES_DATE ASC, PRODUCT_ID ASC, USER_ID ASC;

-- UNION VS. JOIN
-- 오프라인 및 온라인 데이터를 단순히 JOIN으로 결합하면, 각각의 개별 판매 데이터가 모두 결합되지 않고, 조건에 맞는 항목들만 결합될 것입니다.
-- 오프라인 및 온라인 판매 데이터를 통합하려면 **UNION ALL**을 사용하는 것이 더 적합합니다. UNION ALL을 사용하면 두 테이블의 데이터를 모두 병합할 수 있습니다.

-- 3세대의 대장균의 ID(ID) 를 출력하는 SQL 문을 작성해주세요. 이때 결과는 대장균의 ID 에 대해 오름차순 정렬해주세요.
SELECT C.ID
FROM ECOLI_DATA A
LEFT JOIN ECOLI_DATA B ON B.PARENT_ID = A.ID
LEFT JOIN ECOLI_DATA C ON C.PARENT_ID = B.ID
WHERE A.PARENT_ID IS NULL
AND C.ID IS NOT NULL
ORDER BY C.ID ASC;

-- LEFT JOIN
-- LEFT JOIN은 왼쪽 테이블의 모든 행을 반환하고, **오른쪽 테이블에서 일치하는 항목이 없는 경우 NULL**로 표시합니다.
-- 주로, 하나의 테이블에 있는 모든 데이터를 유지하면서 추가 정보를 가져오고자 할 때 사용됩니다.
-- A의 데이터를 다 가져오고 B만 일부만 가져옴. 그 다음은 테이블을 다 가져오고 C와 ID가 같은 행만 또 데려옴.

-- 각 세대별 자식이 없는 개체의 수(COUNT)와 세대(GENERATION)를 출력하는 SQL문을 작성해주세요. 
-- 이때 결과는 세대에 대해 오름차순 정렬해주세요. 단, 모든 세대에는 자식이 없는 개체가 적어도 1개체는 존재합니다.
WITH RECURSIVE cte AS (SELECT id, parent_id, 1 AS gen
                       FROM ecoli_data
                       WHERE parent_id IS NULL

                       UNION ALL

                       SELECT e.id, e.parent_id, cte.gen + 1 AS gen
                       FROM ecoli_data e
                                JOIN cte ON cte.id = e.parent_id)
SELECT COUNT(a.id) AS 'COUNT', a.gen AS generation
FROM cte a
         LEFT JOIN cte b ON a.id = b.parent_id
WHERE b.id IS NULL
GROUP BY a.gen
ORDER BY a.gen

-- 첫 번째 SELECT (기초 케이스):
-- SELECT id, parent_id, 1 AS gen:
-- ecoli_data 테이블에서 부모 ID가 NULL인 개체(즉, 루트 개체)들을 선택합니다.
-- 이 개체들은 첫 번째 세대 (세대 1)로 간주되고, gen 컬럼에 1을 할당합니다.

-- 두 번째 SELECT (재귀적 부분):
-- UNION ALL을 사용하여 이전의 결과와 결합합니다.
-- 여기서 ecoli_data의 각 개체 e에 대해, CTE에서 부모 개체(cte)와 조인하여 자식 개체를 찾습니다.
-- cte.gen + 1 AS gen을 통해 자식 개체의 세대를 증가시킵니다. 즉, 부모의 세대에 1을 더해 새로운 세대를 계산합니다.
-- 이 과정을 통해 모든 세대의 개체들이 재귀적으로 탐색됩니다.

-- LEFT JOIN:

-- CTE a와 b를 조인합니다. 여기서 a는 부모 개체이고, b는 자식 개체입니다.
-- ON a.id = b.parent_id 조건을 통해 a 개체에 대해 b 개체가 자식인지 확인합니다.
-- 자식이 없는 개체 필터링:

-- WHERE b.id IS NULL 조건을 통해 자식이 없는 개체(즉, b에서 매칭되는 개체가 없는 경우)만 선택합니다.
-- COUNT와 GROUP BY:

-- COUNT(a.id) AS 'COUNT'를 사용하여 자식이 없는 개체의 수를 세고, a.gen으로 세대 정보를 가져옵니다.
-- GROUP BY a.gen을 통해 각 세대별로 개체 수를 집계합니다.
-- 정렬:

-- ORDER BY a.gen을 통해 결과를 세대별로 오름차순 정렬합니다.

SELECT B.TITLE,B.BOARD_ID,R.REPLY_ID,R.WRITER_ID,R.CONTENTS,
        DATE_FORMAT(R.CREATED_DATE,'%Y-%m-%d') AS CREATED_DATE
       --  SUBSTR(R.CREATED_DATE, 1, 10) AS CREATED_DATE
FROM USED_GOODS_BOARD AS B
JOIN USED_GOODS_REPLY AS R 
ON R.BOARD_ID = B.BOARD_ID
WHERE DATE_FORMAT(B.CREATED_DATE,'%Y-%m') = '2022-10'
ORDER BY R.CREATED_DATE,B.TITLE;

