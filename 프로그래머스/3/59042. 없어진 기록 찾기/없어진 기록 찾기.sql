/*  입양을 간 기록은 있는데
    보호소에 들어온 기록이 없는 동물의 ID와 이름을 
    ID 순으로 조회
    ANIMAL_INS 테이블은 동물 보호소에 들어온 동물
    ANIMAL_OUTS 테이블은 동물 보호소에서 입양 보낸 동물의 정보 */

SELECT B.ANIMAL_ID, B.NAME
FROM ANIMAL_OUTS AS B
WHERE ANIMAL_ID IN
(SELECT B.ANIMAL_ID
 FROM ANIMAL_OUTS AS B
 LEFT JOIN ANIMAL_INS AS A
 ON B.ANIMAL_ID = A.ANIMAL_ID
 WHERE A.ANIMAL_ID IS NULL)
ORDER BY 1 ASC