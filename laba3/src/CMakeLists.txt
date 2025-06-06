add_executable(logic_minimizer
    main.cpp
    Lexer.cpp
    ShuntingYard.cpp
    Evaluator.cpp
    TruthTableGenerator.cpp
    NormalFormBuilder.cpp
    QuineMcCluskey.cpp
    Utils.cpp
)

# Убедимся, что бинарник сохраняется с правильным именем
set_target_properties(logic_minimizer PROPERTIES OUTPUT_NAME "logic_minimizer")
target_include_directories(logic_minimizer PRIVATE .)