#include "minishell.h"
static volatile sig_atomic_t got_sigint = 0;

static void on_sigint(int sig) {
    (void)sig;
    got_sigint = 1;     // async-signal-safe
    rl_done = 1;        // tells readline() to return ASAP
}

int main(void) {
    // 1) Disable Readline’s own handlers
    rl_catch_signals = 0;
    rl_catch_sigwinch = 0;

    // 2) Install SIGINT handler WITHOUT SA_RESTART
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;        // <-- no SA_RESTART
    sa.sa_handler = on_sigint;
    sigaction(SIGINT, &sa, NULL);

    while (1) {
        char *line = readline("minishell$ ");
        if (got_sigint) {
            got_sigint = 0;
            // behave like bash: print newline, clear line buffer, redraw prompt
            write(STDOUT_FILENO, "\n", 1);
            rl_replace_line("", 0);
            rl_on_new_line();
            rl_redisplay();
            free(line);     // readline may return partial buffer; free it
            continue;
        }
        if (!line) {        // EOF (Ctrl+D)
            printf("exit\n");
            break;
        }
        if (*line) add_history(line);
        // ... do work ...
        free(line);
    }
    return 0;
}
