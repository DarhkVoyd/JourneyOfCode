-- Keep a log of any SQL queries you execute as you solve the mystery.

--Starting with the crime scene reports to gather leads
select * from crime_scene_reports where year = 2021 and month = 7 and day = 28;

--Gathered 3 leads that are: 1. Left Parking in Car within 10 minutes of theft 2. Theft was at Leggett Street ATM the morning withdrawing money 3. Took the earliest flight next day out of city

--Drafting First Suspect List i.e of people who were at Leggett Street ATM in the morning withdrawing money
select * from people where id IN (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where day = 28 and month = 7 and year = 2021 and atm_location = "Leggett Street" and transaction_type = "withdraw"));

--Drafting Second Suspecdt List i.e of people who left the city in earliest flight next day
select * from flights where day = 29 and month = 7 and year = 2021;
--The earliest flight was at 8 hours 20 minutes. Next Checking from where to where this flight travels
select * from airports where id = 8;
select * from airports where id = 4;
--Now we know our Theif escaped in this flight to New York
--Now checking the passengers who travelled in this flight
select * from people where passport_number in (select passport_number from passengers where flight_id = 36);

-- After Drafting the second suspect list we narrow our suspects by matching it with our first suspect list. Now we have only Four suspects 1. Kenny 2. Taylor 3. Luca 4. Bruce
-- Drafting Third Suspect List i.e people who called around the day on theft for less than a minute for narrowing the suspect list (Kenny Not Suspect anymore as he did not call anyone)
select name from people where phone_number in (select caller from phone_calls where day = 28 and month = 7 and year = 2021 and duration < 60);
-- Drafting Accomplice Suspect List i.e. people who possible suspects called (Bruce called Robin & Taylor called Jack)
select name from people where phone_number in (select receiver from phone_calls where day = 28 and month = 7 and year = 2021 and duration < 60);
-- Lastly finding our Theif i.e the suspect who's car was at the bakery and left around the time of theft (Bruce's car left around the time of theft)
select name from people where license_plate in (select license_plate from bakery_security_logs where day = 28 and month = 7 and year = 2021 and hour = 10);
-- The Theif comes out to be Bruce (as in Bruce Wayne from Batman) who left to New York City with the help of his accomplice Robin (This was fun! :))
-- CS50 has been wonderful, I dream to visit and attend a live class someday in the near future.