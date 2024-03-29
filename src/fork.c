#include "mm.h"
#include "scheduler.h"
#include "entry.h"
#include "common.h"

int copy_process(u64 fn, u64 arg)
{

    // Disable task switching until the process is done being copied
    preempt_disable();
    struct task_struct *p;

    // Allocate new page and put task struct at its beginning.
    // the rest will be available to the new task/process.
    p = (struct task_struct *)get_free_page();
    
    // Return is could not get a free page
    if (!p) {
        return 1;
    }
    
    // Configure the task struct
    p->priority = current->priority;
    p->state = TASK_RUNNING;
    p->counter = p->priority;
    p->preempt_count = 1;               //disable preemtion until schedule_tail
    p->cpu_context.x19 = fn;
    p->cpu_context.x20 = arg;
    p->cpu_context.pc = (u64) &ret_from_fork;
    p->cpu_context.sp = (u64) p + THREAD_SIZE;
    int pid = nr_tasks++;               // TODO: Better to "encapsulate" it and call a function. What happens if pid > 64?
    task[pid] = p;

    // Enables task switching once again.
    preempt_enable();
    return 0;
}