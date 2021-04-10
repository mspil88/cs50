/*In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.*/


select distinct title
from
(select *, row_number() over (partition by title order by title) as rn
from movies as a
inner join stars as b
on a.id = b.movie_id
inner join people as c
on b.person_id = c.id
where c.name = 'Johnny Depp' or c.name = 'Helena Bonham Carter')
where rn =2;


