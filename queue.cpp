// queue.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <time.h>
#include <iostream>
#include <locale>
#include "Header.h"


int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    double time_of_array = 0;

    int n = 1000;
    double something;
    int var = 1;//переменная для счета входов в цикл с выводом информации

    queue* q_1 = (queue*)malloc(sizeof(queue));
    queue* q_2 = (queue*)malloc(sizeof(queue));
    queue* one_more = (queue*)malloc(sizeof(queue));

    int length_q_1=0;
    int length_q_2=0;
    int the_longest_app = 0;
    double time_of_empty_1 = 0;
    double time_of_empty_2 = 0;

    double max_time = 0;
    double average_time = 0;
    double max_time_work = 0;

        
    application cur_1;
    application cur_2;

    ao* ao_1 = (ao*)malloc(sizeof(ao));
    init_ao(ao_1, 1);
    //ao_1->finished = (application*)malloc(sizeof(application) * n);//создать фиктивную заявку с нулевыми параметрими, чтобы проверять на пустоту
    ao* ao_2 = (ao*)malloc(sizeof(ao));
    init_ao(ao_2, 2);

    init_queue(q_1);
    init_queue(q_2);

    int b1 = 0, b2 = 0, c1 = 0, c2 = 0, a1 = 0, a2 = 0;
    int first_done = 0;
   
    double useless_time_1 = 0;
    double useless_time_2 = 0;
    int num_of_done = 0;
    double random_interval;

    std::cout << "введите значеия b1, b2, c1, c2, a1, a2\n";
    std::cin >> b1;
    std::cin >> b2;
    std::cin >> c1;
    std::cin >> c2;
    std::cin >> a1;
    std::cin >> a2;

        
    application* tmp = (application*)malloc(sizeof(application)* n);
    application new_one;

    double random = 0;
    double time_work = 0;

    random_interval = (a2 - a1) * random + a1; //итервал, который будет считать вермя, когда закончаться заявки
    
    for (int i = 0; i < n; i++)
    {
        random = (double)rand() / RAND_MAX;
        init_app(&new_one);
        new_one.f_or_s = random;
        new_one.time_2 = (b2 - b1) * random + b1;
        new_one.time_3 = (c2 - c1) * random + c1;
        new_one.interval = (a2 - a1) * random + a1;
        new_one.finished = 0;
        new_one.num = i;
        tmp[i] = new_one;
    }

    int i = 0;

    while(num_of_done < n){

        if (i < n) {
            q_1->time += tmp[i].interval;
            q_2->time += tmp[i].interval;
            time_of_array += tmp[i].interval;


            while (first_done != 0 && ao_1->finished->head->app.time_of_dequeue_1 + ao_1->finished->head->app.time_2 > 
                q_2->time - tmp[i].interval && ao_1->finished->head->app.time_of_dequeue_1 + ao_1->finished->head->app.time_2 <= q_2->time)
            {
                //ao_2->useless += ao_1->finished->head->app.time_of_dequeue_1 + ao_1->finished->head->app.time_2 - (q_2->time - tmp[i].interval);

               something = ao_1->finished->head->app.time_of_dequeue_1 + ao_1->finished->head->app.time_2;
                cur_2 = dequeue(ao_1->finished);
                cur_2.time_of_enqueue_2 = something;
                enqueue(q_2, cur_2);
                length_q_2++;
                first_done--;
            }

            if (tmp[i].f_or_s > 0.4)
            {
                tmp[i].time_of_enqueue_1 = q_1->time;
                if (q_1->head = NULL) {
                    tmp[i].if_first = 1;
                }
                tmp[i].time_of_enqueue_1 = q_1->time;
                enqueue(q_1, tmp[i]);
                length_q_1++;

            }


            else if (tmp[i].f_or_s <= 0.4)
            {
                tmp[i].time_of_enqueue_2 = q_2->time;
                enqueue(q_2, tmp[i]);
                length_q_2++;
            }


            while (length_q_1 != 0 && q_1->time >= ao_1->time_work + ao_1->useless)
            {
                cur_1 = dequeue(q_1);
                cur_1.time_of_dequeue_1 = q_1->time;
                cur_1.useless_time += cur_1.time_of_dequeue_1 - cur_1.time_of_enqueue_1;
                ao_1->useless += q_1->time - (ao_1->time_work + ao_1->useless);
                process_application(ao_1, &cur_1);
                enqueue(ao_1->finished, cur_1);
                length_q_1--;
                first_done++;
            }

            if (length_q_1 != 0 && q_1->time < ao_1->time_work + ao_1->useless)
            {
                cur_1 = dequeue(q_1);
                cur_1.time_of_dequeue_1 = q_1->time;
                cur_1.useless_time += cur_1.time_of_dequeue_1 - cur_1.time_of_enqueue_1;
                cur_1.useless_time += (ao_1->time_work + ao_1->useless) - q_1->time;
                process_application(ao_1, &cur_1);
                enqueue(ao_1->finished, cur_1);
                length_q_1--;
                first_done++;
            }
            //else if (length_q_1 == 0)
            //{
            //    ao_1->useless += random_interval;
            //}

            while (length_q_2 != 0 && q_2->time >= ao_2->time_work + ao_2->useless)
            {
                cur_2 = dequeue(q_2);
                cur_2.time_of_dequeue_2 = q_2->time;
                cur_2.useless_time += cur_2.time_of_dequeue_2 - cur_2.time_of_enqueue_2;
                ao_2->useless += q_2->time - (ao_2->time_work + ao_2->useless);

                average_time += cur_2.useless_time;

                if (cur_2.useless_time > max_time)
                {
                    the_longest_app = cur_2.num;
                    max_time = cur_2.useless_time;
                }

                if (cur_2.useless_time > max_time_work) {
                    max_time_work = cur_2.useless_time;
                }

                process_application(ao_2, &cur_2);
                length_q_2--;
                num_of_done++;


                if (num_of_done % 100 == 0 && var == num_of_done / 100)
                {
                    write_info(num_of_done, ao_1->useless, ao_2->useless, length_q_1, length_q_2, the_longest_app, max_time, average_time / 100, ao_1->time_work + ao_1->useless, ao_2->time_work + ao_2->useless);
                    var++;
                    max_time = 0;
                    std::cout << "\n";
                    average_time = 0;
                }
            }

            if (length_q_2 != 0 && q_2->time < ao_2->time_work + ao_2->useless)
            {
                cur_2 = dequeue(q_2);
                cur_2.time_of_dequeue_2 = q_2->time;
                cur_2.useless_time += cur_2.time_of_dequeue_2 - cur_2.time_of_enqueue_2;
                cur_2.useless_time += ao_2->time_work + ao_2->useless - q_2->time;

                average_time += cur_2.useless_time;

                if (cur_2.useless_time > max_time) {
                    the_longest_app = cur_2.num;
                    max_time = cur_2.useless_time;
                }
                if (cur_2.useless_time > max_time_work) {
                    max_time_work = cur_2.useless_time;
                }

                process_application(ao_2, &cur_2);
                length_q_2--;
                num_of_done++;

                if (num_of_done % 100 == 0 && var == num_of_done / 100)
                {
                    write_info(num_of_done, ao_1->useless, ao_2->useless, length_q_1, length_q_2, the_longest_app, max_time, average_time /100, ao_1->time_work + ao_1->useless, ao_2->time_work + ao_2->useless);
                    var++;
                    max_time = 0;
                    std::cout << "\n";
                    average_time = 0;
                }
            }
            else if (length_q_2 == 0) {
                ao_2->useless += random_interval;
            }

            i++;
        }

        else //если обработанных заявок еще недостаточно, а в массиве они уже закончились 
        {
            q_1->time += random_interval;
            q_2->time += random_interval;
            time_of_array += random_interval;

            while (first_done != 0 && ao_1->finished->head->app.time_of_dequeue_1 + ao_1->finished->head->app.time_2 >
                q_2->time - random_interval && ao_1->finished->head->app.time_of_dequeue_1 + ao_1->finished->head->app.time_2 <= q_2->time)
            {
               // ao_2->useless += ao_1->finished->head->app.time_of_dequeue_1 + ao_1->finished->head->app.time_2 - (q_2->time - random_interval);

                something = ao_1->finished->head->app.time_of_dequeue_1 + ao_1->finished->head->app.time_2;
                cur_2 = dequeue(ao_1->finished);
                cur_2.time_of_enqueue_2 = something;
                enqueue(q_2, cur_2);
                length_q_2++;
                first_done--;
            }

            while (length_q_1 != 0 && q_1->time >= ao_1->time_work + ao_1->useless)
            {
                cur_1 = dequeue(q_1);
                cur_1.time_of_dequeue_1 = q_1->time;
                cur_1.useless_time += cur_1.time_of_dequeue_1 - cur_1.time_of_enqueue_1;
                ao_1->useless += q_1->time - (ao_1->time_work + ao_1->useless);
                process_application(ao_1, &cur_1);
                enqueue(ao_1->finished, cur_1);
                length_q_1--;
                first_done++;
            }

            if (length_q_1 != 0 && q_1->time < ao_1->time_work + ao_1->useless)
            {
                cur_1 = dequeue(q_1);
                cur_1.time_of_dequeue_1 = q_1->time;
                cur_1.useless_time += cur_1.time_of_dequeue_1 - cur_1.time_of_enqueue_1;
                cur_1.useless_time += (ao_1->time_work + ao_1->useless) - q_1->time;
                process_application(ao_1, &cur_1);
                enqueue(ao_1->finished, cur_1);
                length_q_1--;
                first_done++;
            }

            while (first_done != 0 && ao_1->finished->head->app.time_of_dequeue_1 + ao_1->finished->head->app.time_2 <= q_2->time)
            {
                cur_2 = dequeue(ao_1->finished);
                if (q_2->head == NULL) {
                    cur_2.if_first = 1;
                }
                cur_2.time_of_enqueue_2 = q_2->time;
                enqueue(q_2, cur_2);
                length_q_2++;
                first_done--;
            }
            while (length_q_2 != 0 && q_2->time >= ao_2->time_work + ao_2->useless)
            {
                cur_2 = dequeue(q_2);
                cur_2.time_of_dequeue_2 = q_2->time;
                ao_2->useless += q_2->time - (ao_2->time_work + ao_2->useless);
                cur_2.useless_time += cur_2.time_of_dequeue_2 - cur_2.time_of_enqueue_2;

                average_time += cur_2.useless_time;

                if (cur_2.useless_time > max_time)
                {
                    the_longest_app = cur_2.num;
                    max_time = cur_2.useless_time;
                }

                if (cur_2.useless_time > max_time_work) {
                    max_time_work = cur_2.useless_time;
                }

                process_application(ao_2, &cur_2);
                length_q_2--;
                num_of_done++;
                if (num_of_done % 100 == 0 && var == num_of_done / 100)
                {
                    write_info(num_of_done, ao_1->useless, ao_2->useless, length_q_1, length_q_2, the_longest_app, max_time, average_time / 100, ao_1->time_work + ao_1->useless, ao_2->time_work + ao_2->useless);
                    var++;
                    max_time = 0;
                    std::cout << "\n";
                    average_time = 0;
                }
            }

            if (length_q_2 != 0 && q_2->time < ao_2->time_work + ao_2->useless)
            {
                cur_2 = dequeue(q_2);
                cur_2.time_of_dequeue_2 = q_2->time;
                cur_2.useless_time += ao_2->time_work + ao_2->useless - q_2->time;
                cur_2.useless_time += cur_2.time_of_dequeue_2 - cur_2.time_of_enqueue_2;

                average_time += cur_2.useless_time;

                if (cur_2.useless_time > max_time) {
                    the_longest_app = cur_2.num;
                    max_time = cur_2.useless_time;
                }

                if (cur_2.useless_time > max_time_work) {
                    max_time_work = cur_2.useless_time;
                }

                process_application(ao_2, &cur_2);
                length_q_2--;
                num_of_done++;
                if (num_of_done % 100 == 0 && var == num_of_done / 100)
                {
                    write_info(num_of_done, ao_1->useless, ao_2->useless, length_q_1, length_q_2, the_longest_app, max_time, average_time / 100, ao_1->time_work + ao_1->useless, ao_2->time_work + ao_2->useless);
                    var++;
                    max_time = 0;
                    average_time = 0;

                    std::cout << "\n";
                }

                
            }

            else if (length_q_2 == 0)
            {
                ao_2->useless += random_interval;
            }
        }

        if (num_of_done == 1000) {
            std::cout << "\nмаксимальое время ожидания заявки в очередях за все время  ";
            std::cout << max_time_work;
            std::cout << "\nвремя очередей   ";
            std::cout << q_1->time<<"\n";
            std::cout <<q_2->time<<"\n";
            std::cout << ao_2->time_work;
        }
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
