SELECT dept, gender, emp_id, marathon_rank
FROM (
    SELECT 
        dept,
        gender,
        emp_id,
        marathon_rank,
        ROW_NUMBER() OVER (
            PARTITION BY dept, gender
            ORDER BY marathon_rank ASC
        ) AS rn
    FROM marathon_results
) t
WHERE rn = 1;
----------------------------------------------

GROUP BY vs PARTITION BY 차이

GROUP BY — 행을 합쳐서 집계
sqlSELECT dept, COUNT(*) 
FROM marathon_results
GROUP BY dept;
dept  | COUNT(*)
------|--------
HR    | 5        ← 5명이 1행으로 합쳐짐
IT    | 3

그룹당 1행만 나옴 → 개인 emp_id 못 가져옴


PARTITION BY — 행 유지하면서 그룹 정보 추가
sqlSELECT dept, emp_id, marathon_rank,
       ROW_NUMBER() OVER (PARTITION BY dept ORDER BY marathon_rank)
FROM marathon_results;
dept  | emp_id | marathon_rank | rn
------|--------|---------------|----
HR    | A001   | 5             | 1   ← HR에서 1등
HR    | A002   | 8             | 2
HR    | A003   | 12            | 3
IT    | B001   | 2             | 1   ← IT에서 1등
IT    | B002   | 7             | 2

행이 그대로 유지 → emp_id도 같이 뽑을 수 있음


결론

부서별 1등 한 명씩 뽑으려면 PARTITION BY 써야 해요.
GROUP BY는 emp_id처럼 개인 정보를 같이 못 가져오는 게 근본적인 한계입니다.