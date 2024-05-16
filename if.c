#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Quadruple
typedef struct {
    int line;
    char* op;
    char* arg1;
    char* arg2;
    char* result;
} Quadruple;

// Structure for Triple
typedef struct {
    int line;
    char* op;
    char* arg1;
    char* arg2;
} Triple;

// Structure for Indirect Triple
typedef struct {
    int line;
    char* op;
    char* arg1;
} IndirectTriple;

int labelIndex = 0;
int tempIndex = 0;

char* generateLabel() {
    char* label = (char*)malloc(10 * sizeof(char));
    sprintf(label, "L%d", labelIndex++);
    return label;
}

char* generateTemp() {
    char* temp = (char*)malloc(10 * sizeof(char));
    sprintf(temp, "t%d", tempIndex++);
    return temp;
}

void generateIfCode(char* condition, char* trueLabel, char* falseLabel, Quadruple* quadruples, int* quadIndex) {
    quadruples[*quadIndex].line = *quadIndex;
    quadruples[*quadIndex].op = "IF";
    quadruples[*quadIndex].arg1 = condition;
    quadruples[*quadIndex].arg2 = "";
    quadruples[*quadIndex].result = trueLabel;
    (*quadIndex)++;

    quadruples[*quadIndex].line = *quadIndex;
    quadruples[*quadIndex].op = "GOTO";
    quadruples[*quadIndex].arg1 = falseLabel;
    quadruples[*quadIndex].arg2 = "";
    quadruples[*quadIndex].result = "";
    (*quadIndex)++;
}

void generateWhileCode(char* condition, char* startLabel, char* endLabel, Quadruple* quadruples, int* quadIndex) {
    quadruples[*quadIndex].line = *quadIndex;
    quadruples[*quadIndex].op = "IF";
    quadruples[*quadIndex].arg1 = condition;
    quadruples[*quadIndex].arg2 = "";
    quadruples[*quadIndex].result = endLabel;
    (*quadIndex)++;

    quadruples[*quadIndex].line = *quadIndex;
    quadruples[*quadIndex].op = "GOTO";
    quadruples[*quadIndex].arg1 = endLabel;
    quadruples[*quadIndex].arg2 = "";
    quadruples[*quadIndex].result = "";
    (*quadIndex)++;
}

int main() {
    // Initialize structures
    Quadruple quadruples[20];
    Triple triples[20];
    IndirectTriple indirectTriples[20];

    // Initialize index counters
    int quadIndex = 0, tripleIndex = 0, indTripleIndex = 0;

    char* ifCondition = "x < y";
    char* ifTrueLabel = generateLabel();
    char* ifFalseLabel = generateLabel();
    generateIfCode(ifCondition, ifTrueLabel, ifFalseLabel, quadruples, &quadIndex);

    char* whileCondition = "i < 5";
    char* whileStartLabel = generateLabel();
    char* whileEndLabel = generateLabel();
    generateWhileCode(whileCondition, whileStartLabel, whileEndLabel, quadruples, &quadIndex);

    // Print Quadruples Table Header
    printf("Quadruples Table:\n");
    printf("| Line | Operation | Argument 1 | Argument 2 | Result |\n");
    printf("|------|-----------|------------|------------|--------|\n");

    // Print Quadruples
    for (int i = 0; i < quadIndex; i++) {
        printf("| %-4d | %-9s | %-10s | %-10s | %-6s |\n", quadruples[i].line, quadruples[i].op,
               quadruples[i].arg1, quadruples[i].arg2, quadruples[i].result);
    }

    // Print Triples Table Header
    printf("\nTriples Table:\n");
    printf("| Line | Operation | Argument 1 | Argument 2 |\n");
    printf("|------|-----------|------------|------------|\n");

    // Print Triples (Dummy data for illustration)
    triples[tripleIndex++] = (Triple){1, "IF", "x < y", ""};
    triples[tripleIndex++] = (Triple){2, "GOTO", "L1", ""};
    triples[tripleIndex++] = (Triple){3, "LABEL", "L1", ""};

    for (int i = 0; i < tripleIndex; i++) {
        printf("| %-4d | %-9s | %-10s | %-10s |\n", triples[i].line, triples[i].op,
               triples[i].arg1, triples[i].arg2);
    }

    // Print Indirect Triples Table Header
    printf("\nIndirect Triples Table:\n");
    printf("| Line | Operation | Argument 1 |\n");
    printf("|------|-----------|------------|\n");

    // Print Indirect Triples (Dummy data for illustration)
    indirectTriples[indTripleIndex++] = (IndirectTriple){1, "IF", "x < y"};
    indirectTriples[indTripleIndex++] = (IndirectTriple){2, "GOTO", "L1"};
    indirectTriples[indTripleIndex++] = (IndirectTriple){3, "LABEL", "L1"};

    for (int i = 0; i < indTripleIndex; i++) {
        printf("| %-4d | %-9s | %-10s |\n", indirectTriples[i].line, indirectTriples[i].op,
               indirectTriples[i].arg1);
    }

    free(ifTrueLabel);
    free(ifFalseLabel);
    free(whileStartLabel);
    free(whileEndLabel);

    return 0;
}
