/*In 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.*/


create index movie_idx on movies (id);

create index movie_idx_d on directors (movie_id);

create index person_idx_d on directors (person_id);

create index person_idx on people (id);

create index movie_idx_r on ratings (movie_id);


select count(c.name)
from movies as a
inner join directors as b
on a.id = b.movie_id
inner join people as c
on b.person_id or c.id
inner join ratings as d
on a.id = d.movie_id
where d.rating >= 9;

