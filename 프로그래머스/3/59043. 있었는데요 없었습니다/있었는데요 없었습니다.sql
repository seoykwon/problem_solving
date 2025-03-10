select
    ai.ANIMAL_ID,
    ao.NAME
from ANIMAL_INS as ai
join ANIMAL_OUTS  as ao
on ai.ANIMAL_ID = ao.ANIMAL_ID
where ai.DATETIME > ao.DATETIME
order by ai.DATETIME;