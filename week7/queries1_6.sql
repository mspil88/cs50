/* question 1*/
select title from movies where year = 2008;

/*question 2*/

select birth from people where name = 'Emma Stone';

/*question 3*/

select title from movies where year >= 2018 order by title;

/*question 4*/

select count(distinct(movie_id)) from ratings where rating == 10;

/*question 5*/

select title, year  from movies where title like 'Harry Potter%' order by year;

/*question 6*/
select avg(b.rating) from movies as a 
inner join ratings as b
on a.id = b.movie_id
where a.year = 2012;


