#include "catch.hpp"
#include "course.h"
#include "handler.h"
#include "reservation.h"
#include "room.h"
#include "rsystem.h"
#include <iostream>
#include <sstream>

TEST_CASE("Class tests") {
    std::stringstream ss;
    auto old_buf = std::cout.rdbuf(ss.rdbuf());
    SECTION("Room") {
        auto room = Room("c404");
        CHECK(room.name.length() == 4);
        CHECK(room.isFree(0, 1));
        CHECK(room.isFree(2, 3));
        CHECK(room.isFree(12, 19));
        CHECK(room.isFreeFor(16) == 0);
        CHECK(room.occupy(2, 5));
        CHECK(!room.isFree(0, 3));
        CHECK(room.isFreeFor(3) == 5);
        CHECK(!room.occupy(4, 7));
        CHECK(room.occupy(16, 22));
        CHECK(room.isFreeFor(16) == -1);
        CHECK(room.isFree(0, 1));
        CHECK(room.isFree(0, 2));
        CHECK(!room.isFree(2, 3));
        CHECK(!room.isFree(4, 6));
        CHECK(room.isFree(5, 7));
        CHECK(!room.isFree(-1, 1));
        CHECK(room.isFree(22, 24));
        CHECK(!room.isFree(22, 25));
        room.schedule();
        CHECK(ss.str() == "__XXX___________XXXXXX__\n");
    }
    SECTION("Course") {
        auto course = Course("pb161", "teach");
        CHECK(course.code == "pb161");
        CHECK(course.teacher == "teach");
        course.print();

        auto course2 = Course("pb162", "");
        course2.print();
        CHECK(ss.str() == "Course: pb161 [Teacher: teach]\nCourse: pb162\n");
    }
    SECTION("Reservation") {
        auto res = Reservation("room", "course", 1, 5);
        res.print();
        CHECK(ss.str() == "Reservation for Course course in Room room [1-5]\n");
    }
    std::cout.rdbuf(old_buf);
}

TEST_CASE("Advanced tests") {
    std::stringstream ss;
    auto old_buf = std::cout.rdbuf(ss.rdbuf());
    SECTION("Room1") {
        auto room = Room("A217");
        CHECK(room.isFree(0, 24));
        CHECK(room.isFree(0, 5));
        CHECK(room.isFree(15, 24));
        CHECK(!room.isFree(23, 0));
        CHECK(!room.isFree(22, 26));
        room.schedule();
        for (int i = 0; i < 24; i++) {
            CHECK(room.isFree(i, i + 1));
        }
        for (int i = 0; i < 24; i += 4) {
            CHECK(room.occupy(i, i + 2));
        }
        for (int i = 0; i < 24; i += 4) {
            CHECK(!room.isFree(i, i + 2));
            CHECK(room.isFree(i + 2, i + 4));
        }
        room.print();
        room.schedule();
        CHECK(ss.str() ==
              "________________________\nRoom: A217\nXX__XX__XX__XX__XX__XX__\n");
    }
    SECTION("Room2") {
        auto room = Room("A217");
        for (int i = 0; i < 24; i += 4) {
            CHECK(room.occupy(i + 2, i + 4));
        }
        for (int i = 0; i < 24; i += 4) {
            CHECK(room.isFree(i, i + 2));
            CHECK(!room.isFree(i + 2, i + 4));
        }
        room.schedule();
        CHECK(ss.str() == "__XX__XX__XX__XX__XX__XX\n");
    }
    SECTION("Room3") {
        auto room = Room("A217");
        CHECK(!room.occupy(12, 25));
        for (int i = 0; i < 24; i += 6) {
            CHECK(room.occupy(i, i + 3));
        }
        for (int i = 0; i < 24; i += 6) {
            CHECK(!room.isFree(i, i + 3));
            CHECK(room.isFree(i + 3, i + 6));
        }
        CHECK(!room.occupy(0, 1));
        CHECK(!room.occupy(4, 7));
        CHECK(!room.occupy(1, 4));
        CHECK(!room.occupy(5, 3));
        CHECK(room.isFreeFor(4) == -1);
        CHECK(room.isFreeFor(35) == -1);
        CHECK(room.isFreeFor(3) == 3);
        room.schedule();
        CHECK(ss.str() == "XXX___XXX___XXX___XXX___\n");
    }
    SECTION("RSystem") {
        auto rs = ReservationSystem();
        CHECK(rs.addRoom("room"));
        CHECK(!rs.addRoom("room"));
        try {
            rs.getRoom("nope");
            CHECK(false); // Should throw an exception
        } catch (const std::exception &e) {
            CHECK(true);
        }

        CHECK(rs.addCourse("course", ""));
        CHECK(!rs.addCourse("course", ""));
        try {
            rs.getCourse("nope");
            CHECK(false); // Should throw an exception
        } catch (const std::exception &e) {
            CHECK(true);
        }
    }
    std::cout.rdbuf(old_buf);
}

TEST_CASE("Integration tests") {
    std::string roomn1 = "A217";
    std::string roomn2 = "A320";
    std::string roomn3 = "A418";
    std::string cs1 = "pb161";
    std::string cs2 = "ib002";
    std::string cs3 = "ak047";

    auto rs = ReservationSystem();

    SECTION("RSystem") {
        CHECK(rs.addRoom(roomn1));
        CHECK(rs.hasRoom(roomn1));
        CHECK(!rs.hasRoom(roomn2));
        CHECK(rs.getRoom(roomn1).name == roomn1);
        CHECK(rs.addRoom(roomn2));
        CHECK(rs.addRoom(roomn3));
        CHECK(rs.hasRoom(roomn2));
        CHECK(rs.hasRoom(roomn3));
        CHECK(rs.hasRoom(roomn1));

        CHECK(rs.addCourse(cs1, "Barrack"));
        CHECK(rs.addCourse(cs2, "Obama"));
        CHECK(rs.addCourse(cs3, ""));
        CHECK(rs.hasCourse(cs2));
        CHECK(!rs.hasCourse("Trump"));
        CHECK(rs.getCourse(cs2).teacher == "Obama");

        CHECK(!rs.makeReservation("not course", roomn1, 1, 3));
        CHECK(!rs.makeReservation(cs1, "not room", 3, 5));

        CHECK(rs.getRooms()[0].name == roomn1);
        CHECK(rs.getCourses()[0].code == cs1);
        SECTION("Any reservation") {
            CHECK(rs.makeAnyReservation(cs1, 4));
            CHECK(rs.getReservations()[0].end_time -
                  rs.getReservations()[0].start_time ==
                  4);
            CHECK(!rs.makeAnyReservation("NOT_COURSE", 2));
            for (int i = 0; i < 8; i++) {
                CHECK(rs.makeAnyReservation(cs2, 8));
            }
            CHECK(!rs.makeAnyReservation(cs2, 8));
        }
        SECTION("Reservations") {
            CHECK(!rs.makeReservation("not course", roomn1, 5, 6));
            CHECK(!rs.makeReservation(cs1, "not room", 5, 6));
            CHECK(rs.makeReservation(cs1, roomn1, 1, 3));
            CHECK(rs.makeReservation(cs2, roomn1, 3, 5));
            CHECK(rs.makeReservation(cs3, roomn1, 16, 20));
            CHECK(!rs.makeReservation(cs1, roomn1, 2, 4));
            CHECK(rs.getReservations()[1].room_name == roomn1);
            CHECK(rs.getReservations()[1].course_code == cs2);
            CHECK(rs.getReservations()[1].start_time == 3);
            CHECK(rs.getReservations()[1].end_time == 5);
        }
    }
}

TEST_CASE("Handler") {
    std::stringstream input;
    auto oldcin = std::cin.rdbuf(input.rdbuf());
    std::stringstream ss;
    auto realOut = std::cout.rdbuf(ss.rdbuf());
    /*
      auto handler = Handler();

      SECTION("1"){
        input << "1\nroom\n0\n";
        handler.handle();
        CHECK(ss.str() == "...");
      }*/

    std::cin.rdbuf(oldcin);
    std::cout.rdbuf(realOut);
}