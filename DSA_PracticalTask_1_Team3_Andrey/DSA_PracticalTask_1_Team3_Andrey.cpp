#include <conio.h>
#include <stdio.h>
#include <locale.h>
#include <windows.h>

struct list
{
   list(char _elem = 0, list *_next = NULL) : elem(_elem), next(_next) { }

   bool dupls = false;

   char elem;
   list *next;
};

void print(list *l);
void unique(list **l);
char input(const char *path, list *l);

int main()
{
   setlocale(0, "");

   list *S = new list();

   input("symbols.txt", S);
   unique(&S);
   print(S);

   return 0 * _getch();
}

char input(const char *path, list *l)
{
   FILE *stream = NULL;
   fopen_s(&stream, path, "r");

   if (stream)
   {
      char elem = 0;
      list *p = l, *pre = p;
      // Считываем все символы из файла.
      for ( ; fscanf_s(stream, "%c", &elem, 1) != EOF && p; )
      {
         bool isUnique = true;
         for (list *q = l; q && isUnique; q = q->next)
         {
            if (q->elem == elem)
            {
               q->dupls = true;
               isUnique = false;
            }
         }
         if (isUnique)
         {
            p->elem = elem;
            p->next = new list();
            pre = p;
            p = p->next;
         }
      }
      delete p;
      pre->next = NULL;

      fclose(stream);
      return 0;
   }
   else
   {
      perror("Завершение работы программы");
      return -1;
   }
}

void unique(list **l)
{
   for (list **p = l; *p; )
   {
      if ((*p)->dupls)
      {
         list *w = (*p)->next;
         delete *p;

         *p = w;
      }
      else p = &(*p)->next;
   }
}

void print(list *l)
{
   printf_s("Результат работы программы: \n");
 
   if (!l)
      printf_s("Уникальные элементы не были обнаружены.");
   else
      for (list *p = l; p; p = p->next)
         printf_s("%c", p->elem);
}