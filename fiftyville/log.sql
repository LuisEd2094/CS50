-- Check just the ones where the Street maches
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

-- Get all WITHDRAW in the same day of crime
.mode column
SELECT account_number
FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND transaction_type = 'withdraw'
AND atm_location = 'Leggett Street';

-- GET ID FROM PEOPLE WHI WITDREW THAT DAY
.mode column
SELECT person_id
FROM bank_accounts
WHERE account_number IN (SELECT account_number
FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND transaction_type = 'withdraw'
AND atm_location = 'Leggett Street')

-- GET NAME of person who made call within time frame, left bakery and made a withdraw
.mode column
SELECT name
FROM people
WHERE
license_plate in (SELECT license_plate
FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute > 15
AND minute < 25
AND activity = 'exit')

AND phone_number in (SELECT phone_number
FROM phone_calls
JOIN people ON
people.phone_number = phone_calls.caller
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60)
AND id IN(SELECT person_id
FROM bank_accounts
WHERE account_number IN (SELECT account_number
FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND transaction_type = 'withdraw'
AND atm_location = 'Leggett Street'))

-- Bruce and Diana


-- GET fiftyville airport ID

SELECT id
FROM airports
WHERE city = 'Fiftyville'

-- GET ID of first flight leaving on 29th from Fiftyville

SELECT id
FROM flights
WHERE
origin_airport_id IN (SELECT id
FROM airports
WHERE city = 'Fiftyville')
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour ASC
LIMIT 1

-- GET PASSPORTS FROM PEOPLE TRAVELING ON FIRST FLIGHT

SELECT passport_number
FROM passengers
WHERE flight_id = (SELECT id
FROM flights
WHERE
origin_airport_id IN (SELECT id
FROM airports
WHERE city = 'Fiftyville')
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour ASC
LIMIT 1)

-- GET BRUCE AS ONLY SUSCPECT FROM LICENSE, CALLS, ATM AND FLIGHT NEXT DAY

.mode column
SELECT name
FROM people
WHERE
passport_number IN (SELECT passport_number
FROM passengers
WHERE flight_id = (SELECT id
FROM flights
WHERE
origin_airport_id IN (SELECT id
FROM airports
WHERE city = 'Fiftyville')
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour ASC
LIMIT 1)
)
AND name IN (SELECT name
FROM people
WHERE
license_plate in (SELECT license_plate
FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute > 15
AND minute < 25
AND activity = 'exit')

AND phone_number in (SELECT phone_number
FROM phone_calls
JOIN people ON
people.phone_number = phone_calls.caller
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60)
AND id IN(SELECT person_id
FROM bank_accounts
WHERE account_number IN (SELECT account_number
FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND transaction_type = 'withdraw'
AND atm_location = 'Leggett Street')) )



-- GET NAME of PERSON who Bruce Called! Robin
SELECT name
FROM people
WHERE phone_number in (SELECT receiver
FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60
AND caller in (SELECT phone_number
FROM people
WHERE
passport_number IN (SELECT passport_number
FROM passengers
WHERE flight_id = (SELECT id
FROM flights
WHERE
origin_airport_id IN (SELECT id
FROM airports
WHERE city = 'Fiftyville')
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour ASC
LIMIT 1)
)
AND name IN (SELECT name
FROM people
WHERE
license_plate in (SELECT license_plate
FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute > 15
AND minute < 25
AND activity = 'exit')

AND phone_number in (SELECT phone_number
FROM phone_calls
JOIN people ON
people.phone_number = phone_calls.caller
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60)
AND id IN(SELECT person_id
FROM bank_accounts
WHERE account_number IN (SELECT account_number
FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND transaction_type = 'withdraw'
AND atm_location = 'Leggett Street')) )
))


-- GET NAME OF CITY HE FLEW TO

.mode column
SELECT city
FROM airports
WHERE id = (SELECT destination_airport_id
FROM flights
WHERE
origin_airport_id IN (SELECT id
FROM airports
WHERE city = 'Fiftyville')
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour ASC
LIMIT 1
)