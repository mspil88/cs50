/*In 8.sql, write a SQL query to list the names of all people who starred in Toy Story*/

select c.name
from movies as a
inner join stars as b
on a.id = b.movie_id
inner join people as c
on b.person_id = c.id
where a.title = 'Toy Story';