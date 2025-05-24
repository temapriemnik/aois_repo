# Базовый образ с GCC и Python
FROM gcc:12 AS builder

WORKDIR /app

# Копируем все исходники
COPY . .

# Установка зависимостей
RUN apt update && \
    apt install -y cmake libgtest-dev lcov python3

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

# Не меняем образ — продолжаем использовать тот же
FROM builder

# Переключаемся в рабочую папку
WORKDIR /app

# Запускаем Python HTTP-сервер
EXPOSE 8000

CMD ["python3", "-m", "http.server", "8000"]