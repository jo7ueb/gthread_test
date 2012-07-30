#include<gtkmm.h>
#include<iostream>
#include<linux/unistd.h>

void slot_thread() {
  std::cout << "Thread started!" << std::endl;
  sleep(2);
  std::cout << "Thread terminated!" << std::endl;
}

int main() {
  Glib::thread_init();
  std::cout << "Main function!" << std::endl;

  Glib::Thread *thread = Glib::Thread::create(sigc::ptr_fun(&slot_thread));
  thread->join();

  std::cout << "Main terminated." << std::endl;
}
