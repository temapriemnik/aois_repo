class DiagonalMemorySystem:
    def __init__(self, size=16):
        self.size = size
        self.storage = [[0] * size for _ in range(size)]

    def load_memory(self, data):
        if len(data) != self.size or any(len(row) != self.size for row in data):
            raise ValueError(f"Data must be {self.size}x{self.size} matrix")
        self.storage = [row.copy() for row in data]

    def get_memory_row(self, index):
        return [self.storage[(i + index) % self.size][index] for i in range(self.size)]

    def get_memory_column(self, index):
        return [self.get_memory_row(i)[index] for i in range(self.size)]

    def save_memory_row(self, index, data):
        if len(data) != self.size:
            raise ValueError(f"Data length must be {self.size}")
        for i in range(self.size):
            self.storage[(i + index) % self.size][index] = data[i]

    def perform_logic(self, operation, data1, data2=None):
        ops = {
            'conjunction': lambda a, b: a & b,
            'disjunction': lambda a, b: a | b,
            'exclusive_or': lambda a, b: a ^ b,
            'negation': lambda a, _: 1 - a
        }
        if operation not in ops:
            raise ValueError("Unknown operation")
        
        if operation == 'negation':
            return [ops[operation](bit, None) for bit in data1]
        return [ops[operation](a, b) for a, b in zip(data1, data2)]

    def find_adjacent(self, ref_index, search_direction='up'):
        target = self.get_memory_row(ref_index)
        result_index = -1
        min_diff = float('inf')

        for i in range(self.size):
            if i == ref_index:
                continue
            if self.get_memory_row(i) == target:
                diff = (i - ref_index) % self.size
                if search_direction == 'up':
                    if diff > (self.size // 2):
                        continue
                    if diff < min_diff:
                        min_diff = diff
                        result_index = i
                elif search_direction == 'down':
                    if diff <= (self.size // 2):
                        continue
                    adjusted_diff = self.size - diff
                    if adjusted_diff < min_diff:
                        min_diff = adjusted_diff
                        result_index = i

        return result_index

    def calculate_addition(self, pattern):
        for i in range(self.size):
            row = self.get_memory_row(i)
            if row[:3] == pattern:
                num_a = int(''.join(map(str, row[3:7])), 2)
                num_b = int(''.join(map(str, row[7:11])), 2)
                total = num_a + num_b
                result_bits = list(map(int, f"{total:05b}"))[-5:]

                bits_a = list(map(int, f"{num_a:04b}"))
                bits_b = list(map(int, f"{num_b:04b}"))
                new_row = row[:3] + bits_a + bits_b + result_bits
                self.save_memory_row(i, new_row)

    def show_memory(self, title="Memory Contents"):
        print(f"\n{title}:")
        for row in self.storage:
            print(' '.join(map(str, row)))