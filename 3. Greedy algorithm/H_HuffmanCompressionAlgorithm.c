#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

char* content;

typedef struct Node {
    char alp;
    int count;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(char alp, int count) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->alp = alp;
    newNode->count = count;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void print(Node* root, char* code, int depth) {
    if (root->left == NULL && root->right == NULL) {
        code[depth] = '\0';
        printf("%c: %s\n", root->alp, code);
        return;
    }

    if (root->left != NULL) {
        code[depth] = '0';
        print(root->left, code, depth + 1);
    }
    if (root->right != NULL) {
        code[depth] = '1';
        print(root->right, code, depth + 1);
    }
}

void huffman_code() {
    int count[N] = { 0 }; // 0: A, 1: T, 2: G, 3: C

    // 사용 빈도 체크
    for (int i = 0; content[i] != '\0'; i++) {
        switch (content[i]) {
        case 'A': count[0]++; break;
        case 'T': count[1]++; break;
        case 'G': count[2]++; break;
        case 'C': count[3]++; break;
        }
    }

    printf("count:\n");
    for (int i = 0; i < N; i++) {
        char alp = "ATGC"[i];
        printf("%c: %d\n", alp, count[i]);
    }

    printf("\n");

    // 노드 생성
    Node* root = createNode('\0', 0);
    root->left = createNode('A', count[0]);
    root->right = createNode('\0', 0);
    root->right->left = createNode('\0', 0);
    root->right->right = createNode('C', count[3]);
    root->right->left->left = createNode('T', count[1]);
    root->right->left->right = createNode('G', count[2]);

    // Huffman code 출력
    char code[48];
    printf("Huffman code:\n");
    print(root, code, 0);

    printf("\n");

    // 입력
    char input[] = "10110010001110101010100";
    Node* current = root;
    printf("Result:\n");
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        // 현재 루트에서 하위 루트에 아무것도 없다면 (얘가 마지막이라면)
        if (current->left == NULL && current->right == NULL) {
            printf("%c", current->alp);
            current = root;
        }
    }
    printf("\n");
}

int main() {
    FILE* file;
    char filename[] = "Huffman_input.txt";
    int fileSize;

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("fopen 실패\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    rewind(file);

    content = (char*)malloc(sizeof(char) * (fileSize + 1));
    if (content == NULL) {
        fclose(file);
        return 1;
    }
    fread(content, sizeof(char), fileSize, file);
    content[fileSize] = '\0';

    huffman_code();

    free(content);
    fclose(file);

    return 0;
}