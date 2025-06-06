# Базовый образ с GCC
FROM gcc:12 AS builder

WORKDIR /app

# Копируем все исходники
COPY . .

# Установка зависимостей
RUN apt update && \
    apt install -y cmake libgtest-dev lcov python3

# Сборка основного исполняемого файла
RUN mkdir -p build && cd build && \
    cmake ../src && make main

# Сборка тестов
RUN mkdir -p tests/build && cd tests/build && \
    cmake .. && make

# Запуск тестов для генерации .gcda файлов
RUN cd tests/build && ./logic_tests

# Генерация отчёта о покрытии
RUN cd tests/build && \
    lcov --capture --directory /app --output-file coverage.info && \
    genhtml coverage.info --output-directory /app/coverage_report

# Проверяем, создан ли отчёт
RUN ls -la /app/coverage_report

# Используем тот же образ для финальной сборки
FROM gcc:12

# Переключаемся в рабочую папку
WORKDIR /app

# Копируем основной исполняемый файл, тесты и отчет из предыдущего этапа
COPY --from=builder /app/build/main .
COPY --from=builder /app/tests/build/logic_tests .
COPY --from=builder /app/coverage_report ./coverage_report

# Запускаем Python HTTP-сервер
EXPOSE 8000

CMD ["python3", "-m", "http.server", "8000"]