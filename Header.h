#pragma once


typedef struct application {
	double time_2;
	double time_3;
	double interval; 
	double useless_time;
	double time_of_enqueue_1;
	double time_of_dequeue_1;
	double time_of_enqueue_2;
	double time_of_dequeue_2;
	double f_or_s;
	int finished;
	int if_first;
	int num;
}application;

typedef struct node {
	application app;
	node* next;
	node* prev;

};

typedef struct stack {
	struct node* head;
}stack;

typedef struct queue {
	node* head;
	node* tail;
	double time;
}queue;


typedef struct ao {
	queue* finished;
	double time_work;
	double useless;
	int free;
	int num;
}ao;

void enqueue(queue* q, application new_app);
void init_queue(queue* q);
application dequeue(queue* q);
void process_application(ao* the_ao, application* app);
void function(queue* q, application* tmp, int i);
void add_to_queue(queue* q, application app);
void init_ao(ao* ao_1, int num);
void write_info(int num, double useless_time_1, double useless_time_2, int q_1_length, int q_2_length, int the_num,
	double the_longest_time, double average_time, double all_time_1, double all_time_2);

int stack_init(stack* s);
void init_app(application* app);
//int stack_is_empty(const stack* s);
int stack_push(stack* s, application val);
application pop(stack* s);
//void print_stack(stack* s);