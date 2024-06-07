#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur data untuk simpul karyawan
struct Employee {
    int employeeId;
    char name[100];
    char position[100];
    long long int salary;
    struct Employee* left;
    struct Employee* right;
    int height;  // Digunakan untuk AVL Tree
};

typedef struct Employee Employee;

// Struktur data untuk Binary Search Tree (BST)
struct BST {
    Employee* root;
};

typedef struct BST BST;

// Struktur data untuk AVL Tree
struct AVL {
    Employee* root;
};

typedef struct AVL AVL;

// Fungsi bantuan untuk membuat simpul karyawan baru
Employee* createEmployee(int employeeId, const char* name, const char* position, long long int salary) {
    Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
    if (newEmployee == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    newEmployee->employeeId = employeeId;
    strcpy(newEmployee->name, name);
    strcpy(newEmployee->position, position);
    newEmployee->salary = salary;
    newEmployee->left = NULL;
    newEmployee->right = NULL;
    newEmployee->height = 1;

    return newEmployee;
}

Employee* minValueNode(Employee* node) {
    Employee* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

Employee* removeNodeBST(Employee* root, int employeeId) {
    if (root == NULL) return root;

    if (employeeId < root->employeeId)
        root->left = removeNodeBST(root->left, employeeId);
    else if (employeeId > root->employeeId)
        root->right = removeNodeBST(root->right, employeeId);
    else {
        if (root->left == NULL) {
            Employee* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Employee* temp = root->left;
            free(root);
            return temp;
        }

        Employee* temp = minValueNode(root->right);

        root->employeeId = temp->employeeId;
        strcpy(root->name, temp->name);
        strcpy(root->position, temp->position);
        root->salary = temp->salary;

        root->right = removeNodeBST(root->right, temp->employeeId);
    }

    return root;
}

Employee* removeNodeAVL(Employee* root, int employeeId) {
        if (root == NULL) return root;

    if (employeeId < root->employeeId)
        root->left = removeNodeBST(root->left, employeeId);
    else if (employeeId > root->employeeId)
        root->right = removeNodeBST(root->right, employeeId);
    else {
        if (root->left == NULL) {
            Employee* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Employee* temp = root->left;
            free(root);
            return temp;
        }

        Employee* temp = minValueNode(root->right);

        root->employeeId = temp->employeeId;
        strcpy(root->name, temp->name);
        strcpy(root->position, temp->position);
        root->salary = temp->salary;

        root->right = removeNodeBST(root->right, temp->employeeId);
    }

    return root;
}

void inorderTraversalBST(Employee* root);
void inorderTraversalAVL(Employee* root);

Employee* searchBST(Employee* root, int employeeId) {
    if (root == NULL || root->employeeId == employeeId) {
        return root;
    }

    if (employeeId < root->employeeId) {
        return searchBST(root->left, employeeId);
    }

    return searchBST(root->right, employeeId);
}

Employee* searchAVL(Employee* root, int employeeId) {
    if (root == NULL || root->employeeId == employeeId) {
        return root;
    }

    if (employeeId < root->employeeId) {
        return searchBST(root->left, employeeId);
    }

    return searchBST(root->right, employeeId);
}

void displayData(Employee* node) {
    if (node != NULL) {
        printf("ID: %d, Nama: %s, Jabatan: %s, Gaji: %lld\n", node->employeeId, node->name, node->position, node->salary);
    }
}

void displayTree(Employee* root, const char* treeType) {
    printf("\nLihat %s:\n", treeType);
    inorderTraversalBST(root);
    
}


// Fungsi bantuan untuk mendapatkan tinggi dari simpul
int getHeight(Employee* node) {
    if (node == NULL) return 0;
    return node->height;
}

// Fungsi bantuan untuk menghitung keseimbangan simpul
int getBalance(Employee* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

double fmax(double x, double y);
int getHeight(Employee* node);

// Fungsi bantuan untuk melakukan rotasi kanan pada AVL Tree
Employee* rightRotate(Employee* y) {
    Employee* x = y->left;
    Employee* T = x->right;

    x->right = y;
    y->left = T;

    y->height = 1 + fmax(getHeight(y->left), getHeight(y->right));
    x->height = 1 + fmax(getHeight(x->left), getHeight(x->right));

    return x;
}

// Fungsi bantuan untuk melakukan rotasi kiri pada AVL Tree
Employee* leftRotate(Employee* x) {
    Employee* y = x->right;
    Employee* T = y->left;

    y->left = x;
    x->right = T;

    x->height = 1 + fmax(getHeight(x->left), getHeight(x->right));
    y->height = 1 + fmax(getHeight(y->left), getHeight(y->right));

    return y;
}

// Fungsi untuk menyisipkan simpul baru ke dalam BST
Employee* insertBST(Employee* node, int employeeId, const char* name, const char* position, long long int salary) {
    if (node == NULL) {
        return createEmployee(employeeId, name, position, salary);
    }

    if (employeeId < node->employeeId) {
        node->left = insertBST(node->left, employeeId, name, position, salary);
    } else if (employeeId > node->employeeId) {
        node->right = insertBST(node->right, employeeId, name, position, salary);
    } else {
        // Jika ada ID karyawan yang sama, tidak perlu disisipkan
        return node;
    }

    return node;
}

// Fungsi untuk menyisipkan simpul baru ke dalam AVL Tree
Employee* insertAVL(Employee* node, int employeeId, const char* name, const char* position, long long int salary) {
    if (node == NULL) {
        return createEmployee(employeeId, name, position, salary);
    }

    if (employeeId < node->employeeId) {
        node->left = insertAVL(node->left, employeeId, name, position, salary);
    } else if (employeeId > node->employeeId) {
        node->right = insertAVL(node->right, employeeId, name, position, salary);
    } else {
        // Jika ada ID karyawan yang sama, tidak perlu disisipkan
        return node;
    }

    node->height = 1 + fmax(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && employeeId < node->left->employeeId) {
        return rightRotate(node);
    }
    if (balance < -1 && employeeId > node->right->employeeId) {
        return leftRotate(node);
    }
    if (balance > 1 && employeeId > node->left->employeeId) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && employeeId < node->right->employeeId) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Fungsi untuk menyisipkan karyawan ke dalam BST
void insertDataBST(BST* bst, int employeeId, const char* name, const char* position, long long int salary) {
    bst->root = insertBST(bst->root, employeeId, name, position, salary);
    printf("Karyawan berhasil ditambahkan.\n");
}

// Fungsi untuk menyisipkan karyawan ke dalam AVL Tree
void insertDataAVL(AVL* avl, int employeeId, const char* name, const char* position, long long int salary) {
    avl->root = insertAVL(avl->root, employeeId, name, position, salary);
    printf("Karyawan berhasil ditambahkan.\n");
}

// (Fungsi-fungsi lain untuk operasi di dalam BST dan AVL Tree)

// Fungsi untuk menampilkan statistik gaji
void salaryStatistics(Employee* node, long long int* totalSalary, int* employeeCount, long long int* maxSalary, long long int* minSalary) {
    if (node != NULL) {
        salaryStatistics(node->left, totalSalary, employeeCount, maxSalary, minSalary);

        *totalSalary += node->salary;
        *employeeCount += 1;
        if (node->salary > *maxSalary) {
            *maxSalary = node->salary;
        }
        if (node->salary < *minSalary || *minSalary == 0) {
            *minSalary = node->salary;
        }

        salaryStatistics(node->right, totalSalary, employeeCount, maxSalary, minSalary);
    }
}

// Fungsi untuk menampilkan statistik gaji dari BST
void displaySalaryStatisticsBST(BST* bst) {
    long long int totalSalary = 0;
    int employeeCount = 0;
    long long int maxSalary = 0;
    long long int minSalary = 0;

    salaryStatistics(bst->root, &totalSalary, &employeeCount, &maxSalary, &minSalary);

    if (employeeCount > 0) {
        printf("Statistik Gaji:\n");
        printf("Gaji Rata-rata: %.2lf\n", (double)totalSalary / employeeCount);
        printf("Gaji Tertinggi: %lld\n", maxSalary);
        printf("Gaji Terendah: %lld\n", minSalary);
    } else {
        printf("Belum ada data karyawan.\n");
    }
}

// Fungsi untuk menampilkan statistik gaji dari AVL Tree
void displaySalaryStatisticsAVL(AVL* avl) {
    long long int totalSalary = 0;
    int employeeCount = 0;
    long long int maxSalary = 0;
    long long int minSalary = 0;

    salaryStatistics(avl->root, &totalSalary, &employeeCount, &maxSalary, &minSalary);

    if (employeeCount > 0) {
        printf("Statistik Gaji:\n");
        printf("Gaji Rata-rata: %lld\n", totalSalary / employeeCount);
        printf("Gaji Tertinggi: %lld\n", maxSalary);
        printf("Gaji Terendah: %lld\n", minSalary);
    } else {
        printf("Belum ada data karyawan.\n");
    }
}

// Fungsi untuk menulis data ke dalam file dari BST
void writeToFileBST(Employee* node, FILE* file) {
    if (node != NULL) {
        writeToFileBST(node->left, file);
        fprintf(file, "%d,%s,%s,%lld\n", node->employeeId, node->name, node->position, node->salary);
        writeToFileBST(node->right, file);
    }
}

// Fungsi untuk membaca data dari file dan memasukkannya ke dalam BST
void readFromFileBST(BST* bst, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("File opening failed");
        return;
    }

    int employeeId;
    char name[100], position[100];
    long long int salary;

    while (fscanf(file, "%d,%[^,],%[^,],%lld\n", &employeeId, name, position, &salary) == 4) {
        bst->root = insertBST(bst->root, employeeId, name, position, salary);
    }

    fclose(file);
}

// Fungsi untuk menulis data ke dalam file dari AVL Tree
void writeToFileAVL(Employee* node, FILE* file) {
    if (node != NULL) {
        writeToFileAVL(node->left, file);
        fprintf(file, "%d,%s,%s,%lld\n", node->employeeId, node->name, node->position, node->salary);
        writeToFileAVL(node->right, file);
    }
}

// Fungsi untuk membaca data dari file dan memasukkannya ke dalam AVL Tree
void readFromFileAVL(AVL* avl, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("File opening failed");
        return;
    }

    int employeeId;
    char name[100], position[100];
    long long int salary;

    while (fscanf(file, "%d,%[^,],%[^,],%lld\n", &employeeId, name, position, &salary) == 4) {
        avl->root = insertAVL(avl->root, employeeId, name, position, salary);
    }

    fclose(file);
}

void inorderTraversalBST(Employee* root) {
    if (root != NULL) {
        inorderTraversalBST(root->left);
        printf("ID: %d, Nama: %s, Jabatan: %s, Gaji: %lld\n", root->employeeId, root->name, root->position, root->salary);
        inorderTraversalBST(root->right);
    }
}

void inorderTraversalAVL(Employee* root) {
    if (root != NULL) {
        inorderTraversalAVL(root->left);
        printf("ID: %d, Nama: %s, Jabatan: %s, Gaji: %lld\n", root->employeeId, root->name, root->position, root->salary);
        inorderTraversalAVL(root->right);
    }
}
// (Fungsi-fungsi lain yang berkaitan dengan operasi di dalam BST dan AVL Tree)
double fmax(double x, double y);
// Fungsi utama
int main() {
    
    int treeType; // 1 untuk BST, 2 untuk AVL
    printf("Pilih jenis pohon:\n");
    printf("1. Binary Search Tree (BST)\n");
    printf("2. AVL Tree\n");
    printf("Pilihan (1 atau 2): ");
    scanf("%d", &treeType);

    BST bst;
    AVL avl;

        if (treeType == 1) {
        bst.root = NULL;
        readFromFileBST(&bst, "employee_data_bst.txt");
        displayTree(bst.root, "BST");
    } else if (treeType == 2) {
        avl.root = NULL;
        readFromFileAVL(&avl, "employee_data_avl.txt");
        displayTree(avl.root, "AVL Tree");
    } else {
        printf("Pilihan tidak valid. Program berhenti.\n");
        return 1;
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Tambah Karyawan\n");
        printf("2. Hapus Karyawan\n");
        printf("3. Cari Karyawan\n");
        printf("4. Lihat Pohon\n");
        printf("5. Statistik Gaji\n");
        printf("6. Simpan dan Keluar\n");
        printf("Pilih menu (1-6): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            {
                int employeeId;
                char name[100], position[100];
                long long int salary;

                printf("Masukkan ID Karyawan: ");
                scanf("%d", &employeeId);
                getchar(); // Membersihkan newline di buffer

                printf("Masukkan Nama: ");
                fgets(name, sizeof(name), stdin);
                strtok(name, "\n"); // Menghapus newline dari string

                printf("Masukkan Jabatan: ");
                fgets(position, sizeof(position), stdin);
                strtok(position, "\n");

                printf("Masukkan Gaji: ");
                scanf("%lld", &salary);

                if (treeType == 1) {
                    insertDataBST(&bst, employeeId, name, position, salary);
                } else if (treeType == 2) {
                    insertDataAVL(&avl, employeeId, name, position, salary);
                }

                break;
            }
        case 2:
            {
                int employeeId;
                printf("Masukkan ID Karyawan yang akan dihapus: ");
                scanf("%d", &employeeId);

                if (treeType == 1) {
                    bst.root = removeNodeBST(bst.root, employeeId);
                } else if (treeType == 2) {
                    avl.root = removeNodeAVL(avl.root, employeeId);
                }

                printf("Karyawan dengan ID %d berhasil dihapus.\n", employeeId);
                break;
            }
        case 3:
            {
                int employeeId;
                printf("Masukkan ID Karyawan yang akan dicari: ");
                scanf("%d", &employeeId);

                Employee* result;
                if (treeType == 1) {
                    result = searchBST(bst.root, employeeId);
                } else if (treeType == 2) {
                    result = searchAVL(avl.root, employeeId);
                }

                if (result != NULL) {
                    printf("Karyawan ditemukan - ID: %d, Nama: %s, Jabatan: %s, Gaji: %lld\n",
                           result->employeeId, result->name, result->position, result->salary);
                } else {
                    printf("Karyawan tidak ditemukan dengan ID: %d\n", employeeId);
                }
                break;
            }
          case 4:
            if (treeType == 1) {
                displayTree(bst.root, "BST");
            } else if (treeType == 2) {
                displayTree(avl.root, "AVL Tree");
                 break;
            }
            
        case 5:
            if (treeType == 1) {
                displaySalaryStatisticsBST(&bst);
            } else if (treeType == 2) {
                displaySalaryStatisticsAVL(&avl);
                 break;
            }
        case 6:
            printf("Menyimpan data...\n");
            if (treeType == 1) {
                // Menulis data ke dalam file sebelum keluar
                writeToFileBST(bst.root, fopen("employee_data_bst.txt", "w"));
                displayTree(bst.root, "BST");
            } else if (treeType == 2) {
                // Menulis data ke dalam file sebelum keluar
                writeToFileAVL(avl.root, fopen("employee_data_avl.txt", "w"));
                displayTree(avl.root, "AVL Tree");
            }
            printf("Data berhasil disimpan. Keluar dari program.\n");
            break;
        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }

    } while (choice != 6);

    return 0;
}
