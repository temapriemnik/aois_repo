import unittest
from main import DiagonalMemorySystem

class TestMemorySystem(unittest.TestCase):
    def setUp(self):
        self.small_matrix = [
            [1,0,0,1],
            [0,1,1,0],
            [1,1,0,0],
            [0,0,1,1]
        ]
        self.dms_small = DiagonalMemorySystem(4)
        self.dms_small.load_memory(self.small_matrix)

    def test_memory_access(self):
        expected_row = [self.small_matrix[(i+1)%4][1] for i in range(4)]
        self.assertEqual(self.dms_small.get_memory_row(1), expected_row)

        diagonal_rows = [self.dms_small.get_memory_row(i) for i in range(4)]
        expected_col = [row[2] for row in diagonal_rows]
        self.assertEqual(self.dms_small.get_memory_column(2), expected_col)

    def test_memory_write(self):
        new_data = [1,1,1,1]
        self.dms_small.save_memory_row(3, new_data)
        self.assertEqual(self.dms_small.get_memory_row(3), new_data)

    def test_logic_operations(self):
        row0 = self.dms_small.get_memory_row(0)
        row1 = self.dms_small.get_memory_row(1)
        self.assertEqual(
            self.dms_small.perform_logic('conjunction', row0, row1),
            [a & b for a, b in zip(row0, row1)]
        )
        self.assertEqual(
            self.dms_small.perform_logic('negation', row0),
            [1 - a for a in row0]
        )

    def test_adjacent_search(self):
        self.dms_small.save_memory_row(2, self.dms_small.get_memory_row(0))
        self.assertEqual(self.dms_small.find_adjacent(0, 'down'), 2)

if __name__ == '__main__':
    unittest.main()