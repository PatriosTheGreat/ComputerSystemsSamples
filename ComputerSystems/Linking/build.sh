function single_line_build() {
    clang -Og -o prog main.c sum.c
}

function separate_build() {
    # Preprocessor
    cpp main.c /tmp/main.i

    # C-compiler
    cc /tmp/main.i -Og -o /tmp/main.s

    # Assembler
    as -o /tmp/main.o /tmp/main.s


    # Preprocessor
    cpp sum.c /tmp/sum.i

    # C-compiler
    cc /tmp/sum.i -Og -o /tmp/sum.s

    # Assembler
    as -o /tmp/sum.o /tmp/sum.s

    # Linker
    ld -o prog /tmp/main.o /tmp/sum.o
}

single_line_build