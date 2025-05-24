# Stage 1: Build with CMake
FROM gcc:12 AS builder

WORKDIR /app

# Копируем всё содержимое (включая CMakeLists.txt)
COPY . .

# Устанавливаем зависимости
RUN apt update && apt install -y cmake

# Собираем проект
RUN mkdir -p build && cd build && \
    cmake .. && \
    make

# Stage 2: Финальный образ
FROM ubuntu:latest

WORKDIR /app

# Копируем бинарник из сборки
COPY --from=builder /app/build/logic_minimizer /app/logic_minimizer

# Запускаем программу
CMD ["./logic_minimizer"]