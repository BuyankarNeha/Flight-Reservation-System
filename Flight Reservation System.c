#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEAT_COST 150.00
#define MAX_SEATS 100

int available_seats[MAX_SEATS];

struct Date {
    int day;
    int month;
    int year;
};

struct Reservation {
    int booking_id;
    char passenger_name[50];
    char flight_number[10];
    char destination[50];
    char departure_airport[50];
    char arrival_airport[50];
    struct Date travel_date;
    int seat_count;
    int seat_numbers[MAX_SEATS];
    double total_fare;
    char boarding_time[10];
    char gate[5];
};

double calculate_fare(int seat_count) {
    return seat_count * SEAT_COST;
}

void assign_seat_numbers(struct Reservation *res) {
    int assigned = 0;
    for (int i = 0; i < MAX_SEATS && assigned < res->seat_count; i++) {
        if (available_seats[i] == 0) {
            res->seat_numbers[assigned] = i + 1;
            available_seats[i] = 1;
            assigned++;
        }
    }
}

void book_ticket() {
    struct Reservation res;

    printf("Enter Passenger Name: ");
    scanf("%s", res.passenger_name);
    printf("Enter Flight Number: ");
    scanf("%s", res.flight_number);
    printf("Enter Destination: ");
    scanf("%s", res.destination);
    printf("Enter Departure Airport: ");
    scanf("%s", res.departure_airport);
    printf("Enter Arrival Airport: ");
    scanf("%s", res.arrival_airport);
    printf("Enter Date of Travel (DD MM YYYY): ");
    scanf("%d %d %d", &res.travel_date.day, &res.travel_date.month, &res.travel_date.year);
    printf("Enter Number of Seats: ");
    scanf("%d", &res.seat_count);

    int available = 0;
    for (int i = 0; i < MAX_SEATS; i++) {
        if (available_seats[i] == 0) {
            available++;
        }
    }

    if (res.seat_count > available) {
        printf("Error: Only %d seats are available.\n", available);
        return;
    }

    assign_seat_numbers(&res);
    res.total_fare = calculate_fare(res.seat_count);
    res.booking_id = rand() % 10000 + 1;
    strcpy(res.boarding_time, "10:30 PM");
    strcpy(res.gate, "G10");

    printf("\n********** Flight Ticket **********\n");
    printf("Passenger Name: %s\n", res.passenger_name);
    printf("Flight Number: %s\n", res.flight_number);
    printf("Destination: %s\n", res.destination);
    printf("Departure Airport: %s\n", res.departure_airport);
    printf("Arrival Airport: %s\n", res.arrival_airport);
    printf("Date of Travel: %02d-%02d-%d\n", res.travel_date.day, res.travel_date.month, res.travel_date.year);
    printf("Number of Seats: %d\n", res.seat_count);
    printf("Assigned Seats: ");
    for (int i = 0; i < res.seat_count; i++) {
        printf("%d ", res.seat_numbers[i]);
    }
    printf("\nTotal Fare: $%.2f\n", res.total_fare);
    printf("Boarding Time: %s\n", res.boarding_time);
    printf("Gate: %s\n", res.gate);
    printf("Booking ID: %d\n", res.booking_id);
    printf("***********************************\n");
}

int main() {
    int choice;

    for (int i = 0; i < MAX_SEATS; i++) {
        available_seats[i] = 0;
    }

    while (1) {
        printf("\nFlight Reservation System\n");
        printf("1. Book Flight Ticket\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                book_ticket();
                break;
            case 2:
                printf("Exiting the system. Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
