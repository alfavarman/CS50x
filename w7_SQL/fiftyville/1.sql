-- SELECT id, description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street LIKE "Humphrey%";

-- -- --------------------------------------------------------------------------+
-- -- | id  |                                                                                                       description                                                                                                        |
-- -- +-----+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- -- | 295 | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
-- -- | 297 | Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
-- -- +-----+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

-- SELECT interviews.name, interviews.transcript, CSR.description, CSR.id, atm.account_number, atm.atm_location, atm.transaction_type, atm.amount, f.origin_airport_id, f.destination_airport_id FROM interviews
-- INNER JOIN crime_scene_reports AS CSR ON CSR.year = interviews.year AND CSR.month = interviews.month AND CSR.day = interviews.day
-- INNER JOIN atm_transactions AS atm ON atm.year = interviews.year AND atm.month = interviews.month AND atm.day = interviews.day
-- INNER JOIN flights AS f ON f.year = interviews.year AND f.month = interviews.month AND f.day = interviews.day
-- WHERE interviews.year = 2021 AND interviews.month = 7 AND interviews.day = 28;

-- SELECT name, transcript, id FROM interviews
-- WHERE interviews.year = 2021 AND interviews.month = 7 AND interviews.day = 28;

-- -- |  name   |                                                                                                                                                     transcript                                                                                                                                                      |
-- -- +---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- -- | Jose    | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”                                                                                                                               |
-- -- | Eugene  | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”                                                                                                                                                                                      |
-- -- | Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.                                                                                                                   |
-- -- | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- -- | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- -- | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
-- -- | Lily    | Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city far, far away, so it may never bother us again. My sons have successfully arrived in Paris.                                                                        |
-- -- +---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

-- crime 10:15

-- German accent                                                                                                                   |
-- ten minutes of the theft get into a car in the bakery parking lot and drive away 28 7 2021 10:25

-- SELECT activity, license_plate, minute FROM bakery_security_logs
-- WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND  minute < 30 AND minute > 20;

-- fiftyville/ $ cat 1.sql | sqlite3 fiftyville.db
-- +----------+---------------+--------+
-- | activity | license_plate | minute |
-- +----------+---------------+--------+
-- | exit     | L93JTIZ       | 21     |
-- | exit     | 322W7JE       | 23     |
-- | exit     | 0NTHK55       | 23     |
-- +----------+---------------+--------+


-- -- Earlier this morning  the ATM on Leggett Street withdraw  28 7 2021  less than 10:15
-- SELECT atm_transactions.id, atm_transactions.account_number, atm_transactions.transaction_type, atm_transactions.amount, bank_accounts.person_id, bank_accounts.creation_year, people.*
-- FROM atm_transactions
-- INNER JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
-- INNER JOIN people ON bank_accounts.person_id = people.id
-- WHERE atm_transactions.year = 2021
--   AND atm_transactions.month = 7
--   AND atm_transactions.day = 28
--   AND atm_transactions.transaction_type = 'withdraw'
--   AND atm_transactions.atm_location = 'Leggett Street';
-- -- +-----+----------------+------------------+--------+-----------+---------------+--------+---------+----------------+-----------------+---------------+
-- -- | id  | account_number | transaction_type | amount | person_id | creation_year |   id   |  name   |  phone_number  | passport_number | license_plate |
-- -- +-----+----------------+------------------+--------+-----------+---------------+--------+---------+----------------+-----------------+---------------+
-- -- | 267 | 49610011       | withdraw         | 50     | 686048    | 2010          | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- -- | 336 | 26013199       | withdraw         | 35     | 514354    | 2012          | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- -- | 269 | 16153065       | withdraw         | 80     | 458378    | 2012          | 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
-- -- | 264 | 28296815       | withdraw         | 20     | 395717    | 2014          | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
-- -- | 288 | 25506511       | withdraw         | 20     | 396669    | 2014          | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- -- | 246 | 28500762       | withdraw         | 48     | 467400    | 2014          | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- -- | 266 | 76054385       | withdraw         | 60     | 449774    | 2015          | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
-- -- | 313 | 81061156       | withdraw         | 30     | 438727    | 2018          | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
-- -- +-----+----------------+------------------+--------+-----------+---------------+--------+---------+----------------+-----------------+---------------+

-- SELECT people.name, people.phone_number
-- FROM atm_transactions
-- INNER JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
-- INNER JOIN people ON bank_accounts.person_id = people.id
-- WHERE atm_transactions.year = 2021
--   AND atm_transactions.month = 7
--   AND atm_transactions.day = 28
--   AND atm_transactions.transaction_type = 'withdraw'
--   AND atm_transactions.atm_location = 'Leggett Street'
--   AND people.phone_number IN (
--     SELECT phone_calls.caller FROM phone_calls
--     WHERE phone_calls.year = 2021
--     AND phone_calls.month = 7
--     AND phone_calls.day = 28
--     AND phone_calls.duration < 60)
--   AND people.license_plate IN (
--     SELECT license_plate FROM bakery_security_logs
--     WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND  minute < 30)
--   AND people.passport_number in (select passport_number from passengers
--     where flight_id IN (
--     SELECT flights.id from flights
--   INNER JOIN airports ON airports.id = flights.origin_airport_id
--   WHERE airports.full_name LIKE "%Fiftyville%"
--   AND flights.year = 2021
--   AND flights.month = 7
--   AND flights.day = 29
--   AND flights.hour < 11  LIMIT 1));

-- +-------+----------------+
-- | name  |  phone_number  |
-- +-------+----------------+
-- | Bruce | (367) 555-5533 |
-- +-------+----------------+

-- leaving the bakery,28 7 2021 10:15 - 10:25  outcall duration < 60 sec
-- SELECT phone_calls.caller, phone_calls.receiver FROM phone_calls
-- WHERE phone_calls.year = 2021
--   AND phone_calls.month = 7
--   AND phone_calls.day = 28
--   AND phone_calls.duration < 60;
  -- fiftyville/ $ cat 1.sql | sqlite3 fiftyville.db
-- +----------------+----------------+
-- |     caller     |    receiver    |
-- +----------------+----------------+
-- | (130) 555-0289 | (996) 555-8899 |
-- | (499) 555-9472 | (892) 555-8872 | (892) 555-8872 (717) 555-1342
-- | (367) 555-5533 | (375) 555-8161 |
-- | (499) 555-9472 | (717) 555-1342 |
-- | (286) 555-6063 | (676) 555-6554 |
-- | (770) 555-1861 | (725) 555-3243 |
-- | (031) 555-6622 | (910) 555-3251 |
-- | (826) 555-1652 | (066) 555-9701 |
-- | (338) 555-6650 | (704) 555-2131 |
-- +----------------+----------------+
-- earliest flight departure Fiftyville
-- SELECT flights.*, airports.* from flights
-- INNER JOIN airports ON airports.id = flights.origin_airport_id
-- WHERE airports.full_name LIKE "%Fiftyville%"
--   AND flights.year = 2021
--   AND flights.month = 7
--   AND flights.day = 29
--   AND flights.hour < 11;


-- fiftyville/ $ cat 1.sql | sqlite3 fiftyville.db
-- +----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-----------------------------+------------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | id | abbreviation |          full_name          |    city    |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-----------------------------+------------+
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
-- | 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     | 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+----+--------------+-----------------------------+------------+


-- SELECT activity, license_plate, minute FROM bakery_security_logs
-- WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND  minute < 30 AND minute > 20;

-- SELECT atm_transactions.id, atm_transactions.account_number, atm_transactions.transaction_type, atm_transactions.amount, bank_accounts.person_id, bank_accounts.creation_year, people.*
-- FROM atm_transactions
-- INNER JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
-- INNER JOIN people ON bank_accounts.person_id = people.id
-- WHERE atm_transactions.year = 2021
--   AND atm_transactions.month = 7
--   AND atm_transactions.day = 28
--   AND atm_transactions.transaction_type = 'withdraw'
--   AND atm_transactions.atm_location = 'Leggett Street';

-- SELECT phone_calls.caller, phone_calls.receiver FROM phone_calls
-- WHERE phone_calls.year = 2021
--   AND phone_calls.month = 7
--   AND phone_calls.day = 28
--   AND phone_calls.duration < 60;

-- SELECT flights.*, airports.* from flights
-- INNER JOIN airports ON airports.id = flights.origin_airport_id
-- WHERE airports.full_name LIKE "%Fiftyville%"
--   AND flights.year = 2021
--   AND flights.month = 7
--   AND flights.day = 29
--   AND flights.hour < 11;


-- SELECT passport_number from passengers
-- INNER JOIN flights ON flights.id = passengers.flight_id
-- WHERE flight_id IN (
--   SELECT flightsid from flights
--   INNER JOIN airports ON airports.id = flights.origin_airport_id
--   WHERE airports.full_name LIKE "%Fiftyville%"
--   AND flights.year = 2021
--   AND flights.month = 7
--   AND flights.day = 29
--   AND flights.hour < 11
--   );

-- COMBINE ALL:

-- SELECT people.name, people.phone_number FROM people
-- WHERE people.license_plate IN (
--                                 SELECT license_plate
--                                 FROM bakery_security_logs
--                                 WHERE year = 2021
--                                 AND month = 7
--                                 AND day = 28
--                                 AND hour = 10
--                                 AND  minute < 30
--                                 AND minute > 20)
-- AND people.passport_number IN (
--   SELECT passport_number from passengers
--   INNER JOIN flights ON flights.id = passengers.flight_id
--   WHERE flight_id IN (
--     SELECT flights.id from flights
--     INNER JOIN airports ON airports.id = flights.origin_airport_id
--     WHERE airports.full_name LIKE "%Fiftyville%"
--     AND flights.year = 2021
--     AND flights.month = 7
--     AND flights.day = 29
--     AND flights.hour < 9
--     ))
-- AND people.phone_number IN (
--   SELECT phone_calls.caller FROM phone_calls
--   WHERE phone_calls.year = 2021
--   AND phone_calls.month = 7
--   AND phone_calls.day = 28
--   AND phone_calls.duration < 60);


-- +--------+----------------+
-- |  name  |  phone_number  |
-- +--------+----------------+
-- | Kelsey | (499) 555-9472 |
-- +--------+----------------+

-- SELECT DISTINCT full_name, city FROM airports WHERE id = 4;
-- fiftyville/ $ cat 1.sql | sqlite3 fiftyville.db
-- +-------------------+---------------+
-- |     full_name     |     city      |
-- +-------------------+---------------+
-- | LaGuardia Airport | New York City |
-- +-------------------+---------------+


-- select name, passport_number from people
-- where phone_number = "(892) 555-8872" OR phone_number = "(717) 555-1342";
-- +---------+-----------------+
-- |  name   | passport_number |
-- +---------+-----------------+
-- | Larry   | 2312901747      |
-- | Melissa | 7834357192      |
-- +---------+-----------------+



-- select name from people
-- where phone_number = "(892) 555-8872" OR phone_number = "(717) 555-1342"
-- and passport_number in (
--   SELECT passport_number from passengers
--   where flight_id = 34);

-- fiftyville/ $ cat 1.sql | sqlite3 fiftyville.db
-- +-------+
-- | name  |
-- +-------+
-- | Larry |
-- +-------+

-- SELECT flights.*, airports.* from flights
-- INNER JOIN airports ON airports.id = flights.origin_airport_id
-- WHERE airports.full_name LIKE "%Fiftyville%"
--   AND flights.year = 2021
--   AND flights.month = 7
--   AND flights.day = 29
--   AND flights.hour < 11;



-- SELECT phone_calls.receiver FROM phone_calls
-- WHERE phone_calls.year = 2021
--   AND phone_calls.month = 7
--   AND phone_calls.day = 28
--   AND phone_calls.duration < 60
--   AND phone_calls.caller = "(367) 555-5533";


-- select name from people
-- where phone_number = (SELECT phone_calls.receiver FROM phone_calls
-- WHERE phone_calls.year = 2021
--   AND phone_calls.month = 7
--   AND phone_calls.day = 28
--   AND phone_calls.duration < 60
--   AND phone_calls.caller = "(367) 555-5533");