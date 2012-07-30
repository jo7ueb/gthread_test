/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * TestApp.cpp: Implimentation of TestApp class
 * Copyright (C) 2012 Yasunori Endo
 *
 */

#include"TestApp.h"
#include<iostream>
#include<cstring>
#include<linux/unistd.h>

GtkTest::TestApp::TestApp() {
    enabled = false;
    std::cout << "Test" << std::endl;
    img = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, false, 
                              IMG_BITS_PER_SAMPLE, 
                              IMG_WIDTH, IMG_HEIGHT);
    img->fill(0x000000ff);

    th_save = Glib::Threads::Thread::create( sigc::mem_fun(*this, 
                                                           &TestApp::f_save) );
    th_draw = Glib::Threads::Thread::create( sigc::mem_fun(*this, 
                                                           &TestApp::f_draw) );
    std::cout << "TestApp initialized." << std::endl;
}


void GtkTest::TestApp::run() {
    enabled = true;
}


void GtkTest::TestApp::f_save() {
    std::cout << "f_save() started." << std::endl;
    
    // wait for thread enabled
    while(!enabled);
    std::cout << "Now thread start working." << std::endl;
    
    // time
    time_t time_raw;
    struct tm *tmp;
    struct tm time_gmt;
    struct tm time_jst;
    time(&time_raw);
    tmp = gmtime(&time_raw);
    memcpy(&time_gmt, tmp, sizeof(struct tm));
    tmp = localtime(&time_raw);
    memcpy(&time_jst, tmp, sizeof(struct tm));
    
    char str_time[17];
    strftime(str_time, sizeof(str_time), "%Y%m%d-%H%M:%S", &time_gmt);
    std::cout << "GMT: " << str_time << std::endl;
    strftime(str_time, sizeof(str_time), "%Y%m%d-%H%M:%S", &time_jst);
    std::cout << "JST: " << str_time << std::endl;
    strftime(str_time, sizeof(str_time), "%y%m%d%H%M", &time_jst);
    std::cout << "Part of filename: " << str_time << std::endl;

    // OK, let's save pictures!
    for(int i=0; i<=20; ++i) {
        time_t rtime;
        struct tm *gtime;
        time(&rtime);
        gtime = gmtime(&rtime);
        char timestr[7];
        strftime(timestr, sizeof(timestr), "%H%M%S", gtime);
        char filename[11];
        sprintf(filename, "%s.png", timestr);

        img->save(filename, "png");

        sleep(1);
    }

    enabled = false;
    std::cout << "f_save() terminated." << std::endl;
}


void GtkTest::TestApp::f_draw() {
    std::cout << "f_draw() started." << std::endl;

    // wait for thread enabled
    while(!enabled);
    std::cout << "f_draw() activated." << std::endl;

    // draw picture
    guint8 *pixels = img->get_pixels();
    std::cout << "Pixbuf handler obtained." << std::endl;
    int x = 0;

    while(enabled) {
        // plot line
        if(x <= IMG_WIDTH) {
            for(int y=0; y<IMG_HEIGHT; ++y) {
                int offset = (y * IMG_WIDTH + x) * 3;
                pixels[offset + 0] = 255;
                pixels[offset + 1] = 255;
                pixels[offset + 2] = 255;
            }
            ++x;
        } else {
            x = 0;
            img->fill(0x000000ff);
            std::cout << "Image initialized." << std::endl;
        }

        // wait for next line
        usleep(100000);
    }
    std::cout << "f_draw() terminated." << std::endl;
}


void GtkTest::TestApp::join_threads() {
    std::cout << "Wait for threads." << std::endl;
    th_save->join();
    th_draw->join();
    return;
}
