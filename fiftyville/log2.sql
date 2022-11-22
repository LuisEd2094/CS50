-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Check all crimes and streets on the day in question without checking for Street to check if anything interesting happened
.mode column
SELECT description,  street
FROM crime_scene_reports
WHERE year = 2021
AND month = 7
and day = 28;
--Happned at 10:15

-- Check just the ones where the Street maches since other crimes don't seem to be related
.mode column
SELECT description
FROM crime_scene_reports
WHERE year = 2021
AND month = 7
AND day = 28
AND street = 'Humphrey Street';


-- Check interviews on the day of the crime
.mode column
SELECT transcript
FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28;
-- Interesting data: 1- 10 min ish after theft, got into car at the Bakery parking lot, check video camaras.
--  2- Someone heard the thief calling the accompl, said they bought the earliest flight out of town the next day (29/07) and they were told to buy the ticket. ----
-- 3 - ATM at legget street, he was witdw money

-- Start with phone call, check the format for duration to later filter out the calls, added .mode column since its better formatted

.mode column
SELECT caller, receiver
FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;



-- Check what's on table, will now filter for wtw
.mode column
SELECT atm_location, transaction_type, amount
FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28;

-- check just the wtws in Legget Street, got back several withdraws, nothing useful although maybe we can later use the amount for the tickets or something

.mode column
SELECT atm_location, transaction_type
FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND transaction_type = 'withdraw'
AND atm_location = 'Leggett Street';


-- GET licence plates of people leaving betwn 1015 and 10 25
.mode column
SELECT license_plate
FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute > 15
AND minute < 25
AND activity = 'exit';


-- Get names of people who made a call for less than a minute during theft, Sofia, Kelsey, Bruce, Kelsey, Taylor, Diana, Carina, Kenny, Benista - Possible theft

.mode column
SELECT name
FROM phone_calls
JOIN people ON
people.phone_number = phone_calls.caller
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;

-- Get names of people who got the call Jack, Larry, Robin, Melissa, James, Philip, Jaqueline, Doris, Anna-- Possible accompl

.mode column
SELECT name
FROM phone_calls
JOIN people ON
people.phone_number = phone_calls.receiver
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;

-- Get the names of suspects that left the Bakary based on license plate - Bruce Sofia Diana Kelsey Taylor

.mode column
SELECT activity, people.license_plate, minute, name
FROM bakery_security_logs
JOIN people ON
people.license_plate = bakery_security_logs.license_plate
WHERE year = 2021
AND month = 7
AND day = 28
AND activity = 'exit'
AND people.license_plate in (SELECT license_plate FROM people
where name in ('Sofia', 'Kelsey', 'Bruce', 'Kelsey' ,
'Taylor', 'Diana', 'Carina', 'Kenny', 'Benista'));


-- Get the name of poeople who got a call from one of the Suspects that we filtered through the Licence plate, and WIthdraws
-- Accmplis are now Robin James Philip
-- DO AGAIN LATER WHEN SUSPECT LIST IS SMALLER
.mode column
SELECT name
FROM phone_calls
JOIN people ON
people.phone_number = phone_calls.receiver
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60
AND phone_calls.caller IN (SELECT phone_number
FROM people
WHERE name IN ('Bruce', 'Diana', 'Taylor'));


-- GIVES YOU THE NAMES of the people that wtdw, for someme reason it wont allow me to join, but I can use the numbers to check names
-- Suspects are now Bruce Diana Taylor
.mode column
SELECT account_number, name
FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND transaction_type = 'withdraw'
AND atm_location = 'Leggett Street'
AND account_number IN (SELECT account_number
FROM bank_accounts
WHERE person_id IN (SELECT id FROM people
WHERE name in ('Bruce', 'Sofia', 'Diana', 'Kelsey', 'Taylor') ));


-- Check what info I have on Airports
.mode column
SELECT abbreviation, full_name, city
FROM airports

-- Check what info I have on Flights leaving from Fiftyville

-- GIVES destination airport ID from earliest flight leaving on the 29th
.mode column
SELECT destination_airport_id, hour
FROM flights
WHERE
day = 29
AND month = 7
AND year = 2021
AND origin_airport_id = (SELECT id
FROM airports
WHERE city = 'Fiftyville' )
ORDER BY hour ASC LIMIT 1

-- GIVES Passports of all pax on earliest flight

SELECT passport_number
FROM passengers
WHERE
flight_id =(
SELECT id
FROM flights
WHERE
day = 29
AND month = 7
AND year = 2021
AND origin_airport_id = (SELECT id
FROM airports
WHERE city = 'Fiftyville' )
ORDER BY hour ASC LIMIT 1)

-- GIVES YOU NAMES OF THE PEOPLE ON THE FLIGHT

.mode column
SELECT name
FROM people
WHERE
passport_number IN (
SELECT passport_number
FROM passengers
WHERE
flight_id =(
SELECT id
FROM flights
WHERE
day = 29
AND month = 7
AND year = 2021
AND origin_airport_id = (SELECT id
FROM airports
WHERE city = 'Fiftyville' )
ORDER BY hour ASC LIMIT 1))


-- GIVES YOU THE NAMES OF THE PEOPLE FILTERED BY SUSPECT AND ACCOMPL

.mode column
SELECT name
FROM people
WHERE
name in ('Bruce', 'Diana', 'Taylor', 'Robin', 'James', 'Philip')
AND passport_number IN (
SELECT passport_number
FROM passengers
WHERE
flight_id =(
SELECT id
FROM flights
WHERE
day = 29
AND month = 7
AND year = 2021
AND origin_airport_id = (SELECT id
FROM airports
WHERE city = 'Fiftyville' )
ORDER BY hour ASC LIMIT 1))
