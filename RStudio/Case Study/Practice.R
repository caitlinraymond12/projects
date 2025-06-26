#load packages
library(tidyverse)
library(ggplot2)
library(readr)
library(data.table)
library(lubridate)
library(writexl)
setwd("C:\\Users\\caitl\\OneDrive\\Documents\\RStudio")

#read into a variable called duration
duration <- fread("2020_data.csv", select = c("started_at", "ended_at", "start_station_name", "member_casual" ))

#calculate difference in time             
duration$time_difference <- (difftime(duration$ended_at, duration$started_at))

#remove any negative times or times equal to 0 seconds.
duration <- duration[duration$time_difference > 0]


#convert seconds into h:mm:ss
duration$time_difference <- seconds_to_period(duration$time_difference)
head(duration)


#create column for days of the week
duration$weekday <- weekdays(as.Date(duration$started_at))

View(duration)




avg_member <- aggregate(duration$time_difference, list(duration$member_casual), "mean")
avg_member

max_member <- aggregate(duration$time_difference, list(duration$member_casual), "max")
max_member

min_member <- aggregate(duration$time_difference, list(duration$member_casual), "min")
min_member

#makes the seconds into regular numbers
duration$time_difference <- as.numeric(duration$time_difference)

#max, min, mean of members and casual
member_max <- duration[duration$member_casual == 'member']
member_max <- max(member_max$time_difference)


member_min <- duration[duration$member_casual == 'member']
member_min <- min(member_min$time_difference)


member_mean <- duration[duration$member_casual == 'member']
member_mean <- round(mean(member_mean$time_difference),0)


casual_max <- duration[duration$member_casual == 'casual']
casual_max <- max(casual_max$time_difference)


casual_min <- duration[duration$member_casual == 'casual']
casual_min <- min(casual_min$time_difference)


casual_mean <- duration[duration$member_casual == 'casual']
casual_mean <- round(mean(casual_mean$time_difference),0)

summary_stats <- matrix(c(member_mean, member_max, member_min, casual_mean, casual_max, casual_min), ncol = 2)

rownames(summary_stats) = c('Mean', 'Max', 'Min')
colnames(summary_stats) = c('Member','Casual')

summary_stats

  
#turn all summary stats into h:mm:ss


casual_max <- seconds_to_period(casual_max)
casual_mean <- seconds_to_period(casual_mean)
casual_min <- seconds_to_period(casual_min)


member_max <- seconds_to_period(member_max)
member_mean <- seconds_to_period(member_mean)
member_min <- seconds_to_period(member_min)


#count total member/casual

member_count <- as.numeric(duration[duration$member_casual == 'member'] %>% 
                             summarise(n = n()))

casual_count <- as.numeric(duration[duration$member_casual == 'casual'] %>% 
                             summarise(n = n()))


#avg, min, max day of week

avg_dayofweek <- aggregate(duration$time_difference, list(duration$weekday), mean)
avg_dayofweek$x <- seconds_to_period(round(avg_dayofweek$x, 0))
avg_dayofweek


max_dayofweek <- aggregate(duration$time_difference, list(duration$weekday), max)
max_dayofweek$x <- seconds_to_period(max_dayofweek$x)
max_dayofweek

min_dayofweek <- aggregate(duration$time_difference, list(duration$weekday), min)
min_dayofweek$x <- seconds_to_period(min_dayofweek$x)
min_dayofweek


count_dayofweek <- duration %>% 
  group_by(weekday) %>% 
  summarise(n = n())
count_dayofweek

avg_dayofweek <- aggregate(duration$time_difference, list(duration$weekday), mean)
avg_dayofweek$x <- seconds_to_period(round(avg_dayofweek$x, 0))
avg_dayofweek

#avg/max/min day of week by membership status MEMBER
member_duration <- duration[duration$member_casual == 'member']


memberavg_dayofweek <- aggregate(member_duration$time_difference, list(member_duration$weekday), mean)
memberavg_dayofweek$x <- seconds_to_period(round(memberavg_dayofweek$x, 0))
memberavg_dayofweek

membermax_dayofweek <- aggregate(member_duration$time_difference, list(member_duration$weekday), max)
membermax_dayofweek$x <- seconds_to_period(membermax_dayofweek$x)
membermax_dayofweek

membermin_dayofweek <- aggregate(member_duration$time_difference, list(member_duration$weekday), min)
membermin_dayofweek$x <- seconds_to_period(membermin_dayofweek$x)
membermin_dayofweek

#avg/max/min day of week by membership status CASUAL

casual_duration <- duration[duration$member_casual == 'casual']


casualavg_dayofweek <- aggregate(casual_duration$time_difference, list(casual_duration$weekday), mean)
casualavg_dayofweek$x <- seconds_to_period(round(casualavg_dayofweek$x, 0))
casualavg_dayofweek

casualmax_dayofweek <- aggregate(casual_duration$time_difference, list(casual_duration$weekday), max)
casualmax_dayofweek$x <- seconds_to_period(casualmax_dayofweek$x)
casualmax_dayofweek

casualmin_dayofweek <- aggregate(casual_duration$time_difference, list(casual_duration$weekday), min)
casualmin_dayofweek$x <- seconds_to_period(casualmin_dayofweek$x)
casualmin_dayofweek


##count days of week member/casual

#grouped bar chart
ggplot(duration, aes(weekday)) + geom_bar(aes(fill=member_casual), position = "dodge")
#stacked bar chart
ggplot(duration, aes(weekday)) + geom_bar(aes(fill=member_casual))

##count days of week
ggplot(duration, aes(weekday)) + geom_bar(fill = "lightblue")


##time distribution
hist(duration$time_difference)

View(duration)
casual_max

#histogram of time distribution
x <- duration$time_difference
hist(x, breaks = 50000, xlim = c(0, 6000))

hist(x, breaks = 50000, xlim = c(0, 3000))
abline(v = mean(duration$time_difference), col = "red", lwd = 3)


#all the summary statistics
member_max
member_min
member_mean
casual_max
casual_min
casual_mean

member_count
casual_count

avg_dayofweek
min_dayofweek
max_dayofweek

casualavg_dayofweek
casualmax_dayofweek
casualmin_dayofweek

memberavg_dayofweek
membermax_dayofweek
membermin_dayofweek

#creating a dataframe of summary stats

c(memberavg_dayofweek)

Member_Avg <- c(memberavg_dayofweek$x)
Member_Max <- c(membermax_dayofweek$x)
Member_Min <- c(membermin_dayofweek$x)
Casual_Avg <- c(casualavg_dayofweek$x)
Casual_Max <- c(casualmax_dayofweek$x)
Casual_Min <- c(casualmin_dayofweek$x)

Day_of_Week_Stats <- data.frame(c(memberavg_dayofweek$Group.1), Member_Avg, Member_Max, Member_Min, Casual_Avg, Casual_Max, Casual_Min)
Day_of_Week_Stats
View(Day_of_Week_Stats)

write_xlsx(Day_of_Week_Stats, "Sum_Stats_Weekdays.xlsx")

