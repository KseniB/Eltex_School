## Чат с общей комнатой (POSIX)

Создать чат в связке клиент-сервер с межпроцессным взаимодействием очереди сообщений. Вывод всех сообщений на экран с указанием имени клиента.

---

## Makefile

make server_bin - Скомпилировать и выполнить бинарный файл сервера. Удалить бинарный файл по завершению программы;

make client_bin - Скомпилировать и выполнить бинарный файл клиента. Удалить бинарный файл по завершению программы;

make server_debug - Скомпилировать и выполнить файл сервера для отладки через gdb. Удалить бинарный файл по завершению программы;

make client_debug - Скомпилировать и выполнить файл клиента для отладки через gdb. Удалить бинарный файл по завершению программы;

make clean - Удалить скомпилированные бинарные файлы.
