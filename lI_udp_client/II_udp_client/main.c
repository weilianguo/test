/*
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Example application for demonstrating the RIOT network stack
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include <string.h>
#include <xtimer.h>
#include "shell.h"
#include "msg.h"

#define MAIN_QUEUE_SIZE     (8)
#define SERVER_PORT			123

extern void send(char *addr_str, uint16_t port, char *data, int len);

static int udp_cmd(int argc, char **argv)
{
    if (argc != 2) {
        printf("udp_send <IPv6 address>\n");
        return -1;
    }
	char str[] = "Hello IEEE 802.15.4!";
	for (int i = 0; i < 10; i++) {
		printf("send %d packet\n", i+1);
		send(argv[1], SERVER_PORT, str, strlen(str));
		xtimer_msleep(1000);
	}
    return 0;
}

static const shell_command_t shell_commands[] = {
    { "udp_send", "send data over UDP and listen on UDP ports", udp_cmd },
    { NULL, NULL, NULL }
};

int main(void)
{
    /* we need a message queue for the thread running the shell in order to
     * receive potentially fast incoming networking packets */
    puts("RIOT network stack example application");
    char buf[512];
    shell_run(shell_commands, buf, SHELL_DEFAULT_BUFSIZE);
    /* should be never reached */
    return 0;
}
