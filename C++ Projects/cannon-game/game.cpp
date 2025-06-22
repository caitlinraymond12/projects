#include "library.h"

void top_distance(const int x, const int y, const int radius) {
    const double W1 = radius * 2.5;
    const double W2 = radius * 1.75;
    const double L1 = 1.5 * radius;
    const double L2 = 5 * radius;
    const double adj = L1 + L2 + 2 * radius;
    const double opp = W1 - W2;
    const double hyp = adj * adj + opp * opp;
    const double distance = sqrt(hyp);
    draw_distance(distance);
}

void enemy_windows(const int x, const int y) {
    move_to(x, y);
    set_heading_degrees(180);
    draw_distance(10);
    turn_left_by_degrees(90);
    draw_distance(25);
    turn_left_by_degrees(90);
    draw_distance(10);
    turn_left_by_degrees(90);
    draw_distance(25);
}

void enemy_base(const int x) {
    set_pen_width(4);
    set_pen_color(color::black);
    set_heading_degrees(0);
    move_to(500, 500);
    draw_distance(150);
    move_to(x, 500);
    draw_distance(75);
    turn_right_by_degrees(90);
    draw_distance(100);
    turn_right_by_degrees(90);
    draw_distance(75);
    enemy_windows(x + 10, 450);
    enemy_windows(x + 60, 450);
}

void points(const double velocity, const double radians, const double time, const int xstart, const int ystart, const int enemy_x) {
    set_pen_color(color::light_blue);
    const int y = 500 - (velocity * time * cos(radians) - .5 * 32.174 * time * time);
    const int x = velocity * time * sin(radians);
    const int yactual = y - ystart;
    const int xactual = x + xstart;

    if (yactual >= 350 && xactual > 498)
        if (xactual < 502) {
            print("YOU LOSE");
            new_line();
            return;
        }
    if (yactual >= 425 && xactual >= enemy_x)
        if (yactual <= 500 && xactual <= enemy_x + 100) {
            print("YOU WON!\n");
            print("The cannon travelled ");
            print(x - xstart);
            print(" feet and was in the air for ");
            print(time);
            print(" seconds");
            new_line();
            return;
        }
    if (yactual == 500 && x < enemy_x) {
        print("YOU LOSE");
        return;
    }
    if (yactual == 500 && x > enemy_x + 50) {
        print("YOU LOSE");
        return;
    }
    if (y <= 500 + ystart) {
        draw_point(xactual, yactual);
        points(velocity, radians, time + .005, xstart, ystart, enemy_x);
    }
}

void starting_point(const double x1, const double y1, const double x2, const double y2, const double velocity, const double radians, const double time, const int enemy_x) {
    const int xstart = x1 + ((x2 - x1) / 2);
    const int ystart1 = y1 + ((y2 - y1) / 2);
    const int ystart = 500 - ystart1;
    points(velocity, radians, time, xstart, ystart, enemy_x);
}

void canon_shape(const int x, const int y, const int radius, const double velocity, const double radians, const double time, const int enemy_x) {
    turn_left_by_degrees(90);
    draw_distance(1.5 * radius);
    turn_right_by_degrees(90);
    draw_distance(2.5 * radius);
    turn_right_by_degrees(95);
    top_distance(x, y, radius);
    const double x1 = get_x_position();
    const double y1 = get_y_position();
    turn_right_by_degrees(85);
    draw_distance(1.75 * radius);
    const double x2 = get_x_position();
    const double y2 = get_y_position();
    turn_right_by_degrees(90);
    draw_distance(5 * radius);
    starting_point(x1, y1, x2, y2, velocity, radians, time, enemy_x);
}

void make_circle(const int deg, const int radius, const int degrees) {
    set_pen_width(3);
    set_pen_color(color::black);
    const double pi = acos(-1.0);
    const double length = (2 * pi * radius) / 360;
    if (deg < 630 + degrees) {
        draw_distance(length);
        turn_right_by_degrees(1);
        make_circle(deg + 1, radius, degrees);
    }
}

void canon(const int x, const int y, const int degrees, const double velocity, const double radians, const double time, const int enemy_x) {
    move_to(x, y);
    set_heading_degrees(0);
    make_circle(0, 13, degrees);
    canon_shape(x, y, 13, velocity, radians, time, enemy_x);
}

void clear_screen() {
    move_to(500, 250);
    set_pen_width(10000);
    set_pen_color(color::white);
    draw_point();
}

void initial_velocity(const int tries) {
    const int enemy_x = random_in_range(600, 900);
    enemy_base(enemy_x);
    print("\nYou are on try ");
    print(tries);
    print(" out of 3\n");
    print("Enter Initial Velocity ");
    const int velocity = read_int();
    print("Enter Angle of Cannon ");
    const int angle = read_int();
    const double pi = acos(-1.0);
    const double radians = (pi * angle) / 180;
    canon(30, 480, angle, velocity, radians, 0, enemy_x);
    new_line();
    if (tries == 3)
        print("You're out of tries");
    if (tries == 1 || tries == 2) {
        print("Do you want to try again? ");
        const string test = read_string();
        if (test == "yes" || test == "Yes") {
            clear_screen();
            initial_velocity(tries + 1);
        }
    }
}

void main() {
    make_window(1000, 500);
    initial_velocity(1);
}

