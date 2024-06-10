#ifndef CALC_H
#define CALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* \brief структура для односвязного списка
 * @param priority приоритет оператора
 * @param op оператор
 * @param num число
 * @param is_num проверка число находится в структуре или оператор
 * @param next указатель на следующий элемент списка
 */
typedef struct Node Node;
struct Node {
  int priority;
  char op;
  double num;
  int is_num;
  struct Node *next;
};

/// \brief вывод односвязного списка
/// \param list указатель на последний элемент
void print(Node *list);

/// \brief добавляет узел в стек, куда записывается либо число либо оператор
/// \param plist указатель на последний элемент стека
/// \param n число
/// \param is_num проверка число находится в структуре или оператор
/// \param op оператор
void push(Node **plist, double n, int is_num, char op);

/// \brief проверка на то пуст ли стек
/// \param list указатель на последний элемент стека
int is_empty(Node *list);

/// \brief удаляет все элементы стека если они есть
/// \param plist указатель на последний элемент стека
void delete_stack(Node **plist);

/// \brief вытаскивает один узел из стека и записывает то что там было либо в
/// num либо в op \param plist указатель на последний элемент стека \param num
/// переменная для записи числа \param op переменна для записи оператора \return
/// ошибки: 0 - ошибок нет, 1 - стек уже пуст и взять из него элемент невозможно
int pop(Node **plist, double *num, char *op);

/// \brief проверка на то является ли аргумент числом
/// \param n символ
/// \return 1 - если символ является числои, 0 - если нет
int is_num(char n);

/// \brief определяет приоритет оператора
/// \param op оператор
/// \return приоритет (1/2/3/4) или -1 если оператор не определен
int define_priority(char op);

/// \brief все математические операции
/// \param num1 первый оперант
/// \param num2 второй оперант
/// \param op оператор
/// \param error флаг, отслеживающий ошибки
/// \return результат операции
double operations(double num1, double num2, char op, int *error);

/// \brief переворот стека
/// \param plist указатель на последний элемент стека
void reverse_stack(Node **plist);

/// \brief присваивает оператору нужый для стека символ и корректирует индекс
/// строки \param ch1 1 символ строки \param ch2 2 символ строки \param index
/// указатель на индекс элемента строки на которм сейчас находимся \return
/// символ оператора
char check_op(char ch1, char ch2, int *index);

/// \brief дополняет нотацию операторами из временного стека
/// \param notation указатель на последний элемент нотации
/// \param tmp указатель на последний элемент временного стека
/// \param er флаг, отслеживающий ошибки, в случае ошибки меняется на 1
void fill_notation(Node **notation, Node **tmp, int *er);

/// \brief подсчет ответа
/// \param notation указатель на последний элемент нотации
/// \param error флаг, отслеживающий ошибки, в случае ошибки меняется на 1
/// \return результат подсчета выражения
double calc_result(Node **notation, int *error);

/// \brief перевод строки в постфиксную нотацию с помощью стека, основанного на
/// односвязном списке \param notation указатель на последний элемент нотации
/// \param stack_tmp указатель на последний элемент временного стека
/// \param input указатель на первый слемент строки с выражением для подсчета
/// \param len длина строки
/// \param error флаг, отслеживающий ошибки, в случае ошибки меняется на 1
/// \param x заменяет х в строке
void convert_to_notation(Node **notation, Node **stack_tmp, char *input,
                         int len, int *error, double x);

/// \brief Проверка открытого файла: что существует и что не пуст
/// \param input указатель на первый слемент строки с выражением для подсчета
/// \param result результат подсчета
/// \param x заменяет х в строке
/// \return при возникновение любых ошибок во время вычисления возвращает 1 и в
/// рез ничего не записывается если ошибок не было, возвращает 0
int calc(char *input, double *result, double x);

/// \brief записывает все число в буферный массив в виде строки, а после
/// переводит в число записывает в num \param input указатель на первый слемент
/// строки с выражением для подсчета \param index указатель на индекс элемента
/// строки на которм сейчас находимся \param error флаг, отслеживающий ошибки, в
/// случае ошибки меняется на 1 \param num куда записывается число
void check_num(char *input, int *index, int *error, double *num);

/// \brief Проверка открытого файла: что существует и что не пуст
/// \param sum вся сумма кредита
/// \param months срок кредита в месяцах
/// \param rate процентная ставка по кредиту
/// \param monthly_max максимальная месячная выплата
/// \param monthly_min минимальная месячная выплата
/// \param percents переплаты по процентам
/// \param all вся сумма выплат
/// \param mode 1 - подсчет аннуитетного платежа, 2 - подсчет
/// дифференцированного платежа
void credit_calc(double sum, int months, double rate, double *monthly_max,
                 double *monthly_min, double *percents, double *all, int mode);

#endif
