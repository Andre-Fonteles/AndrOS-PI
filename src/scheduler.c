#include "scheduler.h"
#include "irq.h"
#include "string_utils.h"
#include "mini_uart.h"

static struct task_struct init_task = INIT_TASK; // The initial kernel_main task
struct task_struct *current = &(init_task);      // Current task being executed
int nr_tasks = 1;                                // Number of currently running tasks
struct task_struct *task[NR_TASKS] = {           // Array of all tasks in the system
    &(init_task),
};

void preempt_disable(void)
{
    current->preempt_count++;
}

void preempt_enable(void)
{
    current->preempt_count--;
}

void _schedule(void)
{
    preempt_disable();
    int next, c;
    struct task_struct *p;
    while (1)
    {
        c = -1;
        next = 0;
        for (int i = 0; i < NR_TASKS; i++)
        {
            // Finds tasks with the biggest counter
            p = task[i];
            if (p && p->state == TASK_RUNNING && p->counter > c)
            {
                c = p->counter;
                next = i;
            }
        }

        // If a task exists such that c > 0, then break the loop. The same happens if no task is running
        if (c)
        {
            break;
        }

        // Increase counter for all existing tasks
        for (int i = 0; i < NR_TASKS; i++)
        {
            p = task[i];
            if (p)
            {
                // counter = (counter / 2) + priority
                // counter will never be > 2 * priority
                p->counter = (p->counter >> 1) + p->priority;
            }
        }
    }
    switch_to(task[next]);
    preempt_enable();
}

void schedule(void)
{
    current->counter = 0;
    _schedule();
}

void switch_to(struct task_struct *next)
{
    if (current == next)
        return;

    struct task_struct *prev = current;
    current = next;
    cpu_switch_to(prev, next);
}

void schedule_tail(void)
{
    preempt_enable();
}

void timer_tick(void)
{
    // uart_send_string("tic tac");
    --current->counter;
    if (current->counter > 0 || current->preempt_count > 0)
    {
        return;
    }

    current->counter = 0;
    enable_irq();  // Enable interrupt during schedule
    _schedule();   // Run the scheduling algorithm
    disable_irq(); // Disable interrupt again
}