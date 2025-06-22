#include "library.h"

const string months[] = { "", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

void text(const int color, const int hour, const int minute, const int second) {
    const int date = get_calendar_date();
    const int year = date / 10000;
    const int month = (date % 10000) / 100;
    const int day = date % 100;
    move_to(75, 50);
    set_pen_color(color, color, color);
    set_font("Arial", 50);
    if (hour > 12) {
        const int houradj = hour - 12;
        write_string(houradj);
    }
    else {
        write_string(hour);
    }
    write_string(":");
    if (minute < 10) {
        write_string("0");
    }
    write_string(minute);
    if (hour > 12) {
        write_string("p.m");
    }
    else {
        write_string("a.m");
    }
    move_to(55, 370);
    set_font("Arial", 30);
    write_string(day);
    if (day % 10 == 1) {
        write_string("st ");
    }
    if (day % 10 == 2) {
        write_string("nd ");
    }
    if (day % 10 == 3) {
        write_string("rd ");
    }
    else {
        write_string("st ");
    }
    write_string(months[month]);
    write_string(" ");
    write_string(year);
}

void clock_hands(const int color) {
    const int time = get_clock_time();
    const int hour = time / 10000;
    const int minute = (time % 10000) / 100;
    const int second = time % 100;
    const double hour_hand = ((minute * 30) / 60 + (hour * 30));
    const double minute_hand = minute * 6;
    const double second_hand = (second * 360) / 60;
    set_pen_color(color, color, color);
    move_to(150, 200);
    set_heading_degrees(second_hand);
    set_pen_width(1);
    draw_distance(85);
    move_to(150, 200);
    set_heading_degrees(minute_hand);
    set_pen_width(2);
    draw_distance(85);
    move_to(150, 200);
    set_heading_degrees(hour_hand);
    set_pen_width(4 + (5 * color));
    draw_distance(60);
    if (color == 1) {
        move_to(150, 200);
        set_pen_width(3);
        set_heading_degrees(second_hand - 6);
        draw_distance(85);
        move_to(150, 200);
        set_heading_degrees(minute_hand - 6);
        draw_distance(85);
    }
    if (color == 0) {
        wait(.15);
        text(1, hour, minute, second);
        clock_hands(1);
    }
    if (color == 1) {
        text(0, hour, minute, second);
        clock_hands(0);
    }
}

void clock_face(const int time) {
    move_to(150, 200);
    set_pen_width(1);
    if (time <= 360) {
        if (time % 5 == 0) {
            set_pen_width(3);
        }
        set_pen_color(color::white);
        draw_distance(100);
        set_pen_color(color::black);
        draw_distance(6);
        set_pen_color(color::white);
        turn_right_by_degrees(6);
        clock_face(time + 1);
    }
}

void main() {
    make_window(300, 400);
    clock_face(0);
    clock_hands(0);
}

