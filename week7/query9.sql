/*In 9.sql, write a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year*/

select distinct c.name, c.birth
from movies as a
inner join stars as b
on a.id = b.movie_id
inner join people as c
on b.person_id = c.id
where a.year = 2004
order by c.birth;