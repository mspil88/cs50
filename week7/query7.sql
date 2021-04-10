/*In 7.sql, write a SQL query to list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title*/

select a.title, b.rating
from movies as a
inner join ratings as b
on a.id = b.movie_id
where a.year = 2010
order by b.rating, a.title;

