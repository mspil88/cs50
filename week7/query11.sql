/*In 11.sql, write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.*/

select a.title
from movies as a
inner join stars as b
on a.id = b.movie_id
inner join people as c
on b.person_id = c.id
inner join ratings as d
on a.id = d.movie_id
where c.name = 'Chadwick Boseman'
order by d.rating desc
limit 5;

