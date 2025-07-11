# Stage 1: Build with CMake
FROM gcc:12 AS builder

WORKDIR /app

COPY . .

RUN apt update && \
    apt install -y cmake libgtest-dev lcov python3

# Build main project
RUN mkdir -p build && cd build && \
    cmake .. && \
    make

# Build and run tests
RUN mkdir -p build_tests && cd build_tests && \
    cmake .. -DBUILD_TESTS=ON && \
    make && \
    cd .. && ./logic_tests && \
    cd build_tests && \
    lcov --capture --directory . --output-file coverage.info && \
    genhtml coverage.info --output-directory coverage_report

# Stage 2: Runtime image
FROM ubuntu:latest

WORKDIR /app

# Копируем оба бинарника и отчет
COPY --from=builder /app/logic_minimizer .
COPY --from=builder /app/logic_tests .
COPY --from=builder /app/build_tests/coverage_report ./coverage_report

RUN apt update && apt install -y python3
EXPOSE 8000

CMD bash -c "cd /app && nohup python3 -m http.server 8000 --directory coverage_report >/dev/null 2>&1 & ./logic_minimizer"