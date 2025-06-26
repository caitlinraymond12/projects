The topic for this case study was given as a final capstone project for the Google Data Analytics course. All the cleaning, analysis, interpretations, and work is my own. 


# Overview

This case study focuses on a fictional bike sharing company called Cyclistic, and the objective is to convert casual riders into annual members, who are more profitable for the company. My goal is to discover the differences between these two customers and give recommendations to the marketing department on how to target casual riders and convince them to become annual members. 

In this case study, I will be following the Ask, Prepare, Process, Analyze, Share, and Act steps in the data analysis process. 

## Ask

What is the problem that is trying to be solved?

Cyclistic has a large number of customers, and has been able to bring in so many new users because they offer flexible passes. Because Cyclistic already has so many customers, our goal isn’t to bring in any new customers, but to convert existing casual riders into annual members. Casual riders are defined as customers that purchase single-use or daily passes, and annual members are those that purchase annual passes. 

The question I will be investigating in this study is:

_In what ways do annual members and casual riders differ and why would a casual rider become an annual member?_

The business task is to implement a successful marketing campaign that targets casual riders and influences them to purchase an annual membership. The way this business task will be completed will be investigating data on the riders and finding the key differences between the two types and comparing them. 

The insights found can drive business decisions as we can use that information to group similarities between the annual members, and answer the question why a casual rider might benefit from becoming an annual member. 

Key stakeholders to keep in mind during this process are the Cyclistic marketing analytics team and the Cyclistic executive team.

## Prepare 

The data that has been used in the following study has been collected over the course of 2019,  and has been made publicly available by Motivate International Inc. Each dataset contains hundreds of thousands of rows of data, and although there are some missing / incorrect values, the majority of data is present and reliable. 

The data is stored in .csv files, and split into Q1, Q2, Q3, and Q4 of 2019. 

This data will help investigate the difference between casual riders and annual members. It includes data such as:
* Start Time
* End Time
* Trip Duration
* Start Station
* End Station 
* User Type
* Gender
* Birthyear

 These different pieces of information can be used to paint a picture of a casual rider and of an annual member to clearly highlight the differences between the two. 



## Process

In order to process the data, I will be using RStudio to clean the data, document the cleaning process, and export a new dataset with only clean and correct values. 

```
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

#remove previous data frames
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

#create "weekday" columns for days of the week
totaltrips$weekday <- weekdays(as.Date(totaltrips$start_time))

#add "month" column 
totaltrips$month <- format(as.Date(totaltrips$start_time), "%m")

#ensure data types in each row are as expected
str(totaltrips)

#export clean data to a new .csv file

write.csv(totaltrips, "totaltrips.csv")
```

The following cleaning steps were taken:

* Rename all of Q2’s variables to match Q1, Q3, and Q4’s variables.
* Combine four datasets into just one dataset.
* Remove any rows with negative times or times equal to 0. 
* Change usertype “Subscriber” to “member”
* Change usertype “Customer” to “casual”
* Add weekday column
* Add month column


The only nulls were found in the gender and birth year row. We won’t remove the rows from the entire dataset, because other parts of their data will be important, but we will keep in mind that they are missing a bit of their data when examining gender and birth year more closely. 


## Analyze 

The focus of this stage is to dive deep into the data. It is important to find relationships between the data and mark anything unusual that could be useful to solving the business problem and answering the question: 

_In what ways do annual members and casual riders differ and why would a casual rider become an annual member?_

To begin, load in appropriate packages and read totaltrips.csv into a variable.

```
#load packages
library(tidyverse)
library(readr)
library(data.table)
library(lubridate)
library(writexl)
library(readxl)

#read into variable
totaltrips <- read_csv("totaltrips.csv")
```

Trip Duration Stats:

```
# Overall stats for all trips 
summary(totaltrips)

# Trip duration stats for casual riders and members
max_usertype <- aggregate(totaltrips$tripduration, list(totaltrips$usertype), "max")
max_usertype

avg_usertype <- aggregate(totaltrips$tripduration, list(totaltrips$usertype), "mean")
avg_usertype

min_usertype <- aggregate(totaltrips$tripduration, list(totaltrips$usertype), "min")
min_usertype
```

Age Stats:

```
# Age stats for casual riders and members 
max_bday <- aggregate(totaltrips$birthyear, list(totaltrips$usertype), "max", na.rm = TRUE)
max_bday

avg_bday <- aggregate(totaltrips$birthyear, list(totaltrips$usertype), "mean", na.rm = TRUE)
avg_bday

min_bday <- aggregate(totaltrips$birthyear, list(totaltrips$usertype), "min", na.rm = TRUE)
min_bday
```

Weekly Stats:

```
# put days of week in order
totaltrips$weekday <- ordered(totaltrips$weekday, levels=c("Sunday", "Monday",
                                                           "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"))

# Find average time per day of week split by member / casual 

weekday_means <- aggregate(totaltrips$tripduration ~ totaltrips$usertype + totaltrips$weekday,
          FUN = mean)

weekday_max <- aggregate(totaltrips$tripduration ~ totaltrips$usertype + totaltrips$weekday,
                           FUN = max)

weekday_min <- aggregate(totaltrips$tripduration ~ totaltrips$usertype + totaltrips$weekday,
                           FUN = min)
```

Count Totals:

```
# count total men/ woman 

member_female_count <- nrow(totaltrips[totaltrips$gender == 'Female' & totaltrips$usertype == 'member',])
casual_female_count <- nrow(totaltrips[totaltrips$gender == 'Female' & totaltrips$usertype == 'casual',])
total_female_count <- nrow(totaltrips[totaltrips$gender == 'Female',])

member_male_count <- nrow(totaltrips[totaltrips$gender == 'Male' & totaltrips$usertype == 'member',])
casual_male_count <- nrow(totaltrips[totaltrips$gender == 'Male' & totaltrips$usertype == 'casual',])
total_male_count <- nrow(totaltrips[totaltrips$gender == 'Male',])

#count total member/casual

member_count <- nrow(totaltrips[totaltrips$usertype == 'member',])

casual_count <- nrow(totaltrips[totaltrips$usertype == 'casual',])

#count rides by days of week member / casual 

count_dayofweek <- totaltrips %>%
  group_by(usertype, weekday) %>% 
  summarise(n = n())
count_dayofweek
```
Assign Stats to Unique Variables:

```
#all the summary statistics

member_max = max_usertype[[2]][[2]]
member_min = min_usertype[[2]][[2]]
member_mean = avg_usertype[[2]][[2]]

casual_max = max_usertype[[2]][[1]]
casual_min = min_usertype[[2]][[1]]
casual_mean = avg_usertype[[2]][[1]]

member_count
casual_count

weekday_max
weekday_means
weekday_min
count_dayofweek

casual_female_count
member_female_count
total_female_count

casual_male_count
member_male_count
total_male_count

avg_bday
min_bday
max_bday

casual_year_max = max_bday[[2]][[1]]
casual_year_avg = avg_bday[[2]][[1]]
casual_year_min = min_bday[[2]][[1]]

member_year_max = max_bday[[2]][[2]]
member_year_avg = avg_bday[[2]][[2]]
member_year_min = min_bday[[2]][[2]]

count_dayofweek
```
Export Summary Stats as .xlsx File:

```
# creating a dataframe of summary stats

Rows <- c("Max Duration", "Mean Duration", "Min Duration", "Female" , "Male" , "Youngest Year" , "Average Year", "Oldest Year")
Member_Stats <- c(member_max, member_mean, member_min, member_female_count, member_male_count, member_year_max, member_year_avg, member_year_min)
Casual_Stats <- c(casual_max, casual_mean, casual_min, casual_female_count, casual_male_count, casual_year_max, casual_year_avg, casual_year_min)
Stats <- data.frame(Rows, Member_Stats, Casual_Stats)
write_xlsx(Stats, "Member_Casual.xlsx")
```

What are some key differences between the two groups?

* Casual riders had an average ride time of 3420 seconds, about 57 minutes. 
* Members had an average ride time of 859 seconds, about 14 minutes, 19 seconds. 
* Females were almost evenly split between the categories.
* Of the males, 74.7% were in the members category. 
* Members tended to be slightly older with a median age of 32 while casual riders had a median age of 28.**
* The youngest member was 5 years old. 
* The youngest casual rider was 16 years old.
* Members utilized Cyclistic a significant amount more than casual riders during the weekdays. 
* Member usage goes down during the weekends and up during the weekdays. 
* Casual rider usage goes down during the weekdays and up during the weekends.
* Casual riders had a significantly longer average duration for every day of the week.  

** Median was used as opposed to average to account for outliers. 


## Share


What is all this information trying to tell us?

It allows us to paint a picture of what these two groups are like. 

### Members 

Members are people that use these bikes in their daily life. They might use it with their kids, as the median age is 32 years old and the youngest was 5 years old. They also use these bikes on shorter trips, perhaps using it as a mode of transport when during their daily tasks such as running to the grocery store or going to the gym. Because these bikes were used by members heavily during the week and saw a drop off during the weekends, it’s likely that they are being used by people to go to and from work. Members are more likely to be men. 

### Casual Riders

Casual Riders are people that use these bikes on occasion. They have a very high usage on the weekends and a relatively low usage on the weekdays, so it’s likely that casual riders are people that are using them when going out with friends or using them to go do a weekend activity, and not using them as a part of their daily life. They tend to be younger. Casual riders tend to use these bikes for long periods of time, and tend to go farther than do members.

Graphs for days of week:

```
colors <- c("coral2", "darkslategray3")

# count day of week casual/member
ggplot(totaltrips, aes(weekday)) + geom_bar(aes(fill=usertype), position = "dodge")

# average duration casual/member
totaltrips %>%
  group_by(usertype, weekday) %>%
  summarise(number_of_rides = n()
            ,average_duration = mean(tripduration)) %>%
  arrange(usertype, weekday) %>%
  ggplot(aes(x = weekday, y = average_duration, fill = usertype)) +
  geom_col(position = "dodge")

# average trip duration casual / member 
totaltrips %>%
  group_by(usertype) %>%
  summarise(average_duration = mean(tripduration)) %>%
  arrange(usertype) %>%
  ggplot(aes(x = usertype, y = average_duration)) +
  geom_col(aes(fill = colors))

# casual/member age distribution
years <- unique(totaltrips$birthyear)
sort(years)
sum(totaltrips$birthyear == 2014, na.rm = TRUE)
# there are 5 brithdays in 2014. They are all in the member category, as the youngest birhtday in the casual category was 2003.
# birthyears range from 1759 - 2014. This data is from 2019, so we'll ignore any birhtday older than 100 years old.

totaltrips_under18 = totaltrips[totaltrips$birthyear >= 1919 & totaltrips$birthyear <= 2003,]
ggplot(totaltrips_under18, aes(birthyear)) + geom_bar(aes(fill=usertype), position = "dodge")
```

**Counts for each day of week divided by Casual Riders and Annual Members:**
<br/><img src='/images/Count Days of Week.png'>

**Average for each day of week divded by Casual Riders and Annual Members:**
<br/><img src='/images/Average Days of Week.png'>

**Average duration for Casual Riders and Annual Members:**
<br/><img src='/images/Average Trip Duration.png'>

**Age Distribution for Casual Riders and Annual Members:**
<br/><img src='/images/Age Distribution.png'>

## Act

How can these insights be applied to the business objective?

Our objective is to convert casual riders into annual members. Throughout this study, we investigated the differences between the two groups. What we found, is that annual members tend to use the bikes as a part of their daily life, while casual riders tend to only use it on specfic ossaciaions. Annual members are likely older and maybe use the bikes with their family, whie casual riders are usually younger. Males make up a large percentage of annual members. 

We can apply these insights by creating a marketing campaign that targets this demographic and influences them to become annual members. 

The ad should:
* Target males, people that live in the city, families.
* Emphasis the convience of taking a quick ride. 

The ad should target males because males are more likely to be annual members. It should also target people that live in the city, because these are people that have a reason to get around the city on a daily basis, not just on the weekends. Because they live there, they likely have friends within the city, favorite stores in the city, and work within the city. All of these things they would easily be able to get to by using these bikes. Finally, the ad should target people that are slightly older, and even families. These are the people with careers that could take these bikes to work, or use these bikes to go out with their children. The ad should also emphasis how easily annual members can take out a bike, get somewhere quick, and not worry about the daily bike fees or the stress of driving through traffic. Annual members tended to have a shorter average trip duration, which shows how these bikes could be a casual part of a member's daily life.