-- In 13.sql, write a SQL query to list the names of all people who starred in a
-- movie in which Kevin Bacon also starred.
-- Your query should output a table with a single column for the name of each person.
-- There may be multiple people named Kevin Bacon in the database.
-- Be sure to only select the Kevin Bacon born in 1958.
-- Kevin Bacon himself should not be included in the resulting list.

-- helper queries:
-- SELECT people.id FROM people
-- WHERE people.birth = 1958 AND people.name = "Kevin Bacon";


-- SELECT movies.id FROM movies
-- INNER JOIN stars AS kbsm ON kbsm.movie_id = movies.id AND kbsm.person_id = (SELECT people.id FROM people
-- WHERE people.birth = 1958 AND people.name = "Kevin Bacon")

-- SELECT people.name FROM people
-- INNER JOIN stars AS s ON s.person_id AND s.movie_id = (
--     SELECT movies.id FROM movies
--     INNER JOIN stars AS kbsm ON kbsm.movie_id = movies.id AND kbsm.person_id = (
--         SELECT people.id FROM people
--         WHERE people.birth = 1958 AND people.name = "Kevin Bacon")
-- );

SELECT people.name FROM people
INNER JOIN stars AS s ON s.person_id = people.id
INNER JOIN movies AS m ON m.id = s.movie_id
INNER JOIN stars AS kb ON kb.movie_id = m.id
INNER JOIN people AS kb_person ON kb_person.id = kb.person_id
WHERE kb_person.name = 'Kevin Bacon' AND kb_person.birth = 1958 AND people.name != 'Kevin Bacon';