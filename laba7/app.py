from main import DiagonalMemorySystem

def run_demo():
    # Исходные данные
    memory_data = [
        [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0],
        [1,1,0,1,1,0,0,0,1,1,1,1,0,0,0,0],
        [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [1,1,1,0,1,0,0,0,0,0,0,1,0,0,0,0],
        [0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0],
        [0,0,1,0,1,1,0,0,0,0,0,1,1,0,0,0],
        [0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0],
        [0,0,0,0,0,1,1,0,1,0,1,0,1,0,0,0],
        [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
        [1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1],
        [0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0],
        [0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0],
        [0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1],
        [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    ]

    dms = DiagonalMemorySystem()
    dms.load_memory(memory_data)

    print("=== Memory System Initialized ===")
    dms.show_memory()

    print("\n1) Memory Access Operations:")
    row2 = dms.get_memory_row(2)
    col3 = dms.get_memory_column(3)
    print(f"   Row 2:    {''.join(map(str, row2))}")
    print(f"   Column 3: {''.join(map(str, col3))}")

    print("\n2) Logical Operations on Row 2 and Row 3:")
    res_and = dms.perform_logic('conjunction', row2, dms.get_memory_row(3))
    res_or = dms.perform_logic('disjunction', row2, dms.get_memory_row(3))
    res_xor = dms.perform_logic('exclusive_or', row2, dms.get_memory_row(3))
    res_not = dms.perform_logic('negation', row2)
    print(f"   AND: {''.join(map(str, res_and))}")
    print(f"   OR:  {''.join(map(str, res_or))}")
    print(f"   XOR: {''.join(map(str, res_xor))}")
    print(f"   NOT: {''.join(map(str, res_not))}")

    dms.save_memory_row(15, res_and)
    print("\nAfter Storing AND Result in Row 15:")
    dms.show_memory()

    print("\n3) Arithmetic Operation for Pattern 111:")
    dms.calculate_addition([1,1,1])
    print("After Calculation:")
    dms.show_memory()
    print(f"Result Field: {''.join(map(str, dms.get_memory_row(0)[-5:]))}")

    dms.save_memory_row(5, dms.get_memory_row(2))
    dms.save_memory_row(14, dms.get_memory_row(2))
    print("\n4) Finding Adjacent Rows:")
    print(f"   Closest Above: {dms.find_adjacent(2, 'up')}")
    print(f"   Closest Below: {dms.find_adjacent(2, 'down')}")

if __name__ == "__main__":
    run_demo()