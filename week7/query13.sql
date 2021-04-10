

select distinct c.name
from movies as a
inner join stars as b
on a.id = b.movie_id
inner join people as c
on b.person_id = c.id
inner join (

select a.title, a.id
from movies as a
inner join stars as b
on a.id = b.movie_id
inner join people as c
on b.person_id = c.id
where c.name = 'Kevin Bacon' and c.birth = 1958
) as d
on a.title = d.title
and a.id = d.id
where c.name != 'Kevin Bacon'
;