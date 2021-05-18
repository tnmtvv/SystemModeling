#include <iostream>
#include "Header.h"


void init_queue(queue* q){
	q->head = NULL;
	q->tail = NULL;
	q->time = 0;
}

int stack_init(stack* s)
{
	s->head = NULL;
	return 0;
}

void init_ao(ao* ao_1, int num) {
	ao_1->time_work = 0;
	ao_1->finished = (queue*)malloc(sizeof(queue));
	init_queue(ao_1->finished);
	ao_1->free = 0;
	ao_1->num = num;
	ao_1->useless = 0;
}

void init_app(application* app) {
	app->finished = 0;
	app->f_or_s = 0;
	app->interval = 0;
	app->time_2 = 0;
	app->time_3 = 0;
	app->time_of_dequeue_1 = 0;
	app->time_of_enqueue_1 = 0;
	app->time_of_dequeue_2 = 0;
	app->time_of_enqueue_2 = 0;
	app->useless_time = 0;
	app->num = 0;
}

void enqueue(queue* q, application new_app){
	node* new_node = (node*)malloc(sizeof(node));


	new_node->app = new_app;
	new_node->next = NULL;
	new_node->prev = NULL;

	if (q->tail != NULL)
	{
		q->tail->next = new_node;
		new_node->prev = q->tail;

	    q->tail = new_node;
		new_node->next = q->tail;
		/*q->tail = new_node;*///это потому что у нас тут как и в стеке указатель указывает на самый конец
	}
	
	else if (q->head == NULL && q->tail == NULL)
	{
		q->tail = new_node;
		q->head = new_node;
	}


	
}

void process_application(ao* the_ao, application* app) {
	if (the_ao->num == 1)
	{
		the_ao->time_work += app->time_2;
	}

	else if (the_ao->num == 2)
	{
		the_ao->time_work += app->time_3;
	}
	
}

void add_to_queue(queue* q, application app){
	q->time += app.interval;

}

void write_info(int num, double useless_time_1, double useless_time_2, int q_1_length, int q_2_length, int the_num, 
	double the_longest_time, double average_time, double all_time_1, double all_time_2) {
	std::cout << "\nбыло обработанно ";
	std::cout << num;
	std::cout << " заявок\n";
	std::cout << "время простоя первого автомамта: ";
	std::cout << useless_time_1;
	std::cout << "\nвремя простоя второго автомамта: ";
	std:: cout<< useless_time_2;
	std::cout << "\nв настоящий момент в первой очереди находятся ";
	std::cout << q_1_length;
	std::cout << " заявок";
	std::cout << "\nв настоящий момент во второй очереди находятся ";
	std::cout << q_2_length;
	std::cout << "\nмаксимальное время ожидания заявки в очередях ";
	std::cout << the_longest_time;
	std::cout << "\nномер заявки с максимальным временем ";
	std::cout << the_num;
	std::cout << "\nсреднее время ожидания заявки в очередях ";
	std::cout << average_time;
	
	std::cout << "\nполное время работы автомата 1 ";
	std::cout << all_time_1;	
	std::cout << "\n полное время работы автомата 2 ";
	std::cout << all_time_2;


}


void function(queue* q, application* tmp, int i) {
	//tmp[i].all_time = q->time + tmp[i].interval;
	//add_to_queue(q_1, tmp[i]);
	enqueue(q, tmp[i]);
}

application dequeue(queue* q) {
	application new_app;
	init_app(&new_app);
	if (q->head != NULL)
	{
		new_app = q->head->app;
		q->head = q->head->next;
	}

	if (q->head == NULL) 
	{
		q->tail = NULL;
	}
	
	return new_app;
}

int stack_is_empty(const stack* s)
{
	return !s->head;
}

int stack_push(stack* s, application val) {

	struct node* n = (node*)malloc(sizeof(struct node));
	if (!n) return -1;

	n->next = s->head;
	n->app = val;
	s->head = n;

	return 0;

}

application pop(stack* s) {
	application new_app;
	new_app.finished = 0;
	new_app.f_or_s = 0;
	new_app.interval = 0;
	new_app.time_2 = 0;
	new_app.time_3 = 0;
	if (s->head)
	{

		new_app = s->head->app; //написала какую-то хрень
		s->head = s->head->next;
	}
	return new_app;
}