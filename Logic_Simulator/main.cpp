#include <cstdio>
#include "full_adder.hpp"

int main() {
    Not_gate not_gate;
    Not_gate not2_gate;

    And_gate and_gate;
    And_gate and2_gate;
    And_gate and3_gate;
    And_gate and4_gate;

    Or_gate or_gate;
    Or_gate or2_gate;
    Or_gate or3_gate;
    Or_gate or4_gate;

    Xor_gate xor_gate;
    Xor_gate xor2_gate;
    Xor_gate xor3_gate;
    Xor_gate xor4_gate;

    Half_adder half_adder;
    Half_adder half2_adder;
    Half_adder half3_adder;
    Half_adder half4_adder;

    Full_adder full_adder;
    Full_adder full2_adder;
    Full_adder full3_adder;
    Full_adder full4_adder;
    Full_adder full5_adder;
    Full_adder full6_adder;
    Full_adder full7_adder;
    Full_adder full8_adder;

    not_gate.SetInput(0, 1);
    not2_gate.SetInput(0, 0);

    and_gate.SetInput(0, 1);
    and_gate.SetInput(1, 1);
    and2_gate.SetInput(0, 1);
    and2_gate.SetInput(1, 0);
    and3_gate.SetInput(0, 0);
    and3_gate.SetInput(1, 1);
    and4_gate.SetInput(0, 0);
    and4_gate.SetInput(1, 0);

    or_gate.SetInput(0, 1);
    or_gate.SetInput(1, 1);
    or2_gate.SetInput(0, 1);
    or2_gate.SetInput(1, 0);
    or3_gate.SetInput(0, 0);
    or3_gate.SetInput(1, 1);
    or4_gate.SetInput(0, 0);
    or4_gate.SetInput(1, 0);

    xor_gate.SetInput(0, 1);
    xor_gate.SetInput(1, 1);
    xor2_gate.SetInput(0, 1);
    xor2_gate.SetInput(1, 0);
    xor3_gate.SetInput(0, 0);
    xor3_gate.SetInput(1, 1);
    xor4_gate.SetInput(0, 0);
    xor4_gate.SetInput(1, 0);

    half_adder.SetInput(0, 1);
    half_adder.SetInput(1, 1);
    half2_adder.SetInput(0, 1);
    half2_adder.SetInput(1, 0);
    half3_adder.SetInput(0, 0);
    half3_adder.SetInput(1, 1);
    half4_adder.SetInput(0, 0);
    half4_adder.SetInput(1, 0);

    full_adder.SetInput(0, 1);
    full_adder.SetInput(1, 1);
    full_adder.SetInput(2, 1);

    full2_adder.SetInput(0, 1);
    full2_adder.SetInput(1, 0);
    full2_adder.SetInput(2, 0);

    full3_adder.SetInput(0, 0);
    full3_adder.SetInput(1, 1);
    full3_adder.SetInput(2, 0);

    full4_adder.SetInput(0, 0);
    full4_adder.SetInput(1, 0);
    full4_adder.SetInput(2, 1);

    full5_adder.SetInput(0, 1);
    full5_adder.SetInput(1, 1);
    full5_adder.SetInput(2, 0);

    full6_adder.SetInput(0, 0);
    full6_adder.SetInput(1, 1);
    full6_adder.SetInput(2, 1);

    full7_adder.SetInput(0, 1);
    full7_adder.SetInput(1, 0);
    full7_adder.SetInput(2, 1);

    full8_adder.SetInput(0, 0);
    full8_adder.SetInput(1, 0);
    full8_adder.SetInput(2, 0);

    printf("NOT GATE\n");
    printf("A | Q\n");
    printf("%d | %d\n", not_gate.GetInput(0), not_gate.GetOutput(0));
    printf("%d | %d\n", not2_gate.GetInput(0), not2_gate.GetOutput(0));
    printf("----------\n");
    printf("AND GATE \n");
    printf("A B | Q\n");
    printf("%d %d | %d\n", and_gate.GetInput(0), and_gate.GetInput(1), and_gate.GetOutput(0));
    printf("%d %d | %d\n", and2_gate.GetInput(0), and2_gate.GetInput(1), and2_gate.GetOutput(0));
    printf("%d %d | %d\n", and3_gate.GetInput(0), and3_gate.GetInput(1), and3_gate.GetOutput(0));
    printf("%d %d | %d\n", and4_gate.GetInput(0), and4_gate.GetInput(1), and4_gate.GetOutput(0));
    printf("----------\n");
    printf("OR GATE \n");
    printf("A B | Q\n");
    printf("%d %d | %d\n", or_gate.GetInput(0), or_gate.GetInput(1), or_gate.GetOutput(0));
    printf("%d %d | %d\n", or2_gate.GetInput(0), or2_gate.GetInput(1), or2_gate.GetOutput(0));
    printf("%d %d | %d\n", or3_gate.GetInput(0), or3_gate.GetInput(1), or3_gate.GetOutput(0));
    printf("%d %d | %d\n", or4_gate.GetInput(0), or4_gate.GetInput(1), or4_gate.GetOutput(0));
    printf("----------\n");
    printf("XOR GATE \n");
    printf("A B | Q\n");
    printf("%d %d | %d\n", xor_gate.GetInput(0), xor_gate.GetInput(1), xor_gate.GetOutput(0));
    printf("%d %d | %d\n", xor2_gate.GetInput(0), xor2_gate.GetInput(1), xor2_gate.GetOutput(0));
    printf("%d %d | %d\n", xor3_gate.GetInput(0), xor3_gate.GetInput(1), xor3_gate.GetOutput(0));
    printf("%d %d | %d\n", xor4_gate.GetInput(0), xor4_gate.GetInput(1), xor4_gate.GetOutput(0));
    printf("----------\n");
    printf("HALF ADDER\n");
    printf("A B | S C\n");
    printf("%d %d | %d %d\n", half_adder.GetInput(0), half_adder.GetInput(1), half_adder.GetOutput(0), half_adder.GetOutput(1));
    printf("%d %d | %d %d\n", half2_adder.GetInput(0), half2_adder.GetInput(1), half2_adder.GetOutput(0), half2_adder.GetOutput(1));
    printf("%d %d | %d %d\n", half3_adder.GetInput(0), half3_adder.GetInput(1), half3_adder.GetOutput(0), half3_adder.GetOutput(1));
    printf("%d %d | %d %d\n", half4_adder.GetInput(0), half4_adder.GetInput(1), half4_adder.GetOutput(0), half4_adder.GetOutput(1));
    printf("----------\n");
    printf("FULL ADDER\n");
    printf("A B C | S C\n");
    printf("%d %d %d | %d %d\n", full_adder.GetInput(0), full_adder.GetInput(1),full_adder.GetInput(2), full_adder.GetOutput(0), full_adder.GetOutput(1));
    printf("%d %d %d | %d %d\n", full2_adder.GetInput(0), full2_adder.GetInput(1),full2_adder.GetInput(2), full2_adder.GetOutput(0), full2_adder.GetOutput(1));
    printf("%d %d %d | %d %d\n", full3_adder.GetInput(0), full3_adder.GetInput(1),full3_adder.GetInput(2), full3_adder.GetOutput(0), full3_adder.GetOutput(1));
    printf("%d %d %d | %d %d\n", full4_adder.GetInput(0), full4_adder.GetInput(1),full4_adder.GetInput(2), full4_adder.GetOutput(0), full4_adder.GetOutput(1));
    printf("%d %d %d | %d %d\n", full5_adder.GetInput(0), full5_adder.GetInput(1),full5_adder.GetInput(2), full5_adder.GetOutput(0), full5_adder.GetOutput(1));
    printf("%d %d %d | %d %d\n", full6_adder.GetInput(0), full6_adder.GetInput(1),full6_adder.GetInput(2), full6_adder.GetOutput(0), full6_adder.GetOutput(1));
    printf("%d %d %d | %d %d\n", full7_adder.GetInput(0), full7_adder.GetInput(1),full7_adder.GetInput(2), full7_adder.GetOutput(0), full7_adder.GetOutput(1));
    printf("%d %d %d | %d %d\n", full8_adder.GetInput(0), full8_adder.GetInput(1),full8_adder.GetInput(2), full8_adder.GetOutput(0), full8_adder.GetOutput(1));


    return 0;
}