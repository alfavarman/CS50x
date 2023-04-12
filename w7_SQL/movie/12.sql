-- In 12.sql, write a SQL query to list the titles of all movies in which both
-- Johnny Depp and Helena Bonham Carter starred.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Johnny Depp.
-- You may assume that there is only one person in the database with the name
-- Helena Bonham Carter.


-- SELECT movies.title FROM movies
-- INNER JOIN stars ON stars.movie_id = movies.id
-- JOIN people AS jd ON stars.person_id = jd.id AND jd.name = "Johnny Depp"
-- JOIN people AS hbc ON stars.person_id = hbc.id AND hbc.name = "Helena Bonham Carter";


SELECT movies.title
FROM movies
INNER JOIN stars ON stars.movie_id = movies.id
INNER JOIN people p1 ON stars.person_id = p1.id AND p1.name = 'Johnny Depp'
INNER JOIN stars s ON s.movie_id = movies.id
INNER JOIN people p2 ON s.person_id = p2.id AND p2.name = 'Helena Bonham Carter';


-- SELECT movies.title
-- FROM movies
-- INNER JOIN stars ON stars.movie_id = movies.id
-- INNER JOIN people ON stars.person_id = people.id AND people.name = 'Johnny Depp'
-- INNER JOIN stars s ON s.movie_id = movies.id
-- INNER JOIN people p ON s.person_id = p.id AND p.name = 'Helena Bonham Carter';

