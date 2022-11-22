SELECT destination_airport_id
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