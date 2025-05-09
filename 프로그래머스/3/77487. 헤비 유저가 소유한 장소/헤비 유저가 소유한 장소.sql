-- 코드를 입력하세요
SELECT P.ID, P.NAME, P.HOST_ID
FROM PLACES P
WHERE P.HOST_ID IN (
SELECT PL.HOST_ID
FROM PLACES PL
GROUP BY HOST_ID
HAVING COUNT(PL.HOST_ID) > 1)
ORDER BY P.ID;