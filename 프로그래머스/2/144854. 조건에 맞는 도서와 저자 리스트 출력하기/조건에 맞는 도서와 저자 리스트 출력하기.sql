SELECT
    b.book_id,
    a.author_name,
    DATE_FORMAT(b.published_date, '%Y-%m-%d') published_date
FROM
    book b
    LEFT JOIN author a
    # USING(author_id)
    ON B.AUTHOR_ID = A.AUTHOR_ID
WHERE
    b.category = '경제'
ORDER BY
    3;