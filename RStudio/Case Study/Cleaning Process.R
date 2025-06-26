#load packages
library(tidyverse)
library(readr)
library(data.table)
library(lubridate)
library(writexl)
library(readxl)

setwd("C:\\Users\\caitl\\OneDrive\\Documents\\RStudio\\Case Study")


#read into variable
q1_2019 <- read_csv("2019_Q1.csv")
q2_2019 <- read_csv("2019_Q2.csv")
q3_2019 <- read_csv("2019_Q3.csv")
q4_2019 <- read_csv("2019_Q4.csv")

# change q2 column names to match q1, q3, and q4
q2_2019 <- rename(q2_2019,
                  trip_id = `01 - Rental Details Rental ID`,
                  start_time = `01 - Rental Details Local Start Time`,
                  end_time = `01 - Rental Details Local End Time`,
                  bikeid = `01 - Rental Details Bike ID`,
                  tripduration = `01 - Rental Details Duration In Seconds Uncapped`,
                  from_station_id = `03 - Rental Start Station ID`,
                  from_station_name = `03 - Rental Start Station Name`,
                  to_station_id = `02 - Rental End Station ID`,
                  to_station_name = `02 - Rental End Station Name`,
                  usertype = `User Type`,
                  gender = `Member Gender`,
                  birthyear = `05 - Member Details Member Birthday Year`)



#aggreate into one dataframe
totaltrips <- bind_rows(q1_2019, q2_2019, q3_2019, q4_2019)

View(totaltrips)

#remove previous data frame
rm(q1_2019)
rm(q2_2019)
rm(q3_2019)
rm(q4_2019)


#remove any rows with negative times or times equal to 0 seconds
totaltrips <- totaltrips[which(totaltrips$tripduration > 0)]



#count how many nulls in each row to determine if significant
count(totaltrips[is.na(totaltrips$trip_id),])
count(totaltrips[is.na(totaltrips$start_time),])
count(totaltrips[is.na(totaltrips$end_time),])
count(totaltrips[is.na(totaltrips$tripduration),])
count(totaltrips[is.na(totaltrips$from_station_id),])
count(totaltrips[is.na(totaltrips$from_station_name),])
count(totaltrips[is.na(totaltrips$to_station_id),])
count(totaltrips[is.na(totaltrips$to_station_name),])
count(totaltrips[is.na(totaltrips$usertype),])
count(totaltrips[is.na(totaltrips$gender),])
count(totaltrips[is.na(totaltrips$birthyear),])


# "gender" column has 559206 null values and "birthyear" has 538751 null values. the rest have none. 


#ensure "usertype" column only has "Subscriber" and "Customer" 

unique(totaltrips$usertype)

#change "Subscriber" to "member" and "Customer" to "casual"

totaltrips <- totaltrips %>% 
  mutate(usertype = recode(usertype, "Subscriber" = "member",
                           "Customer" = "casual"))



# add "month" column 

totaltrips$month <- format(as.Date(totaltrips$start_time), "%m")

#create "weekday" columns for days of the week
totaltrips$weekday <- weekdays(as.Date(totaltrips$start_time))

# ensure data types in each row are as expected
str(totaltrips)

#export clean data to a new .csv file

write.csv(totaltrips, "totaltrips.csv")


