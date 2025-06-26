#load packages
library(tidyverse)
library(readr)
library(data.table)
library(lubridate)
library(writexl)
library(readxl)


setwd("C:\\Users\\caitl\\OneDrive\\Documents\\RStudio\\Case Study")


#read into variable
totaltrips <- read_csv("totaltrips.csv")

View(totaltrips)


# Overall stats for all trips 
summary(totaltrips)


# Trip duration stats for casual riders and members
max_usertype <- aggregate(totaltrips$tripduration, list(totaltrips$usertype), "max")
max_usertype

avg_usertype <- aggregate(totaltrips$tripduration, list(totaltrips$usertype), "mean")
avg_usertype

min_usertype <- aggregate(totaltrips$tripduration, list(totaltrips$usertype), "min")
min_usertype


# Age stats for casual riders and members 
max_bday <- aggregate(totaltrips$birthyear, list(totaltrips$usertype), "max", na.rm = TRUE)
max_bday

avg_bday <- aggregate(totaltrips$birthyear, list(totaltrips$usertype), "mean", na.rm = TRUE)
avg_bday

min_bday <- aggregate(totaltrips$birthyear, list(totaltrips$usertype), "min", na.rm = TRUE)
min_bday

med_bday <- aggregate(totaltrips$birthyear, list(totaltrips$usertype), "median", na.rm = TRUE)
med_bday


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

weekday_max
weekday_min
weekday_means


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
casual_year_med = med_bday[[2]][[1]]

member_year_max = max_bday[[2]][[2]]
member_year_avg = avg_bday[[2]][[2]]
member_year_min = min_bday[[2]][[2]]
member_year_med = med_bday[[2]][[2]]




# creating a dataframe of summary stats

Rows <- c("Max Duration", "Mean Duration", "Min Duration", "Female" , "Male" , "Youngest Year" , "Average Year", "Oldest Year")
Member_Stats <- c(member_max, member_mean, member_min, member_female_count, member_male_count, member_year_max, member_year_avg, member_year_min)
Casual_Stats <- c(casual_max, casual_mean, casual_min, casual_female_count, casual_male_count, casual_year_max, casual_year_avg, casual_year_min)

Stats <- data.frame(Rows, Member_Stats, Casual_Stats)

View(Stats)

write_xlsx(Stats, "Member_Casual.xlsx")
write_xlsx(weekday_max, "Weekday_Max.xlsx")
write_xlsx(weekday_means, "Weekday_Mean.xlsx")
write_xlsx(weekday_min, "Weekday_Min.xlsx")
write_xlsx(count_dayofweek, "Weekday_Count.xlsx")




# count day of week casual/member

ggplot(totaltrips, aes(weekday)) + geom_bar(aes(fill=usertype), position = "dodge")

# average duration casual/member by day of week
totaltrips %>%
  group_by(usertype, weekday) %>%
  summarise(number_of_rides = n()
            ,average_duration = mean(tripduration)) %>%
  arrange(usertype, weekday) %>%
  ggplot(aes(x = weekday, y = average_duration, fill = usertype, color = colors)) +
  geom_col(position = "dodge")

# average trip duration casual / member 

colors <- c("coral2", "darkslategray3")

totaltrips %>%
  group_by(usertype) %>%
  summarise(average_duration = mean(tripduration)) %>%
  arrange(usertype) %>%
  ggplot(aes(x = usertype, y = average_duration)) +
  geom_col(aes(fill = color))

# casual/member age distribution
years <- unique(totaltrips$birthyear)
sort(years)
sum(totaltrips$birthyear == 2014, na.rm = TRUE)
# there are 5 brithdays in 2014. They are all in the member category, as the youngest birhtday in the casual category was 2003.
# birthyears range from 1759 - 2014. This data is from 2019, so we'll ignore any birhtday older than 100 years old.

totaltrips_under18 = totaltrips[totaltrips$birthyear >= 1919 & totaltrips$birthyear <= 2003,]
ggplot(totaltrips_under18, aes(birthyear)) + geom_bar(aes(fill=usertype), position = "dodge")



#grouped bar chart 

ggplot(totaltrips, aes(weekday)) + geom_bar(aes(fill=usertype), position = "dodge")


ggplot(totaltrips, aes(fill=usertype, y = mean(tripduration), x = weekday)) +
  geom_col(position = "dodge", stat = "identity")

#histogram of time distribution
x <- totaltrips$tripduration
hist(x, breaks = 50000, xlim = c(0, 6000))

hist(x, breaks = 50000, xlim = c(0, 3000))
abline(v = mean(duration$time_difference), col = "red", lwd = 3)



# average duration 

totaltrips %>% group_by(usertype, weekday) %>% 
  summarise(number_of_rides = n(), average_duration = mean(tripduration)) %>% 
  arrange(usertype, weekday) %>%
  ggplot(aes(x = weekday, y = tripduration, fill = usertype)) +
  geom_col(position = "dodge")

totaltrips

totaltrips %>%  groupby(usertype, weekday) %>% 
  ggplot(aes(x = weekday, y = mean(tripduration)), fill=usertype)
                       + geom_col(position = "dodge")



totaltrips %>%
  group_by(usertype, weekday) %>%
  summarise(number_of_rides = n()
            ,average_duration = mean(tripduration)) %>%
  arrange(usertype, weekday) %>%
  ggplot(aes(x = weekday, y = average_duration, fill = usertype)) +
  geom_col(position = "dodge")

# Let's create a visualization for average duration
all_trips_v2 %>%
  mutate(weekday = wday(started_at, label = TRUE)) %>%
  group_by(member_casual, weekday) %>%
  summarise(number_of_rides = n()
            ,average_duration = mean(ride_length)) %>%
  arrange(member_casual, weekday) %>%
  ggplot(aes(x = weekday, y = average_duration, fill = member_casual)) +
  geom_col(position = "dodge")


