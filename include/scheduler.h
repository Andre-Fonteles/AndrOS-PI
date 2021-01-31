#ifndef _SCHEDULER_H
#define _SCHEDULER_H

#define THREAD_CPU_CONTEXT 0 				// offset of cpu_context in task_struct 

#ifndef __ASSEMBLER__

#define THREAD_SIZE 4096

#define NR_TASKS 64							// We currently accept a max of 64 tasks.

#define FIRST_TASK task[0]
#define LAST_TASK task[NR_TASKS-1]

#define TASK_RUNNING				0

extern struct task_struct *current;
extern struct task_struct * task[NR_TASKS];
extern int nr_tasks;

struct cpu_context {
	unsigned long x19;
	unsigned long x20;
	unsigned long x21;
	unsigned long x22;
	unsigned long x23;
	unsigned long x24;
	unsigned long x25;
	unsigned long x26;
	unsigned long x27;
	unsigned long x28;
	unsigned long fp;
	unsigned long sp;
	unsigned long pc;
};

// This struct represents a process.
struct task_struct {
	struct cpu_context cpu_context;
	long state;	                        // Running, sleeping, ...
	long counter;                       // How long has the task been running.
	long priority;                      // Priority is copied to counter. The higher it is, the longer the task runs.
	long preempt_count;                 // If the field != 0, the task cannot be interrupted.
};

extern void schedule_tail(void);
extern void init_scheduler(void);
extern void sched_init(void);
extern void schedule(void);
extern void timer_tick(void);
extern void preempt_disable(void);
extern void preempt_enable(void);
extern void switch_to(struct task_struct* next);
extern void cpu_switch_to(struct task_struct* prev, struct task_struct* next);

#define INIT_TASK \
/*cpu_context*/	{ {0,0,0,0,0,0,0,0,0,0,0,0,0}, \
/* state etc */	0, 0, 1, 0 \
}

#endif

#endif /*_SCHEDULER_H */