/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * main.cpp: Entry point for this project
 * Copyright (C) 2012 Yasunori Endo
 *
 */

#include<iostream>
#include<cstdlib>
#include<gtkmm.h>
#include<linux/unistd.h>
#include"TestApp.h"

int main(int argc, char **argv) {
    Glib::thread_init();
    Gtk::Main gm(argc, argv);
    GtkTest::TestApp app;

    // Sleep test before running
    std::cout << "Wait for a second." << std::endl;
    sleep(1);
    app.run();

    app.join_threads();
    std::cout << "All threads terminated." << std::endl;
    return EXIT_SUCCESS;
}
