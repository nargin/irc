#ifndef MYSIGNAL_HPP
#define MYSIGNAL_HPP

#include <signal.h>
#include <termios.h>
#include <iostream>
#include <stdlib.h>

void echo_ctl(int state);
void	handle_sigint(int sig);

#endif