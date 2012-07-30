/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * TestApp.h: Test application code
 * Copyright (C) 2012 Yasunori Endo
 *
 */

#ifndef INCL_TESTAPP
#define INCL_TESTAPP

#include<gdkmm/pixbuf.h>
#include<glibmm/refptr.h>
#include<glibmm/threads.h>

#define IMG_WIDTH 100
#define IMG_HEIGHT 100
#define IMG_BITS_PER_SAMPLE 8

namespace GtkTest {

    class TestApp {
    public:
        TestApp();
        void run();
        void join_threads();

    private:
        volatile bool enabled; // volatile is necessory to run thread correctly
        Glib::Threads::Thread *th_save, *th_draw;
        Glib::RefPtr<Gdk::Pixbuf> img;
        void f_save();
        void f_draw();
    };
}
#endif /* INCL_TESTAPP */
