#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <getopt.h>

// Мьютекс для обеспечения безопасности доступа к глобальным данным
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

long long result = 1; // Результат факториала

// Структура для передачи параметров в поток
struct ThreadData {
    int start;         // Число для вычисления факториала
    int end;
    int thread_id;     // Идентификатор потока
};

void partial_factorial(void *args) {
  struct ThreadData *data = (struct ThreadData *)args;
  int start = data->start;
  int end = data->end;
  int thread_id = data->thread_id;

  long long partial_result = 1;

  for (int i = start; i <= end; i++) {
    partial_result = (partial_result * i);
  }

  pthread_mutex_lock(&mutex);
  result = (result * partial_result);
  pthread_mutex_unlock(&mutex);

  printf("pnum %d: %lld\n", thread_id, partial_result);

  pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
  int k = -1; // число, факториал которого необходимо вычислить
  int pnum = -1; // количество потоков
  int mod = -1; // модуль факториала

  while (1) {
    int option_index = 0;
    static struct option long_options[] = {
      {"k", required_argument, 0, 'k'},
      {"pnum", required_argument, 0, 'p'},
      {"mod", required_argument, 0, 'm'},
      {0, 0, 0, 0}};

    int c = getopt_long(argc, argv, "k:p:m:", long_options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 'k':
        sscanf(optarg, "%d", &k);
        break;
      case 'p':
        sscanf(optarg, "%d", &pnum);
        break;
      case 'm':
        sscanf(optarg, "%d", &mod);
        break;
      default:
        fprintf(stderr, "Usage: %s -k <number> --pnum=<threads> --mod=<modulus>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }

  if (k == -1 || pnum == -1 || mod == -1) {
    fprintf(stderr, "Usage: %s -k <number> --pnum=<threads> --mod=<modulus>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  pthread_t threads[pnum];
  struct ThreadData thread_data[pnum];


  int start_counter = 1;
  int end_counter = 1;

  int pnum_counter = pnum; // 4
  int k_counter = k; // 10

  for (int i = 0; i < pnum; i++) {
    end_counter = start_counter + k_counter / pnum_counter - 1;

    pnum_counter -= 1;
    k_counter -= (end_counter - start_counter + 1);

    thread_data[i].start = start_counter;
    thread_data[i].end = end_counter;
    thread_data[i].thread_id = i + 1;

    if (pthread_create(&threads[i], NULL, (void *(*)(void *))partial_factorial, (void *)&thread_data[i]) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    start_counter = end_counter + 1;
  }

  for (int i = 0; i < pnum; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("pthread_join");
      exit(EXIT_FAILURE);
    }
  }

  pthread_mutex_lock(&mutex);
  long long final_result = result % mod;
  pthread_mutex_unlock(&mutex);

  // Вывод факториала
  printf("factorial = %lld\n", result);
  
  // Вывод результата
  printf("%d! mod %d = %lld\n", k, mod, final_result);

  // Уничтожение мьютекса
  pthread_mutex_destroy(&mutex);
  
  return 0;
}